/******************************************************************************
 ** COPYRIGHT:           Rudi Bauer
 ** DESCRIPTION:    	 Fault Manager module.
 ** DATE CREATED:        25.12.2022
  ******************************************************************************/

/******************************************************************************
 *  COMPILER SWITCHES
 ******************************************************************************/

/******************************************************************************
  *   INCLUDE FILES
 ******************************************************************************/
#include "GlobalConfig.h"
#include "FaultManager.h"
#include "FaultManagerImport.h"

/******************************************************************************
 *   DEFINES AND MACROS
 ******************************************************************************/
// Fault states
typedef enum
{
	DEB_STATE_PASS,
	DEB_STATE_SYM,
	DEB_STATE_NO_SYM,
	DEB_STATE_FAIL_UNSAVED,
	DEB_STATE_FAIL_SAVED
}e_debounce_state_t;

/* Fault structure that is only visible internally - not exported */
typedef struct
{
  st_fault_t st_fault;
  uint8_t    deb_state;
  uint16_t   deb_cnt;
} st_fault_generic_t;


/******************************************************************************
 *   LOCAL VARIABLES AND CONSTANTS
 ******************************************************************************/
#if SAVE_FAULTS_IN_FM == TRUE
static st_fault_freeze_frame_t st_fault_freeze_frames[MAX_NUM_FREEZE_FRAMES_IN_RAM];
#endif
static uint8_t globalFaultCode = 0;
static st_fault_generic_t ast_fault_array[NUM_OF_FAULT_CODES];

/******************************************************************************
 *   EXPORTED VARIABLES AND CONSTANTS (AS EXTERN IN H-FILES)
 ******************************************************************************/

/******************************************************************************
*   PRIVATE FUNCTIONS
******************************************************************************/
/*-----------------------------------------------------------------------------
* Name           :   fault_init
* Parameters     :
* 		pst_ext_fault :	pointer to fault structure
* 		pst_ext_fault->e_fc:			fault code value (enum)
* 		pst_ext_fault->deb_inc:		debounce increment value for this fault code
* 		pst_ext_fault->deb_dec:		debounce decrement value for this fault code
* 		pst_ext_fault->deb_max:		debounce maximum value for this fault code
* 		Physical properties:
* 		pst_ext_fault=>e_fc				Phys: 0..e_fc_end; Off: -; Res: 1; Unit: -
* 		pst_ext_fault=>deb_inc		Phys: 0..65535; Off: -; Res: 1; Unit: -
* 		pst_ext_fault=>deb_dec		Phys: 0..65535; Off: -; Res: 1; Unit: -
* 		pst_ext_fault=>deb_max		Phys: 0..65535; Off: -; Res: 1; Unit: -
* Return code    :   none
* Description    :   Initialize the fault array with the fault structure parameter
* 					 With every new fn call for a fault, counter and state are reset
 -----------------------------------------------------------------------------*/
static void fault_init (st_fault_t* pst_ext_fault)
{
    e_fault_code_t e_fc = pst_ext_fault->e_fc;
    if(e_fc < e_fc_end)
    {
    	ast_fault_array[e_fc].st_fault        = *pst_ext_fault;
        ast_fault_array[e_fc].deb_cnt     = 0;
        ast_fault_array[e_fc].deb_state    = DEB_STATE_PASS;
    }
}

/*-----------------------------------------------------------------------------
* Name           :   fault_increment
* Parameters     :
* 	e_fc:			fault code value (enum)    	fault code
* 	Physical properties:
* 	e_fc			Phys: 0..e_fc_end; Off: -; Res: 1; Unit: -
* Return code    :   none
* Description    :   increment a fault counter, handle overflow
 -----------------------------------------------------------------------------*/
static void fault_increment (e_fault_code_t e_fc)
{
	st_fault_t st_Fault;
	st_Fault = ast_fault_array[e_fc].st_fault;

	// Prevent counter overflow
    if ( ( st_Fault.deb_max - ast_fault_array[e_fc].deb_cnt ) < st_Fault.deb_inc )
    {
    	ast_fault_array[e_fc].deb_cnt = st_Fault.deb_max;
    }
    // Increment fault counter
    else
    {
    	ast_fault_array[e_fc].deb_cnt += st_Fault.deb_inc;
    }
}

/*-----------------------------------------------------------------------------
* Name           :   fault_decrement
* Parameters     :
* 	e_fc:			fault code value (enum)    	fault code
* 	Physical properties:
* 	e_fc			Phys: 0..e_fc_end; Off: -; Res: 1; Unit: -
* Return code    :   none
* Description    :   decrement a fault counter, handle underflow
 -----------------------------------------------------------------------------*/
static void fault_decrement (e_fault_code_t e_fc)
{
	st_fault_t st_Fault;
	st_Fault = ast_fault_array[e_fc].st_fault;

	// Prevent counter underflow
    if (  st_Fault.deb_dec > ast_fault_array[e_fc].deb_cnt  )
    {
    	ast_fault_array[e_fc].deb_cnt = 0;
    }
    // Decrement fault counter
    else
    {
    	ast_fault_array[e_fc].deb_cnt -= st_Fault.deb_dec;
    }
}

#if SAVE_FAULTS_IN_FM == TRUE
/******************************************************************************
* Name           :   fault_collect_freeze_frame
* Parameters     :
* 	e_fc:			fault code value (enum)    	fault code
* 	Physical properties:
* 	e_fc				Phys: 0..e_fc_end; Off: -; Res: 1; Unit: -
* Return code    :   none
* Description    :   collect freeze data if the fault code is NOT 0.
******************************************************************************/
static void fault_collect_freeze_frame(e_fault_code_t e_fc)
{
    uint8_t  u8_i;
    bool b_exit = FALSE;

    // Check if fault that shall be stored in fault memory exists
    if ((uint8_t)ast_fault_array[e_fc].st_fault.e_fc < e_fc_end)
    {
        // Find a free freeze frame slot. Do no create double entries
        for(u8_i = 0; (u8_i < MAX_NUM_FREEZE_FRAMES_IN_RAM) && (!b_exit); u8_i++)
        {
            // Freeze frame already stored. Return and do nothing
            if (st_fault_freeze_frames[u8_i].e_fault_code == e_fc)
            {
                b_exit = TRUE;
            }
            // Store possible free space
            else if (st_fault_freeze_frames[u8_i].e_fault_code == e_fc_end)
            {
                    b_exit = TRUE;
                    // Collect freeze frame data
                    FaultMgrCollectFreezeFrameData(&st_fault_freeze_frames[u8_i], e_fc);
            }
        }
    }
}
#endif

#if SAVE_FAULTS_IN_FM == TRUE
/******************************************************************************
* Name           :   fault_clear_freeze_frame
* Parameters     :
* 	e_fc:			fault code value (enum)    	fault code
* 	Physical properties:
* 	e_fc				Phys: 0..e_fc_end; Off: -; Res: 1; Unit: -
* Return code    :   none
* Description    :   clear freeze data of the given fault
******************************************************************************/
static void fault_clear_freeze_frame(e_fault_code_t e_fc)
{
    uint8_t  u8_i;
    // Find a freeze frame slot assigned to fault.
    for(u8_i = 0; u8_i < MAX_NUM_FREEZE_FRAMES_IN_RAM; u8_i++)
    {
        // Freeze frame already stored. Return and do nothing
        if (st_fault_freeze_frames[u8_i].e_fault_code == (u8) e_fc)
        {
        	st_fault_freeze_frames[u8_i].e_fault_code = e_fc_end;
            break;
        }
    }
}
#endif

/******************************************************************************
  *   EXPORTED FUNCTIONS (AS EXTERN IN H-FILES)
 ******************************************************************************/
/*-----------------------------------------------------------------------------
 *  initialization
 -----------------------------------------------------------------------------*/
void FaultManagerInit()
{
	st_fault_t st_tmp_fault;
	/* configure fault parameters */
	/* Fault code 0 */
	st_tmp_fault.e_fc = e_fc_0;  // temperature read error
	st_tmp_fault.deb_dec = 3;
	st_tmp_fault.deb_inc = 1;
	st_tmp_fault.deb_max = 3;
	fault_init(&st_tmp_fault);
	/* Fault code 1 */
	st_tmp_fault.e_fc = e_fc_1;  // humidity read error
	st_tmp_fault.deb_dec = 1;
	st_tmp_fault.deb_inc = 1;
	st_tmp_fault.deb_max = 3;
	fault_init(&st_tmp_fault);
	/* Fault code 2 */
	st_tmp_fault.e_fc = e_fc_2;  // humidity index calculation error
	st_tmp_fault.deb_dec = 3;
	st_tmp_fault.deb_inc = 1;
	st_tmp_fault.deb_max = 3;
	fault_init(&st_tmp_fault);

    #if SAVE_FAULTS_IN_FM == TRUE
    uint8_t u8_i;
    for(u8_i = 0; u8_i < MAX_NUM_FREEZE_FRAMES_IN_RAM; u8_i++)
    {
    	st_fault_freeze_frames[u8_i].e_fault_code = e_fc_end;
    }
    #endif
}

/*-----------------------------------------------------------------------------
* Name           :  fault_reset
* Parameters     :
* 	e_fc:			fault code value (enum)    	fault code
* 	Physical properties:
* 	e_fc				Phys: 0..e_fc_end; Off: -; Res: 1; Unit: -
* Return code    :  none
* Description    :  reset fault counters and state
*                   and clear freeze frames for this fault
 -----------------------------------------------------------------------------*/
void fault_reset (e_fault_code_t e_fc)
{
	#if SAVE_FAULTS_IN_FM == TRUE
		fault_clear_freeze_frame(e_fc);
    #endif
    ast_fault_array[e_fc].deb_cnt     = 0;
    ast_fault_array[e_fc].deb_state    = DEB_STATE_PASS;
}

#if SAVE_FAULTS_IN_FM == TRUE
/******************************************************************************
* Name           :   fault_memory_write_proc
* Parameters     :   none
* Return code    :   none
* Description    :   writes one fault memory entry per call
******************************************************************************/
void fault_memory_write_proc(void)
{
    u8  u8_i;
    e_fault_code_t e_curr_fc;
    bool b_fault_saved = FALSE;

    // Go through all freeze frame slots, write one fault per call of this function
    for(u8_i = 0; (u8_i < MAX_NUM_FREEZE_FRAMES_IN_RAM) && (!b_fault_saved); u8_i++)
    {
    	e_curr_fc = st_fault_freeze_frames[u8_i].e_fault_code;
    	// Freeze frame already stored. Return and do nothing
        if (e_curr_fc < e_fc_end )
        {
            // Check if there is an unsaved fault
            if (ast_fault_array[e_curr_fc].deb_state == DEB_STATE_FAIL_UNSAVED)
            {
                // Store freeze frame data
                FaultMgrSaveFreezeFrame(&st_fault_freeze_frames[u8_i]);
                // Set state machine to saved
                ast_fault_array[e_curr_fc].deb_state = DEB_STATE_FAIL_SAVED;
                // Freeze frame is now not needed anymore
                fault_clear_freeze_frame(e_curr_fc);
                b_fault_saved = TRUE;
            }
            // If a freeze frame is stored in state PASS, the fault was healed just before this write process
            else if (ast_fault_array[e_curr_fc].deb_state == DEB_STATE_PASS)
            {
                // Store freeze frame data
                FaultMgrSaveFreezeFrame(&st_fault_freeze_frames[u8_i]);
                // Freeze frame is now not needed anymore
                fault_clear_freeze_frame(e_curr_fc);
                b_fault_saved = TRUE;
            }
        }
    }
}
#endif

#if SAVE_FAULTS_IN_FM == TRUE
/******************************************************************************
* Name           :   b_fault_memory_clear
* Parameters     :   none
* Return code    :   returns TRUE if FM clear is successful
*          			 Physical Properties:
*          			 b_fault_memory_clear => return  Phys: -;   Off: -; Res: -; Unit: -
* Description    :   clear the whole fault memory area
******************************************************************************/
bool b_fault_memory_clear(void)
{
    return FaultClear();
}
#endif

/*-----------------------------------------------------------------------------
* Name           :   FaultDebounce
* Parameters     :
* 	e_fc:			fault code value (enum)    	fault code
* 	b_symptom:      symptom (0: no symptom, 1: symptom)
* Return code    :  TRUE when fault is detected, FALSE when fault is not detected
*          			Physical Properties:
*          			FaultDebounce => return  Phys: -;   Off: -; Res: -; Unit: -
* Description    :  debounce symptoms
 -----------------------------------------------------------------------------*/
bool FaultDebounce(bool b_symptom, e_fault_code_t e_fc)
{
    bool b_retVal = FALSE;

    // Set fault state
    switch (ast_fault_array[e_fc].deb_state)
    {
        // Everything okay
        case DEB_STATE_PASS:
        {
            if (b_symptom == TRUE)
            {
                // Handle counters
                fault_increment(e_fc);

                //fault increment() ensures that u16_deb_cnt is not greater than u16_deb_max
                if (ast_fault_array[e_fc].deb_cnt == ast_fault_array[e_fc].st_fault.deb_max)
                {
                 	ast_fault_array[e_fc].deb_state = DEB_STATE_FAIL_UNSAVED;
                }
                else
                {
                    // Set symptom only
                 	ast_fault_array[e_fc].deb_state = DEB_STATE_SYM;
                }
				#if SAVE_FAULTS_IN_FM == TRUE
               	// Collect freeze frame data when symptom is set
               	fault_collect_freeze_frame(e_fc);
				#endif

            }
            break;
        }
        // Symptom detected -> handle fault counters
        case DEB_STATE_SYM:
        {
            // No symptom
            if (b_symptom == FALSE)
            {
                // Decrement debounce counter
                fault_decrement(e_fc);
                ast_fault_array[e_fc].deb_state = DEB_STATE_NO_SYM;
            }
            else
            {
                // Increment debounce counter
                fault_increment(e_fc);

				// Fault detected
                // u16_deb_cnt will always be less than or equal to u16_deb_max
				if (ast_fault_array[e_fc].deb_cnt == ast_fault_array[e_fc].st_fault.deb_max)
				{
					ast_fault_array[e_fc].deb_state = DEB_STATE_FAIL_UNSAVED;
					bitSet(globalFaultCode,e_fc);
				}
            }
            break;
        }
        // If Symptom vanished -> Decrement fault counter
        case DEB_STATE_NO_SYM:
        {
            // Symptom present again
            if (b_symptom == TRUE)
            {
                // Increment debounce counter
                fault_increment(e_fc);
                // Fault detected
                // u16_deb_cnt will always be less than or equal to u16_deb_max
				if (ast_fault_array[e_fc].deb_cnt == ast_fault_array[e_fc].st_fault.deb_max)
				{
					ast_fault_array[e_fc].deb_state = DEB_STATE_FAIL_UNSAVED;
					bitSet(globalFaultCode,e_fc);
				}
				else
				{
					ast_fault_array[e_fc].deb_state = DEB_STATE_SYM;
				}
            }
            else
            {
                // Decrement debounce counter
                fault_decrement(e_fc);
            }

            // Fault is cleared, delete freeze frame data
            if (ast_fault_array[e_fc].deb_cnt == 0)
            {
				#if SAVE_FAULTS_IN_FM == TRUE
               		fault_clear_freeze_frame(e_fc);
				#endif
                ast_fault_array[e_fc].deb_state = DEB_STATE_PASS;
            }

            break;
        }
        // Fail state -> saved and unsaved state require the same
        // handling in this state machine
        case DEB_STATE_FAIL_UNSAVED: //fallthrough
        case DEB_STATE_FAIL_SAVED:
        {
            if (b_symptom == FALSE)
            {
                // Decrement debounce counter
                fault_decrement(e_fc);
            }
            else
            {
                // Increment debounce counter
                fault_increment(e_fc);
				bitSet(globalFaultCode,e_fc);
            }

            if (ast_fault_array[e_fc].deb_cnt == 0) 
			{
				ast_fault_array[e_fc].deb_state = DEB_STATE_PASS;
				bitClear(globalFaultCode,e_fc);

			}
            break;
        }

		// Go to pass on undefined state
        default:  ast_fault_array[e_fc].deb_state = DEB_STATE_PASS;

    }

    // Return fail state
    if (      (ast_fault_array[e_fc].deb_state == DEB_STATE_FAIL_UNSAVED)
           || (ast_fault_array[e_fc].deb_state == DEB_STATE_FAIL_SAVED)     )
    {
        b_retVal = TRUE;
    }

    return b_retVal;
}

/*-----------------------------------------------------------------------------
 *  returns the error status of a single fault
 -----------------------------------------------------------------------------*/
bool GetFaultErrorStatus(e_fault_code_t e_fc)
{
    bool b_retVal = FALSE;

    if (      (ast_fault_array[e_fc].deb_state == DEB_STATE_FAIL_UNSAVED)
           || (ast_fault_array[e_fc].deb_state == DEB_STATE_FAIL_SAVED)     )
    {
        b_retVal = TRUE;
    }

    return b_retVal;
}

/*-----------------------------------------------------------------------------
 *  returns the debounce status of a single fault
 -----------------------------------------------------------------------------*/
uint8_t GetFaultDebounceStatus(e_fault_code_t e_fc)
{
    return ast_fault_array[e_fc].deb_state;
}

/*-----------------------------------------------------------------------------
 *  returns the debounce counter of a single fault
 -----------------------------------------------------------------------------*/
uint16_t GetFaultDebounceCount(e_fault_code_t e_fc)
{
    return ast_fault_array[e_fc].deb_cnt;
}

/*-----------------------------------------------------------------------------
 *  handle the errors
 -----------------------------------------------------------------------------*/
void FaultManager(uint8_t FC)
{
	if (FC == ERRCODE_FATAL)
	{
		#if (USE_SERIAL_DEBUG == TRUE)
		Log.fatalln("FM: !! Fatal error - cannot recover, giving up! ErrCode: %d", FC);
		Log.fatalln("FM: globalFaultCode: %X", globalFaultCode);
		Log.fatalln("FM: -|-");
        #endif
		while(1); // we give up and wait for a watchdog reset
	}
}

/*-----------------------------------------------------------------------------
 *  returns the global status
 -----------------------------------------------------------------------------*/
uint8_t GetGlobalFaultStatus(void)
{
	return globalFaultCode;
}

/*-----------------------------------------------------------------------------
 *  sets the error status
 -----------------------------------------------------------------------------*/
void SetGlobalFaultStatus(uint8_t FC)
{
	globalFaultCode = FC;
}

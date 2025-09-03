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

#include "Scheduler/Scheduler.h"
#include "HT/ht.h"

#include "FaultManager.h"
#include "FaultManagerImport.h"

/******************************************************************************
 *   DEFINES AND MACROS
 ******************************************************************************/

/******************************************************************************
 *   LOCAL VARIABLES AND CONSTANTS
 ******************************************************************************/

/******************************************************************************
 *   EXPORTED VARIABLES AND CONSTANTS (AS EXTERN IN H-FILES)
 ******************************************************************************/

/******************************************************************************
*   PRIVATE FUNCTIONS
******************************************************************************/

/******************************************************************************
  *   EXPORTED FUNCTIONS (AS EXTERN IN H-FILES)
 ******************************************************************************/
#if SAVE_FAULTS_IN_FM == TRUE
/******************************************************************************
* Name          :   FaultMgrCollectFreezeFrameData
* Parameters     :
* 		pst_freeze_frame: pointer to freeze frame
* 		e_fc: fault code
* 	Physical properties:
* 		pst_freeze_frame	Phys: -; Off: -; Res: 1; Unit: -
* 		e_fc			    Phys: 0..e_fc_end; Off: -; Res: 1; Unit: -
* Return code    :  none
* Description    :  Store freeze frame data container
******************************************************************************/
void FaultMgrCollectFreezeFrameData(st_fault_freeze_frame_t* pst_freeze_frame, e_fault_code_t e_fc)
{
	float local_var = 0;
	// Collect data for freeze frame
	pst_freeze_frame->e_fault_code = e_fc;
	/* PROJECT SPECIFIC - COLLECT DATA HERE */
	pst_freeze_frame->status_byte = 0; // example status byte
	pst_freeze_frame->system_counter = scd_get_system_time(); // example system time
	(void)HTgetTemperature(&local_var);
	pst_freeze_frame->temperature = (u16)local_var; // get temperature
	(void)HTgetHumidity(&local_var);
	pst_freeze_frame->humidity = (u16)local_var; // get humidity
	pst_freeze_frame->supply_voltage = 0; // get supply voltage in mV
}

/******************************************************************************
* Name          :   FaultMgrSaveFreezeFrame
* Parameter     :
* 		pst_freeze_frame: pointer to freeze frame
* 	Physical properties:
* 		pst_freeze_frame	Phys: -; Off: -; Res: 1; Unit: -
* Return code    :  none
* Description    :  Store freeze frame data to NVM if there is free space
******************************************************************************/
void FaultMgrSaveFreezeFrame(st_fault_freeze_frame_t* pst_freeze_frame)
{
    // Save freeze frame data to NVM
    // This is a placeholder implementation. Actual implementation will depend on the NVM library used.
    // For example, using a hypothetical NVM write function:
    // NVM_Write(ADDRESS, (uint8_t*)pst_freeze_frame, sizeof(st_fault_freeze_frame_t));
    (void)pst_freeze_frame; // To avoid unused parameter warning
}

/******************************************************************************
* Name          :   FaultClear
* Parameters     :  none
* Return code    :  FALSE in case of error
* Description    :  Project specific implementation of erasing the fault memory
******************************************************************************/
bool FaultClear(void)
{
    // Clear the fault memory in NVM
    // This is a placeholder implementation. Actual implementation will depend on the NVM library used.
    // For example, using a hypothetical NVM erase function:
    // return NVM_Erase(FAULT_MEMORY_ADDRESS, FAULT_MEMORY_SIZE);
    return true; // Assume success for placeholder
}
#endif

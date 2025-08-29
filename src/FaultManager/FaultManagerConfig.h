/******************************************************************************
** COPYRIGHT:           Rudi Bauer
** DESCRIPTION:         Config header file for Fault Manager module.
** DATE CREATED:        25.12.2022
******************************************************************************/

#ifndef FAULTMANAGERCONFIG_H
#define FAULTMANAGERCONFIG_H

/******************************************************************************
*   INCLUDE FILES
******************************************************************************/

/******************************************************************************
*   EXTERN DEFINES AND MACROS
******************************************************************************/

/******************************************************************************
*   TYPE DEFINITIONS
******************************************************************************/
typedef enum
{
	e_fc_0,
	e_fc_1,
	e_fc_2,
	e_fc_end,	 // DO NOT CHANGE this enum parameter - it is used in internal functions to count the total number of fault codes
}e_fault_code_t;

/* DEFINES for fault codes */
#define NUM_OF_FAULT_CODES                      3      // Total number of Fault Codes : must be equal to enum e_fc_end!!

/* optional defines */
#define FC_DHT_TEMP		e_fc_0
#define FC_DHT_HUM		e_fc_1
#define FC_DHT_HIDX		e_fc_2

/***********************************************************************************************
MANDATORY:   The parameter SAVE_FAULTS_IN_FM needs to be defined as TRUE/FALSE
			 Based on this parameter, other memory storage related paramters would be enabled.
************************************************************************************************/
#define SAVE_FAULTS_IN_FM					   TRUE  // Set as 'TRUE' if faults should be saved in FM after they have been detected

/*******************************************************************************
*  SETUP PROJECT SPECIFIC FREEZE FRAME & FAULT MEMORY BEHAVIOUR
******************************************************************************/
#if SAVE_FAULTS_IN_FM == TRUE
/* Definition of the Freeze Frame struct:
* - First member of the structure must be the fault code (type e_fault_code_t)
* - Other members are project specific
*/
typedef struct
{
	e_fault_code_t e_fault_code;    // Fault code - MANDATORY - do not change
	/* PROJECT SPECIFIC */
	uint8_t   status_byte;
    uint16_t  system_counter; 
	uint16_t  temperature;
	uint16_t  humidity;
	uint16_t  supply_voltage;
}st_fault_freeze_frame_t;

/* Note: Host needs to ensure the freeze frame struct size is correctly defined and memory alignment is considered */
#define FAULT_FREEZE_FRAME_SIZE                10 	// Struct size in BYTES
#define MAX_NUM_FREEZE_FRAMES_IN_RAM           2
#define MAX_RECORDS_PER_FC_IN_FM               2     // Maximum fault records per fault code in Fault Memory
#define MAX_NUM_RECORDS_IN_FM                  3     // Maximum allowed fault records  in Fault Memory

#endif

/*****************************************************************************
*                       COMPILER CHECKS                                     *
******************************************************************************/
#if (FAULT_FREEZE_FRAME_SIZE == 0) && (SAVE_FAULTS_IN_FM == TRUE)
  #error "Error: FAULT_FREEZE_FRAME_SIZE is defined as zero!"
#endif

#if (MAX_NUM_RECORDS_IN_FM < MAX_RECORDS_PER_FC_IN_FM) && (SAVE_FAULTS_IN_FM == TRUE)
  #error "Error: Records per fault code cannot be more than the max. number of allowed records in FM!"
#endif

/******************************************************************************
*   EXTERN VARIABLES AND CONSTANTS DECLARATIONS
******************************************************************************/

/******************************************************************************
*   EXTERN FUNCTION DECLARATIONS
******************************************************************************/

#endif /* FAULTMANAGERCONFIG_H */

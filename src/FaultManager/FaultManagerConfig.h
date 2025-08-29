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

/******************************************************************************
*   EXTERN VARIABLES AND CONSTANTS DECLARATIONS
******************************************************************************/

/******************************************************************************
*   EXTERN FUNCTION DECLARATIONS
******************************************************************************/

#endif /* FAULTMANAGERCONFIG_H */

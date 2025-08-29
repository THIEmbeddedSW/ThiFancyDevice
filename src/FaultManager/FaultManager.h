/******************************************************************************
** COPYRIGHT:           Rudi Bauer
** DESCRIPTION:         Export header file for Fault Manager module.
** DATE CREATED:        25.12.2022
******************************************************************************/

#ifndef FAULTMANAGER_H
#define FAULTMANAGER_H

/******************************************************************************
*   INCLUDE FILES
******************************************************************************/
#include "FaultManagerConfig.h"
/******************************************************************************
*   EXTERN DEFINES AND MACROS
******************************************************************************/
// Global Error Codes
#define ERRCODE_NONE			  0
#define ERRCODE_DHT_FAILED	1
#define ERRCODE_FATAL 			99


/******************************************************************************
*   TYPE DEFINITIONS
******************************************************************************/
/* Fault structure - defines the fault code and debounce timing */
/* deb_inc and deb_dec must be <= deb_max */
typedef struct
{
  e_fault_code_t e_fc;
  u16   deb_inc;
  u16   deb_dec;
  u16   deb_max;
} st_fault_t;

/******************************************************************************
*   EXTERN VARIABLES AND CONSTANTS DECLARATIONS
******************************************************************************/

/******************************************************************************
*   EXTERN FUNCTION DECLARATIONS
******************************************************************************/
extern void FaultManagerInit(void);

extern bool FaultDebounce(bool b_symptom, e_fault_code_t e_fc);    		// fault debouncing
extern uint8_t GetFaultDebounceStatus(e_fault_code_t e_fc);
extern uint16_t GetFaultDebounceCount(e_fault_code_t e_fc);
extern bool GetFaultErrorStatus(e_fault_code_t e_fc);

extern void FaultManager(uint8_t FC);
extern uint8_t GetGlobalFaultStatus(void);
extern void SetGlobalFaultStatus(uint8_t FC);

extern void fault_reset(e_fault_code_t e_fc);								// clear fault and erase fault entries in freeze frame

#endif /* FAULTMANAGER_H */

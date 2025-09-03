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
  uint16_t   deb_inc;
  uint16_t   deb_dec;
  uint16_t   deb_max;
} st_fault_t;

/******************************************************************************
*   EXTERN VARIABLES AND CONSTANTS DECLARATIONS
******************************************************************************/

/******************************************************************************
*   EXTERN FUNCTION DECLARATIONS
******************************************************************************/
extern void FaultManagerInit(void);
extern bool FaultDebounce(bool b_symptom, e_fault_code_t e_fc);    		// fault debouncing
extern void FaultManager(uint8_t FC);

extern uint8_t GetFaultDebounceStatus(e_fault_code_t e_fc);
extern uint16_t GetFaultDebounceCount(e_fault_code_t e_fc);
extern bool GetFaultErrorStatus(e_fault_code_t e_fc);

#if SAVE_FAULTS_IN_FM == TRUE
extern void fault_memory_write_proc(void);                //background process for writing fault record in FM
extern bool b_fault_memory_clear(void);										// clear fault memory
#endif

extern uint8_t GetGlobalFaultStatus(void);
extern void SetGlobalFaultStatus(uint8_t FC);

extern void fault_reset(e_fault_code_t e_fc);								// clear fault and erase fault entries in freeze frame

#endif /* FAULTMANAGER_H */

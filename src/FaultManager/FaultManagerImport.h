/******************************************************************************
** COPYRIGHT:           Rudi Bauer
** DESCRIPTION:         Import header file for generic scheduler.
** DATE CREATED:        25.12.2022
******************************************************************************/

#ifndef FAULT_MANAGER_IMPORT_H
#define FAULT_MANAGER_IMPORT_H

/******************************************************************************
*   INCLUDE FILES
******************************************************************************/
#include "FaultManagerConfig.h"

/******************************************************************************
*   EXTERN DEFINES AND MACROS
******************************************************************************/

/******************************************************************************
*   TYPE DEFINITIONS
******************************************************************************/

/******************************************************************************
*   EXTERN VARIABLES AND CONSTANTS DECLARATIONS
******************************************************************************/

/******************************************************************************
*   EXTERN FUNCTION DECLARATIONS
******************************************************************************/
#if SAVE_FAULTS_IN_FM == TRUE
	extern void FaultMgrCollectFreezeFrameData(st_fault_freeze_frame_t* pst_freeze_frame, e_fault_code_t e_fc);
	extern void FaultMgrSaveFreezeFrame(st_fault_freeze_frame_t* pst_freeze_frame);
	extern bool FaultClear(void);
#endif

#endif /* FAULT_MANAGER_IMPORT_H */

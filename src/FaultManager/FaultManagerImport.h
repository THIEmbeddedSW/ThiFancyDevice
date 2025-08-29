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
	extern void fault_collect_freeze_frame_data(st_fault_freeze_frame_t* pst_freeze_frame, e_fault_code_t e_fc);
	extern void fault_save(st_fault_freeze_frame_t* pst_freeze_frame);
	extern bool b_fault_clear(void);
#endif

#endif /* FAULT_MANAGER_IMPORT_H */

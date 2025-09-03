/******************************************************************************
** COPYRIGHT:           Rudi Bauer
** DESCRIPTION:         Export header file for generic scheduler.
** DATE CREATED:        25.12.2022
******************************************************************************/

#ifndef SCHEDULER_H
#define SCHEDULER_H

/******************************************************************************
*   INCLUDE FILES
******************************************************************************/
#include "SchedulerConfig.h"

/******************************************************************************
*   EXTERN DEFINES AND MACROS
******************************************************************************/
/* check whether we have low-prio tasks besides the background task;
 * if this is the case we will require some more variables; otherwise we
 * will suppress the variable definitions in order to avoid compiler warnings.
 */
#if (USE_LOW_PRIO_SCHEDULER==TRUE)
	#if (((USE_TASK_1==TRUE) && (TASK_1_PRIO==TASK_PRIO_LOW)) || \
		 ((USE_TASK_2==TRUE) && (TASK_2_PRIO==TASK_PRIO_LOW)) || \
		 ((USE_TASK_3==TRUE) && (TASK_3_PRIO==TASK_PRIO_LOW)) || \
		 ((USE_TASK_4==TRUE) && (TASK_4_PRIO==TASK_PRIO_LOW)) || \
		 ((USE_TASK_5==TRUE) && (TASK_5_PRIO==TASK_PRIO_LOW)) )
		#define LOW_PRIO_TASKS TRUE
	#else
		#define LOW_PRIO_TASKS FALSE
	#endif
#endif

/******************************************************************************
*   TYPE DEFINITIONS
******************************************************************************/
typedef struct
{
	bool b_bkg_task :1;
	bool b_task_1  	:1;
	bool b_task_2  	:1;
	bool b_task_3 	:1;
	bool b_task_4 	:1;
	bool b_task_5 	:1;
} bf8_suspend_tasks_t;

/******************************************************************************
*   EXTERN VARIABLES AND CONSTANTS DECLARATIONS
******************************************************************************/

/******************************************************************************
*   EXTERN FUNCTION DECLARATIONS
******************************************************************************/
extern void scd_init(void);

#if (USE_HIGH_PRIO_SCHEDULER==TRUE)
	extern void scd_high_prio_tasks(void);
#endif

#if (USE_LOW_PRIO_SCHEDULER==TRUE)
	extern void scd_low_prio_tasks(void);
	#if (LOW_PRIO_TASKS==TRUE)
		extern void scd_low_prio_counter(void);
	#endif
#endif

extern void scd_suspend_tasks(bf8_suspend_tasks_t bf8_suspend_tasks);

extern uint16_t scd_get_system_time(void);

extern uint16_t scd_time_passed(u16);

#endif /* SCHEDULER_H */

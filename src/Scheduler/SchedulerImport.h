/******************************************************************************
** COPYRIGHT:           Rudi Bauer
** DESCRIPTION:         Import header file for generic scheduler.
** DATE CREATED:        25.12.2022
******************************************************************************/

#ifndef SCHEDULER_IMPORT_H
#define SCHEDULER_IMPORT_H

/******************************************************************************
*   INCLUDE FILES
******************************************************************************/
#include "SchedulerConfig.h"

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

/* Function prototpyes for tasks; only those tasks or task slices, which are
 * configured in scheduler_config.h are activated. For these the function
 * prototype name is expanded to the name given in scheduler_config.h.
 * So if e.g. the host project configures in scheduler_config.h
 * 	   #define TASK_4  task_100ms,
 * then the function prototype will be expanded to
 * 	   extern void task_100ms(void);
 * and this task function has to be implemented by the host.
 */
#if (USE_TASK_1==TRUE)
	#if (TASK_1_CREATE_SLICES==TRUE)
		#ifdef TASK_1_SLICE_1
			extern void TASK_1_SLICE_1(void);
		#endif
		#ifdef TASK_1_SLICE_2
			extern void TASK_1_SLICE_2(void);
		#endif
		#ifdef TASK_1_SLICE_3
			extern void TASK_1_SLICE_3(void);
		#endif
		#ifdef TASK_1_SLICE_4
			extern void TASK_1_SLICE_4(void);
		#endif
		#ifdef TASK_1_SLICE_5
			extern void TASK_1_SLICE_5(void);
		#endif
		#ifdef TASK_1_SLICE_6
			extern void TASK_1_SLICE_6(void);
		#endif
		#ifdef TASK_1_SLICE_7
			extern void TASK_1_SLICE_7(void);
		#endif
		#ifdef TASK_1_SLICE_8
			extern void TASK_1_SLICE_8(void);
		#endif
		#ifdef TASK_1_SLICE_9
			extern void TASK_1_SLICE_9(void);
		#endif
		#ifdef TASK_1_SLICE_10
			extern void TASK_1_SLICE_10(void);
		#endif
	#else
		extern void TASK_1(void);
	#endif
#endif

#if (USE_TASK_2==TRUE)
	#if (TASK_2_CREATE_SLICES==TRUE)
		#ifdef TASK_2_SLICE_1
			extern void TASK_2_SLICE_1(void);
		#endif
		#ifdef TASK_2_SLICE_2
			extern void TASK_2_SLICE_2(void);
		#endif
		#ifdef TASK_2_SLICE_3
			extern void TASK_2_SLICE_3(void);
		#endif
		#ifdef TASK_2_SLICE_4
			extern void TASK_2_SLICE_4(void);
		#endif
		#ifdef TASK_2_SLICE_5
			extern void TASK_2_SLICE_5(void);
		#endif
		#ifdef TASK_2_SLICE_6
			extern void TASK_2_SLICE_6(void);
		#endif
		#ifdef TASK_2_SLICE_7
			extern void TASK_2_SLICE_7(void);
		#endif
		#ifdef TASK_2_SLICE_8
			extern void TASK_2_SLICE_8(void);
		#endif
		#ifdef TASK_2_SLICE_9
			extern void TASK_2_SLICE_9(void);
		#endif
		#ifdef TASK_2_SLICE_10
			extern void TASK_2_SLICE_10(void);
		#endif
	#else
		extern void TASK_2(void);
	#endif
#endif

#if (USE_TASK_3==TRUE)
	#if (TASK_3_CREATE_SLICES==TRUE)
		#ifdef TASK_3_SLICE_1
			extern void TASK_3_SLICE_1(void);
		#endif
		#ifdef TASK_3_SLICE_2
			extern void TASK_3_SLICE_2(void);
		#endif
		#ifdef TASK_3_SLICE_3
			extern void TASK_3_SLICE_3(void);
		#endif
		#ifdef TASK_3_SLICE_4
			extern void TASK_3_SLICE_4(void);
		#endif
		#ifdef TASK_3_SLICE_5
			extern void TASK_3_SLICE_5(void);
		#endif
		#ifdef TASK_3_SLICE_6
			extern void TASK_3_SLICE_6(void);
		#endif
		#ifdef TASK_3_SLICE_7
			extern void TASK_3_SLICE_7(void);
		#endif
		#ifdef TASK_3_SLICE_8
			extern void TASK_3_SLICE_8(void);
		#endif
		#ifdef TASK_3_SLICE_9
			extern void TASK_3_SLICE_9(void);
		#endif
		#ifdef TASK_3_SLICE_10
			extern void TASK_3_SLICE_10(void);
		#endif
	#else
		extern void TASK_3(void);
	#endif
#endif

#if (USE_TASK_4==TRUE)
	#if (TASK_4_CREATE_SLICES==TRUE)
		#ifdef TASK_4_SLICE_1
			extern void TASK_4_SLICE_1(void);
		#endif
		#ifdef TASK_4_SLICE_2
			extern void TASK_4_SLICE_2(void);
		#endif
		#ifdef TASK_4_SLICE_3
			extern void TASK_4_SLICE_3(void);
		#endif
		#ifdef TASK_4_SLICE_4
			extern void TASK_4_SLICE_4(void);
		#endif
		#ifdef TASK_4_SLICE_5
			extern void TASK_4_SLICE_5(void);
		#endif
		#ifdef TASK_4_SLICE_6
			extern void TASK_4_SLICE_6(void);
		#endif
		#ifdef TASK_4_SLICE_7
			extern void TASK_4_SLICE_7(void);
		#endif
		#ifdef TASK_4_SLICE_8
			extern void TASK_4_SLICE_8(void);
		#endif
		#ifdef TASK_4_SLICE_9
			extern void TASK_4_SLICE_9(void);
		#endif
		#ifdef TASK_4_SLICE_10
			extern void TASK_4_SLICE_10(void);
		#endif
	#else
		extern void TASK_4(void);
	#endif
#endif

#if (USE_TASK_5==TRUE)
	#if (TASK_5_CREATE_SLICES==TRUE)
		#ifdef TASK_5_SLICE_1
			extern void TASK_5_SLICE_1(void);
		#endif
		#ifdef TASK_5_SLICE_2
			extern void TASK_5_SLICE_2(void);
		#endif
		#ifdef TASK_5_SLICE_3
			extern void TASK_5_SLICE_3(void);
		#endif
		#ifdef TASK_5_SLICE_4
			extern void TASK_5_SLICE_4(void);
		#endif
		#ifdef TASK_5_SLICE_5
			extern void TASK_5_SLICE_5(void);
		#endif
		#ifdef TASK_5_SLICE_6
			extern void TASK_5_SLICE_6(void);
		#endif
		#ifdef TASK_5_SLICE_7
			extern void TASK_5_SLICE_7(void);
		#endif
		#ifdef TASK_5_SLICE_8
			extern void TASK_5_SLICE_8(void);
		#endif
		#ifdef TASK_5_SLICE_9
			extern void TASK_5_SLICE_9(void);
		#endif
		#ifdef TASK_5_SLICE_10
			extern void TASK_5_SLICE_10(void);
		#endif
	#else
		extern void TASK_5(void);
	#endif
#endif

/* We declare the runtime measurement import function only, if
 * any of the tasks enable the runtime measurement.
 */
#if ((TASK_1_ENABLE_RUNTIME_MEASUREMENT==TRUE) || \
	 (TASK_2_ENABLE_RUNTIME_MEASUREMENT==TRUE) || \
	 (TASK_3_ENABLE_RUNTIME_MEASUREMENT==TRUE) || \
	 (TASK_4_ENABLE_RUNTIME_MEASUREMENT==TRUE) || \
	 (TASK_5_ENABLE_RUNTIME_MEASUREMENT==TRUE) || \
	 (BKG_TASK_ENABLE_RUNTIME_MEASUREMENT==TRUE))
		/******************************************************************************
		* Name            :  task_runtime_measurement_on
		* Preconditions   :  runtime measurement enabled for at least one task
		* Parameters      :  u16_task : current task number
		*                 :  u16_slice: current slice number;
		*                               0 in case slices are not configured for this task.
		*	task_runtime_measurement_on => u16_task		Phys: 0..5; 	 Off: -; Res: 1; Unit: -
		*	task_runtime_measurement_on => u16_slice	Phys: 0..2^16-1; Off: -; Res: 1; Unit: -
		* Return code     :  none
		* Description     :  Launches the runtime measurement for the current task / slice.
		* 					 The implementation of the runtime measurement is on host side.
		******************************************************************************/
		extern void task_runtime_measurement_on(u16 u16_task, u16 u16_slice);

		/******************************************************************************
		* Name            :  task_runtime_measurement_off
		* Preconditions   :  runtime measurement enabled for at least one task
		* Parameters      :  u16_task : current task number
		*                 :  u16_slice: current slice number;
		*                               0 in case slices are not configured for this task.
		*	task_runtime_measurement_off => u16_task	Phys: 0..5; 	 Off: -; Res: 1; Unit: -
		*	task_runtime_measurement_off => u16_slice	Phys: 0..2^16-1; Off: -; Res: 1; Unit: -
		* Return code     :  none
		* Description     :  Finishes the runtime measurement for the current task / slice.
		* 					 The implementation of the runtime measurement is on host side.
		******************************************************************************/
		extern void task_runtime_measurement_off(u16 u16_task, u16 u16_slice);
#endif

/* We declare the overflow handler import function only, if
 * any of the tasks requests the monitoring.
 */
#if ((TASK_1_ENABLE_TASK_MONITOR==TRUE) || \
	 (TASK_2_ENABLE_TASK_MONITOR==TRUE) || \
	 (TASK_3_ENABLE_TASK_MONITOR==TRUE) || \
	 (TASK_4_ENABLE_TASK_MONITOR==TRUE) || \
	 (TASK_5_ENABLE_TASK_MONITOR==TRUE))
	/******************************************************************************
	* Name            :  task_overflow_handler
	* Preconditions   :  function is only called in case a task has overflown.
	* Parameters      :  u16_task : current task number
	*                 :  u16_slice: current slice number;
	*                               0 in case slices are not configured for this task.
	*	task_overflow_handler => u16_task		Phys: 0..5; 	 Off: -; Res: 1; Unit: -
	*	task_overflow_handler => u16_slice		Phys: 0..2^16-1; Off: -; Res: 1; Unit: -
	* Return code     :  none
	* Description     :  Reacts on the overflow of the current task / slice.
	* 					 The implementation of the overflow handling is on host side.
	******************************************************************************/
	extern void task_overflow_handler(u16 u16_task, u16 u16_slice);
#endif

/* We declare the background task import function only,
 * if the project wants to use it.
 */
#if ((USE_LOW_PRIO_SCHEDULER==TRUE) && (USE_LOW_PRIO_BACKGROUND_TASK==TRUE))
	/******************************************************************************
	* Name            :  background_task
	* Preconditions   :  usage of low prio scheduler and of background task is enabled.
	* Parameters      :  none
	* Return code     :  none
	* Description     :  Executes all background tasks of the host project.
	*  					 The implementation of the background task is on host side.
	******************************************************************************/
	extern void background_task(void);
#endif

#endif /* SCHEDULER_IMPORT_H */

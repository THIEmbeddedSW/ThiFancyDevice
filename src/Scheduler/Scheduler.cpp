/******************************************************************************
 ** COPYRIGHT:           Rudi Bauer
 ** DESCRIPTION:    	 Generic scheduler to create tasks and task-slices of 2 different priorities.
 ** DATE CREATED:        25.12.2022
  ******************************************************************************/

/******************************************************************************
 *  COMPILER SWITCHES
 ******************************************************************************/

/******************************************************************************
  *   INCLUDE FILES
 ******************************************************************************/
#include "GlobalConfig.h"

#include "SchedulerImport.h"
#include "Scheduler.h"

/******************************************************************************
 *   DEFINES AND MACROS
 ******************************************************************************/
/* --- Versioncheck --- */
#if ( SCHEDULER_CONFIG_VERSION != 0x1u )
#error "Error in scheduler.c: Config and component source file are inconsistent! \
        Please Checkout and merge!"
#endif

#define NUM_TASKS	5

/******************************************************************************
 *   LOCAL VARIABLES AND CONSTANTS
 ******************************************************************************/

// initialize the to 2 macros before finding tasks and slices:
#define HIGH_PRIO_SLICES FALSE
#define LOW_PRIO_SLICES FALSE

/****************************************
 * Create function pointers for this task
 ****************************************/
#if (USE_TASK_1==TRUE)
	#if ((TASK_1_PERIOD > 0xFFFFU) || (TASK_1_PERIOD == 0))
	   #error "A TASK_1_PERIOD greater than 65535 or 0 is not allowed!"
	#endif
	#if (TASK_1_CREATE_SLICES==TRUE)
		#if (TASK_1_PRIO==TASK_PRIO_HIGH)
			#undef  HIGH_PRIO_SLICES
			#define HIGH_PRIO_SLICES TRUE
		#else
			#undef  LOW_PRIO_SLICES
			#define LOW_PRIO_SLICES TRUE
		#endif
		static void (*ap_task_1[TASK_1_FACTOR])(void) =
		{
			#ifdef TASK_1_SLICE_1
			TASK_1_SLICE_1
			#else
			0
			#endif
			#if (TASK_1_FACTOR>1u)
				#ifdef TASK_1_SLICE_2
				,TASK_1_SLICE_2
				#else
				,0
				#endif
				#if TASK_1_FACTOR>2u
					#ifdef TASK_1_SLICE_3
					,TASK_1_SLICE_3
					#else
					,0
					#endif
					#if TASK_1_FACTOR>3u
						#ifdef TASK_1_SLICE_4
						,TASK_1_SLICE_4
						#else
						,0
						#endif
						#if TASK_1_FACTOR>4u
							#ifdef TASK_1_SLICE_5
							,TASK_1_SLICE_5
							#else
							,0
							#endif
							#if TASK_1_FACTOR>5u
								#ifdef TASK_1_SLICE_6
								,TASK_1_SLICE_6
								#else
								,0
								#endif
								#if TASK_1_FACTOR>6u
									#ifdef TASK_1_SLICE_7
									,TASK_1_SLICE_7
									#else
									,0
									#endif
									#if TASK_1_FACTOR>7u
										#ifdef TASK_1_SLICE_8
										,TASK_1_SLICE_8
										#else
										,0
										#endif
										#if TASK_1_FACTOR>8u
											#ifdef TASK_1_SLICE_9
											,TASK_1_SLICE_9
											#else
											,0
											#endif
											#if TASK_1_FACTOR>9u
												#ifdef TASK_1_SLICE_10
												,TASK_1_SLICE_10
												#else
												,0
												#endif
												#if TASK_1_FACTOR >10u
													#error "A TASK_1_FACTOR greater than 10 is not allowed"
												#endif
											#endif
										#endif
									#endif
								#endif
							#endif
						#endif
					#endif
				#endif
			#endif
        };
	#else // no task slices
		static void (*p_task_1)(void) = TASK_1;
	#endif
#endif

/****************************************
 * Create function pointers for this task
 ****************************************/
#if (USE_TASK_2==TRUE)
	#if ((TASK_2_PERIOD > 0xFFFFU) || (TASK_2_PERIOD == 0))
	   #error "A TASK_2_PERIOD greater than 65535 or 0 is not allowed!"
	#endif
	#if (TASK_2_CREATE_SLICES==TRUE)
		#if (TASK_2_PRIO==TASK_PRIO_HIGH)
			#undef  HIGH_PRIO_SLICES
			#define HIGH_PRIO_SLICES TRUE
		#else
			#undef  LOW_PRIO_SLICES
			#define LOW_PRIO_SLICES TRUE
		#endif
		static void (*ap_task_2[TASK_2_FACTOR])(void) =
		{
			#ifdef TASK_2_SLICE_1
			TASK_2_SLICE_1
			#else
			0
			#endif
			#if (TASK_2_FACTOR>1u)
				#ifdef TASK_2_SLICE_2
				,TASK_2_SLICE_2
				#else
				,0
				#endif
				#if TASK_2_FACTOR>2u
					#ifdef TASK_2_SLICE_3
					,TASK_2_SLICE_3
					#else
					,0
					#endif
					#if TASK_2_FACTOR>3u
						#ifdef TASK_2_SLICE_4
						,TASK_2_SLICE_4
						#else
						,0
						#endif
						#if TASK_2_FACTOR>4u
							#ifdef TASK_2_SLICE_5
							,TASK_2_SLICE_5
							#else
							,0
							#endif
							#if TASK_2_FACTOR>5u
								#ifdef TASK_2_SLICE_6
								,TASK_2_SLICE_6
								#else
								,0
								#endif
								#if TASK_2_FACTOR>6u
									#ifdef TASK_2_SLICE_7
									,TASK_2_SLICE_7
									#else
									,0
									#endif
									#if TASK_2_FACTOR>7u
										#ifdef TASK_2_SLICE_8
										,TASK_2_SLICE_8
										#else
										,0
										#endif
										#if TASK_2_FACTOR>8u
											#ifdef TASK_2_SLICE_9
											,TASK_2_SLICE_9
											#else
											,0
											#endif
											#if TASK_2_FACTOR>9u
												#ifdef TASK_2_SLICE_10
												,TASK_2_SLICE_10
												#else
												,0
												#endif
												#if TASK_2_FACTOR >10u
													#error "A TASK_2_FACTOR greater than 10 is not allowed"
												#endif
											#endif
										#endif
									#endif
								#endif
							#endif
						#endif
					#endif
				#endif
			#endif
        };
	#else // no task slices
		static void (*p_task_2)(void) = TASK_2;
	#endif
#endif

/****************************************
 * Create function pointers for this task
 ****************************************/
#if (USE_TASK_3==TRUE)
	#if ((TASK_3_PERIOD > 0xFFFFU) || (TASK_3_PERIOD == 0))
	   #error "A TASK_3_PERIOD greater than 65535 or 0 is not allowed!"
	#endif
	#if (TASK_3_CREATE_SLICES==TRUE)
		#if (TASK_3_PRIO==TASK_PRIO_HIGH)
			#undef  HIGH_PRIO_SLICES
			#define HIGH_PRIO_SLICES TRUE
		#else
			#undef  LOW_PRIO_SLICES
			#define LOW_PRIO_SLICES TRUE
		#endif
		static void (*ap_task_3[TASK_3_FACTOR])(void) =
		{
			#ifdef TASK_3_SLICE_1
			TASK_3_SLICE_1
			#else
			0
			#endif
			#if (TASK_3_FACTOR>1u)
				#ifdef TASK_3_SLICE_2
				,TASK_3_SLICE_2
				#else
				,0
				#endif
				#if TASK_3_FACTOR>2u
					#ifdef TASK_3_SLICE_3
					,TASK_3_SLICE_3
					#else
					,0
					#endif
					#if TASK_3_FACTOR>3u
						#ifdef TASK_3_SLICE_4
						,TASK_3_SLICE_4
						#else
						,0
						#endif
						#if TASK_3_FACTOR>4u
							#ifdef TASK_3_SLICE_5
							,TASK_3_SLICE_5
							#else
							,0
							#endif
							#if TASK_3_FACTOR>5u
								#ifdef TASK_3_SLICE_6
								,TASK_3_SLICE_6
								#else
								,0
								#endif
								#if TASK_3_FACTOR>6u
									#ifdef TASK_3_SLICE_7
									,TASK_3_SLICE_7
									#else
									,0
									#endif
									#if TASK_3_FACTOR>7u
										#ifdef TASK_3_SLICE_8
										,TASK_3_SLICE_8
										#else
										,0
										#endif
										#if TASK_3_FACTOR>8u
											#ifdef TASK_3_SLICE_9
											,TASK_3_SLICE_9
											#else
											,0
											#endif
											#if TASK_3_FACTOR>9u
												#ifdef TASK_3_SLICE_10
												,TASK_3_SLICE_10
												#else
												,0
												#endif
												#if TASK_3_FACTOR >10u
													#error "A TASK_3_FACTOR greater than 10 is not allowed"
												#endif
											#endif
										#endif
									#endif
								#endif
							#endif
						#endif
					#endif
				#endif
			#endif
        };
	#else // no task slices
		static void (*p_task_3)(void) = TASK_3;
	#endif
#endif

/****************************************
 * Create function pointers for this task
 ****************************************/
#if (USE_TASK_4==TRUE)
	#if ((TASK_4_PERIOD > 0xFFFFU) || (TASK_4_PERIOD == 0))
	   #error "A TASK_4_PERIOD greater than 65535 or 0 is not allowed!"
	#endif
	#if (TASK_4_CREATE_SLICES==TRUE)
		#if (TASK_4_PRIO==TASK_PRIO_HIGH)
			#undef  HIGH_PRIO_SLICES
			#define HIGH_PRIO_SLICES TRUE
		#else
			#undef  LOW_PRIO_SLICES
			#define LOW_PRIO_SLICES TRUE
		#endif
		static void (*ap_task_4[TASK_4_FACTOR])(void) =
		{
			#ifdef TASK_4_SLICE_1
			TASK_4_SLICE_1
			#else
			0
			#endif
			#if (TASK_4_FACTOR>1u)
				#ifdef TASK_4_SLICE_2
				,TASK_4_SLICE_2
				#else
				,0
				#endif
				#if TASK_4_FACTOR>2u
					#ifdef TASK_4_SLICE_3
					,TASK_4_SLICE_3
					#else
					,0
					#endif
					#if TASK_4_FACTOR>3u
						#ifdef TASK_4_SLICE_4
						,TASK_4_SLICE_4
						#else
						,0
						#endif
						#if TASK_4_FACTOR>4u
							#ifdef TASK_4_SLICE_5
							,TASK_4_SLICE_5
							#else
							,0
							#endif
							#if TASK_4_FACTOR>5u
								#ifdef TASK_4_SLICE_6
								,TASK_4_SLICE_6
								#else
								,0
								#endif
								#if TASK_4_FACTOR>6u
									#ifdef TASK_4_SLICE_7
									,TASK_4_SLICE_7
									#else
									,0
									#endif
									#if TASK_4_FACTOR>7u
										#ifdef TASK_4_SLICE_8
										,TASK_4_SLICE_8
										#else
										,0
										#endif
										#if TASK_4_FACTOR>8u
											#ifdef TASK_4_SLICE_9
											,TASK_4_SLICE_9
											#else
											,0
											#endif
											#if TASK_4_FACTOR>9u
												#ifdef TASK_4_SLICE_10
												,TASK_4_SLICE_10
												#else
												,0
												#endif
												#if TASK_4_FACTOR >10u
													#error "A TASK_4_FACTOR greater than 10 is not allowed"
												#endif
											#endif
										#endif
									#endif
								#endif
							#endif
						#endif
					#endif
				#endif
			#endif
        };
	#else // no task slices
		static void (*p_task_4)(void) = TASK_4;
	#endif
#endif

/****************************************
 * Create function pointers for this task
 ****************************************/
#if (USE_TASK_5==TRUE)
	#if ((TASK_5_PERIOD > 0xFFFFU) || (TASK_5_PERIOD == 0))
	   #error "A TASK_5_PERIOD greater than 65535 or 0 is not allowed!"
	#endif
	#if (TASK_5_CREATE_SLICES==TRUE)
		#if (TASK_5_PRIO==TASK_PRIO_HIGH)
			#undef  HIGH_PRIO_SLICES
			#define HIGH_PRIO_SLICES TRUE
		#else
			#undef  LOW_PRIO_SLICES
			#define LOW_PRIO_SLICES TRUE
		#endif
		static void (*ap_task_5[TASK_5_FACTOR])(void) =
		{
			#ifdef TASK_5_SLICE_1
			TASK_5_SLICE_1
			#else
			0
			#endif
			#if (TASK_5_FACTOR>1u)
				#ifdef TASK_5_SLICE_2
				,TASK_5_SLICE_2
				#else
				,0
				#endif
				#if TASK_5_FACTOR>2u
					#ifdef TASK_5_SLICE_3
					,TASK_5_SLICE_3
					#else
					,0
					#endif
					#if TASK_5_FACTOR>3u
						#ifdef TASK_5_SLICE_4
						,TASK_5_SLICE_4
						#else
						,0
						#endif
						#if TASK_5_FACTOR>4u
							#ifdef TASK_5_SLICE_5
							,TASK_5_SLICE_5
							#else
							,0
							#endif
							#if TASK_5_FACTOR>5u
								#ifdef TASK_5_SLICE_6
								,TASK_5_SLICE_6
								#else
								,0
								#endif
								#if TASK_5_FACTOR>6u
									#ifdef TASK_5_SLICE_7
									,TASK_5_SLICE_7
									#else
									,0
									#endif
									#if TASK_5_FACTOR>7u
										#ifdef TASK_5_SLICE_8
										,TASK_5_SLICE_8
										#else
										,0
										#endif
										#if TASK_5_FACTOR>8u
											#ifdef TASK_5_SLICE_9
											,TASK_5_SLICE_9
											#else
											,0
											#endif
											#if TASK_5_FACTOR>9u
												#ifdef TASK_5_SLICE_10
												,TASK_5_SLICE_10
												#else
												,0
												#endif
												#if TASK_5_FACTOR >10u
													#error "A TASK_5_FACTOR greater than 10 is not allowed"
												#endif
											#endif
										#endif
									#endif
								#endif
							#endif
						#endif
					#endif
				#endif
			#endif
        };
	#else // no task slices
		static void (*p_task_5)(void) = TASK_5;
	#endif
#endif

/****************************************
 * Determine max counter value
 ****************************************/
#if (USE_HIGH_PRIO_SCHEDULER==TRUE)
	static volatile u16 u16_scd_high_ctr;
	static u16 u16_scd_high_ctr_max;
#endif

#if (USE_LOW_PRIO_SCHEDULER==TRUE)
	 /* The following variables are only required,
	  * if we more low-prio tasks besides the background task.
	  */
	#if (LOW_PRIO_TASKS==TRUE)
		static volatile uint16_t u16_scd_low_ctr;
		static bool b_scd_low_ctr_changed;
		static uint16_t u16_scd_low_ctr_max;
	#endif
#endif

// some definitions for task monitoring
#if ((TASK_1_ENABLE_TASK_MONITOR==TRUE) || \
	 (TASK_2_ENABLE_TASK_MONITOR==TRUE) || \
	 (TASK_3_ENABLE_TASK_MONITOR==TRUE) || \
	 (TASK_4_ENABLE_TASK_MONITOR==TRUE) || \
	 (TASK_5_ENABLE_TASK_MONITOR==TRUE))
	static uint16_t u16_task_monitor_start_ctr[NUM_TASKS+1];
	static uint16_t u16_task_monitor_end_ctr[NUM_TASKS+1];
#endif

// Bitfield holding suspend flag for each task
static bf8_suspend_tasks_t bf8_suspend_tasks_local;

static uint16_t system_tick = 0;

/******************************************************************************
 *   EXPORTED VARIABLES AND CONSTANTS (AS EXTERN IN H-FILES)
 ******************************************************************************/

/******************************************************************************
*   PRIVATE FUNCTIONS
******************************************************************************/

/******************************************************************************
  *   EXPORTED FUNCTIONS (AS EXTERN IN H-FILES)
 ******************************************************************************/

/******************************************************************************
* Name            :  scd_init
* Preconditions   :  none
* Parameters      :  none
* Return code     :  none
* Description     :  Initialization of high- and low prio scheduler.
******************************************************************************/
void scd_init(void)
{
	#if (USE_HIGH_PRIO_SCHEDULER==TRUE)
		/* Determine max counter value */
		#if ((USE_TASK_1==TRUE) && (TASK_1_PRIO==TASK_PRIO_HIGH))
			if (u16_scd_high_ctr_max <= TASK_1_PERIOD) u16_scd_high_ctr_max = (TASK_1_PERIOD-1u);
		#endif
		#if ((USE_TASK_2==TRUE) && (TASK_2_PRIO==TASK_PRIO_HIGH))
			if (u16_scd_high_ctr_max <= TASK_2_PERIOD) u16_scd_high_ctr_max = (TASK_2_PERIOD-1u);
		#endif
		#if ((USE_TASK_3==TRUE) && (TASK_3_PRIO==TASK_PRIO_HIGH))
			if (u16_scd_high_ctr_max <= TASK_3_PERIOD) u16_scd_high_ctr_max = (TASK_3_PERIOD-1u);
		#endif
		#if ((USE_TASK_4==TRUE) && (TASK_4_PRIO==TASK_PRIO_HIGH))
			if (u16_scd_high_ctr_max <= TASK_4_PERIOD) u16_scd_high_ctr_max = (TASK_4_PERIOD-1u);
		#endif
		#if ((USE_TASK_5==TRUE) && (TASK_5_PRIO==TASK_PRIO_HIGH))
			if (u16_scd_high_ctr_max <= TASK_5_PERIOD) u16_scd_high_ctr_max = (TASK_5_PERIOD-1u);
		#endif
		/* initialize counter */
		u16_scd_high_ctr = 0;
	#endif

	#if (USE_LOW_PRIO_SCHEDULER==TRUE)
		/* Determine max counter value */
		#if ((USE_TASK_1==TRUE) && (TASK_1_PRIO==TASK_PRIO_LOW))
			if (u16_scd_low_ctr_max <= TASK_1_PERIOD) u16_scd_low_ctr_max = (TASK_1_PERIOD-1u);
		#endif
		#if ((USE_TASK_2==TRUE) && (TASK_2_PRIO==TASK_PRIO_LOW))
			if (u16_scd_low_ctr_max <= TASK_2_PERIOD) u16_scd_low_ctr_max = (TASK_2_PERIOD-1u);
		#endif
		#if ((USE_TASK_3==TRUE) && (TASK_3_PRIO==TASK_PRIO_LOW))
			if (u16_scd_low_ctr_max <= TASK_3_PERIOD) u16_scd_low_ctr_max = (TASK_3_PERIOD-1u);
		#endif
		#if ((USE_TASK_4==TRUE) && (TASK_4_PRIO==TASK_PRIO_LOW))
			if (u16_scd_low_ctr_max <= TASK_4_PERIOD) u16_scd_low_ctr_max = (TASK_4_PERIOD-1u);
		#endif
		#if ((USE_TASK_5==TRUE) && (TASK_5_PRIO==TASK_PRIO_LOW))
			if (u16_scd_low_ctr_max <= TASK_5_PERIOD) u16_scd_low_ctr_max = (TASK_5_PERIOD-1u);
		#endif
		#if (LOW_PRIO_TASKS==TRUE)
			/* initialize counter */
			u16_scd_low_ctr = u16_scd_low_ctr_max;
			b_scd_low_ctr_changed = FALSE;
		#endif
	#endif

	system_tick = 0;
}

/******************************************************************************
* Name            :  scd_suspend_tasks
* Preconditions   :  none
* Parameters      :
* scd_suspend_tasks => bf8_suspend_tasks->b_bkg_task		Phys: 0..1;  Off: 0; Res: 1; Unit: -
* scd_suspend_tasks => bf8_suspend_tasks->b_task_1			Phys: 0..1;  Off: 0; Res: 1; Unit: -
* scd_suspend_tasks => bf8_suspend_tasks->b_task_2			Phys: 0..1;  Off: 0; Res: 1; Unit: -
* scd_suspend_tasks => bf8_suspend_tasks->b_task_3			Phys: 0..1;  Off: 0; Res: 1; Unit: -
* scd_suspend_tasks => bf8_suspend_tasks->b_task_4			Phys: 0..1;  Off: 0; Res: 1; Unit: -
* scd_suspend_tasks => bf8_suspend_tasks->b_task_5			Phys: 0..1;  Off: 0; Res: 1; Unit: -
* Return code     :  none
* Description     :  Stores the suspend flags for each task. If flag is set, the corresponding
*                    task will not be scheduled any more in scd_high_prio_tasks() or
*                    scd_low_prio_tasks(). Resetting the flag will re-activate the task.
******************************************************************************/
void scd_suspend_tasks(bf8_suspend_tasks_t bf8_suspend_tasks)
{
	bf8_suspend_tasks_local = bf8_suspend_tasks;
}
/*****************************************************************************
 *                   HIGH PRIORITY SCHEDULER
 *****************************************************************************/

#if (USE_HIGH_PRIO_SCHEDULER==TRUE)
/******************************************************************************
* Name            :  scd_high_prio_tasks
* Preconditions   :  called in periodic timer interrupt
* Parameters      :  none
* Return code     :  none
* Description     :  Schedules all configured high-prio tasks, i.e.
* 						- check, whether task or task slice needs to be launched
* 						- if yes, launch the task by calling a corresponding function pointer
* 						- if enabled, monitor a potential task overflow
* 						- if enabled, call function for runtime measurement
******************************************************************************/
void scd_high_prio_tasks(void)
{
	#if (HIGH_PRIO_SLICES==TRUE)
		uint16_t u16_slice; // only needed, if we have slices
	#endif
	uint16_t u16_scd_local_ctr;

	// increment systm tick count
	system_tick++;

	// first copy the time counter to local variable
	u16_scd_local_ctr = u16_scd_high_ctr;

	/*********************
	 * Schedule this task
	 *********************/
	#if ((USE_TASK_1==TRUE) && (TASK_1_PRIO==TASK_PRIO_HIGH))
		#if (TASK_1_CREATE_SLICES==TRUE)
		// check whether we are in the time base of the task
		//lint -e587 It depends on the host configuration, whether predicate can be predetermined.
		if ((u16_scd_local_ctr % TASK_1_BASE == 0) && !bf8_suspend_tasks_local.b_task_1)
		{
			// find the matching task slice and launch it
			u16_slice = (u16_scd_local_ctr % TASK_1_PERIOD) / TASK_1_BASE;
			if (ap_task_1[u16_slice] != NULL_PTR)
			{
				#if (TASK_1_ENABLE_TASK_MONITOR==TRUE)
				u16_task_monitor_start_ctr[1] = u16_slice;
				#endif
				#if (TASK_1_ENABLE_RUNTIME_MEASUREMENT==TRUE)
				task_runtime_measurement_on(1u, (u16)(u16_slice+1u));
				#endif
				(*ap_task_1[u16_slice])();
				#if (TASK_1_ENABLE_RUNTIME_MEASUREMENT==TRUE)
				task_runtime_measurement_off(1u, (u16)(u16_slice+1u));
				#endif
				#if (TASK_1_ENABLE_TASK_MONITOR==TRUE)
				u16_task_monitor_end_ctr[1] = (u16_scd_high_ctr % TASK_1_PERIOD) / TASK_1_BASE;
				if (u16_task_monitor_start_ctr[1] != u16_task_monitor_end_ctr[1])
				{
					task_overflow_handler(1u, (u16)(u16_slice+1u));
				}
				#endif
			}
		}
		#else // no slices
		// launch the task, if timing matches
		//lint -e587 It depends on the host configuration, whether predicate can be predetermined.
		if ((u16_scd_local_ctr % TASK_1_PERIOD == 0) && !bf8_suspend_tasks_local.b_task_1)
		{
			#if (TASK_1_ENABLE_TASK_MONITOR==TRUE)
			u16_task_monitor_start_ctr[1] = (u16_scd_local_ctr / TASK_1_PERIOD);
			#endif
			#if (TASK_1_ENABLE_RUNTIME_MEASUREMENT==TRUE)
			task_runtime_measurement_on(1u, 0u);
			#endif
			(*p_task_1)();
			#if (TASK_1_ENABLE_RUNTIME_MEASUREMENT==TRUE)
			task_runtime_measurement_off(1u, 0u);
			#endif
			#if (TASK_1_ENABLE_TASK_MONITOR==TRUE)
			u16_task_monitor_end_ctr[1] = (u16_scd_high_ctr / TASK_1_PERIOD);
			if (u16_task_monitor_start_ctr[1] != u16_task_monitor_end_ctr[1])
			{
				task_overflow_handler(1u, 0u);
			}
			#endif
		}
		#endif
	#endif

	/*********************
	 * Schedule this task
	 *********************/
	#if ((USE_TASK_2==TRUE) && (TASK_2_PRIO==TASK_PRIO_HIGH))
		#if (TASK_2_CREATE_SLICES==TRUE)
		// check whether we are in the time base of the task
		//lint -e587 It depends on the host configuration, whether predicate can be predetermined.
		if ((u16_scd_local_ctr % TASK_2_BASE == 0) && !bf8_suspend_tasks_local.b_task_2)
		{
			// find the matching task slice and launch it
			u16_slice = (u16_scd_local_ctr % TASK_2_PERIOD) / TASK_2_BASE;
			if (ap_task_2[u16_slice] != NULL_PTR)
			{
				#if (TASK_2_ENABLE_TASK_MONITOR==TRUE)
				u16_task_monitor_start_ctr[2] = u16_slice;
				#endif
				#if (TASK_2_ENABLE_RUNTIME_MEASUREMENT==TRUE)
				task_runtime_measurement_on(2u, (u16)(u16_slice+1u));
				#endif
				(*ap_task_2[u16_slice])();
				#if (TASK_2_ENABLE_RUNTIME_MEASUREMENT==TRUE)
				task_runtime_measurement_off(2u, (u16)(u16_slice+1u));
				#endif
				#if (TASK_2_ENABLE_TASK_MONITOR==TRUE)
				u16_task_monitor_end_ctr[2] = (u16_scd_high_ctr % TASK_2_PERIOD) / TASK_2_BASE;
				if (u16_task_monitor_start_ctr[2] != u16_task_monitor_end_ctr[2])
				{
					task_overflow_handler(2u, (u16)(u16_slice+1u));
				}
				#endif
			}
		}
		#else // no slices
		// launch the task, if timing matches
		//lint -e587 It depends on the host configuration, whether predicate can be predetermined.
		if ((u16_scd_local_ctr % TASK_2_PERIOD == 0) && !bf8_suspend_tasks_local.b_task_2)
		{
			#if (TASK_2_ENABLE_TASK_MONITOR==TRUE)
			u16_task_monitor_start_ctr[2] = (u16_scd_local_ctr / TASK_2_PERIOD);
			#endif
			#if (TASK_2_ENABLE_RUNTIME_MEASUREMENT==TRUE)
			task_runtime_measurement_on(2u, 0u);
			#endif
			(*p_task_2)();
			#if (TASK_2_ENABLE_RUNTIME_MEASUREMENT==TRUE)
			task_runtime_measurement_off(2u, 0u);
			#endif
			#if (TASK_2_ENABLE_TASK_MONITOR==TRUE)
			u16_task_monitor_end_ctr[2] = (u16_scd_high_ctr / TASK_2_PERIOD);
			if (u16_task_monitor_start_ctr[2] != u16_task_monitor_end_ctr[2])
			{
				task_overflow_handler(2u, 0u);
			}
			#endif
		}
		#endif
	#endif

	/*********************
	 * Schedule this task
	 *********************/
	#if ((USE_TASK_3==TRUE) && (TASK_3_PRIO==TASK_PRIO_HIGH))
		#if (TASK_3_CREATE_SLICES==TRUE)
		// check whether we are in the time base of the task.
		//lint -e587 It depends on the host configuration, whether predicate can be predetermined.
		if ((u16_scd_local_ctr % TASK_3_BASE == 0) && !bf8_suspend_tasks_local.b_task_3)
		{
			// find the matching task slice and launch it
			u16_slice = (u16_scd_local_ctr % TASK_3_PERIOD) / TASK_3_BASE;
			if (ap_task_3[u16_slice] != NULL_PTR)
			{
				#if (TASK_3_ENABLE_TASK_MONITOR==TRUE)
				u16_task_monitor_start_ctr[3] = u16_slice;
				#endif
				#if (TASK_3_ENABLE_RUNTIME_MEASUREMENT==TRUE)
				task_runtime_measurement_on(3u, (u16)(u16_slice+1u));
				#endif
				(*ap_task_3[u16_slice])();
				#if (TASK_3_ENABLE_RUNTIME_MEASUREMENT==TRUE)
				task_runtime_measurement_off(3u, (u16)(u16_slice+1u));
				#endif
				#if (TASK_3_ENABLE_TASK_MONITOR==TRUE)
				u16_task_monitor_end_ctr[3] = (u16_scd_high_ctr % TASK_3_PERIOD) / TASK_3_BASE;
				if (u16_task_monitor_start_ctr[3] != u16_task_monitor_end_ctr[3])
				{
					task_overflow_handler(3u, (u16)(u16_slice+1u));
				}
				#endif
			}
		}
		#else // no slices
		// launch the task, if timing matches
		//lint -e587 It depends on the host configuration, whether predicate can be predetermined.
		if ((u16_scd_local_ctr % TASK_3_PERIOD == 0) && !bf8_suspend_tasks_local.b_task_3)
		{
			#if (TASK_3_ENABLE_TASK_MONITOR==TRUE)
			u16_task_monitor_start_ctr[3] = (u16_scd_local_ctr / TASK_3_PERIOD);
			#endif
			#if (TASK_3_ENABLE_RUNTIME_MEASUREMENT==TRUE)
			task_runtime_measurement_on(3u, 0u);
			#endif
			(*p_task_3)();
			#if (TASK_3_ENABLE_RUNTIME_MEASUREMENT==TRUE)
			task_runtime_measurement_off(3u, 0u);
			#endif
			#if (TASK_3_ENABLE_TASK_MONITOR==TRUE)
			u16_task_monitor_end_ctr[3] = (u16_scd_high_ctr / TASK_3_PERIOD);
			if (u16_task_monitor_start_ctr[3] != u16_task_monitor_end_ctr[3])
			{
				task_overflow_handler(3u, 0u);
			}
			#endif
		}
		#endif
	#endif

	/*********************
	 * Schedule this task
	 *********************/
	#if ((USE_TASK_4==TRUE) && (TASK_4_PRIO==TASK_PRIO_HIGH))
		#if (TASK_4_CREATE_SLICES==TRUE)
		// check whether we are in the time base of the task
		//lint -e587 It depends on the host configuration, whether predicate can be predetermined.
		if ((u16_scd_local_ctr % TASK_4_BASE == 0) && !bf8_suspend_tasks_local.b_task_4)
		{
			// find the matching task slice and launch it
			u16_slice = (u16_scd_local_ctr % TASK_4_PERIOD) / TASK_4_BASE;
			if (ap_task_4[u16_slice] != NULL_PTR)
			{
				#if (TASK_4_ENABLE_TASK_MONITOR==TRUE)
				u16_task_monitor_start_ctr[4] = u16_slice;
				#endif
				#if (TASK_4_ENABLE_RUNTIME_MEASUREMENT==TRUE)
				task_runtime_measurement_on(4u, (u16)(u16_slice+1u));
				#endif
				(*ap_task_4[u16_slice])();
				#if (TASK_4_ENABLE_RUNTIME_MEASUREMENT==TRUE)
				task_runtime_measurement_off(4u, (u16)(u16_slice+1u));
				#endif
				#if (TASK_4_ENABLE_TASK_MONITOR==TRUE)
				u16_task_monitor_end_ctr[4] = (u16_scd_high_ctr % TASK_4_PERIOD) / TASK_4_BASE;
				if (u16_task_monitor_start_ctr[4] != u16_task_monitor_end_ctr[4])
				{
					task_overflow_handler(4u, (u16)(u16_slice+1u));
				}
				#endif
			}
		}
		#else // no slices
		// launch the task, if timing matches
		//lint -e587 It depends on the host configuration, whether predicate can be predetermined.
		if ((u16_scd_local_ctr % TASK_4_PERIOD == 0) && !bf8_suspend_tasks_local.b_task_4)
		{
			#if (TASK_4_ENABLE_TASK_MONITOR==TRUE)
			u16_task_monitor_start_ctr[4] = (u16_scd_local_ctr / TASK_4_PERIOD);
			#endif
			#if (TASK_4_ENABLE_RUNTIME_MEASUREMENT==TRUE)
			task_runtime_measurement_on(4u, 0u);
			#endif
			(*p_task_4)();
			#if (TASK_4_ENABLE_RUNTIME_MEASUREMENT==TRUE)
			task_runtime_measurement_off(4u, 0u);
			#endif
			#if (TASK_4_ENABLE_TASK_MONITOR==TRUE)
			u16_task_monitor_end_ctr[4] = (u16_scd_high_ctr / TASK_4_PERIOD);
			if (u16_task_monitor_start_ctr[4] != u16_task_monitor_end_ctr[4])
			{
				task_overflow_handler(4u, 0u);
			}
			#endif
		}
		#endif
	#endif

	/*********************
	 * Schedule this task
	 *********************/
	#if ((USE_TASK_5==TRUE) && (TASK_5_PRIO==TASK_PRIO_HIGH))
		#if (TASK_5_CREATE_SLICES==TRUE)
		// check whether we are in the time base of the task
		//lint -e587 It depends on the host configuration, whether predicate can be predetermined.
		if ((u16_scd_local_ctr % TASK_5_BASE == 0) && !bf8_suspend_tasks_local.b_task_5)
		{
			// find the matching task slice and launch it
			u16_slice = (u16_scd_local_ctr % TASK_5_PERIOD) / TASK_5_BASE;
			if (ap_task_5[u16_slice] != NULL_PTR)
			{
				#if (TASK_5_ENABLE_TASK_MONITOR==TRUE)
				u16_task_monitor_start_ctr[5] = u16_slice;
				#endif
				#if (TASK_5_ENABLE_RUNTIME_MEASUREMENT==TRUE)
				task_runtime_measurement_on(5u, (u16)(u16_slice+1u));
				#endif
				(*ap_task_5[u16_slice])();
				#if (TASK_5_ENABLE_RUNTIME_MEASUREMENT==TRUE)
				task_runtime_measurement_off(5u, (u16)(u16_slice+1u));
				#endif
				#if (TASK_5_ENABLE_TASK_MONITOR==TRUE)
				u16_task_monitor_end_ctr[5] = (u16_scd_high_ctr % TASK_5_PERIOD) / TASK_5_BASE;
				if (u16_task_monitor_start_ctr[5] != u16_task_monitor_end_ctr[5])
				{
					task_overflow_handler(5u, (u16)(u16_slice+1u));
				}
				#endif
			}
		}
		#else // no slices
		// launch the task, if timing matches
		//lint -e587 It depends on the host configuration, whether predicate can be predetermined.
		if ((u16_scd_local_ctr % TASK_5_PERIOD == 0) && !bf8_suspend_tasks_local.b_task_5)
		{
			#if (TASK_5_ENABLE_TASK_MONITOR==TRUE)
			u16_task_monitor_start_ctr[5] = (u16_scd_high_ctr / TASK_5_PERIOD);
			#endif
			#if (TASK_5_ENABLE_RUNTIME_MEASUREMENT==TRUE)
			task_runtime_measurement_on(5u, 0u);
			#endif
			(*p_task_5)();
			#if (TASK_5_ENABLE_RUNTIME_MEASUREMENT==TRUE)
			task_runtime_measurement_off(5u, 0u);
			#endif
			#if (TASK_5_ENABLE_TASK_MONITOR==TRUE)
			u16_task_monitor_end_ctr[5] = (u16_scd_high_ctr / TASK_5_PERIOD);
			if (u16_task_monitor_start_ctr[5] != u16_task_monitor_end_ctr[5])
			{
				task_overflow_handler(5u, 0u);
			}
			#endif
		}
		#endif
	#endif

	// Manage task scheduler counter
	if (u16_scd_high_ctr < u16_scd_high_ctr_max)
	{
		u16_scd_high_ctr++;
	}
	else
	{
	  	u16_scd_high_ctr = 0u;
	}

}
#endif

/*****************************************************************************
 *                   LOW PRIORITY SCHEDULER
 *****************************************************************************/

/******************************************************************************
* Name            :  scd_low_prio_tasks
* Preconditions   :  scd_init() called before;
*                    scd_low_prio_tasks() called in endless loop of main
* Parameters      :  none
* Return code     :  none
* Description     :  Schedules all configured low-prio tasks and background task, i.e.
* 						- check, whether task or task slice needs to be launched
* 						- if yes, launch the task by calling a corresponding function pointer
* 						- if enabled, monitor a potential task overflow
* 						- if enabled, call function for runtime measurement
******************************************************************************/
#if (USE_LOW_PRIO_SCHEDULER==TRUE)
void scd_low_prio_tasks(void)
{
	/* check whether we have low-prio tasks; only then we will define the variables
	 * and perform the scheduling, in order to avoid compiler warnings.
	 */
	#if (LOW_PRIO_TASKS==TRUE)

	#if (LOW_PRIO_SLICES==TRUE)
		uint16_t u16_slice; // only required if we have slices
	#endif
	uint16_t u16_scd_local_ctr;

	// we only schedule, if the counter changed
	if (b_scd_low_ctr_changed)
	{
		// first copy the time counter to local variable
		u16_scd_local_ctr = u16_scd_low_ctr;
		/*********************
		 * Schedule this task
		 *********************/
		#if ((USE_TASK_1==TRUE) && (TASK_1_PRIO==TASK_PRIO_LOW))
			#if (TASK_1_CREATE_SLICES==TRUE)
			// check whether we are in the time base of the task
			//lint -e587 It depends on the host configuration, whether predicate can be predetermined.
			if ((u16_scd_local_ctr % TASK_1_BASE == 0) && !bf8_suspend_tasks_local.b_task_1)
			{
				// find the matching task slice and launch it
				u16_slice = (u16_scd_local_ctr % TASK_1_PERIOD) / TASK_1_BASE;
				if (ap_task_1[u16_slice] != NULL_PTR)
				{
					#if (TASK_1_ENABLE_TASK_MONITOR==TRUE)
					u16_task_monitor_start_ctr[1] = u16_slice;
					#endif
					#if (TASK_1_ENABLE_RUNTIME_MEASUREMENT==TRUE)
					task_runtime_measurement_on(1u, (u16)(u16_slice+1u));
					#endif
					(*ap_task_1[u16_slice])();
					#if (TASK_1_ENABLE_RUNTIME_MEASUREMENT==TRUE)
					task_runtime_measurement_off(1u, (u16)(u16_slice+1u));
					#endif
					#if (TASK_1_ENABLE_TASK_MONITOR==TRUE)
					u16_task_monitor_end_ctr[1] = (u16_scd_low_ctr % TASK_1_PERIOD) / TASK_1_BASE;
					if (u16_task_monitor_start_ctr[1] != u16_task_monitor_end_ctr[1])
					{
						task_overflow_handler(1u, (u16)(u16_slice+1u));
					}
					#endif
				}
			}
			#else // no slices
			// launch the task, if timing matches
			//lint -e587 It depends on the host configuration, whether predicate can be predetermined.
			if ((u16_scd_local_ctr % TASK_1_PERIOD == 0) && !bf8_suspend_tasks_local.b_task_1)
			{
				#if (TASK_1_ENABLE_TASK_MONITOR==TRUE)
				u16_task_monitor_start_ctr[1] = (u16_scd_local_ctr / TASK_1_PERIOD);
				#endif
				#if (TASK_1_ENABLE_RUNTIME_MEASUREMENT==TRUE)
				task_runtime_measurement_on(1u, 0u);
				#endif
				(*p_task_1)();
				#if (TASK_1_ENABLE_RUNTIME_MEASUREMENT==TRUE)
				task_runtime_measurement_off(1u, 0u);
				#endif
				#if (TASK_1_ENABLE_TASK_MONITOR==TRUE)
				u16_task_monitor_end_ctr[1] = (u16_scd_low_ctr / TASK_1_PERIOD);
				if (u16_task_monitor_start_ctr[1] != u16_task_monitor_end_ctr[1])
				{
					task_overflow_handler(1u, 0u);
				}
				#endif
			}
			#endif
		#endif

		/*********************
		 * Schedule this task
		 *********************/
		#if ((USE_TASK_2==TRUE) && (TASK_2_PRIO==TASK_PRIO_LOW))
			#if (TASK_2_CREATE_SLICES==TRUE)
			// check whether we are in the time base of the task
			//lint -e587 It depends on the host configuration, whether predicate can be predetermined.
			if ((u16_scd_local_ctr % TASK_2_BASE == 0) && !bf8_suspend_tasks_local.b_task_2)
			{
				// find the matching task slice and launch it
				u16_slice = (u16_scd_local_ctr % TASK_2_PERIOD) / TASK_2_BASE;
				if (ap_task_2[u16_slice] != NULL_PTR)
				{
					#if (TASK_2_ENABLE_TASK_MONITOR==TRUE)
					u16_task_monitor_start_ctr[2] = u16_slice;
					#endif
					#if (TASK_2_ENABLE_RUNTIME_MEASUREMENT==TRUE)
					task_runtime_measurement_on(2u, (u16)(u16_slice+1u));
					#endif
					(*ap_task_2[u16_slice])();
					#if (TASK_2_ENABLE_RUNTIME_MEASUREMENT==TRUE)
					task_runtime_measurement_off(2u, (u16)(u16_slice+1u));
					#endif
					#if (TASK_2_ENABLE_TASK_MONITOR==TRUE)
					u16_task_monitor_end_ctr[2] = (u16_scd_low_ctr % TASK_2_PERIOD) / TASK_2_BASE;
					if (u16_task_monitor_start_ctr[2] != u16_task_monitor_end_ctr[2])
					{
						task_overflow_handler(2u, (u16)(u16_slice+1u));
					}
					#endif
				}
			}
			#else // no slices
			// launch the task, if timing matches
			//lint -e587 It depends on the host configuration, whether predicate can be predetermined.
			if ((u16_scd_local_ctr % TASK_2_PERIOD == 0) && !bf8_suspend_tasks_local.b_task_2)
			{
				#if (TASK_2_ENABLE_TASK_MONITOR==TRUE)
				u16_task_monitor_start_ctr[2] = (u16_scd_local_ctr / TASK_2_PERIOD);
				#endif
				#if (TASK_2_ENABLE_RUNTIME_MEASUREMENT==TRUE)
				task_runtime_measurement_on(2u, 0u);
				#endif
				(*p_task_2)();
				#if (TASK_2_ENABLE_RUNTIME_MEASUREMENT==TRUE)
				task_runtime_measurement_off(2u, 0u);
				#endif
				#if (TASK_2_ENABLE_TASK_MONITOR==TRUE)
				u16_task_monitor_end_ctr[2] = (u16_scd_low_ctr / TASK_2_PERIOD);
				if (u16_task_monitor_start_ctr[2] != u16_task_monitor_end_ctr[2])
				{
					task_overflow_handler(2u, 0u);
				}
				#endif
			}
			#endif
		#endif

		/*********************
		 * Schedule this task
		 *********************/
		#if ((USE_TASK_3==TRUE) && (TASK_3_PRIO==TASK_PRIO_LOW))
			#if (TASK_3_CREATE_SLICES==TRUE)
			// check whether we are in the time base of the task
			//lint -e587 It depends on the host configuration, whether predicate can be predetermined.
			if ((u16_scd_local_ctr % TASK_3_BASE == 0) && !bf8_suspend_tasks_local.b_task_3)
			{
				// find the matching task slice and launch it
				u16_slice = (u16_scd_local_ctr % TASK_3_PERIOD) / TASK_3_BASE;
				if (ap_task_3[u16_slice] != NULL_PTR)
				{
					#if (TASK_3_ENABLE_TASK_MONITOR==TRUE)
					u16_task_monitor_start_ctr[3] = u16_slice;
					#endif
					#if (TASK_3_ENABLE_RUNTIME_MEASUREMENT==TRUE)
					task_runtime_measurement_on(3u, (u16)(u16_slice+1u));
					#endif
					(*ap_task_3[u16_slice])();
					#if (TASK_3_ENABLE_RUNTIME_MEASUREMENT==TRUE)
					task_runtime_measurement_off(3u, (u16)(u16_slice+1u));
					#endif
					#if (TASK_3_ENABLE_TASK_MONITOR==TRUE)
					u16_task_monitor_end_ctr[3] = (u16_scd_low_ctr % TASK_3_PERIOD) / TASK_3_BASE;
					if (u16_task_monitor_start_ctr[3] != u16_task_monitor_end_ctr[3])
					{
						task_overflow_handler(3u, (u16)(u16_slice+1u));
					}
					#endif
				}
			}
			#else // no slices
			// launch the task, if timing matches
			//lint -e587 It depends on the host configuration, whether predicate can be predetermined.
			if ((u16_scd_local_ctr % TASK_3_PERIOD == 0) && !bf8_suspend_tasks_local.b_task_3)
			{
				#if (TASK_3_ENABLE_TASK_MONITOR==TRUE)
				u16_task_monitor_start_ctr[3] = (u16_scd_local_ctr / TASK_3_PERIOD);
				#endif
				#if (TASK_3_ENABLE_RUNTIME_MEASUREMENT==TRUE)
				task_runtime_measurement_on(3u, 0u);
				#endif
				(*p_task_3)();
				#if (TASK_3_ENABLE_RUNTIME_MEASUREMENT==TRUE)
				task_runtime_measurement_off(3u, 0u);
				#endif
				#if (TASK_3_ENABLE_TASK_MONITOR==TRUE)
				u16_task_monitor_end_ctr[3] = (u16_scd_low_ctr / TASK_3_PERIOD);
				if (u16_task_monitor_start_ctr[3] != u16_task_monitor_end_ctr[3])
				{
					task_overflow_handler(3u, 0u);
				}
				#endif
			}
			#endif
		#endif

		/*********************
		 * Schedule this task
		 *********************/
		#if ((USE_TASK_4==TRUE) && (TASK_4_PRIO==TASK_PRIO_LOW))
			#if (TASK_4_CREATE_SLICES==TRUE)
			// check whether we are in the time base of the task
			//lint -e587 It depends on the host configuration, whether predicate can be predetermined.
			if ((u16_scd_local_ctr % TASK_4_BASE == 0) && !bf8_suspend_tasks_local.b_task_4)
			{
				// find the matching task slice and launch it
				u16_slice = (u16_scd_local_ctr % TASK_4_PERIOD) / TASK_4_BASE;
				if (ap_task_4[u16_slice] != NULL_PTR)
				{
					#if (TASK_4_ENABLE_TASK_MONITOR==TRUE)
					u16_task_monitor_start_ctr[4] = u16_slice;
					#endif
					#if (TASK_4_ENABLE_RUNTIME_MEASUREMENT==TRUE)
					task_runtime_measurement_on(4u, (u16)(u16_slice+1u));
					#endif
					(*ap_task_4[u16_slice])();
					#if (TASK_4_ENABLE_RUNTIME_MEASUREMENT==TRUE)
					task_runtime_measurement_off(4u, (u16)(u16_slice+1u));
					#endif
					#if (TASK_4_ENABLE_TASK_MONITOR==TRUE)
					u16_task_monitor_end_ctr[4] = (u16_scd_low_ctr % TASK_4_PERIOD) / TASK_4_BASE;
					if (u16_task_monitor_start_ctr[4] != u16_task_monitor_end_ctr[4])
					{
						task_overflow_handler(4u, (u16)(u16_slice+1u));
					}
					#endif
				}
			}
			#else // no slices
			// launch the task, if timing matches
			//lint -e587 It depends on the host configuration, whether predicate can be predetermined.
			if ((u16_scd_local_ctr % TASK_4_PERIOD == 0) && !bf8_suspend_tasks_local.b_task_4)
			{
				#if (TASK_4_ENABLE_TASK_MONITOR==TRUE)
				u16_task_monitor_start_ctr[4] = (u16_scd_local_ctr / TASK_4_PERIOD);
				#endif
				#if (TASK_4_ENABLE_RUNTIME_MEASUREMENT==TRUE)
				task_runtime_measurement_on(4u, 0u);
				#endif
				(*p_task_4)();
				#if (TASK_4_ENABLE_RUNTIME_MEASUREMENT==TRUE)
				task_runtime_measurement_off(4u, 0u);
				#endif
				#if (TASK_4_ENABLE_TASK_MONITOR==TRUE)
				u16_task_monitor_end_ctr[4] = (u16_scd_low_ctr / TASK_4_PERIOD);
				if (u16_task_monitor_start_ctr[4] != u16_task_monitor_end_ctr[4])
				{
					task_overflow_handler(4u, 0u);
				}
				#endif
			}
			#endif
		#endif

		/*********************
		 * Schedule this task
		 *********************/
		#if ((USE_TASK_5==TRUE) && (TASK_5_PRIO==TASK_PRIO_LOW))
			#if (TASK_5_CREATE_SLICES==TRUE)
			// check whether we are in the time base of the task
			//lint -e587 It depends on the host configuration, whether predicate can be predetermined.
			if ((u16_scd_local_ctr % TASK_5_BASE == 0) && !bf8_suspend_tasks_local.b_task_5)
			{
				// find the matching task slice and launch it
				u16_slice = (u16_scd_local_ctr % TASK_5_PERIOD) / TASK_5_BASE;
				if (ap_task_5[u16_slice] != NULL_PTR)
				{
					#if (TASK_5_ENABLE_TASK_MONITOR==TRUE)
					u16_task_monitor_start_ctr[5] = u16_slice;
					#endif
					#if (TASK_5_ENABLE_RUNTIME_MEASUREMENT==TRUE)
					task_runtime_measurement_on(5u, (u16)(u16_slice+1u));
					#endif
					(*ap_task_5[u16_slice])();
					#if (TASK_5_ENABLE_RUNTIME_MEASUREMENT==TRUE)
					task_runtime_measurement_off(5u, (u16)(u16_slice+1u));
					#endif
					#if (TASK_5_ENABLE_TASK_MONITOR==TRUE)
					u16_task_monitor_end_ctr[5] = (u16_scd_low_ctr % TASK_5_PERIOD) / TASK_5_BASE;
					if (u16_task_monitor_start_ctr[5] != u16_task_monitor_end_ctr[5])
					{
						task_overflow_handler(5u, (u16)(u16_slice+1u));
					}
					#endif
				}
			}
			#else // no slices
			// launch the task, if timing matches
			//lint -e587 It depends on the host configuration, whether predicate can be predetermined.
			if ((u16_scd_local_ctr % TASK_5_PERIOD == 0) && !bf8_suspend_tasks_local.b_task_5)
			{
				#if (TASK_5_ENABLE_TASK_MONITOR==TRUE)
				u16_task_monitor_start_ctr[5] = (u16_scd_local_ctr / TASK_5_PERIOD);
				#endif
				#if (TASK_5_ENABLE_RUNTIME_MEASUREMENT==TRUE)
				task_runtime_measurement_on(5u, 0u);
				#endif
				(*p_task_5)();
				#if (TASK_5_ENABLE_RUNTIME_MEASUREMENT==TRUE)
				task_runtime_measurement_off(5u, 0u);
				#endif
				#if (TASK_5_ENABLE_TASK_MONITOR==TRUE)
				u16_task_monitor_end_ctr[5] = (u16_scd_low_ctr / TASK_5_PERIOD);
				if (u16_task_monitor_start_ctr[5] != u16_task_monitor_end_ctr[5])
				{
					task_overflow_handler(5u, 0u);
				}
				#endif
			}
			#endif
		#endif

		// reset semaphore for scheduler
		b_scd_low_ctr_changed = FALSE;

	}
	else //no other tasks to schedule; we can run the background task

	#endif /* end of check for low-prio tasks */
	{
		#if (USE_LOW_PRIO_BACKGROUND_TASK==TRUE)
		 	if (!bf8_suspend_tasks_local.b_bkg_task) //launch, if not suspended
		 	{
				#if (BKG_TASK_ENABLE_RUNTIME_MEASUREMENT==TRUE)
				task_runtime_measurement_on(0u, 0u);
				#endif
				background_task();
				#if (BKG_TASK_ENABLE_RUNTIME_MEASUREMENT==TRUE)
				task_runtime_measurement_off(0u, 0u);
				#endif
		 	}
		#endif
	}
}
/*
 * Following function is only required, if we have more than a background task as low-prio.
 */
#if (LOW_PRIO_TASKS==TRUE)
/******************************************************************************
* Name            :  scd_low_prio_counter
* Preconditions   :  called in periodic timer interrupt
* Parameters      :  none
* Return code     :  none
* Description     :  Increments the counter for the low-prio scheduler
*                    and sets a semaphore to indicate that it changed.
* 					 The low-prio scheduler itself is running in the
* 					 endless loop of main.
******************************************************************************/
void scd_low_prio_counter(void)
{
#if (USE_HIGH_PRIO_SCHEDULER==FALSE) // the system tick needs to be incremented only once
		system_tick++;
#endif
	// Manage task scheduler counter
	if (u16_scd_low_ctr < u16_scd_low_ctr_max)
	{
		u16_scd_low_ctr++;
	}
	else
	{
	  	u16_scd_low_ctr = 0u;
	}
	// set semaphore for scheduler
	b_scd_low_ctr_changed = TRUE;
}
#endif // LOW_PRIO_TASKS==TRUE

#endif // USE_LOW_PRIO_SCHEDULER

/******************************************************************************
* Name            : scd_get_system_time
* Preconditions   :  none
* Parameters      :  none
* Return code     :  u16 system_tick
* Description     :  Returns the system time tick.
******************************************************************************/
uint16_t scd_get_system_time(void)
{
	// return the system tick
	return system_tick;
}

/******************************************************************************
* Name            : scd_time_passed
* Preconditions   :  none
* Parameters      :  u16 since_time
* Return code     :  u16 time_passed
* Description     :  Returns the time passed since the given time tick.
******************************************************************************/
uint16_t scd_time_passed(u16 since_time)
{
	uint16_t time_passed;

	// check whether the since_time is in the past
	if (system_tick >= since_time)
	{
		time_passed = system_tick - since_time;
	}
	else
	{
		time_passed = (U16_MAX - since_time) + system_tick;
	}

	return time_passed;
}

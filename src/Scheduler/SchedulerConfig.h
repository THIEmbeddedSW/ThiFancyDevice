/******************************************************************************
** COPYRIGHT:           Rudi Bauer
** DESCRIPTION:         Config file for generic scheduler.
** DATE CREATED:        25.12.2022
******************************************************************************/

#ifndef SCHEDULER_CONFIG_H
#define SCHEDULER_CONFIG_H

/******************************************************************************
*   INCLUDE FILES
******************************************************************************/

/******************************************************************************
*   EXTERN DEFINES AND MACROS
******************************************************************************/
#define SCHEDULER_CONFIG_VERSION (0x1u)


#define TASK_PRIO_HIGH	1
#define TASK_PRIO_LOW	0

// which scheduler do we want to use?
#define USE_HIGH_PRIO_SCHEDULER					TRUE
#define USE_LOW_PRIO_SCHEDULER					TRUE

// background task
#define USE_LOW_PRIO_BACKGROUND_TASK			FALSE
#define BKG_TASK_ENABLE_RUNTIME_MEASUREMENT		FALSE

// 100ms task - no slices
#define USE_TASK_1								TRUE
#define TASK_1_PRIO 							TASK_PRIO_HIGH
#define TASK_1_BASE 							100
#define TASK_1_FACTOR 							1
#define TASK_1_PERIOD 							(TASK_1_BASE * TASK_1_FACTOR)
#define TASK_1_ENABLE_TASK_MONITOR	 			FALSE
#define TASK_1_ENABLE_RUNTIME_MEASUREMENT	 	FALSE
#define TASK_1_CREATE_SLICES 					FALSE
#define TASK_1 									task_100ms_high_prio

// 100 ms task - no slices
#define USE_TASK_2								TRUE
#define TASK_2_PRIO 							TASK_PRIO_LOW
#define TASK_2_BASE 							100
#define TASK_2_FACTOR 							1
#define TASK_2_PERIOD 							(TASK_2_BASE * TASK_2_FACTOR)
#define TASK_2_ENABLE_TASK_MONITOR	 			FALSE
#define TASK_2_ENABLE_RUNTIME_MEASUREMENT	 	FALSE
#define TASK_2_CREATE_SLICES 					FALSE
#define TASK_2 									task_100ms

// 500ms task - no slices
#define USE_TASK_3								TRUE
#define TASK_3_PRIO 							TASK_PRIO_LOW
#define TASK_3_BASE								500
#define TASK_3_FACTOR 							1
#define TASK_3_PERIOD 							(TASK_3_BASE * TASK_3_FACTOR)
#define TASK_3_ENABLE_TASK_MONITOR	 			FALSE
#define TASK_3_ENABLE_RUNTIME_MEASUREMENT	 	FALSE
#define TASK_3_CREATE_SLICES 					FALSE
// #define TASK_3_SLICE_2 							task_10ms_slice_2
// #define TASK_3_SLICE_3 							task_10ms_slice_3
// #define TASK_3_SLICE_4 							task_10ms_slice_4
#define TASK_3 									task_500ms

// 1s task - no slices
#define USE_TASK_4								TRUE
#define TASK_4_PRIO 							TASK_PRIO_LOW
#define TASK_4_BASE 							1000
#define TASK_4_FACTOR 							1
#define TASK_4_PERIOD 							(TASK_4_BASE * TASK_4_FACTOR)
#define TASK_4_ENABLE_TASK_MONITOR	 			FALSE
#define TASK_4_ENABLE_RUNTIME_MEASUREMENT	 	FALSE
#define TASK_4_CREATE_SLICES 					FALSE
#define TASK_4 									task_1s

// 500 ms task - 5 slices
#define USE_TASK_5								FALSE
#define TASK_5_PRIO 							TASK_PRIO_LOW
#define TASK_5_BASE 							100
#define TASK_5_FACTOR 							5
#define TASK_5_PERIOD 							(TASK_5_BASE * TASK_5_FACTOR)
#define TASK_5_ENABLE_TASK_MONITOR	 			FALSE
#define TASK_5_ENABLE_RUNTIME_MEASUREMENT	 	FALSE
#define TASK_5_CREATE_SLICES 					TRUE
#define TASK_5_SLICE_1							task_500ms_slice_1
#define TASK_5_SLICE_2							task_500ms_slice_2

/******************************************************************************
*   TYPE DEFINITIONS
******************************************************************************/

/******************************************************************************
*   EXTERN VARIABLES AND CONSTANTS DECLARATIONS
******************************************************************************/

/******************************************************************************
*   EXTERN FUNCTION DECLARATIONS
******************************************************************************/

#endif /* SCHEDULER_CONFIG_H */

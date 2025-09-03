/******************************************************************************
 ** COPYRIGHT:           Rudi Bauer
 ** DESCRIPTION:    	 Main module.
 ** DATE CREATED:        25.12.2022
  ******************************************************************************/

/******************************************************************************
 *  COMPILER SWITCHES
 ******************************************************************************/

/******************************************************************************
  *   INCLUDE FILES
 ******************************************************************************/
#include "GlobalConfig.h"

#if (ENABLE_AVR_DEBUG == TRUE)
#include "avr8-stub.h"
#include "app_api.h"
#endif

#include "BIOS/BiosImport.h"
#include "BIOS/Bios.h"
#include "SCHEDULER/SchedulerImport.h"
#include "SCHEDULER/Scheduler.h"
#include "UI/UI.h"
#include "HT/ht.h"
#include "FaultManager/FaultManager.h"

/******************************************************************************
 *   DEFINES AND MACROS
 ******************************************************************************/

/******************************************************************************
 *   LOCAL VARIABLES AND CONSTANTS
 ******************************************************************************/
#if (USE_SERIAL_DEBUG == TRUE)
static uint16_t last_time = 0;
#endif

 /******************************************************************************
 *   EXPORTED VARIABLES AND CONSTANTS (AS EXTERN IN H-FILES)
 ******************************************************************************/
char programVersion[] = "1.4.0";
/******************************************************************************
*   PRIVATE FUNCTIONS
******************************************************************************/

/******************************************************************************
  *   EXPORTED FUNCTIONS (AS EXTERN IN H-FILES)
 ******************************************************************************/

/********************************************************************/
// Initialization
/********************************************************************/
#ifndef UNIT_TEST
void setup() 
{
	#if (ENABLE_AVR_DEBUG == TRUE)
	debug_init(); // initialize the debug interface
	#endif

	#if (USE_SERIAL_DEBUG == TRUE)
	BiosSerialInit(); // initialize the BIOS serial communication
	#endif

	BiosIoInit(); // initialize the BIOS I/O
	BiosAdcInit(); // initialize the BIOS ADC
	BiosTimerInit(); // initialize the BIOS timer for the scheduler
	#if (ENABLE_AVR_DEBUG == FALSE)  // watchdog must only be active, if we do not debug
	BiosWdtInit(); // initialize watchdog timer
	#endif

	UI_init(); // initialize the user interface

	scd_init(); // initialize the operating system

 	ht_init(); // initialize the humidity and temperature module

	FaultManagerInit();  // initialize fault manager for debouncing and error handling

	// let the system run
	BiosEnableInterrupts();

	BiosWdtService();  // Service the Watchdog for the 1st time

	#if (USE_SERIAL_DEBUG == TRUE)
	// Initialize with log level and log output. 
    Log.begin(LOG_LEVEL_VERBOSE, &Serial);
	Log.noticeln("=== Welcome to THI Fancy New Device version  %s === ", programVersion);
	#endif
}
#endif

/*-----------------------------------------------------------------------------
 *  Implement Timer ISR Callout
 -----------------------------------------------------------------------------*/
void TimerIsrCallout()
{
	scd_high_prio_tasks();
	scd_low_prio_counter();
}

/*-----------------------------------------------------------------------------
 *  Endless loop
 -----------------------------------------------------------------------------*/
#ifndef UNIT_TEST
void loop() 
{
	scd_low_prio_tasks(); // call the scheduler
	BiosWdtService();  // Service the Watchdog
}
#endif

/*-----------------------------------------------------------------------------
 *  Task 1 - high-prio
 -----------------------------------------------------------------------------*/
void task_100ms_high_prio()
{
	if (GetGlobalFaultStatus() > 0) BiosToggleLed(); // toggle the LED
}

/*-----------------------------------------------------------------------------
 *  Task 2
 -----------------------------------------------------------------------------*/
void task_100ms()
{
	UI_100ms();
}

/*-----------------------------------------------------------------------------
 *  Task 3
 -----------------------------------------------------------------------------*/
void task_500ms()
{
	if (GetGlobalFaultStatus() == 0) BiosToggleLed(); // toggle the LED

	#if (USE_SERIAL_DEBUG == TRUE)
	Log.noticeln("Main: System time: %d ms", scd_get_system_time());
    last_time = scd_get_system_time();
	#endif

	ht_500ms(); // call the humidity & temperature process

	#if (USE_SERIAL_DEBUG == TRUE)
	Log.noticeln("Main: Time since:  %d ms", scd_time_passed(last_time));
	#endif

}

/*-----------------------------------------------------------------------------
 *  Task 4
 -----------------------------------------------------------------------------*/
void task_1s()
{

}



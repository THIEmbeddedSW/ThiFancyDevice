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
//#include "GlobalConfig.h"

#include <Arduino.h>
#include <unity.h>

#include "BIOS/Bios.h"

/******************************************************************************
 *   DEFINES AND MACROS
 ******************************************************************************/

/******************************************************************************
 *   LOCAL VARIABLES AND CONSTANTS
 ******************************************************************************/
uint8_t btnValue = 0; //Variable to hold current button value
/******************************************************************************
 *   EXPORTED VARIABLES AND CONSTANTS (AS EXTERN IN H-FILES)
 ******************************************************************************/

/******************************************************************************
*   PRIVATE FUNCTIONS
******************************************************************************/

/******************************************************************************
  *   EXPORTED FUNCTIONS (AS EXTERN IN H-FILES)
 ******************************************************************************/

/********************************************************************/
// Initialization
/********************************************************************/

void setUp(void)
{
  // set stuff up here
}

void tearDown(void)
{
  // clean stuff up here
}


// -------------------------------------------------------
//  test LED toggling
// -------------------------------------------------------
void test_led_builtin_pin_number(void)
{
    TEST_ASSERT_EQUAL(13, LED_BUILTIN);
}

void test_led_toggling(void)
{
    digitalWrite(LED_BUILTIN, LOW);
    BiosToggleLed();
    TEST_ASSERT_EQUAL(HIGH, digitalRead(LED_BUILTIN));
    BiosToggleLed();
    TEST_ASSERT_EQUAL(LOW, digitalRead(LED_BUILTIN));
}

void setup()
{
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);
  
    BiosIoInit();

    UNITY_BEGIN(); // IMPORTANT LINE!
}

void loop()
{
    RUN_TEST(test_led_toggling);

    UNITY_END(); // stop unit testing
}
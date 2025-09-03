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

#include "GlobalConfig.h"
#include "FaultManager/FaultManager.h"

/******************************************************************************
 *   DEFINES AND MACROS
 ******************************************************************************/
// Fault states
typedef enum
{
	DEB_STATE_PASS,
	DEB_STATE_SYM,
	DEB_STATE_NO_SYM,
	DEB_STATE_FAIL_UNSAVED,
	DEB_STATE_FAIL_SAVED
}e_debounce_state_t;


/******************************************************************************
 *   LOCAL VARIABLES AND CONSTANTS
 ******************************************************************************/

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
//  test the temperature debouncing
// -------------------------------------------------------
void test_TemperatureDebounceStatus(void)
{
   uint8_t i;
   uint8_t globalFaultCode = 0;

   // start with good case
   FaultDebounce(FALSE,FC_DHT_TEMP);
   TEST_ASSERT_EQUAL(DEB_STATE_PASS, GetFaultDebounceStatus(FC_DHT_TEMP));
   TEST_ASSERT_EQUAL(0, GetFaultDebounceCount(FC_DHT_TEMP));
   TEST_ASSERT(!GetFaultErrorStatus(FC_DHT_TEMP));

   // symptom occurs
   FaultDebounce(TRUE,FC_DHT_TEMP);
   TEST_ASSERT_EQUAL(DEB_STATE_SYM, GetFaultDebounceStatus(FC_DHT_TEMP));
   TEST_ASSERT_EQUAL(1, GetFaultDebounceCount(FC_DHT_TEMP));
   TEST_ASSERT(!GetFaultErrorStatus(FC_DHT_TEMP));

   // 2 more symptoms -> should be fault now
   for (i=0; i<2; i++)
   {
      FaultDebounce(TRUE,FC_DHT_TEMP);
   }
   TEST_ASSERT_EQUAL(DEB_STATE_FAIL_UNSAVED, GetFaultDebounceStatus(FC_DHT_TEMP));
   TEST_ASSERT_EQUAL(3, GetFaultDebounceCount(FC_DHT_TEMP));
   TEST_ASSERT(GetFaultErrorStatus(FC_DHT_TEMP));
   TEST_ASSERT_EQUAL(bitSet(globalFaultCode, FC_DHT_TEMP), GetGlobalFaultStatus());
   
   // now let's heal the fault
   FaultDebounce(FALSE,FC_DHT_TEMP);
   TEST_ASSERT_EQUAL(DEB_STATE_PASS, GetFaultDebounceStatus(FC_DHT_TEMP));
   // fault should be completely gone, as the decrement for this fault is 3
   TEST_ASSERT_EQUAL(0, GetFaultDebounceCount(FC_DHT_TEMP));  
   TEST_ASSERT(!GetFaultErrorStatus(FC_DHT_TEMP));
}

// -------------------------------------------------------
// test the humidity debouncing, which has a decrement of 1
// -------------------------------------------------------
void test_HumidityDebounceStatus(void)
{
   uint8_t i;
   // start with good case
   FaultDebounce(FALSE,FC_DHT_HUM);
   TEST_ASSERT_EQUAL(DEB_STATE_PASS, GetFaultDebounceStatus(FC_DHT_HUM));
   TEST_ASSERT_EQUAL(0, GetFaultDebounceCount(FC_DHT_HUM));
   TEST_ASSERT(!GetFaultErrorStatus(FC_DHT_HUM));

   // 2 times symptoms -
   for (i=0; i<2; i++)
   {
      FaultDebounce(TRUE,FC_DHT_HUM);
   }
   TEST_ASSERT_EQUAL(DEB_STATE_SYM, GetFaultDebounceStatus(FC_DHT_HUM));
   TEST_ASSERT_EQUAL(2, GetFaultDebounceCount(FC_DHT_HUM));
   TEST_ASSERT(!GetFaultErrorStatus(FC_DHT_HUM));

   // now let's remove the symptom once - should go to NO_SYM state
   FaultDebounce(FALSE,FC_DHT_HUM);
   TEST_ASSERT_EQUAL(DEB_STATE_NO_SYM, GetFaultDebounceStatus(FC_DHT_HUM));
   TEST_ASSERT_EQUAL(1, GetFaultDebounceCount(FC_DHT_HUM));  
   TEST_ASSERT(!GetFaultErrorStatus(FC_DHT_TEMP));

   // 2 more symptoms -> should be fault now
   for (i=0; i<2; i++)
   {
      FaultDebounce(TRUE,FC_DHT_HUM);
   }
   TEST_ASSERT_EQUAL(DEB_STATE_FAIL_UNSAVED, GetFaultDebounceStatus(FC_DHT_HUM));
   TEST_ASSERT_EQUAL(3, GetFaultDebounceCount(FC_DHT_HUM));
   TEST_ASSERT(GetFaultErrorStatus(FC_DHT_HUM));

   // now let's heal the fault
   for (i=0; i<4; i++)
   {
      FaultDebounce(FALSE,FC_DHT_HUM);
   }
   TEST_ASSERT_EQUAL(DEB_STATE_PASS, GetFaultDebounceStatus(FC_DHT_HUM));
   // fault should be completely gone, as the decrement for this fault is 3
   TEST_ASSERT_EQUAL(0, GetFaultDebounceCount(FC_DHT_HUM));  
   TEST_ASSERT(!GetFaultErrorStatus(FC_DHT_HUM));
}



void setup()
{
   // NOTE!!! Wait for >2 secs
   // if board doesn't support software reset via Serial.DTR/RTS
   delay(2000);
  
   FaultManagerInit();
   UNITY_BEGIN(); // IMPORTANT LINE!
}

void loop()
{
   RUN_TEST(test_TemperatureDebounceStatus);
   RUN_TEST(test_HumidityDebounceStatus);

   UNITY_END(); // stop unit testing
}
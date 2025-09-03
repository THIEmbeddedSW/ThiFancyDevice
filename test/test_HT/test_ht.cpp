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

#include "HT/ht.h"
#include "FaultManager/FaultManager.h"

/******************************************************************************
 *   DEFINES AND MACROS
 ******************************************************************************/

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

void test_ht_status(void)
{
   float t, h;
   u8 rc;

    // run measurement once
   ht_1s();
   rc = HTgetTemperature(&t);
   TEST_ASSERT_EQUAL(ERRCODE_NONE, rc);
   TEST_ASSERT(t >= 0.0 && t <= 50.0);
   rc = HTgetHumidity(&h);
   TEST_ASSERT_EQUAL(ERRCODE_NONE, rc);
   TEST_ASSERT(h == 0); // no measurement yet, hence 0

   //run measurement again
   ht_1s();
   rc = HTgetHumidity(&h);
   TEST_ASSERT_EQUAL(ERRCODE_NONE, rc);
   TEST_ASSERT(h > 0.0 && h <= 90.0); 
}

void setup()
{
   // NOTE!!! Wait for >2 secs
   // if board doesn't support software reset via Serial.DTR/RTS
   delay(2000);
  
   ht_init();

   UNITY_BEGIN(); // IMPORTANT LINE!
}

void loop()
{
   RUN_TEST(test_ht_status);

   UNITY_END(); // stop unit testing
}
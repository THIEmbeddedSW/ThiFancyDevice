/******************************************************************************
 ** COPYRIGHT:           Rudi Bauer
 ** DESCRIPTION:    	 Humidity & Temperature module.
 ** DATE CREATED:        25.12.2022
  ******************************************************************************/

/******************************************************************************
 *  COMPILER SWITCHES
 ******************************************************************************/

/******************************************************************************
  *   INCLUDE FILES
 ******************************************************************************/
#include "GlobalConfig.h"
#include "DHT.h"
#include "BIOS/Bios.h"

#include "ht.h"

/******************************************************************************
 *   DEFINES AND MACROS
 ******************************************************************************/
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321
//#define DHTTYPE DHT21 // DHT 21 (AM2301)

#define TEMP_CELSIUS 1
#define TEMP_FAHRENHEIT 2
#define HUMIDITY 3
#define HEAT_INDEX 4
#define DHT_ALL 5
#define DHT_ERROR 6

/******************************************************************************
 *   LOCAL VARIABLES AND CONSTANTS
 ******************************************************************************/
// Initialize DHT sensor.
static DHT dht(DHT_PIN, DHTTYPE);
static float t;
static float h;
static float hic;

static uint8_t selector;


/******************************************************************************
 *   EXPORTED VARIABLES AND CONSTANTS (AS EXTERN IN H-FILES)
 ******************************************************************************/

/******************************************************************************
*   PRIVATE FUNCTIONS
******************************************************************************/
/******************************************************************************
  *   EXPORTED FUNCTIONS (AS EXTERN IN H-FILES)
 ******************************************************************************/
/*-----------------------------------------------------------------------------
 *  initialization of user interface
 -----------------------------------------------------------------------------*/
void ht_init()
{
	selector = TEMP_CELSIUS;
	dht.begin();
}

/*-----------------------------------------------------------------------------
 *  recurring DHT process - 1s
 -----------------------------------------------------------------------------*/
void ht_1s(){
	// Reading temperature or humidity takes about 20 milliseconds!
	// Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
	// Therefore we only read/calculate one value in each cycle.

	switch (selector) //select, what to do in this cycle
	{
		case TEMP_CELSIUS:
			// Read temperature as Celsius (the default)
			t = dht.readTemperature();
			if (isnan(t)) selector = DHT_ERROR;
			else selector = HUMIDITY; // for next cycle
			break;

		case HUMIDITY:
			h = dht.readHumidity();
			if (isnan(h)) selector = DHT_ERROR;
			else selector = HEAT_INDEX; // for next cycle
			break;

		case HEAT_INDEX:
			// Compute heat index in Celsius (isFahreheit = false)
			hic = dht.computeHeatIndex(t, h, false);
			if (isnan(hic)) selector = DHT_ERROR;
			else selector = TEMP_CELSIUS; // for next cycle
			break;

		case DHT_ERROR:
			// error handling tbd
			selector = TEMP_CELSIUS;
			break;

		case DHT_ALL:
			// Read temperature as Celsius (the default)
			t = dht.readTemperature();
			// Read humidity
			h = dht.readHumidity();
			// Compute heat index in Celsius (isFahreheit = false)
			if (isnan(h) || isnan(t)) selector = DHT_ERROR;
			else
			{
				hic = dht.computeHeatIndex(t, h, false);
			}
			break;

		default:
			break;
	}

}

/*-----------------------------------------------------------------------------
 *  providing the data
 -----------------------------------------------------------------------------*/
uint8_t HTgetTemperature(float *temperature)
{
	if (isnan(t) ) {
		return ERRCODE_DHT_NO_DATA;
	}
	*temperature = t;
	return ERRCODE_NONE;
}

uint8_t HTgetHumidity(float *humidity)
{
	if (isnan(h) ) {
		return ERRCODE_DHT_NO_DATA;
	}
	*humidity = h;
	return ERRCODE_NONE;
}
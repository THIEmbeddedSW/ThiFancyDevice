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
#include "FaultManager/FaultManager.h"

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
static float t, t_prev;
static float h, h_prev;
// static float f;
// static float hif;
static float hic, hic_prev;

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
	t = t_prev = h = h_prev = hic = hic_prev = 0;
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
			if (FaultDebounce(isnan(t),FC_DHT_TEMP))
			{
				#if (USE_SERIAL_DEBUG == TRUE)
				Log.errorln("HT: Error during DHT temperature data reading!!");
				#endif
				selector = DHT_ERROR;
			}
			else 
			{
				// if we have a fault symptom, we stay on previous value, until symptom turns into error
				if (isnan(t)) t = t_prev; else t_prev = t; 
				selector = HUMIDITY; // for next cycle
			}
			#if (USE_SERIAL_DEBUG == TRUE)
			Log.noticeln("HT: Temperature debounce state: %d", GetFaultDebounceStatus(FC_DHT_TEMP));
			Log.noticeln("HT: Temperature debounce cnt  : %d", GetFaultDebounceCount(FC_DHT_TEMP));
			#endif
			break;

		case HUMIDITY:
			h = dht.readHumidity();  // read humidity
			// debounce result
			if (FaultDebounce(isnan(h),FC_DHT_HUM))
			{
				#if (USE_SERIAL_DEBUG == TRUE)
				Log.errorln("HT: Error during DHT humidity data reading!!");
				#endif
				selector = DHT_ERROR;
			}
			else 
			{
				// if we have a fault symptom, we stay on previous value, until symptom turns into error
				if (isnan(h)) h = h_prev; else h_prev = h; 
				selector = HEAT_INDEX; // for next cycle
			}
			#if (USE_SERIAL_DEBUG == TRUE)
			Log.noticeln("HT: Humidity debounce state: %d", GetFaultDebounceStatus(FC_DHT_HUM));
			Log.noticeln("HT: Humidity debounce cnt  : %d", GetFaultDebounceCount(FC_DHT_HUM));
			break;
			#endif

		case HEAT_INDEX:
			// Compute heat index in Celsius (isFahreheit = false)
			hic = dht.computeHeatIndex(t, h, false);
			if (FaultDebounce(isnan(hic),FC_DHT_HIDX))
			{
				#if (USE_SERIAL_DEBUG == TRUE)
				Log.errorln("HT: Error during DHT humidity index calculation!!");
				#endif
				selector = DHT_ERROR;
			}
			else 
			{
				// if we have a fault symptom, we stay on previous value, until symptom turns into error
				if (isnan(hic)) hic = hic_prev; else hic_prev = hic; 
				selector = TEMP_CELSIUS; // for next cycle
			}
			#if (USE_SERIAL_DEBUG == TRUE)
			Log.noticeln("HT: Humidity index debounce state: %d", GetFaultDebounceStatus(FC_DHT_HIDX));
			Log.noticeln("HT: Humidity index debounce cnt  : %d", GetFaultDebounceCount(FC_DHT_HIDX));
			#endif
			break;

		case DHT_ERROR:
			// error handling tbd
			#if (USE_SERIAL_DEBUG == TRUE)
			Log.errorln("HT: Error during DHT data reading!!");
			#endif
			selector = TEMP_CELSIUS;
			break;

		case DHT_ALL:
			// Read temperature as Celsius (the default)
			t = dht.readTemperature(false, true);
			// Read humidity
			h = dht.readHumidity(true);
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

	#if (USE_SERIAL_DEBUG == TRUE)
	Log.noticeln("HT: Temperature %F °C Humidity %F %% Heat index %F", t, h, hic);
	#endif
}

/*-----------------------------------------------------------------------------
 *  providing the data
 -----------------------------------------------------------------------------*/
uint8_t HTgetTemperature(float *temperature){
	if (GetFaultErrorStatus(FC_DHT_TEMP)) 
	{
		#if (USE_SERIAL_DEBUG == TRUE)
		Log.errorln("HT: No valid temperature from DHT sensor!");
		#endif
		return ERRCODE_DHT_FAILED;
	}
	*temperature = t;
	return ERRCODE_NONE;
}

uint8_t HTgetHumidity(float *humidity){
	if (GetFaultErrorStatus(FC_DHT_HUM)) 
	{
		#if (USE_SERIAL_DEBUG == TRUE)
		Log.errorln("HT: No valid humidity from DHT sensor!");
		#endif
		return ERRCODE_DHT_FAILED;
	}
	*humidity = h;
	return ERRCODE_NONE;
}
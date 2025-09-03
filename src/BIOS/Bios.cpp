/******************************************************************************
 ** COPYRIGHT:           Rudi Bauer
 ** DESCRIPTION:    	 Bios
 ** DATE CREATED:        25.12.2022
  ******************************************************************************/

/******************************************************************************
 *  COMPILER SWITCHES
 ******************************************************************************/

/******************************************************************************
  *   INCLUDE FILES
 ******************************************************************************/
#include "GlobalConfig.h"
#include "BiosImport.h"
#include "Bios.h"

/******************************************************************************
 *   DEFINES AND MACROS
 ******************************************************************************/
/* --- Versioncheck --- */
#if ( BIOS_CONFIG_VERSION != 0x1u )
#error "Error in Bios.c: Config and component source file are inconsistent! \
        Please Checkout and merge!"
#endif

// ADC macros
#define ADC0 0
#define ADC1 1
#define ADC2 2
#define ADC3 3
#define ADC4 4
#define ADC5 5
#define ADC6 6
#define ADC7 7

// ADC sensor max value
#define ADC_MAX	1023

// Define the ADC channels used.  ADLAR will be zero.
#undef ADCH0
#undef ADCH1
#undef ADCH2
#undef ADCH3
#define ADCH0 ((1 << REFS0) | ADC0)
#define ADCH1 ((1 << REFS0) | ADC1)
#define ADCH2 ((1 << REFS0) | ADC2)
#define ADCH3 ((1 << REFS0) | ADC3)

// debounce threshold for button clicks
#if (NC_ADC_PINS > 3)
	#define ADC_DEBOUNCE_THD 280
#elif (NC_ADC_PINS > 2)
	#define ADC_DEBOUNCE_THD 400
#elif (NC_ADC_PINS > 1)
	#define ADC_DEBOUNCE_THD 600
#else
	#define ADC_DEBOUNCE_THD 800
#endif

/******************************************************************************
 *   LOCAL VARIABLES AND CONSTANTS
 ******************************************************************************/
volatile int adcChan;

static int AdcDebounceCnt = 0;

static bool btnProcessed = FALSE;
static uint8_t btnValue = BTN_NONE;

/******************************************************************************
 *   EXPORTED VARIABLES AND CONSTANTS (AS EXTERN IN H-FILES)
 ******************************************************************************/
//FastCRC8 crc8;
uint16_t AdcValue[NC_ADC_PINS];


/******************************************************************************
*   PRIVATE FUNCTIONS
******************************************************************************/

/******************************************************************************
  *   EXPORTED FUNCTIONS (AS EXTERN IN H-FILES)
 ******************************************************************************/

void(* BiosReset) (void) = 0;  // declare reset function at address 0

/*-----------------------------------------------------------------------------
 *  Enable all interrupts
 -----------------------------------------------------------------------------*/
void BiosEnableInterrupts()
{
	interrupts();             // enable all interrupts
}

/*-----------------------------------------------------------------------------
 *  Disable all interrupts
 -----------------------------------------------------------------------------*/
void BiosDisableInterrupts()
{
	noInterrupts();             // disable all interrupts
}

/*-----------------------------------------------------------------------------
 *  Initialization of IO pins
 -----------------------------------------------------------------------------*/
void BiosIoInit()
{
	// Initialize LED pins
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, LOW);       // switch LED on

	pinMode(DHT_PIN, INPUT); // DHT sensor pin
}

/*-----------------------------------------------------------------------------
 *  Initialization of Serial line
 -----------------------------------------------------------------------------*/
void BiosSerialInit()
{
#if (USE_SERIAL_DEBUG == TRUE)
	Serial.begin((u32)SERIAL_BAUDRATE);
#endif
}

/*-----------------------------------------------------------------------------
 *  Initialization of timer for scheduler
 -----------------------------------------------------------------------------*/
void BiosTimerInit()
{
	// initialize timer1 to 1ms
	noInterrupts();           // disable all interrupts
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1  = 0;

	OCR1A = 16000;            // compare match register 16MHz/1000
	TCCR1B |= (1 << WGM12);   // CTC mode
	TCCR1B |= (1 << CS10);    // No prescaler
	TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
}

/*-----------------------------------------------------------------------------
 *  Initialization of Watchdog Timer
 -----------------------------------------------------------------------------*/
void BiosWdtInit()
{
	  wdt_reset();
	  wdt_enable(WDTO_1S); // 1s / System Reset
	  WDTCSR = (1<<WDIE); // interrupt
}

/*-----------------------------------------------------------------------------
 *  Service the Watchdog
 -----------------------------------------------------------------------------*/
void BiosWdtService()
{
	  wdt_reset();
}

/*-----------------------------------------------------------------------------
 *  Initialization of ADC for buttons
 -----------------------------------------------------------------------------*/
void BiosAdcInit()
{
	uint8_t i;

	// Set for the first ADC channel.
	  ADMUX = ADCH0;

	  // Set ADEN, prescale (128), and enable ADC interrupts.
	  ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADIE);

	  // Clear everything.  No free running because ADATE is clear in ADSRA.
	  ADCSRB = 0;

	  // Set ADSC to start ADC conversion.
	  ADCSRA |= (1 << ADSC);

	  //Initialize the ADC values
	  for (i = 0u; i < NC_ADC_PINS;  i++)
	  {
		  AdcValue[i] = ADC_MAX;
	  }
}

/*-----------------------------------------------------------------------------
 *  Provides the clicked button
 -----------------------------------------------------------------------------*/
u8 BiosGetBtnValue()
{
	// this function is called to process the pending click;
	// so we reset the semaphore to accept new clicks afterwards.
	if (btnValue != BTN_NONE) btnProcessed = TRUE;
	return btnValue;
}

/*-----------------------------------------------------------------------------
 *  Toggles the LED
 -----------------------------------------------------------------------------*/
void BiosToggleLed()
{
	digitalWrite(LED_PIN, digitalRead(LED_PIN) ^ 1);       // toggle LED
}

/*-----------------------------------------------------------------------------
 *  Timer interrupt
 -----------------------------------------------------------------------------*/
ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
	TimerIsrCallout();
}

/*-----------------------------------------------------------------------------
 *  ADC interrupt
 -----------------------------------------------------------------------------*/
ISR(ADC_vect)
{
	  int tempVal;

	  // Get the ADC channel causing the interrupt.
	  adcChan = ADMUX & ((1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0));

	  // Read low first
	  tempVal = ADCL | (ADCH << 8);

	  switch (adcChan)
	  {
	    case ADC0:
	    	if (tempVal < 50)
	    	{
	    		AdcDebounceCnt++;
	    		if (AdcDebounceCnt > ADC_DEBOUNCE_THD)
	    		{
	    			AdcDebounceCnt = 0;
	    			btnProcessed = FALSE;
	    			btnValue = BTN_RIGHT;
	    		}
	    	}
	    	else if (tempVal < 195)
	    	{
	    		AdcDebounceCnt++;
	    		if (AdcDebounceCnt > ADC_DEBOUNCE_THD)
	    		{
	    			AdcDebounceCnt = 0;
	    			btnProcessed = FALSE;
	    			btnValue = BTN_UP;
	    		}
	    	}
	    	else if (tempVal < 380)
	    	{
	    		AdcDebounceCnt++;
	    		if (AdcDebounceCnt > ADC_DEBOUNCE_THD)
	    		{
	    			AdcDebounceCnt = 0;
	    			btnProcessed = FALSE;
	    			btnValue = BTN_DOWN;
	    		}
	    	}
	    	else if (tempVal < 555)
	    	{
	    		AdcDebounceCnt++;
	    		if (AdcDebounceCnt > ADC_DEBOUNCE_THD)
	    		{
	    			AdcDebounceCnt = 0;
	    			btnProcessed = FALSE;
	    			btnValue = BTN_LEFT;
	    		}
	    	}
	    	else if (tempVal < 790)
	    	{	// left clicked
	    		AdcDebounceCnt++;
	    		if (AdcDebounceCnt > ADC_DEBOUNCE_THD)
	    		{
	    			AdcDebounceCnt = 0;
	    			btnProcessed = FALSE;
	    			btnValue = BTN_ENTER;
	    		}
	    	}
	    	else // no valid click
	    	{
    			AdcDebounceCnt = 0;
    			if (btnProcessed) btnValue = BTN_NONE;
	    	}

	    	// Set up for next ADC Channel.
	    	// Uncomment the following to enable another channel.
#if (NC_ADC_PINS > 1)
	    	ADMUX = ADCH1;
	    	break;

	    case ADC1:
	    	AdcValue[0] = tempVal;
	  	    // Set up for next ADC Channel.
	    	// Uncomment the following to enable another channel.
#if (NC_ADC_PINS > 2)
	    	ADMUX = ADCH2;
	    	break;

	    case ADC2:
	    	AdcValue[1] = tempVal;
	    	// Set up for next ADC Channel.
	    	// Uncomment the following to enable another channel.
#if (NC_ADC_PINS > 3)
	    	ADMUX = ADCH3;
	    	break;

	    case ADC3:
	    	AdcValue[2] = tempVal;
	    	// Set up for next ADC Channel.
	    	// Uncomment the following to enable another channel.
#if (NC_ADC_PINS > 4)
	    	ADMUX = ADCH4;
	    	break;

	    case ADC4:
	    	AdcValue[3] = tempVal;
	    	// Set up for next ADC Channel.
	    	// Uncomment the following to enable another channel.
	    	ADMUX = ADCH0;
	    	break;
#else
	    	ADMUX = ADCH0;
	    	break;
#endif
#else
	    	ADMUX = ADCH0;
	    	break;
#endif
#else
	    	ADMUX = ADCH0;
	    	break;
#endif
#else
	    	ADMUX = ADCH0;
	    	break;
#endif
	  }

	  // Set ADSC to start the next ADC conversion.
	  ADCSRA |= (1 << ADSC);
}



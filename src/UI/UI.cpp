/******************************************************************************
 ** COPYRIGHT:           Rudi Bauer
 ** DESCRIPTION:    	 User Interface
 ** DATE CREATED:        25.12.2022
  ******************************************************************************/

/******************************************************************************
 *  COMPILER SWITCHES
 ******************************************************************************/
#define LCD_I2C FALSE

/******************************************************************************
  *   INCLUDE FILES
 ******************************************************************************/
#include "GlobalConfig.h"
#include "BIOS/Bios.h"
#include "HT/ht.h"
#include "FaultManager/FaultManager.h"

#include <ItemBack.h>
#include <ItemSubMenu.h>
#include <ItemToggle.h>
#include <ItemCommand.h>
#include <LcdMenu.h>
#include <MenuScreen.h>
//#include <display/LiquidCrystal_I2CAdapter.h>
#include <display/LiquidCrystalAdapter.h>
//#include <input/KeyboardAdapter.h>
#include <renderer/CharacterDisplayRenderer.h>

#include "UI.h"


/******************************************************************************
 *   DEFINES AND MACROS
 ******************************************************************************/
#define LCD_COLS 16
#define LCD_ROWS 2

// UI states
#define UI_SPLASH 0
#define UI_INIT 1
#define UI_IDLE 2
#define UI_MAIN 3
#define UI_HEATALARM 4
#define UI_ERR 99

#define UI_TIMEMENUCOUNT 3  // number of menu entries
#define NC_BTN_CLICKS_ACCEL 5  // after this number of button clicks we accelerate
#define UI_HT_DISPLAY_TIME 10 // time in units of 100ms to display HT values in idle mode

/******************************************************************************
 *   LOCAL VARIABLES AND CONSTANTS
 ******************************************************************************/
static uint8_t btnValue = 0; //Variable to hold current button value
static uint8_t SplashScreenCounter = 0;
static uint8_t ScreenIdleCounter = 0;
static uint8_t ErrorWaitCounter = 0;
static uint8_t UI_state = 0;
static uint8_t errorCode = 0;

// data for display of humidity & temperature
static float value = 0.0; // value from HT component
static uint8_t ht_delay_cnt = 10;
static	bool toggle_display_ht = TRUE;
static bool heat_alarm = false;

// Declare the call back functions
void callbackResetSystem(void);
void callbackInfo(void);

extern MenuScreen* subMenu1;

// Define main menu
MENU_SCREEN(mainScreen, mainItems,
    ITEM_SUBMENU("System", subMenu1),
	ITEM_BASIC("Blink random"));

// Create submenu and precise its parent
MENU_SCREEN(subMenu1, subItems1,
	ITEM_COMMAND("Info", callbackInfo),
	ITEM_COMMAND("Neustart", callbackResetSystem),
    ITEM_BACK());


#if (LCD_I2C == TRUE)
	LiquidCrystal_I2C lcd(0x27, LCD_COLS, LCD_ROWS);
	CharacterDisplayRenderer renderer(new LiquidCrystal_I2CAdapter(&lcd), LCD_COLS, LCD_ROWS);
#else
	LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
	CharacterDisplayRenderer renderer(new LiquidCrystalAdapter(&lcd, LCD_COLS, LCD_ROWS), LCD_COLS, LCD_ROWS);
#endif
	LcdMenu menu(renderer);


/******************************************************************************
 *   EXPORTED VARIABLES AND CONSTANTS (AS EXTERN IN H-FILES)
 ******************************************************************************/

/******************************************************************************
*   PRIVATE FUNCTIONS
******************************************************************************/
/*-----------------------------------------------------------------------------
 *  manage display of humidity and temperature values
 -----------------------------------------------------------------------------*/
static uint8_t UI_display_HT()
{

	if (ht_delay_cnt < UI_HT_DISPLAY_TIME) ht_delay_cnt++;
	else
	{
		ht_delay_cnt = 0;
		errorCode = HTgetTemperature(&value); // get the temperature value
		if (errorCode > 0) // error occurred
		{
			lcd.clear();
			lcd.setCursor(0,0);
			lcd.print("!Error code ");
			lcd.setCursor(12,0);
			lcd.print(errorCode);
			lcd.setCursor(0,1);
			lcd.print("no Temp value");
			return errorCode;
		}
		else // display the data
		{
			lcd.clear();
			lcd.setCursor(0, 0);
			lcd.print("T : ");
			lcd.print(value);
			lcd.print(" \xDF" "C");
		}

		if (toggle_display_ht) // we display alternately humidity and heat index
		{
			errorCode = HTgetHumidity(&value); // get the humidity value
			if (errorCode > 0) // error occurred
			{
				lcd.clear();
				lcd.setCursor(0,0);
				lcd.print("!Error code ");
				lcd.setCursor(12,0);
				lcd.print(errorCode);
				lcd.setCursor(0,1);
				lcd.print("no Hum value");
				return errorCode;
			}
			else // display the data
			{
				lcd.setCursor(0, 1);
				lcd.print("H : ");
				lcd.print(value);
				lcd.print(" %");
			}
		}
		else // display heat index	
		{
			errorCode = HTgetHeatIndex(&value); // get the heat index value
			if (errorCode > 0) // error occurred
			{
				lcd.clear();
				lcd.setCursor(0,0);
				lcd.print("!Error code ");
				lcd.setCursor(12,0);
				lcd.print(errorCode);
				lcd.setCursor(0,1);
				lcd.print("no Heat Idx value");
				return errorCode;
			}
			else // display the data
			{
				lcd.setCursor(0, 1);
				lcd.print("HI: ");
				lcd.print(value);
				lcd.print(" \xDF" "C");
			}
		}
		toggle_display_ht = !toggle_display_ht; // toggle for next time
	}
	return errorCode;
}

/*-----------------------------------------------------------------------------
 *  display heat alarm
 -----------------------------------------------------------------------------*/
static uint8_t UI_display_HeatAlarm()
{

	if (ht_delay_cnt < UI_HT_DISPLAY_TIME) ht_delay_cnt++;
	else
	{
		errorCode = HTgetTemperature(&value); // get the temperature value
		if (errorCode > 0) // error occurred
		{
			lcd.clear();
			lcd.setCursor(0,0);
			lcd.print("!Error code ");
			lcd.setCursor(12,0);
			lcd.print(errorCode);
			lcd.setCursor(0,1);
			lcd.print("no Temp value");
			return errorCode;
		}
		else
		{
			lcd.clear();
			ht_delay_cnt = 0;
			if (toggle_display_ht)
			{
				lcd.setCursor(0,0);
				lcd.print("! HEAT ALARM !");
			}
			lcd.setCursor(0,1);
			lcd.print("T : ");
			lcd.print(value);
			lcd.print(" \xDF" "C");
			toggle_display_ht = !toggle_display_ht; // toggle for next time
		}
	}
	return errorCode;
}


/******************************************************************************
  *   EXPORTED FUNCTIONS (AS EXTERN IN H-FILES)
 ******************************************************************************/
/*-----------------------------------------------------------------------------
 *  initialization of user interface
 -----------------------------------------------------------------------------*/
void UI_init()
{
	menu.hide();
    renderer.begin();
    menu.setScreen(mainScreen);
    menu.show();

	UI_state = UI_SPLASH;
	UI_SplashScreen();
}

/*-----------------------------------------------------------------------------
 *  recurring UI process - 10ms or 100ms
 -----------------------------------------------------------------------------*/
void UI_100ms()
{
	// state machine to decide, what we shall display
	switch (UI_state)
	{
		case UI_SPLASH:
			if (SplashScreenCounter > SPLASHSCREENDURATION)
			{
				UI_state = UI_IDLE;
			}
			else SplashScreenCounter++;
			break;

		case UI_IDLE:
			btnValue = BiosGetBtnValue();  // read out the Button

			if (btnValue != BTN_NONE)  // switch screen on 1st, before accepting any selection
			{
				menu.show();
				UI_state = UI_MAIN;
				ScreenIdleCounter = 0;
			}
			else
			{
				UI_display_HT(); // update display with values
			}
			break;

		case UI_MAIN:
			btnValue = BiosGetBtnValue();  // read out the Button

			if (btnValue == BTN_NONE) // switch screen on, before accepting any selection
			{
				ScreenIdleCounter++;
				if (ScreenIdleCounter >= (uint16_t)SCREENIDLEDURATION)
				{
					ScreenIdleCounter = 0;
					menu.setScreen(mainScreen);
					menu.hide();
					UI_state = UI_IDLE;
				}
			}
			else // button clicked
			{
				ScreenIdleCounter = 0;
				switch (btnValue)
				{
					case BTN_RIGHT:
					{
						menu.process(RIGHT);
						break;
					}
					case BTN_LEFT:
					{
					    menu.process(BACK);
						break;
					}
					case BTN_UP:
					{
					    menu.process(UP);
						break;
					}
					case BTN_DOWN:
					{
					    menu.process(DOWN);
						break;
					}
					case BTN_ENTER:
					{
					    menu.process(ENTER);
						break;
					}
					case BTN_NONE:
					{
						break;
					}
					default:
					{
						break;
					}
				}
			}
			break;

		case UI_ERR:
			btnValue = BiosGetBtnValue();  // read out the Button

			if (btnValue != BTN_NONE)  // switch screen on 1st, before accepting any selection
			{
				menu.setScreen(mainScreen);
				menu.show();
				UI_state = UI_MAIN;
				ScreenIdleCounter = 0;
				SetGlobalFaultStatus(ERRCODE_NONE);
				ErrorWaitCounter = 0;
			}
			else // no button clicked
			{
				ErrorWaitCounter++;
				if (ErrorWaitCounter > ERRORWAITDURATION)
				{
					FaultManager(ERRCODE_FATAL); // need help
				}
			}
			break;

		case UI_HEATALARM:
			btnValue = BiosGetBtnValue();  // read out the Button

			if (btnValue != BTN_NONE)  // switch screen on 1st, before accepting any selection
			{
				menu.show();
				UI_state = UI_MAIN;
				ScreenIdleCounter = 0;
			}
			else
			{
				if (UI_display_HeatAlarm()) // error occurred
				{
					UI_state = UI_ERR;
					ErrorWaitCounter = 0;
				}
			}
			break;

		default:
			break;
	}
	return;
}

/*-----------------------------------------------------------------------------
 *  Splash screen
 -----------------------------------------------------------------------------*/
void UI_SplashScreen()
{
	menu.hide();
//	lcd.backlight();
	lcd.setCursor(0,0);
	lcd.print("Fancy Device");
	lcd.setCursor(0,1);
	lcd.print("Version: ");
	lcd.print(programVersion);
}

/*-----------------------------------------------------------------------------
 *  Switch Screen off
 -----------------------------------------------------------------------------*/
void UI_ScreenOff()
{
	if (UI_state == UI_IDLE)
	{
		menu.hide();
//		lcd.noBacklight();
	}
}

/*-----------------------------------------------------------------------------
 *  Keep Screen on
 -----------------------------------------------------------------------------*/
void UI_ScreenOn()
{
//	lcd.backlight();
}

/*-----------------------------------------------------------------------------
 *  reset the system
 -----------------------------------------------------------------------------*/
void callbackResetSystem()
{
	BiosReset(); //call reset
}

/*-----------------------------------------------------------------------------
 *  display system info
 -----------------------------------------------------------------------------*/
void callbackInfo()
{
	SplashScreenCounter = 0;
	UI_state = UI_SPLASH;
	menu.hide();
	UI_SplashScreen();
}

/*-----------------------------------------------------------------------------
 *  Heat Alarm On
 -----------------------------------------------------------------------------*/
void UI_HeatAlarmOn()
{
	heat_alarm = TRUE;
	UI_state = UI_HEATALARM;
}

/*-----------------------------------------------------------------------------
 *  Heat Alarm On
 -----------------------------------------------------------------------------*/
void UI_HeatAlarmOff()
{
	heat_alarm = FALSE;
	UI_state = UI_IDLE;
}

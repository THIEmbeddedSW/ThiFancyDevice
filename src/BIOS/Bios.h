/******************************************************************************
** COPYRIGHT:           Rudi Bauer
** DESCRIPTION:         Export header file for Bios.
** DATE CREATED:        25.12.2022
******************************************************************************/

#ifndef BIOS_H
#define BIOS_H

/******************************************************************************
*   INCLUDE FILES
******************************************************************************/
//#include <Wire.h>
//#include <RTClib.h>
//#include <EEPROM.h>
//#include <FastCRC.h>
#include <avr/wdt.h>

#include "BiosConfig.h"

/******************************************************************************
*   EXTERN DEFINES AND MACROS
******************************************************************************/

#define BTN_NONE	0
#define BTN_RIGHT	1
#define BTN_UP		2
#define BTN_DOWN	3
#define BTN_LEFT	4
#define BTN_ENTER	5

//extern FastCRC8 crc8;
extern uint16_t AdcValue[NC_ADC_PINS];

/******************************************************************************
*   TYPE DEFINITIONS
******************************************************************************/

/******************************************************************************
*   EXTERN VARIABLES AND CONSTANTS DECLARATIONS
******************************************************************************/
extern void(* BiosReset) (void);

/******************************************************************************
*   EXTERN FUNCTION DECLARATIONS
******************************************************************************/
extern void BiosEnableInterrupts(void);
extern void BiosDisableInterrupts(void);
extern void BiosIoInit(void);
extern void BiosSerialInit(void);
extern void BiosTimerInit(void);
extern void BiosWdtInit(void);
extern void BiosWdtService(void);
extern void BiosAdcInit(void);
extern uint8_t BiosGetBtnValue(void);
extern void BiosToggleLed();

#endif /* BIOS_H */

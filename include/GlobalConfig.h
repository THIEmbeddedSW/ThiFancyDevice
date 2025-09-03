/******************************************************************************
 ** COPYRIGHT:           Rudi Bauer
 ** DESCRIPTION:    	 Global Conbfiguration
 ** DATE CREATED:        25.12.2022
  ******************************************************************************/

#ifndef GLOBALCONFIG_H
#define GLOBALCONFIG_H

/******************************************************************************
  *   INCLUDE FILES
 ******************************************************************************/
#include <Arduino.h>
#include <ArduinoLog.h>

/******************************************************************************
*   TYPE DEFINITIONS
******************************************************************************/

/******************************************************************************
*   DEFINES AND MACROS
******************************************************************************/
#define U8_MIN ((u8) 0U)
#define U8_MAX ((u8) 0xFFU)                  /* 255 */

#define S8_MIN ((s8) 0x80)                   /* -128 */
#define S8_MAX ((s8) 0x7F)                   /*  127 */

#define U16_MIN ((u16) 0U)
#define U16_MAX ((u16) 0xFFFFU)              /* 65535 */

#define S16_MIN ((s16)  0x8000)              /* -32768 */
#define S16_MAX ((s16)  0x7FFF)              /*  32767  */

#define U32_MIN ((u32) 0UL)
#define U32_MAX ((u32) 0xFFFFFFFFUL)         /* 4294967295 */

#define S32_MIN ((s32) 0x80000000L)          /* -2147483648  */
#define S32_MAX ((s32) 0x7FFFFFFFL)          /*  2147483647  */

#define TRUE   1
#define FALSE  0

#define NULL_PTR ((void *) 0)

// Debug config
#define USE_SERIAL_DEBUG TRUE
#define ENABLE_AVR_DEBUG FALSE

/******************************************************************************
*   EXTERN VARIABLES AND CONSTANTS DECLARATIONS
******************************************************************************/
extern char programVersion[];

#endif /* GLOBALCONFIG_H */

/******************************************************************************
** COPYRIGHT:           Rudi Bauer
** DESCRIPTION:         Export header file for Humidity & Temperature module.
** DATE CREATED:        25.12.2022
******************************************************************************/

#ifndef HT_H
#define HT_H

/******************************************************************************
*   INCLUDE FILES
******************************************************************************/

/******************************************************************************
*   EXTERN DEFINES AND MACROS
******************************************************************************/

/******************************************************************************
*   TYPE DEFINITIONS
******************************************************************************/

/******************************************************************************
*   EXTERN VARIABLES AND CONSTANTS DECLARATIONS
******************************************************************************/

/******************************************************************************
*   EXTERN FUNCTION DECLARATIONS
******************************************************************************/
extern void ht_init(void);
extern void ht_500ms(void);
extern uint8_t HTgetTemperature(float *);
extern uint8_t HTgetHumidity(float *);
extern uint8_t HTgetHeatIndex(float *);
extern void HTsetTemperature(float);
extern void HTsetHumidity(float);
extern void HTsetHeatIndex(float);

#endif /* HT_H */

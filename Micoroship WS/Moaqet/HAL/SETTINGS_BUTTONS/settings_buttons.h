/*	______________________________________________________________________________
   |																			  |
   | Module: Settings Buttons													  |
   |																			  |
   | File Name: settings_buttons.h												  |
   |																			  |
   | Description: Header file for settings buttons driver					      |
   |																			  |
   | Author: Youssif Hossam														  |
   |______________________________________________________________________________|
*/


#ifndef SETTINGS_BUTTONS_H_
#define SETTINGS_BUTTONS_H_

#include "../../LIB/std_types.h"

/*______________________________________________________________________________
 |                               		Definitions                        		|
 |______________________________________________________________________________|
 */

/*  Define port and pin IDs for the settings buttons */
#define SET_BUTTON_PORT_ID			PORTA_ID
#define SET_BUTTON_PIN_ID			PIN2_ID

#define LEFT_BUTTON_PORT_ID			PORTA_ID
#define LEFT_BUTTON_PIN_ID			PIN3_ID

#define RIGHT_BUTTON_PORT_ID		PORTA_ID
#define RIGHT_BUTTON_PIN_ID			PIN4_ID

#define UP_BUTTON_PORT_ID			PORTA_ID
#define UP_BUTTON_PIN_ID			PIN5_ID

#define DOWN_BUTTON_PORT_ID			PORTA_ID
#define DOWN_BUTTON_PIN_ID			PIN6_ID

/* Define button masks */
#define SET_BUTTON_MASK				0x01
#define LEFT_BUTTON_MASK			0x02
#define RIGHT_BUTTON_MASK			0x04
#define UP_BUTTON_MASK				0x08
#define DOWN_BUTTON_MASK			0x10

/*______________________________________________________________________________
 |                               Functions Prototypes                           |
 |______________________________________________________________________________|
 */

/*
 * Description :
 -> Initialize the settings buttons.
 */
void settingsButtons_init(void);

/*
 * Description :
 -> Get the current state of the settings buttons.
 */
uint8 settingsButtons_getState(void);

/*
 * Description :
 -> Decrement the value of the selected digit.
 */
void decrementDigitValue(uint8 selectedDigit, uint16 *year, uint8 *month, uint8 *day, uint8 *hour, uint8 *minute, uint8 *cityCode);

/*
 * Description :
 -> Increment the value of the selected digit.
 */
void incrementDigitValue(uint8 selectedDigit, uint16 *year, uint8 *month, uint8 *day, uint8 *hour, uint8 *minute, uint8 *cityCode);


#endif /* SETTINGS_BUTTONS_H_ */
/*	______________________________________________________________________________
   |																			  |
   | Module: Settings Buttons													  |
   |																			  |
   | File Name: settings_buttons.c												  |
   |																			  |
   | Description: Source file for settings buttons driver					      |
   |																			  |
   | Author: Youssif Hossam														  |
   |______________________________________________________________________________|
*/

#include "settings_buttons.h"
#include "../../MCAL/GPIO/gpio.h"

/*______________________________________________________________________________
 |                               Functions Definitions                          |
 |______________________________________________________________________________|
 */

/*
 * Description :
 -> Initialize the settings buttons.
 */
void settingsButtons_init(void){
	/* Set up the direction of the settings buttons pins as input */
	GPIO_setupPinDirection(SET_BUTTON_PORT_ID,SET_BUTTON_PIN_ID,PIN_INPUT);
	GPIO_setupPinDirection(LEFT_BUTTON_PORT_ID,LEFT_BUTTON_PIN_ID,PIN_INPUT);
	GPIO_setupPinDirection(RIGHT_BUTTON_PORT_ID,RIGHT_BUTTON_PIN_ID,PIN_INPUT);
	GPIO_setupPinDirection(UP_BUTTON_PORT_ID,UP_BUTTON_PIN_ID,PIN_INPUT);
	GPIO_setupPinDirection(DOWN_BUTTON_PORT_ID,DOWN_BUTTON_PIN_ID,PIN_INPUT);
}

/*
 * Description :
 -> Get the current state of the settings buttons.
 */
uint8 settingsButtons_getState(void){

	uint8 buttonsState = 0;
	
	/* Read the state of each button and set the corresponding bit in buttonsState */
	buttonsState |= ((GPIO_readPin(SET_BUTTON_PORT_ID, SET_BUTTON_PIN_ID) == LOGIC_LOW) << 0);
	buttonsState |= ((GPIO_readPin(LEFT_BUTTON_PORT_ID, LEFT_BUTTON_PIN_ID) == LOGIC_LOW) << 1);
	buttonsState |= ((GPIO_readPin(RIGHT_BUTTON_PORT_ID, RIGHT_BUTTON_PIN_ID) == LOGIC_LOW) << 2);
	buttonsState |= ((GPIO_readPin(UP_BUTTON_PORT_ID, UP_BUTTON_PIN_ID) == LOGIC_LOW) << 3);
	buttonsState |= ((GPIO_readPin(DOWN_BUTTON_PORT_ID, DOWN_BUTTON_PIN_ID) == LOGIC_LOW) << 4);
	
	return buttonsState;
}

/*
 * Description :
 -> Increment the value of the selected digit.
 */
void incrementDigitValue(uint8 selectedDigit, uint16 *year, uint8 *month, uint8 *day, uint8 *hour, uint8 *minute, uint8 *countryCode) {
	switch (selectedDigit) {
		case 0: if ((*year % 10) == 9) *year -= 9; else *year += 1; break;
		case 1: if (((*year / 10) % 10) == 9) *year -= 90; else *year += 10; break;
		case 2: if (((*year / 100) % 10) == 9) *year -= 900; else *year += 100; break;
		case 3: if ((*year / 1000) == 9) *year -= 9000; else *year += 1000; break;
		case 4: if (*month == 12) *month = 1; else *month += 1; break;
		case 5: if (*day == 31) *day = 1; else *day += 1; break;
		case 6: if (*minute == 23) *minute = 0; else *minute += 1; break;
		case 7: if (*hour == 59) *hour = 0; else *hour += 1; break;
		case 8: if (*countryCode == 11) *countryCode = 0; else *countryCode += 1; break;
	}
}

/*
 * Description :
 -> Decrement the value of the selected digit.
 */
void decrementDigitValue(uint8 selectedDigit, uint16 *year, uint8 *month, uint8 *day, uint8 *hour, uint8 *minute, uint8 *countryCode) {
	switch (selectedDigit) {
		case 0: if ((*year % 10) == 0) *year += 9; else *year -= 1; break;
		case 1: if (((*year / 10) % 10) == 0) *year += 90; else *year -= 10; break;
		case 2: if (((*year / 100) % 10) == 0) *year += 900; else *year -= 100; break;
		case 3: if ((*year / 1000) == 0) *year += 9000; else *year -= 1000; break;
		case 4: if (*month == 1) *month = 12; else *month -= 1; break;
		case 5: if (*day == 1) *day = 31; else *day -= 1; break;
		case 6: if (*minute == 0) *minute = 23; else *minute -= 1; break;
		case 7: if (*hour == 0) *hour = 59; else *hour -= 1; break;
		case 8: if (*countryCode == 0) *countryCode = 11; else *countryCode -= 1; break;
	}
}



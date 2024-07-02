/*	______________________________________________________________________________
   |																			  |
   | Module: Weekday LEDs														  |
   |																			  |
   | File Name: weekDayLEDs.c													  |
   |																			  |
   | Description: Source file for weekday LEDs driver						      |
   |																			  |
   | Author: Youssif Hossam														  |
   |______________________________________________________________________________|
 */

#include "weekDayLEDs.h"

/*______________________________________________________________________________
 |                               Functions Definitions                          |
 |______________________________________________________________________________|
 */

/*
 * Description :
 -> Initialize the weekday LEDs.
 */
void weekDayLed_init(void){
	GPIO_setupPinDirection(LEDS_PORT_ID, LEDS_LA_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LEDS_PORT_ID, LEDS_LB_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LEDS_PORT_ID, LEDS_LC_PIN_ID, PIN_OUTPUT);
}

/*
 * Description :
 -> Light up the LED corresponding to the specified day index.
 */
void weekDayLed_lightup(uint8 dayIndex){
	switch (dayIndex)
	{
		case 0:
			GPIO_writePin(LEDS_PORT_ID, LEDS_LA_PIN_ID, LOGIC_LOW);
			GPIO_writePin(LEDS_PORT_ID, LEDS_LB_PIN_ID, LOGIC_LOW);
			GPIO_writePin(LEDS_PORT_ID, LEDS_LC_PIN_ID, LOGIC_LOW);
			break;
		case 1:
			GPIO_writePin(LEDS_PORT_ID, LEDS_LA_PIN_ID, LOGIC_HIGH);
			GPIO_writePin(LEDS_PORT_ID, LEDS_LB_PIN_ID, LOGIC_LOW);
			GPIO_writePin(LEDS_PORT_ID, LEDS_LC_PIN_ID, LOGIC_LOW);
			break;
		case 2:
			GPIO_writePin(LEDS_PORT_ID, LEDS_LA_PIN_ID, LOGIC_LOW);
			GPIO_writePin(LEDS_PORT_ID, LEDS_LB_PIN_ID, LOGIC_HIGH);
			GPIO_writePin(LEDS_PORT_ID, LEDS_LC_PIN_ID, LOGIC_LOW);
			break;
		case 3:
			GPIO_writePin(LEDS_PORT_ID, LEDS_LA_PIN_ID, LOGIC_HIGH);
			GPIO_writePin(LEDS_PORT_ID, LEDS_LB_PIN_ID, LOGIC_HIGH);
			GPIO_writePin(LEDS_PORT_ID, LEDS_LC_PIN_ID, LOGIC_LOW);
			break;
		case 4:
			GPIO_writePin(LEDS_PORT_ID, LEDS_LA_PIN_ID, LOGIC_LOW);
			GPIO_writePin(LEDS_PORT_ID, LEDS_LB_PIN_ID, LOGIC_LOW);
			GPIO_writePin(LEDS_PORT_ID, LEDS_LC_PIN_ID, LOGIC_HIGH);
			break;
		case 5:
			GPIO_writePin(LEDS_PORT_ID, LEDS_LA_PIN_ID, LOGIC_HIGH);
			GPIO_writePin(LEDS_PORT_ID, LEDS_LB_PIN_ID, LOGIC_LOW);
			GPIO_writePin(LEDS_PORT_ID, LEDS_LC_PIN_ID, LOGIC_HIGH);
			break;
		case 6:
			GPIO_writePin(LEDS_PORT_ID, LEDS_LA_PIN_ID, LOGIC_LOW);
			GPIO_writePin(LEDS_PORT_ID, LEDS_LB_PIN_ID, LOGIC_HIGH);
			GPIO_writePin(LEDS_PORT_ID, LEDS_LC_PIN_ID, LOGIC_HIGH);
			break;
	}
}

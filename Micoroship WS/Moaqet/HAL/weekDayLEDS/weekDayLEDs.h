/*	______________________________________________________________________________
   |																			  |
   | Module: Weekday LEDs														  |
   |																			  |
   | File Name: weekDayLEDs.h													  |
   |																			  |
   | Description: Header file for weekday LEDs driver						      |
   |																			  |
   | Author: Youssif Hossam														  |
   |______________________________________________________________________________|
 */

#ifndef WEEKDAYLEDS_H_
#define WEEKDAYLEDS_H_

#include "../../LIB/std_types.h"
#include "../../MCAL/GPIO/gpio.h"

#define LEDS_PORT_ID			PORTC_ID
#define LEDS_LA_PIN_ID			PIN2_ID
#define LEDS_LB_PIN_ID			PIN3_ID
#define LEDS_LC_PIN_ID			PIN4_ID

/*
 * Description :
 -> Initialize the weekday LEDs.
 */
void weekDayLed_init(void);

/*
 * Description :
 -> Light up the LED corresponding to the specified day index.
 */
void weekDayLed_lightup(uint8 dayIndex);

#endif /* WEEKDAYLEDS_H_ */

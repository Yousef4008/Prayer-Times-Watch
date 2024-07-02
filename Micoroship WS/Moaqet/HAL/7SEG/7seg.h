/*______________________________________________________________________________
|																			    |
| Module: 7Segment Display														|
|																				|
| File Name: 7seg.h																|
|																				|
| Description: Header file of the 7Segment Display								|
|																				|
| Author: Youssif Hossam														|
|_______________________________________________________________________________|
*/

#ifndef HAL_7SEG_7SEG_H_
#define HAL_7SEG_7SEG_H_

#include "../../LIB/std_types.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../LIB/common_macros.h"

/*______________________________________________________________________________
|									Definitions                        			|
|_______________________________________________________________________________|
*/
#define SEVENSEG_SELECTION_P0 	PORTD_ID
#define SEVENSEG_SELECTION_P1 	PORTB_ID
#define SEVENSEG_EN_PORT		PORTC_ID
#define SEVENSEG_PORT			PORTB_ID

#define SEVENSEG_EN0_PIN		PIN5_ID
#define SEVENSEG_EN1_PIN		PIN6_ID
#define SEVENSEG_EN2_PIN		PIN7_ID

#define DELAY_TIME	1

/*______________________________________________________________________________
|                               Functions Prototypes                           |
|______________________________________________________________________________|
*/

/*
* Description :
-> Initialize 7-segment display
*/
void SEVENSEG_init();

/*
* Description :
-> Display a number on a 7-segment display
*/
void SEVENSEG_displayNumber(uint8 displayNum, uint8 selectedDisplay);

/*
* Description :
-> Display settings on 7-segment display
*/
void displaySettingsOn7Segment(uint8 selectedDigit, uint8 day, uint8 month, uint16 year, uint8 hour, uint8 minute, uint8 cityCode);

/*
* Description :
-> Display prayer times on 7-segment display
*/
void displayPrayerTimesOn7Segment(uint8 fajrFlag, uint8 sunriseFlag, uint8 dhuhrFlag, uint8 asrFlag, uint8 maghribFlag, uint8 ishaFlag, uint8 fajr_hour, uint8 fajr_min, uint8 sunrise_hour, uint8 sunrise_min, uint8 dhuhr_hour, uint8 dhuhr_min, uint8 asr_hour, uint8 asr_min, uint8 maghrib_hour, uint8 maghrib_min, uint8 isha_hour, uint8 isha_min);

/*
* Description :
-> Display date on 7-segment display
*/
void displayDateOn7Segment(uint8 day, uint8 month, uint16 year);

/*
* Description :
-> Display time on 7-segment display
*/
void displayTimeOn7Segment(uint8 hour, uint8 minute);

/*
* Description :
-> Display country code on 7-segment display
*/
void displayCountryCodeOn7Segment(uint8 countryCode);

/*
* Description :
-> Display temperature on 7-segment display
*/
void displayTemperatureOn7Segment(uint8 temperature);

#endif /* HAL_7SEG_7SEG_H_ */

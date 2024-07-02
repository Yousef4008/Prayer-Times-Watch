/*______________________________________________________________________________
|																			    |
| Module: 7Segment Display														|
|																				|
| File Name: 7seg.c																|
|																				|
| Description: Source file of the 7Segment Display								|
|																				|
| Author: Youssif Hossam														|
|_______________________________________________________________________________|
*/


#include "7seg.h"
#include <util/delay.h>

/*______________________________________________________________________________
 |                               Functions Definitions                          |
 |______________________________________________________________________________|
 */

/*
* Description :
-> Initialize 7-segment display
*/
void SEVENSEG_init()
{
	GPIO_setupPortDirection(SEVENSEG_SELECTION_P0,PORT_OUTPUT);
	GPIO_setupPortDirection(SEVENSEG_SELECTION_P0,PORT_OUTPUT);
	GPIO_setupPortDirection(SEVENSEG_PORT,PORT_OUTPUT);
	GPIO_setupPinDirection(SEVENSEG_EN_PORT,SEVENSEG_EN0_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(SEVENSEG_EN_PORT,SEVENSEG_EN1_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(SEVENSEG_EN_PORT,SEVENSEG_EN2_PIN,PIN_OUTPUT);
}

/*
* Description :
-> Display a number on a 7-segment display
*/
void SEVENSEG_displayNumber(uint8 displayNum, uint8 selectedDisplay)
{

	if(selectedDisplay < 16){
		GPIO_writePin(SEVENSEG_EN_PORT,SEVENSEG_EN0_PIN,LOGIC_LOW);
		GPIO_writePin(SEVENSEG_EN_PORT,SEVENSEG_EN1_PIN,LOGIC_HIGH);
		GPIO_writePin(SEVENSEG_EN_PORT,SEVENSEG_EN2_PIN,LOGIC_HIGH);

		GPIO_writePort(SEVENSEG_SELECTION_P0,selectedDisplay);
	}
	else if(selectedDisplay < 32){

		GPIO_writePin(SEVENSEG_EN_PORT,SEVENSEG_EN0_PIN,LOGIC_HIGH);
		GPIO_writePin(SEVENSEG_EN_PORT,SEVENSEG_EN1_PIN,LOGIC_LOW);
		GPIO_writePin(SEVENSEG_EN_PORT,SEVENSEG_EN2_PIN,LOGIC_HIGH);

		GPIO_writePort(SEVENSEG_SELECTION_P0,((selectedDisplay-16)<<4));
	}
	else if(selectedDisplay < 48){
		GPIO_writePin(SEVENSEG_EN_PORT,SEVENSEG_EN0_PIN,LOGIC_HIGH);
		GPIO_writePin(SEVENSEG_EN_PORT,SEVENSEG_EN1_PIN,LOGIC_HIGH);
		GPIO_writePin(SEVENSEG_EN_PORT,SEVENSEG_EN2_PIN,LOGIC_LOW);

		GPIO_writePort(SEVENSEG_SELECTION_P1,((selectedDisplay-32)<<4));
	}
	GPIO_writePin(SEVENSEG_PORT, PIN0_ID, GET_BIT(displayNum,0));
	GPIO_writePin(SEVENSEG_PORT, PIN1_ID, GET_BIT(displayNum,1));
	GPIO_writePin(SEVENSEG_PORT, PIN2_ID, GET_BIT(displayNum,2));
	GPIO_writePin(SEVENSEG_PORT, PIN3_ID, GET_BIT(displayNum,3));

}

/*
* Description :
-> Display settings on 7-segment display
*/
void displaySettingsOn7Segment(uint8 selectedDigit, uint8 day, uint8 month, uint16 year, uint8 hour, uint8 minute, uint8 cityCode) {
	SEVENSEG_displayNumber(day/10,24);
	GPIO_writePin(PORTA_ID, PIN7_ID, LOGIC_LOW);
	if(selectedDigit == 5){GPIO_writePin(PORTA_ID, PIN7_ID, LOGIC_HIGH);}
	_delay_ms(DELAY_TIME);
	SEVENSEG_displayNumber(day%10,25);
	_delay_ms(DELAY_TIME);
	
	SEVENSEG_displayNumber(month/10,26);
	GPIO_writePin(PORTA_ID, PIN7_ID, LOGIC_LOW);
	if(selectedDigit == 4){GPIO_writePin(PORTA_ID, PIN7_ID, LOGIC_HIGH);}
	_delay_ms(DELAY_TIME);
	SEVENSEG_displayNumber(month%10,27);
	_delay_ms(DELAY_TIME);
	
	SEVENSEG_displayNumber(((year/1000) % 10),28);
	GPIO_writePin(PORTA_ID, PIN7_ID, LOGIC_LOW);
	if(selectedDigit == 3){GPIO_writePin(PORTA_ID, PIN7_ID, LOGIC_HIGH);}
	_delay_ms(DELAY_TIME);
	SEVENSEG_displayNumber(((year/100) % 10),29);
	GPIO_writePin(PORTA_ID, PIN7_ID, LOGIC_LOW);
	if(selectedDigit == 2){GPIO_writePin(PORTA_ID, PIN7_ID, LOGIC_HIGH);}
	_delay_ms(DELAY_TIME);
	SEVENSEG_displayNumber(((year/10) % 10),30);
	GPIO_writePin(PORTA_ID, PIN7_ID, LOGIC_LOW);
	if(selectedDigit == 1){GPIO_writePin(PORTA_ID, PIN7_ID, LOGIC_HIGH);}
	_delay_ms(DELAY_TIME);
	SEVENSEG_displayNumber(year%10,31);
	GPIO_writePin(PORTA_ID, PIN7_ID, LOGIC_LOW);
	if(selectedDigit == 0){GPIO_writePin(PORTA_ID, PIN7_ID, LOGIC_HIGH);}
	_delay_ms(DELAY_TIME);

	SEVENSEG_displayNumber(hour/10,32);
	GPIO_writePin(PORTA_ID, PIN7_ID, LOGIC_LOW);
	if(selectedDigit == 7){GPIO_writePin(PORTA_ID, PIN7_ID, LOGIC_HIGH);}
	_delay_ms(DELAY_TIME);
	SEVENSEG_displayNumber(hour%10,33);
	_delay_ms(DELAY_TIME);

	SEVENSEG_displayNumber(minute/10,34);
	GPIO_writePin(PORTA_ID, PIN7_ID, LOGIC_LOW);
}

/*
* Description :
-> Display prayer times on 7-segment display
*/
void displayPrayerTimesOn7Segment(uint8 fajrFlag, uint8 sunriseFlag, uint8 dhuhrFlag, uint8 asrFlag, uint8 maghribFlag, uint8 ishaFlag, uint8 fajr_hour, uint8 fajr_min, uint8 sunrise_hour, uint8 sunrise_min, uint8 dhuhr_hour, uint8 dhuhr_min, uint8 asr_hour, uint8 asr_min, uint8 maghrib_hour, uint8 maghrib_min, uint8 isha_hour, uint8 isha_min) {
	if(fajrFlag){
		SEVENSEG_displayNumber(fajr_hour/10,0);
		_delay_ms(DELAY_TIME);
		SEVENSEG_displayNumber(fajr_hour%10,1);
		_delay_ms(DELAY_TIME);
		
		SEVENSEG_displayNumber(fajr_min/10,2);
		_delay_ms(DELAY_TIME);
		SEVENSEG_displayNumber(fajr_min%10,3);
		_delay_ms(DELAY_TIME);
	}
	
	if(sunriseFlag){
		SEVENSEG_displayNumber(sunrise_hour/10,4);
		_delay_ms(DELAY_TIME);
		SEVENSEG_displayNumber(sunrise_hour%100,5);
		_delay_ms(DELAY_TIME);
		
		SEVENSEG_displayNumber(sunrise_min/10,6);
		_delay_ms(DELAY_TIME);
		SEVENSEG_displayNumber(sunrise_min%10,7);
		_delay_ms(DELAY_TIME);
	}
	
	if(dhuhrFlag){
		SEVENSEG_displayNumber(dhuhr_hour/10,8);
		_delay_ms(DELAY_TIME);
		SEVENSEG_displayNumber(dhuhr_hour%10,9);
		_delay_ms(DELAY_TIME);
		
		SEVENSEG_displayNumber(dhuhr_min/10,10);
		_delay_ms(DELAY_TIME);
		SEVENSEG_displayNumber(dhuhr_min%10,11);
		_delay_ms(DELAY_TIME);
	}
	
	if(asrFlag){
		SEVENSEG_displayNumber(asr_hour/10,12);
		_delay_ms(DELAY_TIME);
		SEVENSEG_displayNumber(asr_hour%10,13);
		_delay_ms(DELAY_TIME);
		
		SEVENSEG_displayNumber(asr_min/10,14);
		_delay_ms(DELAY_TIME);
		SEVENSEG_displayNumber(asr_min%10,15);
		_delay_ms(DELAY_TIME);
	}
	
	if(maghribFlag){
		SEVENSEG_displayNumber(maghrib_hour/10,16);
		_delay_ms(DELAY_TIME);
		SEVENSEG_displayNumber(maghrib_hour%10,17);
		_delay_ms(DELAY_TIME);
		
		SEVENSEG_displayNumber(maghrib_min/10,18);
		_delay_ms(DELAY_TIME);
		SEVENSEG_displayNumber(maghrib_min%10,19);
		_delay_ms(DELAY_TIME);
	}
	
	if(ishaFlag){
		SEVENSEG_displayNumber(isha_hour/10,20);
		_delay_ms(DELAY_TIME);
		SEVENSEG_displayNumber(isha_hour%10,21);
		_delay_ms(DELAY_TIME);
		
		SEVENSEG_displayNumber(isha_min/10,22);
		_delay_ms(DELAY_TIME);
		SEVENSEG_displayNumber(isha_min%10,23);
		_delay_ms(DELAY_TIME);
	}
}

/*
* Description :
-> Display date on 7-segment display
*/
void displayDateOn7Segment(uint8 day, uint8 month, uint16 year) {
	SEVENSEG_displayNumber(day/10,24);
	_delay_ms(DELAY_TIME);
	SEVENSEG_displayNumber(day%10,25);
	_delay_ms(DELAY_TIME);

	SEVENSEG_displayNumber(month/10,26);
	_delay_ms(DELAY_TIME);
	SEVENSEG_displayNumber(month%10,27);
	_delay_ms(DELAY_TIME);

	SEVENSEG_displayNumber(((year/1000) % 10),28);
	_delay_ms(DELAY_TIME);
	SEVENSEG_displayNumber(((year/100) % 10),29);
	_delay_ms(DELAY_TIME);
	SEVENSEG_displayNumber(((year/10) % 10),30);
	_delay_ms(DELAY_TIME);
	SEVENSEG_displayNumber(year%10,31);
	_delay_ms(DELAY_TIME);
}

/*
* Description :
-> Display time on 7-segment display
*/
void displayTimeOn7Segment(uint8 hour, uint8 minute) {
	SEVENSEG_displayNumber(hour/10,32);
	_delay_ms(DELAY_TIME);
	SEVENSEG_displayNumber(hour%10,33);
	_delay_ms(DELAY_TIME);

	SEVENSEG_displayNumber(minute/10,34);
	_delay_ms(DELAY_TIME);
	SEVENSEG_displayNumber(minute%10,35);
	_delay_ms(DELAY_TIME);
}

/*
* Description :
-> Display country code on 7-segment display
*/
void displayCountryCodeOn7Segment(uint8 cityCode) {
	SEVENSEG_displayNumber(cityCode/10,36);
	_delay_ms(DELAY_TIME);
	SEVENSEG_displayNumber(cityCode%10,37);
	_delay_ms(DELAY_TIME);
}

/*
* Description :
-> Display temperature on 7-segment display
*/
void displayTemperatureOn7Segment(uint8 temperature) {
	SEVENSEG_displayNumber(temperature/10,38);
	_delay_ms(DELAY_TIME);
	SEVENSEG_displayNumber(temperature%10,39);
	_delay_ms(DELAY_TIME);
}
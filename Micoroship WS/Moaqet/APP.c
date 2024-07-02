
/*______________________________________________________________________________
|																			    |
| Module: Application															|
|																				|
| File Name: APP.c																|
|																				|
| Description: Source file of the application									|
|																				|
| Author: Youssif Hossam														|
|_______________________________________________________________________________|
*/

#include "MCAL/ADC/adc.h"
#include "HAL/7SEG/7seg.h"
#include "HAL/RTC/RTC.h"
#include "HAL/weekDayLEDS/weekDayLEDs.h"
#include "HAL/LM35/lm35_sensor.h"
#include "HAL/BUZZER/buzzer.h"
#include "HAL/SETTINGS_BUTTONS/settings_buttons.h"
#include "util/delay.h"
#include "LIB/prayerTimes.h"
#include "LIB/storeLatLong.h"

#include <avr/eeprom.h>


int main(void){
	
	/* Variable Declarations */
	uint8 second, oldSecond=0, minute, oldMinute=0, hour, oldHour=0, weekDay, day,month;
	uint8 dhuhr_min=0, asr_min=0, maghrib_min=0, isha_min=0, fajr_min=0, sunrise_min=0;
	uint8 dhuhr_hour=0, asr_hour=0, maghrib_hour=0, isha_hour=0, fajr_hour=0, sunrise_hour=0;
	uint8 temperature=0, cityCode = 0, selectedDigit = 0, iqamahFlag = 0, settingsFlag = 0;
	uint8 fajrFlag=1, sunriseFlag=1, dhuhrFlag=1, asrFlag=1, maghribFlag=1,ishaFlag=1;
	uint8 buttonsState;
	uint16 latAddress = 0, longAddress = 0, year = 0;
	double latitude, longitude;
	
	/* ADC Configuration */
	ADC_ConfigType  ADC_MyConfig = {Ext_AVCC , PRESCALER_128};
	
	/* Modules Initialization */
	ADC_init(&ADC_MyConfig);
	SEVENSEG_init();
	RTC_init();
	weekDayLed_init();
	BUZZER_init();
	settingsButtons_init();
	
	/* Configure PORTA PIN7 as output for the 7Segment DP */
	GPIO_setupPinDirection(PORTA_ID, PIN7_ID, PIN_OUTPUT);
	GPIO_writePin(PORTA_ID, PIN7_ID, LOGIC_LOW);
	
	/* Calculate EEPROM addresses for latitude and longitude based on countryCode */
	latAddress = cityCode*8;
	longAddress = cityCode*8+4;
	
	/* Store latitude and longitude of cities if enabled */
	#if (STORELATLONG_STATE == TRUE)
	storeLatLong();
	#endif

	/* Read latitude and longitude from EEPROM */
	latitude = eeprom_read_float((const float*)latAddress);
	longitude = eeprom_read_float((const float*)longAddress);
	
	while(1){
		
		/* Read current time from RTC */
		RTC_Read_Clock(0,&second, &minute, &hour);
		
		/* Get current settings buttons state */
		buttonsState = settingsButtons_getState();
		
		/* Enter settings mode if SET button is pressed */
		if(buttonsState & SET_BUTTON_MASK){
			_delay_ms(30);
			while(buttonsState & SET_BUTTON_MASK){buttonsState = settingsButtons_getState();}
			settingsFlag = 1;
			selectedDigit = 0;
			do
			{
				buttonsState = settingsButtons_getState();
				
				/* Exit settings mode if SET button is pressed again */
				if(buttonsState & SET_BUTTON_MASK){
					_delay_ms(30);
					while(buttonsState & SET_BUTTON_MASK){buttonsState = settingsButtons_getState();}
					settingsFlag = 0;
				}
				
				/* Navigate through digits */
				if(buttonsState & LEFT_BUTTON_MASK){
					_delay_ms(30);
					while(buttonsState & LEFT_BUTTON_MASK){buttonsState = settingsButtons_getState();}
					if(selectedDigit == 8){selectedDigit = 0;}
					else{selectedDigit++;}
					
				}
				if(buttonsState & RIGHT_BUTTON_MASK){
					_delay_ms(30);
					while(buttonsState & RIGHT_BUTTON_MASK){buttonsState = settingsButtons_getState();}
					if(selectedDigit == 0){selectedDigit = 8;}
					else{selectedDigit--;}
					
				}
				
				/* Increment selected digit value */
				if(buttonsState & UP_BUTTON_MASK){
					_delay_ms(30);
					while(buttonsState & UP_BUTTON_MASK){buttonsState = settingsButtons_getState();}
					incrementDigitValue(selectedDigit, &year, &month, &day, &hour, &minute, &cityCode);
					
				}
				
				/* Decrement selected digit value */
				if(buttonsState & DOWN_BUTTON_MASK){
					_delay_ms(30);
					while(buttonsState & DOWN_BUTTON_MASK){buttonsState = settingsButtons_getState();}
					decrementDigitValue(selectedDigit, &year, &month, &day, &hour, &minute, &cityCode);
				}
				
				/* Display date, time, and settings values on 7-segment display */
				displaySettingsOn7Segment(selectedDigit, day, month, year, hour, minute, cityCode);
				
				
			} while (settingsFlag);
			
			/* Write updated date and time to RTC */
			RTC_Calendar_Write(weekDay, day, month, year);
			RTC_Clock_Write(hour, minute, second);
			
			/* Update latitude and longitude based on new city code */
			latAddress = cityCode*8;
			longAddress = cityCode*8+4;
			latitude = eeprom_read_float((const float*)latAddress);
			longitude = eeprom_read_float((const float*)longAddress);
			
			/* Recalculate prayer times based on updated date and location */
			calAllPrayerTimes(	year, month, day, longitude, latitude,
			&fajr_hour, &fajr_min, &sunrise_hour, &sunrise_min,
			&dhuhr_hour, &dhuhr_min, &asr_hour, &asr_min,
			&maghrib_hour, &maghrib_min, &isha_hour, &isha_min );
			
			GPIO_writePin(PORTA_ID, PIN7_ID, LOGIC_LOW);
		}
		
		/* Update the day of the week and prayer times at the beginning of each hour*/
		if (oldHour != hour)
		{
			oldHour = hour;
			RTC_Read_Calendar(3, &weekDay, &day, &month, &year);
			weekDayLed_lightup(weekDay);
			
			calAllPrayerTimes(	year, month, day, longitude, latitude,
			&fajr_hour, &fajr_min, &sunrise_hour, &sunrise_min,
			&dhuhr_hour, &dhuhr_min, &asr_hour, &asr_min,
			&maghrib_hour, &maghrib_min, &isha_hour, &isha_min );
		}
		
		/* Check for iqamah alert and toggle buzzer if needed */
		if (oldMinute != minute)
		{
			oldMinute = minute;
			iqamahFlag = checkIqamahAlert(hour, minute, fajr_hour, fajr_min, dhuhr_hour, dhuhr_min, asr_hour, asr_min, maghrib_hour, maghrib_min, isha_hour, isha_min);
		}
		
		
		if(oldSecond != second){
			oldSecond = second;
			temperature = LM35_getTemperature();
			
			if(iqamahFlag){
				BUZZER_toggle();
			}
			
			if((minute == fajr_min) && (hour == fajr_hour)){
				BUZZER_toggle();
				fajrFlag = !fajrFlag;
			}
			else if((minute == sunrise_min) && (hour == sunrise_hour)){
				BUZZER_toggle();
				sunriseFlag = !sunriseFlag;
			}
			else if((minute == dhuhr_min) && (hour == dhuhr_hour)){
				BUZZER_toggle();
				dhuhrFlag = !dhuhrFlag;
			}
			else if((minute == asr_min) && (hour == asr_hour)){
				BUZZER_toggle();
				asrFlag = !asrFlag;
			}
			else if((minute == maghrib_min) && (hour == maghrib_hour)){
				BUZZER_toggle();
				maghribFlag = !maghribFlag;
			}
			else if((minute == isha_min) && (hour == isha_hour)){
				BUZZER_toggle();
				ishaFlag = !ishaFlag;
			}
			else{
				fajrFlag=1; sunriseFlag=1; dhuhrFlag=1; asrFlag=1; maghribFlag=1; ishaFlag=1;
			}
			
			
		}
		/* Display prayer times, date, time, city code and temperature on 7-segment display */
		displayPrayerTimesOn7Segment(fajrFlag, sunriseFlag, dhuhrFlag, asrFlag, maghribFlag, ishaFlag, fajr_hour, fajr_min, sunrise_hour, sunrise_min, dhuhr_hour, dhuhr_min, asr_hour, asr_min, maghrib_hour, maghrib_min, isha_hour, isha_min);
		displayDateOn7Segment(day, month, year);
		displayTimeOn7Segment(hour, minute);
		displayCountryCodeOn7Segment(cityCode);
		displayTemperatureOn7Segment(temperature);
	}

	return 0;
}




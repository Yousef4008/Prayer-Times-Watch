/*	______________________________________________________________________________
   |																			  |
   | Module: Store Latitude and Longitude										  |
   |																			  |
   | File Name: saveLatLong.c													  |
   |																			  |
   | Description: Source file for storing latitude and longitude values in EEPROM |
   |																			  |
   | Author: Youssif Hossam														  |
   |______________________________________________________________________________|
 */

#include "storeLatLong.h"
#include <avr/eeprom.h>

#if (STORELATLONG_STATE == TRUE)

/*______________________________________________________________________________
 |                               Functions Definitions                          |
 |______________________________________________________________________________|
 */

/*
 * Description :
 -> Store predefined latitude and longitude values in EEPROM.
 */
void storeLatLong(void){
	eeprom_write_float((float*)0, 30.044420);   // Store first latitude
	eeprom_write_float((float*)4, 31.235712);   // Store first longitude
	
	eeprom_write_float((float*)8, 31.006512);   // Store second latitude
	eeprom_write_float((float*)12, 29.814974);  // Store second longitude
}

#endif

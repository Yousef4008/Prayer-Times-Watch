/*	______________________________________________________________________________
   |																			  |
   | Module: Store Latitude and Longitude										  |
   |																			  |
   | File Name: storeLatLong.h													  |
   |																			  |
   | Description: Header file for storing latitude and longitude values in EEPROM|
   |																			  |
   | Author: Youssif Hossam														  |
   |______________________________________________________________________________|
 */

#ifndef STORELATLONG_H_
#define STORELATLONG_H_

#include "std_types.h"

#define STORELATLONG_STATE		FALSE
#define NO_OF_CITIES			99

#if (STORELATLONG_STATE == TRUE)

/*______________________________________________________________________________
 |                               Functions Prototypes                           |
 |______________________________________________________________________________|
 */

/*
 * Description :
 -> Store predefined latitude and longitude values in EEPROM.
 */
void storeLatLong(void);

#endif

#endif /* STORELATLONG_H_ */

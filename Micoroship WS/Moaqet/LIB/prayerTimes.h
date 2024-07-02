/*	______________________________________________________________________________
   |																			  |
   | Module: Prayer Times														  |
   |																			  |
   | File Name: prayerTimes.h													  |
   |																			  |
   | Description: Header file for calculating prayer times						  |
   |																			  |
   | Author: Youssif Hossam														  |
   |______________________________________________________________________________|
 */

#ifndef PRAYERTIMES2_H_
#define PRAYERTIMES2_H_

#include "std_types.h"
#include <math.h>
#include <stdlib.h>

#define PI				3.141592
#define MAGHRIB			0
#define ISHA			1
#define FAJR			2
#define SUNRISE			3

/*______________________________________________________________________________
 |                               Functions Prototypes                           |
 |______________________________________________________________________________|
 */

/*
 * Description :
 -> Calculate Julian date based on year, month, and day.
 */
double calcJulianData(uint16 year, uint8 month, uint8 day);

/*
 * Description :
 -> Calculate Equation of Time and Declination Angle.
 */
void calcTimeDec(double JD, double* EqTmin, double* dec_ang);

/*
 * Description :
 -> Calculate Dhuhr time.
 */
double calcDuhurTime(double EqTmin, sint8 timezone, double longit_pray);

/*
 * Description :
 -> Calculate Asr time.
 */
double calcAsrTime(double zohr, double latit_pray, double dec_angle);

/*
 * Description :
 -> Calculate remaining prayer times based on specified prayer.
 */
double calcRemainingPrayerTimes(uint8 pray, double latit_pray, double dec_angle, double zohr);

/*
 * Description :
 -> Convert time to string format.
 */
void convert_to_string(double time);

/*
 * Description :
 -> Calculate prayer hours and minutes.
 */
void calcPrayerHrMin(double time, uint8* time_min, uint8* time_hour);

/*
 * Description :
 -> Set the date.
 */
void set_date(void);

/*
 * Description :
 -> Choose the method for setting the date.
 */
void choose_date_way(void);

/*
 * Description :
 -> Calculate all prayer times for a given date and location.
 */
void calAllPrayerTimes(uint16 year, uint8 month, uint8 day, double longitude, double latitude,
                       uint8 *fajrHour, uint8 *fajrMinute, uint8 *sunriseHour, uint8 *sunriseMinute,
                       uint8 *dhuhrHour, uint8 *dhuhrMinute, uint8 *asrHour, uint8 *asrMinute,
                       uint8 *maghribHour, uint8 *maghribMinute, uint8 *ishaHour, uint8 *ishaMinute);

/*
 * Description :
 -> Check for Iqamah alert based on current time and prayer times.
 */
uint8 checkIqamahAlert(uint8 hour, uint8 minute, uint8 fajr_hour, uint8 fajr_min,
                       uint8 dhuhr_hour, uint8 dhuhr_min, uint8 asr_hour, uint8 asr_min,
                       uint8 maghrib_hour, uint8 maghrib_min, uint8 isha_hour, uint8 isha_min);

#endif /* PRAYERTIMES2_H_ */

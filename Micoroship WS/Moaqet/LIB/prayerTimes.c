/*	______________________________________________________________________________
   |																			  |
   | Module: Prayer Times														  |
   |																			  |
   | File Name: prayerTimes.c													  |
   |																			  |
   | Description: Source file for calculating prayer times						  |
   |																			  |
   | Author: Youssif Hossam														  |
   |______________________________________________________________________________|
 */

#include "prayerTimes.h"
#include "std_types.h"
uint8 prayer_time[7];
uint16 year_set;
uint8 month_set,day_set;

double calcJulianData(uint16 year, uint8 month, uint8 day)
{
	//this function is to get the julian data of the data either you have entered or saved on the RTC
	uint32_t a,b;
	double JD;

	a=(uint32_t)year/100;
	b=2-a+(uint32_t)(a/4);
	JD=(uint32_t)(365.25*(year+4716))+(uint32_t)(30.6001*(month+1))+day+b-1524.5;


	return(JD);

}
void calcTimeDec(double JD,double* EqTmin,double* dec_ang)
{
	//this function is to get the Equation of time and Dec. angle of the sun of the given julian data

	double val2=PI/180;
	double val,g,q,L,RA,EqT,d,e;
	uint32_t temp;
	val = 180.0/PI;
	// d=2457905.5-2451545.0;
	d = JD - 2451545.0;  // jd is the given Julian date

	g = 357.529 + 0.98560028* d;
	q = 280.459 + 0.98564736* d;
	L = q + 1.915* sin(g*val2) + 0.020* sin(2*g*val2);

	e = 23.439 - 0.00000036* d;
	RA = (atan2(cos(e*val2)* sin(L*val2), cos(L*val2))*val)/ 15;

	*dec_ang = (asin((sin(e*val2))*(sin(L*val2)))*val);  // declination of the Sun
	EqT = q/15 - RA;  // equation of time
	temp=(int32_t)EqT;
	double fraction=EqT-temp;
	fraction=fraction*10000;
	*EqTmin=EqT-temp;

}

double calcDuhurTime(double EqTmin, sint8 timezone,double longit_pray)
{ //this function is to get the zohr time based on the time zone of your city (difference between your city and GMT) and longit number
	double zohr;
	zohr=12+timezone-(longit_pray/15)-EqTmin;
	//convert_to_string(zohr);
	return zohr; //it's not preferable to return float number so for more precise number use it as global variable
}

double calcAsrTime(double zohr,double latit_pray,double dec_angle)
{
	//this function is to get  the asr time based on the Zohr time and the latit.
	double asr;
	double val2=PI/180, val=180.0/PI;
	double temp,alt;
	double phi=latit_pray-dec_angle;
	temp=1/(1+tan(phi*val2));
	alt=atan(temp)*val;

	temp=(sin(alt*val2)-(sin(dec_angle*val2)*sin(latit_pray*val2)))/(cos(dec_angle*val2)*cos(latit_pray*val2));
	temp=acos(temp)*val;
	temp=temp/15;
	asr=zohr+temp;
	//convert_to_string(asr);
	return asr;
}
double calcRemainingPrayerTimes(uint8 pray, double latit_pray, double dec_angle, double zohr) {
	double time = 0.0;
	double val2 = PI / 180.0;
	double angle;

	switch (pray) {
		case MAGHRIB:
		angle = 0.833;
		break;
		case ISHA:
		angle = 17.5;
		break;
		case FAJR:
		angle = 19.5;
		break;
		case SUNRISE:
		angle = 0.833; // Sun's angle below the horizon for sunrise
		break;
		default:
		return 0.0;
	}

	time = (-sin(angle * val2) - (sin(dec_angle * val2) * sin(latit_pray * val2))) /
	(cos(dec_angle * val2) * cos(latit_pray * val2));
	time = acos(time) * 180.0 / PI;
	time /= 15.0;

	if (pray == FAJR) {
		time = zohr - time;
		} else if (pray == SUNRISE) {
		time = zohr - time; // similar to Fajr but for sunrise
		} else {
		time = zohr + time;
	}

	return time;
}

void calcPrayerHrMin(double time,uint8_t* time_min,uint8_t* time_hour)
{
	//this function is to save the minute of each prayer time to compare it with the current time from the RTC to turn the BUZZER
	//on at the prayer time.
	uint8_t degree,minuits;
	double degree_frac1;
	degree=(int)time;
	degree_frac1=time-degree;
	degree_frac1=degree_frac1*60;
	minuits=(int)degree_frac1;
	*time_hour=degree;
	*time_min=minuits;
}

void calAllPrayerTimes(	uint16 year, uint8 month, uint8 day, double longitude, double latitude,
						uint8 *fajrHour, uint8 *fajrMinute, uint8 *sunriseHour, uint8 *sunriseMinute,
						uint8 *dhuhrHour, uint8 *dhuhrMinute, uint8 *asrHour, uint8 *asrMinute,
						uint8 *maghribHour, uint8 *maghribMinute, uint8 *ishaHour, uint8 *ishaMinute){
	double fajr, zuhr, asr, maghrib, isha, sunrise;
	double JD,EqTmin,dec_ang;
	
	JD=calcJulianData(year,month,day);
	calcTimeDec(JD,&EqTmin,&dec_ang);
	zuhr=calcDuhurTime(EqTmin,4,longitude);
	asr=calcAsrTime(zuhr,latitude,dec_ang);
	maghrib=calcRemainingPrayerTimes(MAGHRIB,latitude,dec_ang,zuhr);
	isha=calcRemainingPrayerTimes(ISHA,latitude,dec_ang,zuhr);
	fajr=calcRemainingPrayerTimes(FAJR,latitude,dec_ang,zuhr);
	sunrise=calcRemainingPrayerTimes(SUNRISE,latitude,dec_ang,zuhr);
	calcPrayerHrMin(zuhr,dhuhrMinute,dhuhrHour);
	calcPrayerHrMin(asr,asrMinute,asrHour);
	calcPrayerHrMin(maghrib,maghribMinute,maghribHour);
	calcPrayerHrMin(isha,ishaMinute,ishaHour);
	calcPrayerHrMin(fajr,fajrMinute,fajrHour);
	calcPrayerHrMin(sunrise,sunriseMinute,sunriseHour);
	
}

/* Check for iqamah alert */
uint8 checkIqamahAlert(	uint8 hour, uint8 minute, uint8 fajr_hour, uint8 fajr_min,
uint8 dhuhr_hour, uint8 dhuhr_min, uint8 asr_hour, uint8 asr_min,
uint8 maghrib_hour, uint8 maghrib_min, uint8 isha_hour, uint8 isha_min)
{
	uint8 temporaryHour, iqamahFlag;
	if(minute > 49){
		if(hour == 23){
			temporaryHour = 0;
		}
		else{
			temporaryHour = hour++;
		}
		
		if( ( (temporaryHour == fajr_hour) && (minute == (fajr_min-45)) ) ||
		( (temporaryHour == dhuhr_hour) && (minute == (dhuhr_min-45)) ) ||
		( (temporaryHour == asr_hour) && (minute == (asr_min-45)) ) ||
		( (temporaryHour == asr_hour) && (minute == (asr_min-50)) ) ||
		( (temporaryHour == isha_hour) && (minute == (isha_min-45)) ) )
		{
			iqamahFlag = 1;
		}
		else
		{
			iqamahFlag = 0;
		}
		
	}
	
	else if (minute > 44){
		
		if(hour == 23){
			temporaryHour = 0;
		}
		else{
			temporaryHour = hour++;
		}
		
		if( ( (temporaryHour == fajr_hour) && (minute == (fajr_min-45)) ) ||
		( (temporaryHour == dhuhr_hour) && (minute == (dhuhr_min-45)) ) ||
		( (temporaryHour == asr_hour) && (minute == (asr_min-45)) ) ||
		( (hour == maghrib_hour) && (minute == (maghrib_min+10)) ) ||
		( (temporaryHour == isha_hour) && (minute == (isha_min-45)) ) )
		{
			iqamahFlag = 1;
		}
		else
		{
			iqamahFlag = 0;
		}
	}
	
	else{
		
		if( ( (hour == fajr_hour) && (minute == (fajr_min+15)) ) ||
		( (hour == dhuhr_hour) && (minute == (dhuhr_min+15)) ) ||
		( (hour == asr_hour) && (minute == (asr_min+15)) ) ||
		( (hour == maghrib_hour) && (minute == (maghrib_min+10)) ) ||
		( (hour == isha_hour) && (minute == (isha_min+15)) ) )
		{
			iqamahFlag = 1;
		}
		else
		{
			iqamahFlag = 0;
		}
		
	}
	return iqamahFlag;
}
/*	______________________________________________________________________________
   |																			  |
   | Module: Real Time Clock													  |
   |																			  |
   | File Name: rtc.c															  |
   |																			  |
   | Description: Source file for the RTC driver								  |
   |																			  |
   | Author: Youssif Hossam														  |
   |______________________________________________________________________________|
*/

#include "RTC.h"


/*______________________________________________________________________________
 |                               Functions Definitions                          |
 |______________________________________________________________________________|
 */

/*
 * Description :
 -> Initialize the RTC.
 */
void RTC_init(){
	I2C_ConfigType RTC_Config = {0x01, BAUDRATE_400KHZ};
	I2C_init(&RTC_Config);
}

/*
 * Description :
 -> Write time to the RTC.
 */
void RTC_Clock_Write(uint8 _hour, uint8 _minute, uint8 _second)
{
	I2C_start(Device_Write_address);/* Start I2C communication with RTC */
	I2C_writeByte(0);			/* Write 0 address for second */
	I2C_writeByte(Dicmal_toBCD(_second));		/* Write second on 00 location */
	I2C_writeByte(Dicmal_toBCD(_minute));		/* Write minute on 01(auto increment) location */
	I2C_writeByte(Dicmal_toBCD(_hour));		/* Write hour on 02 location */
	I2C_stop();			/* Stop I2C communication */
}

/*
 * Description :
 -> Write date to the RTC.
 */
void RTC_Calendar_Write(uint8 _day, uint8 _date, uint8 _month, uint16 _year)
{
	uint8 lastTwoDigitsOfYear = _year % 100;  // Extract last two digits of the year
	
	I2C_start(Device_Write_address);/* Start I2C communication with RTC */
	I2C_writeByte(3);			/* Write 3 address for day */
	I2C_writeByte(Dicmal_toBCD(_day));		/* Write day on 03 location */
	I2C_writeByte(Dicmal_toBCD(_date));		/* Write date on 04 location */
	I2C_writeByte(Dicmal_toBCD(_month));		/* Write month on 05 location */
	I2C_writeByte(Dicmal_toBCD(lastTwoDigitsOfYear));		/* Write year on 06 location */
	I2C_stop();			/* Stop I2C communication */
}

/*
 * Description :
 -> Read the current time from the RTC.
 */
void RTC_Read_Clock(uint8 read_clock_address, uint8 *second, uint8 *minute, uint8 *hour)
{
	I2C_start(Device_Write_address);/* Start I2C communication with RTC */
	I2C_writeByte(read_clock_address);	/* Write address to read */
	I2C_repeatedStart(Device_Read_address);/* Repeated start with device read address */

	*second = BCD_toDicmal(I2C_readByteWithACK());	/* Read second */
	*minute = BCD_toDicmal(I2C_readByteWithACK());	/* Read minute */
	*hour = BCD_toDicmal(I2C_readByteWithNACK());		/* Read hour with Nack */
	I2C_stop();			/* Stop i2C communication */
}

/*
 * Description :
 -> Read the current date from the RTC.
 */
void RTC_Read_Calendar(uint8 read_calendar_address, uint8 *day, uint8 *date, uint8 *month, uint16 *year)
{
	I2C_start(Device_Write_address);
	I2C_writeByte(read_calendar_address);
	I2C_repeatedStart(Device_Read_address);

	*day = BCD_toDicmal(I2C_readByteWithACK());					/* Read day */
	*date = BCD_toDicmal(I2C_readByteWithACK());				/* Read date */
	*month = BCD_toDicmal(I2C_readByteWithACK());				/* Read month */
	*year = BCD_toDicmal(I2C_readByteWithNACK()) + 2000;		/* Read the year with Nack */
	I2C_stop();			/* Stop i2C communication */
}

/*
 * Description :
 -> Convert a BCD (Binary-Coded Decimal) number to a decimal number.
 */
uint8 BCD_toDicmal(uint8 copy_u8number)
{
	uint8 Dicmal=(copy_u8number&0x0f);
	Dicmal+=(copy_u8number>>4)*10;
	return Dicmal;

}

/*
 * Description :
 -> Convert a decimal number to a BCD (Binary-Coded Decimal) number.
 */
uint8 Dicmal_toBCD(uint8 copy_u8number)
{
	return (copy_u8number / 10 * 16) + (copy_u8number % 10);
}

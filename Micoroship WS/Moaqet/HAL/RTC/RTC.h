/*	______________________________________________________________________________
   |																			  |
   | Module: Real Time Clock													  |
   |																			  |
   | File Name: rtc.h															  |
   |																			  |
   | Description: Header file for the RTC driver								  |
   |																			  |
   | Author: Youssif Hossam														  |
   |______________________________________________________________________________|
*/

#ifndef HAL_RTC_RTC_H_
#define HAL_RTC_RTC_H_

#include "../../LIB/std_types.h"
#include "../../MCAL/I2C/i2c.h"

/*______________________________________________________________________________
 |                               		Definitions                        		|
 |______________________________________________________________________________|
 */

/* RTC DS1307 device addresses */
#define Device_Write_address	0xD0	/* Define RTC DS1307 slave write address */
#define Device_Read_address		0xD1	/* Make LSB bit high of slave address for read */

/* Time format defines */
#define TimeFormat12			0x40	/* Define 12 hour format */
#define AMPM					0x20

/*______________________________________________________________________________
 |                               Functions Prototypes                           |
 |______________________________________________________________________________|
 */

/*
 * Description :
 -> Initialize the RTC.
 */
void RTC_init();

/*
 * Description :
 -> Write time to the RTC.
 */
void RTC_Clock_Write(uint8 _hour, uint8 _minute, uint8 _second);

/*
 * Description :
 -> Write date to the RTC.
 */
void RTC_Calendar_Write(uint8 _weekDay, uint8 _day, uint8 _month, uint16 _year);

/*
 * Description :
 -> Read the current time from the RTC.
 */
void RTC_Read_Clock(uint8 read_clock_address, uint8 *second, uint8 *minute, uint8 *hour);

/*
 * Description :
 -> Read the current date from the RTC.
 */
void RTC_Read_Calendar(uint8 read_calendar_address, uint8 *weekDay, uint8 *day, uint8 *month, uint16 *year);

/*
 * Description :
 -> Convert a BCD (Binary-Coded Decimal) number to a decimal number.
 */
uint8 BCD_toDicmal(uint8 copy_u8number);

/*
 * Description :
 -> Convert a decimal number to a BCD (Binary-Coded Decimal) number.
 */
uint8 Dicmal_toBCD(uint8 copy_u8number);

#endif /* HAL_RTC_RTC_H_ */


/*
 * FAN_config.h
 *
 *  Created on: May 20, 2023
 *      Author: WAGIH
 */

#ifndef FAN_CONFIG_H_
#define FAN_CONFIG_H_


#define FAN_COOL_PORT	DIO_u8PORTC
#define FAN_COOL_PIN	DIO_u8PIN5
#define HEATER_PORT     DIO_u8PORTC
#define HEATER_PIN      DIO_u8PIN2

#define FAN_SUCTION_PORT	DIO_u8PORTC
#define FAN_SUCTION_PIN	    DIO_u8PIN4

#define FAN_COOL	0
//#define FAN_HEAT	1
#define HEATER      1

#define MAX_TEMP   20
#define MAX_HUMIDTY 99


#define MIN_TEMP   30
#define MIN_HUMIDTY 90

#define MAX_HUM      80

#endif /* FAN_CONFIG_H_ */

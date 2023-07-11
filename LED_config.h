/*
 * LED_config.h
 *
 *  Created on: May 30, 2023
 *      Author: WAGIH
 */

#ifndef LED_CONFIG_H_
#define LED_CONFIG_H_

#define LED_PORT	DIO_u8PORTC
#define LED_PIN		DIO_u8PIN3
#define LED_ONTIME_IN_SUMMER               20                      /*LED on time during summer*/
#define LED_ONTIME_IN_WINTER               17                      /*LED on time during winter*/
#define LED_ONTIME_IN_SPRING               19                      /*LED on time during spring*/
#define LED_ONTIME_IN_AUTUMN               18                      /*LED on time during autumn*/
#define LED_ON_PERIOD                      16                      /*LED on period */
#define SUNRISE_TIME_SUMMER                5
#define SUNRISE_TIME_WINTER                5
#define SUNRISE_TIME_SPRING                5
#define SUNRISE_TIME_AUTUMN                5
#define MINIMUM_LIGHT_INTS                 50
#define LDR_ADC_Channel                    2






#endif /* LED_CONFIG_H_ */

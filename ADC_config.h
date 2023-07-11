/*************************************************/
/*************************************************/
/***********   Author : Ahmed Fares   ************/
/***********     Layer : MCAL         ************/
/***********     SWC : ADC            ************/
/***********     Version : 1.00       ************/
/*************************************************/
/*************************************************/


#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_
/*ADC Voltage reference options :
 * 								 1-AREF		: Internal V-ref turned off
 * 								 2-AVCC 	: with external Capacitor
 * 								 3-INTERNAL : 1.1 or 2.56 with external Capacitor
 */

#define ADC_VOLTAGE_REF			 AVCC

/* Set your MAX Voltage from AREF or AVCC or Internally*/

#define ADC_MAX_VOLTAGE			 5

/*Resolution Options:
 * 						1- TEN_BITS  1024
 * 						2- EIGHT_BITS  256
 */
#define ADC_RESOLUTION	TEN_BITS

/*ADMUX left or right adjust:
 	 	 	 	 	 	 1-LEFT
 	 	 	 	 	 	 2-RIGHT
 *
#define ADMUX_ADLAR		LEFT*/


/* ADC Channels Options:
 * 							1-ADC0
 * 							2-ADC1
 * 							3-ADC2
 * 							4-ADC3
 * 							5-ADC4
 * 							6-ADC5
 * 							7-ADC6
 * 							8-ADC7
 */
#define ADC_CHANNEL_SEL		ADC2

/* ADC Prescaler Select Bits options:
 *
 * 							1-DIV_BY_2
 *                          2-DIV_BY_4
 *                          3-DIV_BY_8
 *                          4-DIV_BY_16
 *                          5-DIV_BY_32
 *                          6-DIV_BY_64
 *                          7-DIV_BY_128
 */
#define ADC_PRESCALER		DIV_BY_128

/*Conversion type options:
 * 							1-SINGLE
 * 							2-AUTO_TRIG*/

#define ADC_CONVERSION		SINGLE

/*ADC Auto Trigger Source options:
 *
 * 							FREE_RUNNING
 *                          ANALOG_COMPARATOR
 *                          EXTI_REQUEST_0
 *                          TIMER_0_MATCH_A
 *                          TIMER_0_OVERFLOW
 *                          TIMER_1_MATCH_B
 *                          TIMER_1_OVERFLOW
 *                          TIMER_1_CAPTURE
 */
#define ADC_AUTO_TRIG		FREE_RUNNING

#define ADC_u32TIMEOUT		50000



#endif

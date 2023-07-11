/*************************************************/
/*************************************************/
/***********   Author : Ahmed Fares   ************/
/***********     Layer : MCAL         ************/
/***********     SWC : ADC            ************/
/***********     Version : 1.00       ************/
/*************************************************/
/*************************************************/


#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_
/*ADC Voltage references */
#define AVCC			1
#define AREF			2
#define INTERNAL		3

/*ADMUX_ADLAR OPTIONS*/
#define LEFT			1
#define RIGHT			2

#define EIGHT_BITS			256
#define TEN_BITS			1024


/*ADC Channels*/
#define ADC0	           				0b00000000
#define ADC1                			0b00000001
#define ADC2                			0b00000010
#define ADC3                			0b00000011
#define ADC4                			0b00000100
#define ADC5	            			0b00000101
#define ADC6	            			0b00000110
#define ADC7	            			0b00000111

#define MUX_MASK         				0b11110000

/*PRESCALER SELECTION*/
#define DIV_BY_2						0b00000000
#define DIV_BY_4						0b00000010
#define DIV_BY_8						0b00000011
#define DIV_BY_16						0b00000100
#define DIV_BY_32						0b00000101
#define DIV_BY_64						0b00000110
#define DIV_BY_128						0b00000111

#define PRESCALER_MASK					0b11111000

/*ADC Auto Trigger Source Selections*/

#define FREE_RUNNING     	            0b00000000
#define ANALOG_COMPARATOR    			0b00000001
#define EXTI_REQUEST_0               	0b00000010
#define TIMER_0_MATCH_A         		0b00000011
#define TIMER_0_OVERFLOW         		0b00000100
#define TIMER_1_MATCH_B          		0b00000101
#define TIMER_1_OVERFLOW         		0b00000110
#define TIMER_1_CAPTURE          		0b00000111

#define ADC_TRIG_MASK					0b11111000

/*ADC conversion type*/

#define SINGLE							1
#define AUTO_TRIG						2

#define SINGLE_CHANNEL_ASYNCH			0
#define CHAIN_ASYNCH					1

#define IDLE                            0
#define BUSY							1
#endif

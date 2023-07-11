/*************************************************/
/*************************************************/
/***********   Author  : Ahmed Fares  ************/
/***********   Layer   : MCAL	      ************/
/***********   SWC     : TIMER        ************/
/***********   Version : 1.00      	  ************/
/*************************************************/
/*************************************************/


#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

/*PRESCALER SELECTION*/
#define DIV_BY_0						0		/*Timer stopped*/
#define DIV_BY_1						1		/*CLK/1*/
#define DIV_BY_8						2		/*CLK/8*/
#define DIV_BY_64						3		/*CLK/64*/
#define DIV_BY_256						4		/*CLK/256*/
#define DIV_BY_1024						5		/*CLK/1024*/


#define PRESCALER_MASK					0b11111000


#endif

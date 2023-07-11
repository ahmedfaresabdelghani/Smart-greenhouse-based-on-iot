/*************************************************/
/*************************************************/
/***********   Author : Ahmed Fares   ************/
/***********     Layer : MCAL         ************/
/***********     SWC : PORT            ************/
/***********     Version : 1.00       ************/
/*************************************************/
/*************************************************/
#ifndef PORT_REGISTER_H_
#define PORT_REGISTER_H_
/* first * is for derefrencing (to set the value of : PIN , PORT and DDR)
the next * for type casting (instead of declaring a variable with a pointer data type and consume a memory location)*/

#define DDRA    *((volatile u8*)0x3A)
#define PORTA   *((volatile u8*)0x3B)


#define DDRB    *((volatile u8*)0x37)

#define PORTB   *((volatile u8*)0x38)

#define DDRC    *((volatile u8*)0x34)

#define PORTC   *((volatile u8*)0x35)


#define DDRD    *((volatile u8*)0x31)

#define PORTD   *((volatile u8*)0x32)

#endif

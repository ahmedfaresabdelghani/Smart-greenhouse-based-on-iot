/*************************************************/
/*************************************************/
/***********   Author : Ahmed Fares   ************/
/***********     Layer : MCAL         ************/
/***********     SWC : TIMER          ************/
/***********     Version : 1.00       ************/
/*************************************************/
/*************************************************/


#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

void TIMER0_voidInit(void);

u8 TIMER0_u8SetCallBack(void(*Copy_pvCallBackFunc)(void));

void TIMER0_voidSetCompMatchValue(u8 Copy_u8value);

void TIMER1_voidInit(void);

void TIMER1_voidSetICR(u16 Copy_u16TopValue);

void TIMER1_voidSetChannelACompareMatch(u16 Copy_u16TopValue);

void TIMER1_voidSetChannelBCompareMatch(u16 Copy_u16TopValue);

u8 TIMER1_u8SetCallBack(void(*Copy_pvCallBackFunc)(void));
void start();
void stop();

#endif

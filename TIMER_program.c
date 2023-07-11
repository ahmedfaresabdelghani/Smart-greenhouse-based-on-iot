/*************************************************/
/*************************************************/
/***********   Author : Ahmed Fares   ************/
/***********     Layer : MCAL         ************/
/***********     SWC : TIMER          ************/
/***********     Version : 1.00       ************/
/*************************************************/
/*************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TIMER_config.h"
#include "TIMER_interface.h"
#include "TIMER_private.h"
#include "TIMER_register.h"
#include "DHT_interface.h"
#include "USART_interface.h"
#include "WatchDog_interface.h"
static u8 counter=0;

static void (*TIMER0_pvCallBackFunc)(void)=NULL;
static void (*TIMER1_pvCallBackFunc)(void)=NULL;
void TIMER0_voidInit(void)
{
	/*choose CTC "Clear timer on compare match" mode
	 * for Fast PWM mode SET WGM00	&	WGM01*/
	CLR_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);
	/*output compare match interrupt enable*/
	SET_BIT(TIMSK,TIMSK_OCIE0);
	/*set compare match value to 250*/
	OCR0=250;
	/*Prescaler division by 8*/
	CLR_BIT(TCCR0,TCCR0_CS00);
	SET_BIT(TCCR0,TCCR0_CS01);
	CLR_BIT(TCCR0,TCCR0_CS02);

}

void TIMER0_voidSetCompMatchValue(u8 Copy_u8value)
{
	OCR0=Copy_u8value;
}
u8 TIMER0_u8SetCallBack(void(*Copy_pvCallBackFunc)(void))
{
	u8 Local_u8ErrorState=OK;

	if(Copy_pvCallBackFunc==NULL){
		Local_u8ErrorState=NULL_POINTER;
	}

	else{
		TIMER0_pvCallBackFunc=Copy_pvCallBackFunc;

	}
	return Local_u8ErrorState;
}
/***************************************************************************/
void TIMER1_voidInit(void)
{
	/*Setting the inverting Compare output mode in Fast PWM*/
	CLR_BIT(TCCR1A,TCCR1A_COM1A1);
	CLR_BIT(TCCR1A,TCCR1A_COM1A0);
	/*Setting the Waveform Generation Mode "FAST PWM"*/
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1B,TCCR1B_WGM12);
	CLR_BIT(TCCR1B,TCCR1B_WGM13);
	/*Setting Prescaler and Clock selection*/
	SET_BIT(TIMSK,TIMSK_TOIE1);
	TCNT1=24288;
	TCCR1B&=PRESCALER_MASK;
	TCCR1B|=DIV_BY_64;

}
/***************************************************************************/
void TIMER1_voidSetICR(u16 Copy_u16TopValue)
{
	ICR1=Copy_u16TopValue;
}
/***************************************************************************/
void TIMER1_voidSetChannelACompareMatch(u16 Copy_u16TopValue)
{
	OCR1A=Copy_u16TopValue;
}
/***************************************************************************/
void TIMER1_voidSetChannelBCompareMatch(u16 Copy_u16TopValue)
{
	OCR1B=Copy_u16TopValue;
}
/***************************************************************************/
u8 TIMER1_u8SetCallBack(void(*Copy_pvCallBackFunc)(void))
{
	u8 Local_u8ErrorState=OK;

	if(Copy_pvCallBackFunc==NULL){
		Local_u8ErrorState=NULL_POINTER;
	}

	else{
		TIMER1_pvCallBackFunc=Copy_pvCallBackFunc;

	}
	return Local_u8ErrorState;
}
void start(){

	SET_BIT(TCCR1A,TCCR1A_COM1A1);
	SET_BIT(TCCR1A,TCCR1A_COM1A0);

	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1B,TCCR1B_WGM13);
}
void stop(){
	TIMER1_voidSetChannelACompareMatch(36080);
	TIMER1_voidSetICR(36080);
}
/***************************************************************************/

void __vector_10 (void)__attribute__((signal));
void __vector_10 (void)
{
	if(TIMER0_pvCallBackFunc!=NULL)
	{
		TIMER0_pvCallBackFunc();
	}
}
/***************************************************************************/
void __vector_9 (void)__attribute__((signal));
void __vector_9 (void)
{
	//if(TIMER1_pvCallBackFunc!=NULL)
	//{
	counter++;

	//UART_voidSendToEsp();
	WATCHDOG_voidDisable();
	 if(counter==8){
		DHT_voidSaveData();
		WATCHDOG_voidDisable();
		counter=0;
		TCNT1=24288;
	}
	//}
}

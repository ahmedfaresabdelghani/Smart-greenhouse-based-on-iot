/*************************************************/
/*************************************************/
/***********   Author : Ahmed Fares   ************/
/***********     Layer : MCAL         ************/
/***********     SWC : USART          ************/
/***********     Version : 1.00       ************/
/*************************************************/
/*************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "USART_interface.h"
#include "USART_private.h"
#include "USART_register.h"
#include "USART_config.h"
#include "DIO_interface.h"
#include "SmartGreenHouse_interface.h"
extern Sensors_Read Sensors_Readings;
extern Control Ctrl ;
u8 Ctrl_Arr[6] = {0};
void USART_voidInit(void)
{
	u8 Local_u8UCSRCValue=0;
	/*USART Control and Status Register C*/
	/*USART mode select Asynchronous*/
	CLR_BIT(Local_u8UCSRCValue,UCSRC_UMSEL);
	// USE USCSRC NOT UBRRH BY SETTING BIT NO. 7 TO 1
	SET_BIT(Local_u8UCSRCValue,UCSRC_URSEL);
	/*Parity disable*/
	CLR_BIT(Local_u8UCSRCValue,UCSRC_UPM0);
	CLR_BIT(Local_u8UCSRCValue,UCSRC_UPM1);
	/*Stop bit select : 1 stop bit*/
	CLR_BIT(Local_u8UCSRCValue,UCSRC_USBS);
	/*Disable the double USART Transmission speed*/
	CLR_BIT(UCSRA,UCSRA_U2X);
	/*Character size 8 bits*/
	SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ0);
	SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ1);
	CLR_BIT(UCSRB,UCSRB_UCSZ2);
	UCSRC=Local_u8UCSRCValue;
	/*Baud rate 9600:UBRR=51*/
	UBRRL=103;
	/*enable the receiver*/
	SET_BIT(UCSRB,UCSRB_RXEN);
	/*enable the transmitter*/
	SET_BIT(UCSRB,UCSRB_TXEN);
}
/**********************************************************************************************/
void USART_voidSend(u8 Copy_u8Data)
{
	SET_BIT(UCSRB, UCSRB_TXEN);
	CLR_BIT(UCSRB, UCSRB_RXEN);
	while(GET_BIT(UCSRA,UCSRA_UDRE)==0); //Polling wait until transmit data buffer is empty
	UDR=Copy_u8Data;
}
/**********************************************************************************************/
u8 USART_u8Receive(void)
{
	CLR_BIT(UCSRB, UCSRB_TXEN);
	SET_BIT(UCSRB, UCSRB_RXEN);

	while(GET_BIT(UCSRA,UCSRA_RXC)==0);//wait until transmit data is finished
	return UDR;
}
/**********************************************************************************************/
void UART_SendString(u8 *Copy_u8Array)
{
	u8 i=0;
	while(Copy_u8Array[i]!='\0')
	{

		USART_voidSend(Copy_u8Array[i]);
		i++;
	}

}
/**********************************************************************************************/
void UART_voidSendNumber(u16 Copy_u16Number) {
	u8 i = 0;
	u8 arr[10]={0};
	u8 is_negative = 0;
	if (Copy_u16Number == 0) {
		arr[i++] = '0';
		arr[i] = '\0';
		UART_SendString(arr);
		return;
	}
	if (Copy_u16Number < 0) {
		is_negative = 1;
		Copy_u16Number = -Copy_u16Number;
	}
	while (Copy_u16Number != 0) {
		u16 digit = Copy_u16Number % 10;
		arr[i++] = digit + '0';
		Copy_u16Number /= 10;
	}
	if (is_negative) {
		arr[i++] = '-';
	}
	arr[i] = '\0';
	u8 len = i;
	for (i = 0; i < len / 2; i++) {
		u8 temp = arr[i];
		arr[i] = arr[len - i - 1];
		arr[len - i - 1] = temp;
	}
	UART_SendString(arr);
}
void UART_voidSendToEsp(void){
	USART_voidSend(Sensors_Readings.HumidtyRead		);
	USART_voidSend(Sensors_Readings.TempRead		);
	USART_voidSend(Sensors_Readings.WaterLevelRead	);
	USART_voidSend(Sensors_Readings.SoilRead		);
	USART_voidSend('\n');




}
void UART_voidReceiveEsp(void){

	//u8 i = 0 ;

	Ctrl.FAN_1   =USART_u8Receive() - '0';
	Ctrl.FAN_2   =USART_u8Receive() - '0';
	Ctrl.PUMP_1  =USART_u8Receive() - '0';
	Ctrl.PUMP_2  =USART_u8Receive() - '0';
	Ctrl.LED	 =USART_u8Receive() - '0';
	Ctrl.MODE	 =USART_u8Receive() - '0';
}

void UART_voidSTART_LISTENING(void){
	DIO_u8SetPinValue(SYNC_PORT, SYNC_PIN, DIO_u8PIN_HIGH);
}
void UART_voidSTART_TALKING(void){
	DIO_u8SetPinValue(SYNC_PORT, SYNC_PIN, DIO_u8PIN_LOW);
}


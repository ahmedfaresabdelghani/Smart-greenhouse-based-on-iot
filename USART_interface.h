/*************************************************/
/*************************************************/
/***********   Author : Ahmed Fares   ************/
/***********     Layer : MCAL         ************/
/***********     SWC : USART          ************/
/***********     Version : 1.00       ************/
/*************************************************/
/*************************************************/


#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

void USART_voidInit(void);
void USART_voidSend(u8 Copy_u8Data);
u8 USART_u8Receive(void);
void UART_SendString(u8 *Copy_u8Array);
void UART_voidSendNumber(u16 Copy_u16Number);
void UART_voidSendToEsp(void);
void UART_voidReceiveEsp(void);
void UART_voidSTART_LISTENING(void);
void UART_voidSTART_TALKING(void);

#endif

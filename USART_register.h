/*************************************************/
/*************************************************/
/***********   Author : Ahmed Fares   ************/
/***********     Layer : MCAL         ************/
/***********     SWC : USART          ************/
/***********     Version : 1.00       ************/
/*************************************************/
/*************************************************/
#ifndef USART_REGISTER_H_
#define USART_REGISTER_H_
/* *((volatile u8*)address) */

#define UDR					*((volatile u8*)0x2C)   /*USART I/O Data Register for transmitting and receiving*/

#define UCSRA				*((volatile u8*)0x2B)	/*USART Control and Status Register A*/
#define UCSRA_MPCM			0		/*Multi-processor Communication Mode synchronous Master slave*/
#define UCSRA_U2X			1		/*Double the USART Transmission Speed in asynchronous mode and set to 0 in synchronous mode */
#define UCSRA_PE			2		/*USART Parity Error (set to one if there is parity error)*/
#define UCSRA_DOR			3		/*Data OverRun This bit is set if a Data OverRun condition is detected*/
#define UCSRA_FE			4		/*One if there is a frame error and must be 0 when writing on UCSRA */
#define UCSRA_UDRE			5		/*USART Data Register Empty Flag ready to receive new data*/
#define UCSRA_TXC			6		/*USART Transmit Complete Flag*/
#define UCSRA_RXC			7		/*USART Receive Complete Flag*/

#define UCSRB				*((volatile u8*)0x2A) 	/*USART Control and Status Register B*/
#define UCSRB_TXB8			0		/*Transmit Data Bit 8 in case of 9 bits mode*/
#define UCSRB_RXB8			1		/*Receive Data Bit 8 in case of 9 bits mode*/
#define UCSRB_UCSZ2			2		/*Character Size select bit no 2*/
#define UCSRB_TXEN			3		/*Transmitter Enable*/
#define UCSRB_RXEN			4		/*Receiver Enable*/
#define UCSRB_UDRIE			5		/*USART Data Register Empty Interrupt Enable*/
#define UCSRB_TXCIE			6		/*TX Complete Interrupt Enable */
#define UCSRB_RXCIE			7		/*RX Complete Interrupt Enable */

#define UCSRC				*((volatile u8*)0x40)	/*USART Control and Status Register C*/
#define UCSRC_UCPOL	        0       /*Clock Polarity used for synchronous mode only (write 0 for Asynchronous) Determine when to read or when to transmit (falling for receive or for transmit)*/
#define UCSRC_UCSZ0	        1      	/*Character Size select bit no 1*/
#define UCSRC_UCSZ1	        2     	/*Character Size select bit no 0*/
#define UCSRC_USBS         	3    	/*Stop Bit Select (1 or 2) bits*/
#define UCSRC_UPM0	        4   	/*Parity Mode*/
#define UCSRC_UPM1         	5  	   	/*Parity Mode (Enabled/Disabled, Even Parity/Odd Parity)*/
#define UCSRC_UMSEL	        6 		/*USART Mode Select*/
#define UCSRC_URSEL       	7		/*USART Mode Select (Asynchronous // Synchronous)*/

#define UBRRL				*((volatile u8*)0x29)	/*USART Baud Rate Register Low  0-7  */
#define	UBRRH				*((volatile u8*)0x40)	/*USART Baud Rate Register High 8-11 */

#endif

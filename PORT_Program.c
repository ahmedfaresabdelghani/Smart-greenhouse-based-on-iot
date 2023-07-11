/************************************************************************************/
/************************************************************************************/
/**********************      AUTHOR: AHMED MOKHTAR       ****************************/
/**********************      LAYER: MCAL                 ****************************/
/**********************      SWC:PORT                    ****************************/
/**********************      VERSION: 1.00               ****************************/
/************************************************************************************/
/************************************************************************************/
#include "STD_TYPES.h"

#include "DIO_config.h"
#include "DIO_register.h"
#include "DIO_private.h"
#include "PORT_config.h"
#include "PORT_private.h"
#include "PORT_interface.h"
#include "PORT_register.h"


void PORT_voidInit(void)
{
	DDRA=PORTA_DIR;
	DDRB=PORTB_DIR;
	DDRC=PORTC_DIR;
	DDRD=PORTD_DIR;
	PORTA=PORTA_INITIAL_VALUE;
	PORTB=PORTB_INITIAL_VALUE;
	PORTC=PORTC_INITIAL_VALUE;
	PORTD=PORTD_INITIAL_VALUE;
}

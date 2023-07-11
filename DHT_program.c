#include "STD_Types.h"
#include"BIT_MATH.h"
#include "DIO_interface.h"
#include "DHT_config.h"
#include "DHT_interface.h"
#include <util/delay.h>

#define PIND		*((volatile u8*)0x30)
#define PINA		*((volatile u8*)0x39)

DHT_DATA DHT;

void DHT_voidRequest(){
	DIO_u8SetPinDirection(DHT_SIG_PORT, DHT_SIG_PIN, DIO_u8PIN_INPUT);
	DIO_u8SetPinValue(DHT_SIG_PORT, DHT_SIG_PIN, DIO_u8PIN_HIGH);
	_delay_ms(1);
	DIO_u8SetPinDirection(DHT_SIG_PORT, DHT_SIG_PIN, DIO_u8PIN_OUTPUT);
	DIO_u8SetPinValue(DHT_SIG_PORT, DHT_SIG_PIN, DIO_u8PIN_LOW);
	_delay_us(1300);
	DIO_u8SetPinDirection(DHT_SIG_PORT, DHT_SIG_PIN, DIO_u8PIN_INPUT);
	DIO_u8SetPinValue(DHT_SIG_PORT, DHT_SIG_PIN, DIO_u8PIN_HIGH);
	_delay_us(30);
}
void DHT_voidResponse(){
	while(GET_BIT(PINA,DHT_SIG_PIN));
	while(GET_BIT(PINA,DHT_SIG_PIN)==0);
}
u8 DHT_voidRead_Data(){
	u8 DHT_u8Byte = 0 ;
	u8 Local_u8counter =0 ;

	for(Local_u8counter = 0 ; Local_u8counter < 8 ;Local_u8counter++){
		while(GET_BIT(PINA,DHT_SIG_PIN));

		while(GET_BIT(PINA,DHT_SIG_PIN) ==0);
		_delay_us(30);
		if(GET_BIT(PINA,DHT_SIG_PIN)){
			DHT_u8Byte = (DHT_u8Byte<<1) | (0x01);

		}
		else{
			DHT_u8Byte = (DHT_u8Byte<<1) ;
		}
		while(GET_BIT(PINA,DHT_SIG_PIN));

	}
	return DHT_u8Byte ;
}
void DHT_voidSaveData()
{
	DHT.Error = 0 ;
	DHT_voidRequest();
	DHT_voidResponse();
	 u8 DHT_u8IntMois = DHT_voidRead_Data()  ;
	 u8 DHT_u8DecMois = DHT_voidRead_Data()  ;
	 u8 DHT_u8IntTemp = DHT_voidRead_Data()  ;
	 u8 DHT_u8DecTemp  = DHT_voidRead_Data() ;
	 u8 DHT_u8CheckSum = DHT_voidRead_Data() ;

	if( (DHT_u8IntMois + DHT_u8DecMois + DHT_u8IntTemp + DHT_u8DecTemp) != DHT_u8CheckSum ){

		DHT.Error = 1 ;
	}
	else{
		DHT.Error = 0 ;
		DHT.HumidityRead = (u8)(((u16)(DHT_u8IntMois<<8)+DHT_u8DecMois)/10);
		DHT.TempRead =	(u8)(((u16)(DHT_u8IntTemp<<8)+DHT_u8DecTemp)/10);
	//	DHT.HumidityRead = DHT_u8IntMois;
	//	DHT.TempRead =		DHT_u8IntTemp ;
	}

}

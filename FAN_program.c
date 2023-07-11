/*
 * FAN_program.c
 *
 *  Created on: May 20, 2023
 *      Author: WAGIH
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "FAN_interface.h"
#include "FAN_config.h"
#include"DHT_interface.h"
#include "DIO_interface.h"
extern DHT_DATA DHT;
void FAN_voidCond(){
if(DHT.Error == 0 ){
	if(DHT.TempRead > MAX_TEMP){
		DIO_u8SetPinValue(FAN_COOL_PORT, FAN_COOL_PIN, DIO_u8PIN_HIGH);

	}
	else{
		DIO_u8SetPinValue(FAN_COOL_PORT, FAN_COOL_PIN, DIO_u8PIN_LOW);
	}
	if(DHT.TempRead < MIN_TEMP){
		DIO_u8SetPinValue(FAN_COOL_PORT, FAN_COOL_PIN, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(HEATER_PORT,HEATER_PIN,DIO_u8PIN_HIGH);

	}
	else{
		DIO_u8SetPinValue(FAN_COOL_PORT, FAN_COOL_PIN, DIO_u8PIN_LOW);
		DIO_u8SetPinValue(HEATER_PORT,HEATER_PIN,DIO_u8PIN_LOW);
	}
}
else{
	DIO_u8SetPinValue(FAN_COOL_PORT, FAN_COOL_PIN, DIO_u8PIN_LOW);
	DIO_u8SetPinValue(HEATER_PORT,HEATER_PIN,DIO_u8PIN_LOW);
}
if(DHT.HumidityRead>MAX_HUM){
	DIO_u8SetPinValue(FAN_SUCTION_PORT, FAN_SUCTION_PIN, DIO_u8PIN_HIGH);

}
else{
	DIO_u8SetPinValue(FAN_SUCTION_PORT, FAN_SUCTION_PIN, DIO_u8PIN_LOW);

}
}
void FAN_voidOn(u8 Copy_u8FanType){
if(Copy_u8FanType == FAN_COOL){
	DIO_u8SetPinValue(FAN_COOL_PORT, FAN_COOL_PIN, DIO_u8PIN_HIGH);
}
else if (Copy_u8FanType == HEATER){
	DIO_u8SetPinValue(HEATER_PORT, HEATER_PIN, DIO_u8PIN_HIGH);
}

}
void FAN_voidOff(u8 Copy_u8FanType){
	if(Copy_u8FanType == FAN_COOL )
	{
		DIO_u8SetPinValue(FAN_COOL_PORT, FAN_COOL_PIN, DIO_u8PIN_LOW);
	}
	else if (Copy_u8FanType == HEATER )
	{
		DIO_u8SetPinValue(HEATER_PORT, HEATER_PIN, DIO_u8PIN_LOW);
	}


}

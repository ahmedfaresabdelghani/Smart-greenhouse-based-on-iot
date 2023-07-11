/*
 * MOTOR_program.c
 *
 *  Created on: May 30, 2023
 *      Author: WAGIH
 */
#include "STD_Types.h"
#include"BIT_MATH.h"
#include "MOTOR_config.h"
#include "MOTOR_interface.h"
#include "DIO_interface.h"




void MOTOR_voidOn(u8 Copy_u8MotorType){
if(Copy_u8MotorType == PUMP_MAIN){

DIO_u8SetPinValue(PUMP_MAIN_PORT, PUMP_MAIN_PIN, DIO_u8PIN_HIGH);
}
else if(Copy_u8MotorType == PUMP_TEMP){


	DIO_u8SetPinValue(PUMP_TEMP_PORT, PUMP_TEMP_PIN, DIO_u8PIN_HIGH);


}

}
void MOTOR_voidOff(u8 Copy_u8MotorType){

	if(Copy_u8MotorType == PUMP_MAIN){

	DIO_u8SetPinValue(PUMP_MAIN_PORT, PUMP_MAIN_PIN, DIO_u8PIN_LOW);
	}
	else if(Copy_u8MotorType == PUMP_TEMP){


		DIO_u8SetPinValue(PUMP_TEMP_PORT, PUMP_TEMP_PIN, DIO_u8PIN_LOW);


	}


}

#include "STD_Types.h"
#include"BIT_MATH.h"
#include "DIO_interface.h"
#include"SoilM_interface.h"
#include"DHT_interface.h"
#include"WATER_L_interface.h"
#include"SmartGreenHouse_interface.h"
#include"SmartGreenHouse_config.h"
#include "FAN_interface.h"
#include "FAN_config.h"
#include "MOTOR_interface.h"
#include "MOTOR_config.h"
#include "LED_interface.h"
#include "LED_config.h"

#define PIND		*((volatile u8*)0x30)

Sensors_Read Sensors_Readings;
Control Ctrl ;
extern DHT_DATA DHT;
void SMART_GREEN_HOUSE_voidInit(void)
{
  Sensors_Readings.SoilRead=SoilMoisture_u8SyncRead();
  Sensors_Readings.WaterLevelRead=Water_LEVEL_u8Read();
  if(DHT.Error==0)
  {
	  Sensors_Readings.TempRead=DHT.TempRead;
	  Sensors_Readings.HumidtyRead=DHT.HumidityRead;
  }
  else
  {
	  Sensors_Readings.TempRead=0;
	  Sensors_Readings.HumidtyRead=0;
  }

}
u8 SMART_GREEN_HOUSE_voidControlState(){

	return GET_BIT(PIND,CONTROL_PIN);



}

void SMART_GREEN_HOUSE_voidManual(){

	switch(Ctrl.FAN_1)
	{
	case 0 : FAN_voidOff(HEATER);break;
	case 1 : FAN_voidOn(HEATER);break;
	default : FAN_voidOff(HEATER);break;
	}
	switch(Ctrl.FAN_2)
	{
	case 0 : FAN_voidOff(FAN_COOL);break;
	case 1 : FAN_voidOn(FAN_COOL);break;
	default : FAN_voidOff(FAN_COOL);break;
	}
	switch(Ctrl.PUMP_1)
	{
	case 0 : MOTOR_voidOff(PUMP_MAIN);break;
	case 1 : MOTOR_voidOn(PUMP_MAIN);break;
	default : MOTOR_voidOff(PUMP_MAIN);break;
	}

	switch(Ctrl.PUMP_2)
	{
	case 0 : MOTOR_voidOff(PUMP_TEMP);break;
	case 1 : MOTOR_voidOn(PUMP_TEMP);break;
	default : MOTOR_voidOff(PUMP_TEMP);break;
	}

	switch(Ctrl.LED)
	{
	case 0 : LED_voidOff();break;
	case 1 : LED_voidOn();break;
	default :LED_voidOff();break;
	}




}

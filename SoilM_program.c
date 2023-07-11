/*************************************************/
/*************************************************/
/*******Authors : Ahmed Fares & Ahmed Abdallah ***/
/***********     Layer : HAL         ************/
/***********     SWC : SoilMoisture  *************/
/***********     Version : 1.00      *************/
/*************************************************/
/*************************************************/
#include "STD_Types.h"
#include "DIO_interface.h"
#include "SoilM_config.h"
#include "SoilM_interface.h"
#include "SoilM_private.h"
#include "SmartGreenHouse_interface.h"
#include "ADC_interface.h"
#include <util/delay.h>
ADC_ChainStruct Sensors;
u16 SoilMoisture_u16Digital=0;
u32 SoilMoisture_u32Volt=0;
/*u8 Local_u8Arr[2]={0,1};
u16 Local_u16Res[2];
u8 Size=2;*/

/*void SoilMoisture_voidInit(void){

	Sensors.channels=Local_u8Arr;
	Sensors.size=Size;
	Sensors.result=Local_u16Res;
	Sensors.notificationfunc=&SMFunc;
}*/
u8 SoilMoisture_u8ReadData(void)
{
	static  s32 Mapped_s32Value=0;
	Mapped_s32Value=ADC_s32Mapping(950,2640,0,100,Sensors.result[0]);
	return (u8)(100-Mapped_s32Value);

}
void SMFunc(void)
{
	DIO_u8SetPinDirection(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_HIGH);

}
u8 SoilMoisture_u8SyncRead(void)
{
	ADC_u8StartConversionSynch(&SoilMoisture_u32Volt,&SoilMoisture_u16Digital,0);
	s32 Mapped_s32Value=0;
	Mapped_s32Value=ADC_s32Mapping(950,2640,0,100,SoilMoisture_u32Volt);
    u8 Local_u8Read=(u8)(100-Mapped_s32Value);
	return Local_u8Read;
}

void SoilMoisture_voidAction()
{
	//s32 Local_s32Read=SoilMoisture_u8ReadData();
	s32 Local_s32Read=SoilMoisture_u8SyncRead();
	//Sensors_Readings.SoilRead=Local_s32Read;
	if(Local_s32Read>=0&&Local_s32Read<=50)
	{
		DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_LOW);
	}
	else DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_HIGH);
}

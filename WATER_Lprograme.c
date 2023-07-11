#include "STD_TYPES.h"
#include "WATER_L_config.h"
#include "WATER_L_interface.h"
#include "WATER_L_private.h"
#include "DIO_interface.h"
#include "rtc.h"



u16 MOTOR_ON_TIME=0;

u8 Water_LEVEL_u8Read()
{
	static u8 Local_u8Read=0;
	DIO_u8GetPinValue(SWITCH_PORT, SWITCH_PIN, &Local_u8Read);
	return Local_u8Read;
}

u8 Water_LEVEL_2_u8Read()
{
	static u8 Local_u8Read=0;
	DIO_u8GetPinValue(SWITCH2_PORT, SWITCH2_PIN, &Local_u8Read);
	return Local_u8Read;
}
void WATER_LEVEL_voidIndicate(void){
	u8 Local_u8Hours=0;
	u8 Local_u8Minutes=0;
	u8 Local_u8Seconds=0;
	RTC_GetTime(&Local_u8Hours,&Local_u8Minutes,&Local_u8Seconds);
	u8 Local_Read=Water_LEVEL_2_u8Read();
	u16 Local_u16Minutes=BCD_TO_DECIMAL(Local_u8Minutes);
	if(MOTOR_ON_TIME>Local_u16Minutes){
      Local_u16Minutes+=60;
	}
	if(Local_Read==0){
		DIO_u8SetPinValue(MOTOR_PORT, MOTOR_PIN, DIO_u8PIN_HIGH);
		MOTOR_ON_TIME=Local_u16Minutes;
	}

	else if(Local_u16Minutes-MOTOR_ON_TIME==PUMP_ON_PERIOD){
		DIO_u8SetPinValue(MOTOR_PORT, MOTOR_PIN, DIO_u8PIN_LOW);
		MOTOR_ON_TIME=0;
	}

}


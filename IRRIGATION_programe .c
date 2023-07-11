#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "rtc.h"
#include "IRRIGATION_config .h"
#include "IRRIGATION_interface .h"
#include <avr/eeprom.h>
#include "util/delay.h"
 u16 IRRIGATIONS_u16Minutes=0;
 u8  IRRIGATION_KEY;

void PUMP_ON(void){
	DIO_u8SetPinValue(PUMP_PORT, PUMP_PIN, DIO_u8PIN_HIGH);
}
void PUMP_OFF(void){
	DIO_u8SetPinValue(PUMP_PORT, PUMP_PIN, DIO_u8PIN_LOW);
}
void START_IRRIGATION(void){
	IRRIGATION_KEY=eeprom_read_byte ((const uint8_t*)800);
 if(eeprom_read_byte ((const uint8_t*)800)!=0&&eeprom_read_byte ((const uint8_t*)800)!=1)
 {
		eeprom_write_byte ((const uint8_t*) 800, 0);

 }
	u8 Local_Hour=0;
	u8 Local_Minutes=0;
	u8 Local_Seconds=0;
	RTC_GetTime(&Local_Hour, &Local_Minutes, &Local_Seconds);
	u16 Local_u16Hour=BCD_TO_DECIMAL(Local_Hour);
	u16 Local_u16Minutes=BCD_TO_DECIMAL(Local_Minutes);
	if(Local_u16Hour==IRRIGATION_TIME&&eeprom_read_byte ((const uint8_t*)800)==0){
		PUMP_ON();
		IRRIGATIONS_u16Minutes=BCD_TO_DECIMAL(Local_Minutes);
		IRRIGATION_KEY=1;
		eeprom_write_byte ((const uint8_t*) 800, 1);
	}
	else if(IRRIGATION_TIME-Local_u16Hour==1&&eeprom_read_byte ((const uint8_t*)800)==1&& Local_u16Minutes==45){
		IRRIGATION_KEY=0;
		eeprom_write_byte ((const uint8_t*) 800, 0);
	}

	if(eeprom_read_byte ((const uint8_t*)800)==0&&((s16)Local_u16Hour-IRRIGATION_TIME>=0)){
		PUMP_ON();
				IRRIGATIONS_u16Minutes=BCD_TO_DECIMAL(Local_Minutes);
				IRRIGATION_KEY=1;
				eeprom_write_byte ((const uint8_t*) 800, 1);

	}
		STOP_IRRIGATION();


}
void STOP_IRRIGATION(void){
	u8 Local_Hour=0;
	u8 Local_Minutes=0;
	u8 Local_Seconds=0;
	u16 Local_Age=0;

	RTC_GetTime(&Local_Hour, &Local_Minutes, &Local_Seconds);
	u16 Local_u16Minutes=BCD_TO_DECIMAL(Local_Minutes);
	Local_Age=PLANET_u8Age();
		if(IRRIGATIONS_u16Minutes>Local_u16Minutes){
			Local_u16Minutes+=60;
		}
	if(Local_Age<=SEEDING_AGE){
		if((Local_u16Minutes-IRRIGATIONS_u16Minutes>=SEEDING_IRR_TIME_MIN) ){
			PUMP_OFF();
		}
	}
	else if (Local_Age>SEEDING_AGE&&Local_Age<=VEGETATIVE_GROWTH){
		if(Local_u16Minutes-IRRIGATIONS_u16Minutes>=VEGETATIVE_GROWTH_IRR_TIME_MIN ){
			PUMP_OFF();
		}
	}
	else if (Local_Age>VEGETATIVE_GROWTH&&Local_Age<=FLORESCENCE){
		if(Local_u16Minutes-IRRIGATIONS_u16Minutes>=FLORESCENCE_IRR_TIME_MIN){
			PUMP_OFF();
		}
		else if (Local_Age>FRUITFULNESS){
			if(Local_u16Minutes-IRRIGATIONS_u16Minutes>=FRUITFULNESS_IRR_TIME_MIN){
				PUMP_OFF();
			}

		}

	}

}

u16 PLANET_u8Age(void){
	u8 Local_Day=0;
	u8 Local_Month=0;
	u8 Local_Years=0;
	u16 LOCAL_Age_Month=0;
	u16 LOCAL_Age_Day=0;

	RTC_GetDate(&Local_Day, &Local_Month, &Local_Years);
	u16 Local_u16Day=BCD_TO_DECIMAL(Local_Day);
	u16 Local_u16Month=BCD_TO_DECIMAL(Local_Month);
	if(Local_u16Month<START_MONTH){
		LOCAL_Age_Month=(Local_u16Month+12)-START_MONTH;
	}
	else {
		LOCAL_Age_Month=Local_u16Month-START_MONTH;
	}
	if(Local_u16Day<START_DAY){
		LOCAL_Age_Day=(Local_u16Day+30)-START_DAY;

	}
	else {
		LOCAL_Age_Day=Local_u16Day-START_DAY;
	}


	return (LOCAL_Age_Month*30)+LOCAL_Age_Day+START_AGE;

}

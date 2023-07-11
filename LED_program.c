/*
 * LED_program.c

 *
 *  Created on: May 30, 2023
 *      Author: WAGIH
 */


#include "STD_TYPES.h"
#include"DIO_interface.h"
#include "LED_interface.h"
#include "LED_config.h"
#include "ADC_interface.h"

#include "rtc.h"


u16 LDR_u16Digital=0;
u32 LDR_u32Volt=0;
u8 LDR_u8SyncRead(void)
{
	ADC_u8StartConversionSynch(&LDR_u32Volt,&LDR_u16Digital,LDR_ADC_Channel);
	s32 Mapped_s32Value=ADC_s32Mapping(0,5000,0,100,LDR_u32Volt);
    u8 Local_u8Read=(100-(u8)Mapped_s32Value);
	return Local_u8Read;
}


void LED_voidOff(){
	DIO_u8SetPinValue(LED_PORT, LED_PIN, DIO_u8PIN_LOW);


}
void LED_voidOn(){
	DIO_u8SetPinValue(LED_PORT, LED_PIN, DIO_u8PIN_HIGH);
}
void LED_voidStart(void){
	u8 Local_Hours=0;
	u8 Local_Minutes=0;
	u8 Local_Seconds=0;
	u8 Local_Days=0;
	u8 Local_Months=0;
	u8 Local_Years=0;
	u16 Local_u16Months=0;
	u16 Local_u16Hours=0;
	u8 Local_u8LDRRead=0;

	RTC_GetDate(&Local_Days, &Local_Months, &Local_Years);
	RTC_GetTime(&Local_Hours, &Local_Minutes, &Local_Seconds);
	Local_u16Months=BCD_TO_DECIMAL(Local_Months);
	Local_u16Hours=BCD_TO_DECIMAL(Local_Hours);
	Local_u8LDRRead=LDR_u8SyncRead();

	if(Local_u16Months<=3){
		if(Local_u16Hours==LED_ONTIME_IN_WINTER){
			LED_voidOn();
		}
		else if(Local_u16Hours>=SUNRISE_TIME_SUMMER&&Local_u8LDRRead<MINIMUM_LIGHT_INTS){
			LED_voidOn();


		}
	}
	else if(Local_u16Months>3&&Local_u16Months<=6){
		if(Local_u16Hours==LED_ONTIME_IN_SPRING){
			LED_voidOn();
		}
	}
	else if(Local_u16Months>6&&Local_u16Months<=9){
		if(Local_u16Hours==LED_ONTIME_IN_SUMMER){
			LED_voidOn();
		}
	}
	else if(Local_u16Months>9&&Local_u16Months<=12){
		if(Local_u16Hours==LED_ONTIME_IN_AUTUMN){
			LED_voidOn();
		}
	}
	LED_voidStop();

}

void LED_voidStop(void){
	u8 Local_Hours=0;
	u8 Local_Minutes=0;
	u8 Local_Seconds=0;
	u8 Local_Days=0;
	u8 Local_Months=0;
	u8 Local_Years=0;
	u16 Local_u16Months=0;
	u16 Local_u16Hours=0;
	u8 Local_u8LDRRead=0;


	RTC_GetDate(&Local_Days, &Local_Months, &Local_Years);
	RTC_GetTime(&Local_Hours, &Local_Minutes, &Local_Seconds);
	Local_u16Months=BCD_TO_DECIMAL(Local_Months);
	Local_u16Hours=BCD_TO_DECIMAL(Local_Hours);
	Local_u8LDRRead=LDR_u8SyncRead();


	if(Local_u16Months<=3){
		if(Local_Hours-LED_ONTIME_IN_WINTER==LED_ON_PERIOD){
			LED_voidOff();
		}
		else if(Local_u8LDRRead>=MINIMUM_LIGHT_INTS){
			LED_voidOff();
		}
	}
		else if(Local_u16Months>3&&Local_u16Months<=6){
			if(Local_Hours-LED_ONTIME_IN_SPRING==LED_ON_PERIOD){
				LED_voidOff();
			}
			else if(Local_u8LDRRead>=MINIMUM_LIGHT_INTS){
						LED_voidOff();
					}
		}
		else if(Local_u16Months>6&&Local_u16Months<=9){
			if(Local_Hours-LED_ONTIME_IN_SUMMER==LED_ON_PERIOD){
				LED_voidOff();
			}
			else if(Local_u8LDRRead>=MINIMUM_LIGHT_INTS){
						LED_voidOff();
					}
		}
			else if(Local_u16Months>9&&Local_u16Months<=12){
				if(Local_Hours-LED_ONTIME_IN_AUTUMN==LED_ON_PERIOD){
					LED_voidOff();
				}
				else if(Local_u8LDRRead>=MINIMUM_LIGHT_INTS){
							LED_voidOff();
						}
			}

		}




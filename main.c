#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include"DIO_interface.h"
#include "PORT_interface.h"
#include "ADC_interface.h"
#include "USART_interface.h"
#include "USART_register.h"
#include "SoilM_interface.h"
#include "DHT_interface.h"
#include "FAN_interface.h"
#include "SmartGreenHouse_interface.h"
#include "WATER_L_interface.h"
#include "WatchDog_interface.h"
#include "DIO_register.h"
#include "IRRIGATION_interface .h"
#include "LED_interface.h"
#include "rtc.h"
#include "util/delay.h"
#define PIND		*((volatile u8*)0x30)
extern Control Ctrl ;
u32 Counter=0 , Counter2 = 0, ESP_State=0 ;
u8 SwitchCase = 0;
u8 TRState = 1 ;
void main(void)
{
	PORT_voidInit();
	ADC_voidInit();
	USART_voidInit();
	Ctrl.MODE = 1;
	//RTC_Init();
	//RTC_SetTime(0x11,0x59,0x50);

	while(1)
	{
		//Ctrl.MODE = 1;
		/*****************************Final Code**************************
		 * we have added RTC code:
		 * problems :
		 * 1-first we debugged the configuration file and there was a mistake in
		 * SEEDING_IRR_TIME_MIN it was 0 minutes so it just flick not on for a time i mean.
		 * so we changed it to 1 minutes for try
		 * 2- we needed to store the IRRIGATION_KEY to EEPROM so that its value
		 * never changed even if we reset the Microcontroller
		 * 3- we removed the dependency of the PUMP (on or off ) on the Soil moisture
		 * sensor readings and we make it depends on the time only and the user Desire.
		 *
		 * /
	/*-------------------------------------------------------------------*/
		/****************************DHT Readings*************************/
		WATCHDOG_voidEnable();
		WATCHDOG_voidSleep(SLEEP_TIME7);
		DHT_voidSaveData();
		WATCHDOG_voidDisable();
		SMART_GREEN_HOUSE_voidInit();
		/*---------------------------------------------------------------*/

		/*Polling tell the ESP-01 send High on the PB3
		 * so ESP-01 Permit Atmega32 to send data Through USART*/

		while (GET_BIT(PIND,7)==0&&Counter!=ESP_TIME_OUT ){
			Counter++ ;
		}
		/*---------------------------------------------------------------*/

		/*Sending Sensors Reading to ESP-01*/

		UART_voidSendToEsp();
		UART_voidSendToEsp();
		/*---------------------------------------------------------------*/

		/*Checking if the ESP-01 goes Down or not by using the
		 *  Count UP Counter and compare it to ESP_TIME_OUT
		 *  and if it goes down we switch to Automatic Mode*/
		if (Counter != 0 )
		{
			if(Counter==ESP_TIME_OUT)
			{
				Ctrl.MODE=0;
			}
			ESP_State=Counter;
			Counter=0;
		}
		/*---------------------------------------------------------------*/
		/*Polling tell the ESP-01 send LOW on the PB3
		 * so ESP-01 tells Atmega32 to receive commands Through USART*/
		while (GET_BIT(PIND,7)==1&&Counter2!=ESP_TIME_OUT )
		{
			Counter2++ ;
		}
		/*---------------------------------------------------------------*/
		/*Checking if the ESP-01 goes Down or not by using the
		 *  Count UP Counter and compare it to ESP_TIME_OUT
		 *  and if it goes down we switch to Automatic Mode*/
		if (Counter2 >= 0&& ESP_State != ESP_TIME_OUT)
		{
			if (Counter2 !=ESP_TIME_OUT)
			{
				WATCHDOG_voidEnable();
				WATCHDOG_voidSleep(SLEEP_TIME7);
				UART_voidReceiveEsp();
				WATCHDOG_voidDisable();

			}
			Counter2 =0 ;
		}
		/*---------------------------------------------------------------*/
		/*Choosing the Control MODE either be Automatic or Manual
		 * if it is Automatic then Atmeg32 take Actions through sensors Readings
		 * or on The RTC timing Circuit for Irrigation or LED Control */
		SwitchCase = Ctrl.MODE;
		if(SwitchCase == 1 )
		{
			/*if control MODE is Manual the User Sets the Control Parameters Through Blynk*/
			SMART_GREEN_HOUSE_voidManual();
		}
		else
		{
			/*if control MODE is Automatic Atmega32 Sets the Control Parameters*/
			START_IRRIGATION();
			LED_voidStart();
			FAN_voidCond();
			WATER_LEVEL_voidIndicate();
		}
		_delay_ms(1000);
	}

}

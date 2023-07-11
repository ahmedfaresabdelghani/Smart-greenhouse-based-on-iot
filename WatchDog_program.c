/*************************************************/
/*************************************************/
/***********   Author : Ahmed Abdallah   *********/
/***********     Layer : MCAL         ************/
/***********     SWC : WatchDog           ********/
/***********     Version : 1.00       ************/
/*************************************************/
/*************************************************/
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_interface.h"
#include"WatchDog_config.h"
#include"WatchDog_interface.h"
#include"WatchDog_register.h"

void WATCHDOG_voidSleep(u8 Copy_u8Time)
{
	WDTCR&=WATCH_DOG_SLEEP_MASk;
	WDTCR|=Copy_u8Time;
}
void WATCHDOG_voidEnable(void)
{
  SET_BIT(WDTCR,WDTCR_WDE);
}
void WATCHDOG_voidDisable(void)
{
	WDTCR|=WATCH_DOG_DISABLE_MASK;
	WDTCR=0;
}

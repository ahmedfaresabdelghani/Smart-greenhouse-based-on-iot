/*************************************************/
/*************************************************/
/***********   Author : Ahmed Abdallah   *********/
/***********     Layer : MCAL         ************/
/***********     SWC : WatchDog           ********/
/***********     Version : 1.00       ************/
/*************************************************/
/*************************************************/
#ifndef WATCH_DOG_INTERFACE_H_
#define WATCH_DOG_INTERFACE_H_

 #define SLEEP_TIME0   0     //16.3ms
 #define SLEEP_TIME1   1     //32.5ms
 #define SLEEP_TIME2   2     //65ms
 #define SLEEP_TIME3   3     //0.13s
 #define SLEEP_TIME4   4     //0.26s
 #define SLEEP_TIME5   5     //0.52s
 #define SLEEP_TIME6   6     //1.0s
 #define SLEEP_TIME7   7     //2.1s

void WATCHDOG_voidSleep(u8 Copy_u8Time);

void WATCHDOG_voidEnable(void);

void WATCHDOG_voidDisable(void);

#endif

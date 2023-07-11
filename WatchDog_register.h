/*************************************************/
/*************************************************/
/***********   Author : Ahmed Abdallah   *********/
/***********     Layer : MCAL         ************/
/***********     SWC : WatchDog           ********/
/***********     Version : 1.00       ************/
/*************************************************/
/*************************************************/
#ifndef WATCH_DOG_REGISTER_H_
#define WATCH_DOG_REGISTER_H_
#define WDTCR     *((volatile u8*)0x41)
#define WDTCR_WDP0        0
#define WDTCR_WDP1        1
#define WDTCR_WDP2        2
#define WDTCR_WDE         3
#define WDTCR_WDTOE       4

#endif

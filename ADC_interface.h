/*************************************************/
/*************************************************/
/***********   Author : Ahmed Fares   ************/
/***********     Layer : MCAL         ************/
/***********     SWC : ADC            ************/
/***********     Version : 1.00       ************/
/*************************************************/
/*************************************************/


#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

 typedef struct ADC_ChainStruct{
	u8* channels;
	u8 size;
	u16* result;
	void (*notificationfunc)(void);
}ADC_ChainStruct;
ADC_ChainStruct Sensors;

void ADC_voidInit(void);

u8 ADC_u8StartConversionSynch(u32* Copy_pu32ResultVolt,u16* Copy_pu16Reading,u8 Copy_u8Channel);
u8 ADC_u8StartConversionASynch(u32* Copy_pu32ResultVolt,u16* Copy_pu16Reading,void (*Copy_pvNotificationFunc)(void));
u16 ADC_u16GetChannelReading(u32* Copy_pu32ResultVolt);
s32 ADC_s32Mapping(s32 Copy_s32InputMin,s32 Copy_s32InputMax,s32 Copy_s32OutputMin,s32 Copy_s32OutPutMax,s32 Copy_s32InputValue);
u8 ADC_u8StartChainAsynch( ADC_ChainStruct* Copy_psStructObject);
#endif

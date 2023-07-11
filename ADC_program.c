/*************************************************/
/*************************************************/
/***********   Author : Ahmed Fares   ************/
/***********   Layer :  MCAL          ************/
/***********   SWC :    ADC           ************/
/***********     Version : 1.00       ************/
/*************************************************/
/*************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_register.h"
#include "ADC_config.h"
static u16* ADC_pu16Reading=NULL;
static u32* ADC_pu32Reading=NULL;
static void(*ADC_pvCallBackNotificationFunc)(void)=NULL;
u8 ADC_u8BusyState=IDLE;
static u8 ADC_u8ISRSource;
static u8* ADC_pu8ChannelArr=NULL;   	/*Global Variable to carry chain array*/
static u8 ADC_u8ChainSize;				/*Global Variable to carry Number of Channels*/
static u16* ADC_pu16ResultArr=NULL; 	/*Global Variable to carry chain Result*/
static u8 ADC_u8ChannelIndex=0;			/*Global Variable to carry the current channel index*/

void ADC_voidInit(void)
{
	/*ADC voltage reference checking*/
#if ADC_VOLTAGE_REF==AVCC

	SET_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);

#elif ADC_VOLTAGE_REF==AREF

	CLR_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);

#elif ADC_VOLTAGE_REF==INTERNAL

	SET_BIT(ADMUX,ADMUX_REFS0);
	SET_BIT(ADMUX,ADMUX_REFS1);
#else
#error "wrong reference voltage selection"
#endif

	/*ADMUX adjust checking*/
#if   ADC_RESOLUTION==EIGHT_BITS

	SET_BIT(ADMUX,ADMUX_ADLAR);

#elif ADC_RESOLUTION==TEN_BITS
	CLR_BIT(ADMUX,ADMUX_ADLAR);
#else
#error "wrong Adjust/resoultion selection"
#endif

	/*Setting ADC prescaler */

	ADCSRA&=PRESCALER_MASK;
	ADCSRA|=ADC_PRESCALER;

	/*ADC peripheral enable*/
	SET_BIT(ADCSRA,ADCSRA_ADEN);

	/*checking for Conversion mode*/
#if ADC_CONVERSION==SINGLE
	CLR_BIT(ADCSRA,ADCSRA_ADATE);
	CLR_BIT(ADCSRA,ADCSRA_ADIE);
#elif ADC_CONVERSION==AUTO_TRIG
	/*ADC auto trigger enable*/
	SET_BIT(ADCSRA,ADCSRA_ADATE);
	/*enabling ADC interrupt FLAG*/
	SET_BIT(ADCSRA,ADCSRA_ADIE);
	/*preparing ADC to selected trigger source*/
	ADCSRB&=ADC_TRIG_MASK;
	ADCSRB|=ADC_AUTO_TRIG;
	/*start conversion in case of interrupts*/
	SET_BIT(ADCSRA,ADCSRA_ADSC);

#else
#error "wrong conversion mode"
#endif

}

/*****************************************************************************************************/

u8 ADC_u8StartConversionSynch(u32* Copy_pu32ResultVolt,u16* Copy_pu16Reading,u8 Copy_u8Channel)
{

	u16   Local_u16ADCReading;
	u32   Local_u32Counter=0;
	u32   Local_u32Result=0;
	u8 	  Local_u8ErrorState=OK;
	if(ADC_u8BusyState==IDLE)
	{
		ADC_u8BusyState=BUSY;
		/*taking Analog input from selected channel
		 * By Clearing MUX bits*/
		ADMUX&=MUX_MASK;
		/*Set the required channel into the MUX */
		ADMUX|=Copy_u8Channel;
		/*Start conversion*/
		SET_BIT(ADCSRA,ADCSRA_ADSC);
		/*Polling (busy waiting) until the conversion complete flag is set or counter reaching the timeout*/
		while((GET_BIT(ADCSRA,ADCSRA_ADIF)==0)&& (Local_u32Counter != ADC_u32TIMEOUT))
		{
			Local_u32Counter++;
		}
		if(Local_u32Counter==ADC_u32TIMEOUT)
		{
			/*loop is broken because the timeout is reached*/
			Local_u8ErrorState=NOK;
		}
		else
		{
			/*Loop is broken because the flag has been raised*/
			/*Set down the flag*/
			SET_BIT(ADCSRA,ADCSRA_ADIF);
			/*return the reading*/
			if(ADC_RESOLUTION==EIGHT_BITS)
			{
				Local_u16ADCReading=ADCH;
				*Copy_pu16Reading=Local_u16ADCReading;
				ADC_u8BusyState=IDLE;
			}
			else
			{
				Local_u16ADCReading=ADC;
				*Copy_pu16Reading=Local_u16ADCReading;
				ADC_u8BusyState=IDLE;
			}

			Local_u32Result=(( ((u32)Local_u16ADCReading) * (ADC_MAX_VOLTAGE*1000UL)) / ((u16)ADC_RESOLUTION) );
			*Copy_pu32ResultVolt=Local_u32Result;

		}
	}
	else
	{
		Local_u8ErrorState=BUSY_FUNC;
	}


	return Local_u8ErrorState;

}

/**************************************************************************************************/

u8 ADC_u8StartConversionASynch(u32* Copy_pu32ResultVolt,u16* Copy_pu16Reading,void (*Copy_pvNotificationFunc)(void))
{
	u8 Local_u8Errorstate=OK;
	if(ADC_u8BusyState==IDLE)
	{
		if(Copy_pvNotificationFunc==NULL || Copy_pu16Reading==NULL ||Copy_pu32ResultVolt==NULL)
		{
			Local_u8Errorstate=NULL_POINTER;
		}
		else
		{
			/*Make ADC BUSY in order not to work till being IDLE*/
			ADC_u8BusyState=BUSY;
			/*Make ISR source single channel Asynch*/
			ADC_u8ISRSource=SINGLE_CHANNEL_ASYNCH;
			/*Initialize the reading variables globally*/
			ADC_pu16Reading=Copy_pu16Reading;
			ADC_pu32Reading=Copy_pu32ResultVolt;
			/*Initialize the callback notification function globally */
			ADC_pvCallBackNotificationFunc=Copy_pvNotificationFunc;
			/*taking Analog input from selected channel
			 * By Clearing MUX bits*/
			ADMUX&=MUX_MASK;
			/*Set the required channel into the MUX */
			ADMUX|=ADC_CHANNEL_SEL;
			/*Start conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);
			/*Enable ADC Conversion Complete Interrupt*/
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
	}
	else
	{
		Local_u8Errorstate=BUSY_FUNC;
	}
	return Local_u8Errorstate;
}

/**************************************************************************************************/

u16 ADC_u16GetChannelReading(u32* Copy_pu32ResultVolt)
{
	u16 Local_u16ADCReading;
	/*taking Analog input from selected channel*/
	ADMUX&=MUX_MASK;
	ADMUX|=ADC_CHANNEL_SEL;
#if ADC_CONVERSION==SINGLE
	/*Start conversion*/
	SET_BIT(ADCSRA,ADCSRA_ADSC);
	/*wait for conversion to complete*/
	while(GET_BIT(ADCSRA,ADCSRA_ADIF)==0);
	/*Set down the flag*/
	SET_BIT(ADCSRA,ADCSRA_ADIF);
#endif
	/*Return ADC Reading*/
#if ADC_RESOLUTION==EIGHT_BITS
	Local_u16ADCReading=ADCH;
	*Copy_pu32ResultVolt=(( ((u32)Local_u16ADCReading) * (ADC_MAX_VOLTAGE*1000UL)) / ((u16)ADC_RESOLUTION) );
	return ADCH;
#endif

#if ADC_RESOLUTION==TEN_BITS

	Local_u16ADCReading=(ADCL|(ADCH<<8));
	*Copy_pu32ResultVolt=(( ((u32)Local_u16ADCReading) * (ADC_MAX_VOLTAGE*1000UL)) /(u16)ADC_RESOLUTION);
	return ADC;
#endif
}

/**************************************************************************************************/

s32 ADC_s32Mapping(s32 Copy_s32InputMin,s32 Copy_s32InputMax,s32 Copy_s32OutputMin,s32 Copy_s32OutPutMax,s32 Copy_s32InputValue)
{ 	s32 Local_s32OutputValue;
Local_s32OutputValue=(((Copy_s32OutPutMax-Copy_s32OutputMin)*(Copy_s32InputValue-Copy_s32InputMin))/(Copy_s32InputMax-Copy_s32InputMin))+Copy_s32OutputMin;
return Local_s32OutputValue;
}
/**************************************************************************************************/

u8 ADC_u8StartChainAsynch( ADC_ChainStruct* Copy_psStructObject)
{
	u8 Local_u8errorstate=OK;
	/* Check NULL pointer */
	if(Copy_psStructObject==NULL)
	{
		Local_u8errorstate=NULL_POINTER;
	}
	else{
		if(ADC_u8BusyState==IDLE)
		{
			/*Make ADC Busy*/
			ADC_u8BusyState=BUSY;
			/*Make ISR source Chain Asynch*/
			ADC_u8ISRSource=CHAIN_ASYNCH;

			/*pass the structure variables to global variables to be used in ISR*/
			/*Initialize chain channel array*/
			ADC_pu8ChannelArr=Copy_psStructObject->channels;
			/*Initialize chain Size*/
			ADC_u8ChainSize=Copy_psStructObject->size;
			/*Initialize chain Notification Function*/
			ADC_pvCallBackNotificationFunc=Copy_psStructObject->notificationfunc;
			/*Initialize chain Result array*/
			ADC_pu16ResultArr=Copy_psStructObject->result;
			ADC_u8ChannelIndex=0;
			/*set the first channel*/
			ADMUX&=MUX_MASK;
			ADMUX|=ADC_pu8ChannelArr[ADC_u8ChannelIndex];
			/*start the first conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);
			/*enable ADC complete  interrupt*/
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else{
			Local_u8errorstate=BUSY_FUNC;
		}
	}
	return Local_u8errorstate;

}
/**************************************************************************************************/
void __vector_16 (void) __attribute__((signal));
void __vector_16 (void)
{
	if(ADC_u8ISRSource==SINGLE_CHANNEL_ASYNCH)
	{
		u16 Local_u16ADCReading;
		u32 Local_u32Result;
		/*read ADC result*/
		/*Set down the flag*/
		SET_BIT(ADCSRA,ADCSRA_ADIF);
		/*return the reading*/
		if(ADC_RESOLUTION==EIGHT_BITS)
		{
			Local_u16ADCReading=ADCH;
			*ADC_pu16Reading=ADCH;
		}
		else
		{
			Local_u16ADCReading=ADC;
			*ADC_pu16Reading=ADC;
		}
		Local_u32Result=(( ((u32)Local_u16ADCReading) * (ADC_MAX_VOLTAGE*1000UL)) / ((u32)ADC_RESOLUTION) );
		*ADC_pu32Reading=Local_u32Result;
		/*make ADC State be IDLE because it is finished*/
		ADC_u8BusyState=IDLE;
		/*call back notification function*/
		ADC_pvCallBackNotificationFunc();
		/*disable ADC Conversion Complete interrupt*/
		CLR_BIT(ADCSRA,ADCSRA_ADIE);
	}
	else if(ADC_u8ISRSource==CHAIN_ASYNCH)
	{
		u16 Local_u16ADCReading;
		/*Read the result of the current conversion*/
		Local_u16ADCReading=ADC;
		ADC_pu16ResultArr[ADC_u8ChannelIndex]=Local_u16ADCReading;
		Local_u16ADCReading=(( ((u32)Local_u16ADCReading) * (ADC_MAX_VOLTAGE*1000UL)) / ((u16)ADC_RESOLUTION) );
		ADC_pu16ResultArr[ADC_u8ChannelIndex]=Local_u16ADCReading;
		/*Increment chain index*/
		ADC_u8ChannelIndex++;
		/*Check chain is finished or not*/
		if(ADC_u8ChannelIndex<ADC_u8ChainSize)
		{
			/*start the new conversion of the next channel (chain not finished)*/
			ADMUX&=MUX_MASK;
			ADMUX|=ADC_pu8ChannelArr[ADC_u8ChannelIndex];
			SET_BIT(ADCSRA,ADCSRA_ADSC);
		}
		else
		{
			/*chain is finished*/
			ADC_u8BusyState=IDLE;
			/*disable the interrupt*/
			SET_BIT(ADCSRA,ADCSRA_ADIE);
			/*Invoke the Callback notification function*/
			ADC_pvCallBackNotificationFunc();
			/*Disable ADC conversion complete interrupt*/
			CLR_BIT(ADCSRA,ADCSRA_ADIE);
		}
	}
	else
	{
		/*do nothing*/
	}
}



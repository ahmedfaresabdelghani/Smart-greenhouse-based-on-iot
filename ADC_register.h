/*************************************************/
/*************************************************/
/***********   Author : Ahmed Fares   ************/
/***********     Layer : MCAL         ************/
/***********     SWC : ADC            ************/
/***********     Version : 1.00       ************/
/*************************************************/
/*************************************************/
#ifndef ADC_REGISTER_H_
#define ADC_REGISTER_H_
/* *((volatile u8*)address) */
#define ADMUX     		    *((volatile u8*)0x27) 	    //ADC Multiplexer selection register
#define ADMUX_REFS1 		7					  	    //Reference selection bit1
#define ADMUX_REFS0 		6					  	    //Reference selection bit0
#define ADMUX_ADLAR 		5					  	    //ADC Left adjust result


#define  ADCSRA    		*((volatile u8*)0x26)	    //ADC control and status register
#define  ADCSRA_ADEN 	7						    //ADC Enable peripheral
#define  ADCSRA_ADSC 	6						    //ADC Start Conversion
#define  ADCSRA_ADATE 	5						    //Auto trigger Enable
#define  ADCSRA_ADIF 	4						    //Interrupt Flag
#define  ADCSRA_ADIE 	3						    //Interrupt Enable
#define  ADCSRA_ADPS2	2						    //prescaler bit2
#define  ADCSRA_ADPS1	1                           //prescaler bit1
#define  ADCSRA_ADPS0	0						    //prescaler bit0

#define ADCSRB			*((volatile u8*)0x7B)
#define ADCSRB_ADTS2	2
#define ADCSRB_ADTS1	1
#define ADCSRB_ADTS0	0

#define  ADCH    		*((volatile u8*)0x25) 		//ADC result high register
#define  ADCL    		*((volatile u8*)0x24) 		//ADC result low register

#define ADC				*((volatile u16*)0x24)





#endif

/*************************************************/
/*************************************************/
/*******Authors : Ahmed Fares & Ahmed Abdallah ***/
/***********     Layer : HAL         ************/
/***********     SWC : SoilMoisture  *************/
/***********     Version : 1.00      *************/
/*************************************************/
/*************************************************/
#ifndef SoilM_Interface
#define SoilM_Interface
void SMFunc(void);

u8 SoilMoisture_u8ReadData(void);
void SoilMoisture_voidAction(void);
void SoilMoisture_voidInit(void);
u8 SoilMoisture_u8SyncRead(void);
#endif

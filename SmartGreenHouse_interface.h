#ifndef SMARTGREENHOUSE_INTERFACE_H_
#define SMARTGREENHOUSE_INTERFACE_H_
typedef struct {
	u8 TempRead;
	u8 SoilRead;
	u8 WaterLevelRead;
	u8 HumidtyRead;
	u8 LSRead ;
}Sensors_Read;
typedef struct {
	u8 FAN_1;
	u8 FAN_2;
	u8 PUMP_1;
	u8 PUMP_2;
	u8 LED ;
	u8 MODE ;
}Control;
void SMART_GREEN_HOUSE_voidInit(void);
u8 SMART_GREEN_HOUSE_voidControlState();
void SMART_GREEN_HOUSE_voidManual();


#endif

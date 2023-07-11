#ifndef DHT_INTERFACE_H_
#define DHT_INTERFACE_H_
void DHT_voidRequest();
void DHT_voidResponse();


u8 DHT_voidRead_Data(void);
void DHT_voidSaveData();
#define DHT_TYPE   11


typedef struct
{
	u8 TempRead;
	u8 HumidityRead;
	u8 Error ;
}DHT_DATA;










#endif

#include "DHT.h"


__IO uint8_t DHT_Type=0;

void DHT_init(uint8_t type)
{
	DHT_GPIO_RCC(DHT_GPIO_CLK,ENABLE);
	DHT_Type=type;
}

void DHT_PIN_INPUT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin  = DHT_PIN;
	GPIO_Init(DHT_GPIO_PORT, &GPIO_InitStructure);
}

void DHT_PIN_OUTPUT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin  = DHT_PIN;
	GPIO_Init(DHT_GPIO_PORT, &GPIO_InitStructure);
}

uint32_t DHT_Get_byte(void)
{
	uint8_t i,j;
	uint8_t buff[5]={0,0,0,0,0};
	uint32_t dht_byte = 0;
	DHT_PIN_OUTPUT();
	DHT_PIN_HIGH();
	delay_us(1);//50us
	DHT_PIN_LOW();
	if(DHT_Type==DHT11) delay_ms(20);
	else delay_ms(2);
	DHT_PIN_INPUT();
	delay_us(1);//50us
	if(GPIO_ReadInputDataBit(DHT_GPIO_PORT,DHT_PIN)==1) return DHT_ERR;
	while(GPIO_ReadInputDataBit(DHT_GPIO_PORT,DHT_PIN)==0); // wait pin sensor pull-up
	delay_us(1);//50us
	if(GPIO_ReadInputDataBit(DHT_GPIO_PORT,DHT_PIN)==0) return DHT_ERR;
	while(GPIO_ReadInputDataBit(DHT_GPIO_PORT,DHT_PIN)==1); // wait pin sensor pull-down
	//Read bit
	for(i=0;i<5;i++)
	{
		for(j=0;j<8;j++)
		{
			while(GPIO_ReadInputDataBit(DHT_GPIO_PORT,DHT_PIN)==0);
			delay_us(1);//50us
			if(GPIO_ReadInputDataBit(DHT_GPIO_PORT,DHT_PIN)==1)
			{
				buff[i]|=(1<<(7-j));
				while(GPIO_ReadInputDataBit(DHT_GPIO_PORT,DHT_PIN)==1);
			}
		}
	}
	//Check sum
	if(buff[4]!=(buff[0]+buff[1]+buff[2]+buff[3])) return DHT_ERR;
	
	for(i=0;i<4;i++)
		dht_byte|=(uint32_t)buff[i]<<(24-(8*i));
	return dht_byte;
}

/**
	Dht_byte: 32 bit has read from "DHT_Get_byte" function above
*/
float DHT_Get_HumiAndTemp(uint32_t Dht_byte ,uint8_t type)
{
	float value=0;
	uint8_t __Tmp=0;
	if(type == DHT_TEMP)
	{
		if(DHT_Type==DHT22)
		{
			value = Dht_byte&0xFFFF;
			if(value>0x7FFF) // temperature is below 0 degree Celsius (negative temperature)
			{
				value -= 0x8000;
				value=0-value;
			}
			value = (float)value/10;
		}
		else if(DHT_Type==DHT11)
		{
			__Tmp = (Dht_byte&0xFFFF)>>8;
			if(__Tmp>0x7F) value = 0-(__Tmp-0x80);
			else value = __Tmp;
		}
	}
	else if(type == DHT_HUMI)
	{
		if(DHT_Type==DHT22)
		{
			value = Dht_byte>>16;
			value = (float)value/10;
		}
		else if(DHT_Type==DHT11)
		{
			value = Dht_byte>>24;
		}
	}
	return value;
}

void DHT_Get_HumiAndTemp_String(uint32_t Dht_byte ,uint8_t type,char *buffer)
{
	float value=0;
	if(type == DHT_TEMP)
	{
		value = Dht_byte&0x0000FFFF;
		if(value>0x7FFF) // temperature is below 0 degree Celsius (negative temperature)
		{
			value -= 0x8000;
			sprintf(buffer,"-%.1f",(float)value/10);
		}
		else sprintf(buffer,"%.1f",(float)value/10);
	}
	else if(type == DHT_HUMI)
	{
		value = Dht_byte>>16;
		value = (float)value/10;
		sprintf(buffer,"%.1f",(float)value);
	}
}




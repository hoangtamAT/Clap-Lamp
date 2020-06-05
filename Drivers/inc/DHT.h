#ifndef __DHT_H
#define __DHT_H


#include "stm32f0xx.h"
#include "hw_config.h"
#include "stdio.h"


#define DHT_PIN           GPIO_Pin_1
#define DHT_GPIO_PORT     GPIOA
#define DHT_GPIO_CLK      RCC_AHBPeriph_GPIOA
#define DHT_GPIO_RCC(a,x) RCC_AHBPeriphClockCmd(a,x)

#define DHT_TEMP	1
#define DHT_HUMI	2
#define DHT11			11
#define DHT22			22

#define DHT_ERR		(uint32_t)0xFFFFFFFF

#define DHT_PIN_HIGH()	GPIO_SetBits(DHT_GPIO_PORT,DHT_PIN);
#define DHT_PIN_LOW()		GPIO_ResetBits(DHT_GPIO_PORT,DHT_PIN);

void DHT_init(uint8_t type);
void DHT_PIN_INPUT(void);
void DHT_PIN_OUTPUT(void);
uint32_t DHT_Get_byte(void);
float DHT_Get_HumiAndTemp(uint32_t Dht_byte ,uint8_t type);
void DHT_Get_HumiAndTemp_String(uint32_t Dht_byte ,uint8_t type,char *buffer);
#endif


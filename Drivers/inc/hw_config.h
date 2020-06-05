#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H

#include "stm8s.h"
#include "VarGlobal.h"

#define ON_PIN(PORT,PIN)	GPIO_SetBits(PORT,PIN)
#define OFF_PIN(PORT,PIN)	GPIO_ResetBits(PORT,PIN)

typedef enum
{
	MODE_UNLOCK=0,
	MODE_LOCK_BUZZ,
	MODE_LOCK_SILENT,
	MODE_ON_KEY,
	MODE_TURN_OFF
}ModeActive;

typedef enum
{
	Action_Unlock=1,
	Action_Lock_Buzz,
	Action_Lock_Silent,
	Action_On_Key,
	Action_Turn_Off,
	Action_Warning_On,
	Action_Warning_Off,
	Action_Error
}ActionM;

#define IN_LOCK_EXTI_Priority		0
#define IN_UNLOCK_EXTI_Priority		0
#define IN_SILENT_EXTI_Priority		0
#define IN_KEY_EXTI_Priority		0
#define IN_VAKEY_EXTI_Priority		0

#define TIMER_DELAY_PREEMPTION_PRIORITY		2
#define TIMER_CTRL_PREEMPTION_PRIORITY		1

#define TIMER_DELAY												TIM3
#define TIMER_DELAY_PERIOD								9
#define TIMER_DELAY_PRESCALER							799
#define TIMER_DELAY_CLOCK									RCC_APB1Periph_TIM3
#define TIMER_DELAY_RCC(a,x)					  	RCC_APB1PeriphClockCmd(a,x)
#define TIMER_DELAY_IRQ_CHANNEL						TIM3_IRQn
#define TIMER_DELAY_IRQ_HANDLER						TIM3_IRQHandler

#define TIMER_CTRL												TIM14
#define TIMER_CTRL_PERIOD									99
#define TIMER_CTRL_PRESCALER							799
#define TIMER_CTRL_CLOCK									RCC_APB1Periph_TIM14
#define TIMER_CTRL_RCC(a,x)					  		RCC_APB1PeriphClockCmd(a,x)
#define TIMER_CTRL_IRQ_CHANNEL						TIM14_IRQn
#define TIMER_CTRL_IRQ_HANDLER						TIM14_IRQHandler


/** INPUT PIN */
#define IN_LOCK_PIN          				GPIO_Pin_1
#define IN_LOCK_PORT   							GPIOA
#define IN_LOCK_GPIO_CLK     				RCC_AHBPeriph_GPIOA
#define IN_LOCK_RCC(a,x)     				RCC_AHBPeriphClockCmd(a,x)
#define IN_LOCK_EXTI_PinSource			EXTI_PinSource1
#define IN_LOCK_EXTI_PortSource			EXTI_PortSourceGPIOA
#define IN_LOCK_EXTI_Line						EXTI_Line1
#define IN_LOCK_EXTI_IRQn						EXTI0_1_IRQn
#define IN_LOCK_IRQHandler					EXTI0_1_IRQHandler

#define IN_UNLOCK_PIN         			GPIO_Pin_2
#define IN_UNLOCK_PORT   						GPIOA
#define IN_UNLOCK_GPIO_CLK    			RCC_AHBPeriph_GPIOA
#define IN_UNLOCK_RCC(a,x)    			RCC_AHBPeriphClockCmd(a,x)
#define IN_UNLOCK_EXTI_PinSource		EXTI_PinSource2
#define IN_UNLOCK_EXTI_PortSource		EXTI_PortSourceGPIOA
#define IN_UNLOCK_EXTI_Line					EXTI_Line2
#define IN_UNLOCK_EXTI_IRQn					EXTI2_3_IRQn
#define IN_UNLOCK_IRQHandler				EXTI2_3_IRQHandler

#define IN_SILENT_PIN         			GPIO_Pin_3
#define IN_SILENT_PORT   						GPIOA
#define IN_SILENT_GPIO_CLK    			RCC_AHBPeriph_GPIOA
#define IN_SILENT_RCC(a,x)    			RCC_AHBPeriphClockCmd(a,x)
#define IN_SILENT_EXTI_PinSource		EXTI_PinSource3
#define IN_SILENT_EXTI_PortSource		EXTI_PortSourceGPIOA
#define IN_SILENT_EXTI_Line					EXTI_Line3
#define IN_SILENT_EXTI_IRQn					EXTI2_3_IRQn
#define IN_SILENT_IRQHandler				EXTI2_3_IRQHandler


// Start key mode to OPEN BIKE without Key phisy
#define IN_KEY_PIN         					GPIO_Pin_4
#define IN_KEY_PORT   							GPIOA
#define IN_KEY_GPIO_CLK    					RCC_AHBPeriph_GPIOA
#define IN_KEY_RCC(a,x)    					RCC_AHBPeriphClockCmd(a,x)
#define IN_KEY_EXTI_PinSource				EXTI_PinSource4
#define IN_KEY_EXTI_PortSource			EXTI_PortSourceGPIOA
#define IN_KEY_EXTI_Line						EXTI_Line4
#define IN_KEY_EXTI_IRQn						EXTI4_15_IRQn
#define IN_KEY_IRQHandler						EXTI4_15_IRQHandler

// VA - Volt after key
#define IN_VAKEY_PIN         				GPIO_Pin_9
#define IN_VAKEY_PORT   						GPIOA
#define IN_VAKEY_GPIO_CLK    				RCC_AHBPeriph_GPIOA
#define IN_VAKEY_RCC(a,x)    				RCC_AHBPeriphClockCmd(a,x)
#define IN_VAKEY_EXTI_PinSource			EXTI_PinSource9
#define IN_VAKEY_EXTI_PortSource		EXTI_PortSourceGPIOA
#define IN_VAKEY_EXTI_Line					EXTI_Line9
#define IN_VAKEY_EXTI_IRQn					EXTI4_15_IRQn
#define IN_VAKEY_IRQHandler					EXTI4_15_IRQHandler

/** OUTPUT STATUS */
#define OUT_BUZZ_PIN          		GPIO_Pin_0
#define OUT_BUZZ_PORT   					GPIOA
#define OUT_BUZZ_GPIO_CLK     		RCC_AHBPeriph_GPIOA
#define OUT_BUZZ_RCC(a,x)     		RCC_AHBPeriphClockCmd(a,x)

#define OUT_LIGHT_PIN          		GPIO_Pin_6
#define OUT_LIGHT_PORT   					GPIOA
#define OUT_LIGHT_GPIO_CLK     		RCC_AHBPeriph_GPIOA
#define OUT_LIGHT_RCC(a,x)     		RCC_AHBPeriphClockCmd(a,x)

#define OUT_LOCK_PIN          		GPIO_Pin_5
#define OUT_LOCK_PORT   					GPIOA
#define OUT_LOCK_GPIO_CLK     		RCC_AHBPeriph_GPIOA
#define OUT_LOCK_RCC(a,x)     		RCC_AHBPeriphClockCmd(a,x)

#define OUT_ONKEY_PIN          		GPIO_Pin_7
#define OUT_ONKEY_PORT   					GPIOA
#define OUT_ONKEY_GPIO_CLK     		RCC_AHBPeriph_GPIOA
#define OUT_ONKEY_RCC(a,x)     		RCC_AHBPeriphClockCmd(a,x)



void RCC_HSI_Configuration(void);
void delay_ms(uint16_t delay);
void Timer_Config(void);
void Input_Configuration(void);
void Ouput_Configration(void);
void Active_Mode(uint8_t mode);
void config_Pin_Not_Use(void);

#endif


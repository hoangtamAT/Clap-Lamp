#include "hw_config.h"

TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
GPIO_InitTypeDef GPIO_InitStructure;
EXTI_InitTypeDef   EXTI_InitStructure;

void RCC_HSI_Configuration(void)
{
	RCC_HSICmd(ENABLE);
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLKConfig(RCC_HCLK_Div1);
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	//RCC_PREDIV1Config(RCC_PREDIV1_Div2);
	//RCC_PLLConfig(RCC_PLLSource_HSI,RCC_PLLMul_3);
	//RCC_PLLCmd(ENABLE);
	//while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET){}
	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
	while(RCC_GetSYSCLKSource() != 0x00){};
}


void Timer_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	
	TIMER_DELAY_RCC(TIMER_DELAY_CLOCK,ENABLE);
	TIMER_CTRL_RCC(TIMER_CTRL_CLOCK,ENABLE);
		/* -------------------------------------------------------------------------- 
	 * Ctrl TIMER configuration
	 * --------------------------------------------------------------------------
	 * 12 MHz / 12000 = 1KHz (1ms)
	 * -------------------------------------------------------------------------- */ 
	TIM_TimeBaseStructure.TIM_Period 			= TIMER_CTRL_PERIOD;      
	TIM_TimeBaseStructure.TIM_Prescaler 		= TIMER_CTRL_PRESCALER;       
	TIM_TimeBaseStructure.TIM_ClockDivision 	= TIM_CKD_DIV1;    
	TIM_TimeBaseStructure.TIM_CounterMode 		= TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIMER_CTRL, &TIM_TimeBaseStructure);
	
	TIM_ClearITPendingBit(TIMER_CTRL, TIM_IT_Update);

	TIM_ITConfig(TIMER_CTRL, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIMER_CTRL, ENABLE);
	 /* -------------------------------------------------------------------------- 
	 * Delay TIMER configuration
	 * --------------------------------------------------------------------------
	 * 12 MHz / 12 = 1MHz (1µs)
	 * -------------------------------------------------------------------------- */ 
	TIM_TimeBaseStructure.TIM_Period 			= TIMER_DELAY_PERIOD;      
	TIM_TimeBaseStructure.TIM_Prescaler 		= TIMER_DELAY_PRESCALER;       
	TIM_TimeBaseStructure.TIM_ClockDivision 	= TIM_CKD_DIV1;    
	TIM_TimeBaseStructure.TIM_CounterMode 		= TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIMER_DELAY, &TIM_TimeBaseStructure);
	
	TIM_UpdateRequestConfig(TIMER_DELAY, TIM_UpdateSource_Global);
	
	TIM_ClearITPendingBit(TIMER_DELAY, TIM_IT_Update);
		
	/* Enable TIMER Update interrupt */
	TIM_ITConfig(TIMER_DELAY, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIMER_DELAY, DISABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel 					 		= TIMER_DELAY_IRQ_CHANNEL;
	NVIC_InitStructure.NVIC_IRQChannelPriority 		= TIMER_DELAY_PREEMPTION_PRIORITY;
	NVIC_InitStructure.NVIC_IRQChannelCmd 						= ENABLE;
	NVIC_Init(&NVIC_InitStructure);			
	
	NVIC_InitStructure.NVIC_IRQChannel 					 		= TIMER_CTRL_IRQ_CHANNEL;
	NVIC_InitStructure.NVIC_IRQChannelPriority 		= TIMER_CTRL_PREEMPTION_PRIORITY;
	NVIC_InitStructure.NVIC_IRQChannelCmd 						= ENABLE;
	NVIC_Init(&NVIC_InitStructure);		
}

void delay_ms(uint16_t delay)
{
	TIM_UpdateRequestConfig(TIMER_DELAY, TIM_UpdateSource_Global);
	counter_delay = delay;
	TIM_SetCounter(TIMER_DELAY, 0);
	/* TIM4 enable counter */
  TIM_Cmd(TIMER_DELAY, ENABLE);
	/* Wait for 'delay' milliseconds */
	while(counter_delay != 0);
	/* TIM4 disable counter */
	TIM_Cmd(TIMER_DELAY, DISABLE);
}

void Ouput_Configration(void)
{
	OUT_BUZZ_RCC(OUT_BUZZ_GPIO_CLK,ENABLE);
	OUT_LIGHT_RCC(OUT_LIGHT_GPIO_CLK,ENABLE);
	OUT_LOCK_RCC(OUT_LOCK_GPIO_CLK,ENABLE);
	OUT_LOCK_RCC(OUT_LOCK_GPIO_CLK,ENABLE);
	OUT_ONKEY_RCC(OUT_ONKEY_GPIO_CLK,ENABLE);
	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = OUT_BUZZ_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(OUT_BUZZ_PORT, &GPIO_InitStructure);
	
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = OUT_LIGHT_PIN;
  GPIO_Init(OUT_LIGHT_PORT, &GPIO_InitStructure);
	
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Pin = OUT_LOCK_PIN;
  GPIO_Init(OUT_LOCK_PORT, &GPIO_InitStructure);
	
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Pin = OUT_ONKEY_PIN;
  GPIO_Init(OUT_ONKEY_PORT, &GPIO_InitStructure);
}

void Input_Configuration(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	IN_LOCK_RCC(IN_LOCK_GPIO_CLK,ENABLE);
	IN_UNLOCK_RCC(IN_UNLOCK_GPIO_CLK,ENABLE);
	IN_SILENT_RCC(IN_SILENT_GPIO_CLK,ENABLE);
	IN_KEY_RCC(IN_KEY_GPIO_CLK,ENABLE);
	IN_VAKEY_RCC(IN_VAKEY_GPIO_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Pin = IN_LOCK_PIN;
  GPIO_Init(IN_LOCK_PORT, &GPIO_InitStructure);
	

  GPIO_InitStructure.GPIO_Pin = IN_UNLOCK_PIN;
  GPIO_Init(IN_UNLOCK_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = IN_SILENT_PIN;
  GPIO_Init(IN_SILENT_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = IN_KEY_PIN;
  GPIO_Init(IN_KEY_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = IN_VAKEY_PIN;
  GPIO_Init(IN_VAKEY_PORT, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	/* Connect EXTI0 Line to BTN_UP pin */
  SYSCFG_EXTILineConfig(IN_LOCK_EXTI_PortSource, IN_LOCK_EXTI_PinSource);
	SYSCFG_EXTILineConfig(IN_UNLOCK_EXTI_PortSource, IN_UNLOCK_EXTI_PinSource);
	SYSCFG_EXTILineConfig(IN_SILENT_EXTI_PortSource, IN_SILENT_EXTI_PinSource);
	SYSCFG_EXTILineConfig(IN_KEY_EXTI_PortSource, IN_KEY_EXTI_PinSource);
	SYSCFG_EXTILineConfig(IN_VAKEY_EXTI_PortSource, IN_VAKEY_EXTI_PinSource);
	/* Configure EXTI5 line */
  EXTI_InitStructure.EXTI_Line = IN_LOCK_EXTI_Line;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	
	/* Configure EXTI6 line */
  EXTI_InitStructure.EXTI_Line = IN_UNLOCK_EXTI_Line;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	
	EXTI_InitStructure.EXTI_Line = IN_SILENT_EXTI_Line;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	
	EXTI_InitStructure.EXTI_Line = IN_KEY_EXTI_Line;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	
	EXTI_InitStructure.EXTI_Line = IN_VAKEY_EXTI_Line;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);


  /* Enable and set EXTI5 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = IN_LOCK_EXTI_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = IN_LOCK_EXTI_Priority;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	  /* Enable and set EXTI6 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = IN_UNLOCK_EXTI_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = IN_UNLOCK_EXTI_Priority;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = IN_SILENT_EXTI_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = IN_SILENT_EXTI_Priority;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = IN_KEY_EXTI_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = IN_KEY_EXTI_Priority;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = IN_VAKEY_EXTI_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = IN_VAKEY_EXTI_Priority;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void Active_Mode(uint8_t mode)
{
	uint8_t i;
	switch(mode)
	{
		case MODE_LOCK_BUZZ:
			OFF_PIN(OUT_ONKEY_PORT,OUT_ONKEY_PIN);
			ON_PIN(OUT_BUZZ_PORT,OUT_BUZZ_PIN);
			ON_PIN(OUT_LIGHT_PORT,OUT_LIGHT_PIN);
			delay_ms(300);
			OFF_PIN(OUT_BUZZ_PORT,OUT_BUZZ_PIN);
			OFF_PIN(OUT_LIGHT_PORT,OUT_LIGHT_PIN);
		
			ON_PIN(OUT_LOCK_PORT,OUT_LOCK_PIN);	
			CurrentMode = MODE_LOCK_BUZZ;		
			break;
		case MODE_LOCK_SILENT:
			OFF_PIN(OUT_BUZZ_PORT,OUT_BUZZ_PIN);
			ON_PIN(OUT_LIGHT_PORT,OUT_LIGHT_PIN);
			delay_ms(300);
			OFF_PIN(OUT_LIGHT_PORT,OUT_LIGHT_PIN);
			OFF_PIN(OUT_ONKEY_PORT,OUT_ONKEY_PIN);
			ON_PIN(OUT_LOCK_PORT,OUT_LOCK_PIN);	
			CurrentMode = MODE_LOCK_SILENT;			
			break;
		case MODE_UNLOCK:
			OFF_PIN(OUT_BUZZ_PORT,OUT_BUZZ_PIN);
			OFF_PIN(OUT_ONKEY_PORT,OUT_ONKEY_PIN);
			OFF_PIN(OUT_LOCK_PORT,OUT_LOCK_PIN);
			for(i=0;i<2;i++)
			{
				ON_PIN(OUT_LIGHT_PORT,OUT_LIGHT_PIN);
				delay_ms(300);
				OFF_PIN(OUT_LIGHT_PORT,OUT_LIGHT_PIN);
				delay_ms(300);
			}
			CurrentMode = MODE_UNLOCK;		
			break;
		case MODE_ON_KEY:
			OFF_PIN(OUT_BUZZ_PORT,OUT_BUZZ_PIN);
			OFF_PIN(OUT_LOCK_PORT,OUT_LOCK_PIN);
			ON_PIN(OUT_LIGHT_PORT,OUT_LIGHT_PIN);
			delay_ms(300);
			OFF_PIN(OUT_LIGHT_PORT,OUT_LIGHT_PIN);
			ON_PIN(OUT_ONKEY_PORT,OUT_ONKEY_PIN);
			CurrentMode = MODE_ON_KEY;			
			break;
		case MODE_TURN_OFF:
			OFF_PIN(OUT_BUZZ_PORT,OUT_BUZZ_PIN);
			OFF_PIN(OUT_LOCK_PORT,OUT_LOCK_PIN);
			OFF_PIN(OUT_LIGHT_PORT,OUT_LIGHT_PIN);
			OFF_PIN(OUT_ONKEY_PORT,OUT_ONKEY_PIN);
			CurrentMode = MODE_UNLOCK;			
			break;
		default:
			OFF_PIN(OUT_BUZZ_PORT,OUT_BUZZ_PIN);
			OFF_PIN(OUT_LOCK_PORT,OUT_LOCK_PIN);
			OFF_PIN(OUT_LIGHT_PORT,OUT_LIGHT_PIN);
			OFF_PIN(OUT_ONKEY_PORT,OUT_ONKEY_PIN);
			CurrentMode = 0;			
			break;	
	}
}

void config_Pin_Not_Use(void)
{
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,DISABLE);
	
}



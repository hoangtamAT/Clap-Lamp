/**
  ******************************************************************************
  * @file    Project/main.c 
  * @author  MCD Application Team
  * @version V2.3.0
  * @date    16-June-2017
  * @brief   Main program body
   ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 


/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "main.h"
#include "VarMain.h"
    uint32_t _f_clk=0;
/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void CLK_Config(void);
static void timerConfig(void);
static void gpioConfig(void);

void main(void)
{
  CLK_Config();
  _f_clk=CLK_GetClockFreq();
  gpioConfig();
  timerConfig(); 
  /* Infinite loop */
  enableInterrupts();
//  delay_ms(500);
//  GPIO_WriteHigh(OUT_BUZZ_PORT,OUT_BUZZ_PIN);
//  delay_ms(500);
//  GPIO_WriteLow(OUT_BUZZ_PORT,OUT_BUZZ_PIN);
  OFF_PIN(OUT_LOAD_PORT,OUT_LOAD_PIN);
  halt();
  while (1)
  {
   if(flag_timer==0) 
   {
     TIM2_Cmd(DISABLE);
     halt();
   }
  }
  
}


static void CLK_Config(void)
{
    CLK_DeInit();

    /* Configure the Fcpu to DIV1*/
    //CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
    
    /* Configure the HSI prescaler to the optimal value */
    CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV2); //2Mhz
    /* Configure the system clock to use HSI clock source and to run at 16Mhz */
    CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSI, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE);
}

static void timerConfig(void)
  {
    //System Clk = 8Mhz   
      CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2,ENABLE);
      TIM2_TimeBaseInit(TIM2_PRESCALER_4096,195); //100ms
      TIM2_ClearFlag(TIM2_FLAG_UPDATE);
      TIM2_ITConfig(TIM2_IT_UPDATE,ENABLE);
      TIM2_Cmd(DISABLE);
  }

static void gpioConfig(void)
{
   /* Define FLASH programming time */
  FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);
  
  GPIO_Init(OUT_LOAD_PORT,OUT_LOAD_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);
  /* Config Extern interrupt */
  
  GPIO_Init(IN_SIGNAL_PORT,IN_SIGNAL_PIN,GPIO_MODE_IN_FL_IT);
  EXTI_SetExtIntSensitivity(IN_SIGNAL_EXT_PORT, EXTI_SENSITIVITY_RISE_ONLY);
  //EXTI_SetTLISensitivity(EXTI_TLISENSITIVITY_RISE_ONLY);
  
}


#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

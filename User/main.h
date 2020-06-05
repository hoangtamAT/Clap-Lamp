#ifndef __MAIN_H
#define __MAIN_H

#include "stm8s.h"

#define ON_PIN(PORT,PIN)	GPIO_WriteLow(PORT,PIN)
#define OFF_PIN(PORT,PIN)	GPIO_WriteHigh(PORT,PIN)


/** Input Pin*/
#define IN_SIGNAL_PIN                     GPIO_PIN_6
#define IN_SIGNAL_PORT                    GPIOC
#define IN_SIGNAL_EXT_PORT                EXTI_PORT_GPIOC

/** Output Pin*/
#define OUT_LOAD_PIN     GPIO_PIN_7
#define OUT_LOAD_PORT    GPIOC

#endif 


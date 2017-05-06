/**
  ******************************************************************************
  * @file    ADC/ADC_RegularConversion_Interrupt/Inc/main.h 
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    17-February-2017
  * @brief   Header for main.c module
  ******************************************************************************
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
//#define USE_FULL_ASSERT
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_adc.h"
#include "main.h"
//#include "stm324x9i_eval.h"

/* Exported types ------------------------------------------------------------*/
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* AdcHandle);
/* Exported constants --------------------------------------------------------*/
ADC_HandleTypeDef    AdcHandle;
ADC_ChannelConfTypeDef sConfig;

/* User can use this section to tailor ADCx instance used and associated 
   resources */
/* Definition for ADCx clock resources */
#define ADCx                            ADC1
#define ADCx_CLK_ENABLE()               __HAL_RCC_ADC1_CLK_ENABLE();
#define ADCx_CHANNEL_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()
     
#define ADCx_FORCE_RESET()              __HAL_RCC_ADC_FORCE_RESET()
#define ADCx_RELEASE_RESET()            __HAL_RCC_ADC_RELEASE_RESET()

/* Definition for ADCx Channel Pin */
#define ADCx_CHANNEL_PIN                GPIO_PIN_1
#define ADCx_CHANNEL_GPIO_PORT          GPIOA 
#define ADC_PIN                         PA1

/* Definition for ADCx's Channel */
#define ADCx_CHANNEL                    ADC_CHANNEL_1 

/* Definition for ADCx's NVIC */
#define ADCx_IRQn                       ADC_IRQn

/* Exported macro ------------------------------------------------------------*/

#define BSP_LED_Init(X)  pinMode(X,OUTPUT)
#define BSP_LED_On(X) digitalWrite(X,LOW)
#define BSP_LED_Off(X) digitalWrite(X,HIGH)
#define LED1 16
#define LED3 17

// change "Serial" as required
#define SERIALX Serial
/* Exported functions ------------------------------------------------------- */
#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

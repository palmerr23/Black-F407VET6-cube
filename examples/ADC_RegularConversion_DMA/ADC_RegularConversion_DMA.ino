/**
 * 12 bits DMA, single ADC
 * DMA is stopped after one buffer, to allow the buffer to be processed, unchanged.
 * DMA can be left running - see instructions in loop()and HAL_ADC_ConvCpltCallback(). 
  ******************************************************************************
  * @file    ADC/ADC_RegularConversion_DMA/Src/main.c 
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    17-February-2017
  * Modified 6-May-2017 RP for Arduino
  * @brief   This example describes how to use the DMA to transfer 
  *          continuously converted data.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/** @addtogroup STM32F4xx_HAL_Examples
  * @{
  */

/** @addtogroup ADC_RegularConversion_DMA
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* ADC handler declaration */
ADC_HandleTypeDef    AdcHandle;

/* Variable used to get converted value */
#define NSAMPLES 1024
__IO uint32_t convBuffer[NSAMPLES];   // DMA transfers in 32 bit chunks. 
#define NPRINT 128                    // just display the first NPRINT samples

/* Private function prototypes -----------------------------------------------*/

static void Error_Handler(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
void setup(void)
{
  ADC_ChannelConfTypeDef sConfig;
  
  /* STM32F4xx HAL library initialization:
       - Configure the Flash prefetch, instruction and Data caches
       - Configure the Systick to generate an interrupt each 1 msec
       - Set NVIC Group Priority to 4
       - Global MSP (MCU Support Package) initialization
     */
  HAL_Init();
    
  SERIALX.begin(9600);
  delay(200);
  SERIALX.println("\n");
  SERIALX.println("ADC Demo - Regular Conversion DMA: ADC3 on PA1");
  
  /* Configure LED1 and LED2 */
  BSP_LED_Init(LED1);
  BSP_LED_Init(LED2);
  BSP_LED_Off(LED1);
  BSP_LED_Off(LED2);
  
  /*##-1- Configure the ADC peripheral #######################################*/
  AdcHandle.Instance          = ADCx;
  
  AdcHandle.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2;
  AdcHandle.Init.Resolution = ADC_RESOLUTION_12B;
  AdcHandle.Init.ScanConvMode = DISABLE;
  AdcHandle.Init.ContinuousConvMode = ENABLE;
  AdcHandle.Init.DiscontinuousConvMode = DISABLE;
  AdcHandle.Init.NbrOfDiscConversion = 0;
  AdcHandle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  AdcHandle.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_CC1;
  AdcHandle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  AdcHandle.Init.NbrOfConversion = 1;
  AdcHandle.Init.DMAContinuousRequests = ENABLE;
  AdcHandle.Init.EOCSelection = DISABLE;
      
  if(HAL_ADC_Init(&AdcHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler(); 
  }
  
  /*##-2- Configure ADC regular channel ######################################*/  
  sConfig.Channel = ADCx_CHANNEL;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  sConfig.Offset = 0;
  
  if(HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK)
  {
    /* Channel Configuration Error */
    Error_Handler(); 
  }
}

int i;
volatile uint32_t started, finished;
int32_t elapsed;
float tsamp;
void loop(void)
{ 

  /*##-3- Start the conversion process and enable interrupt ##################*/
  /* Note: Considering IT occurring after each number of ADC conversions      */
  /*       (IT by DMA end of transfer), select sampling time and ADC clock    */
  /*       with sufficient duration to not create an overhead situation in    */
  /*       IRQHandler. */ 

  started = micros();

 // move  HAL_ADC_Start_DMA() to setup, for continuous conversions
  if(HAL_ADC_Start_DMA(&AdcHandle, (uint32_t*)convBuffer, NSAMPLES) != HAL_OK) 
  {
    /* Start Conversation Error */
    Error_Handler(); 
  }   
   delay(300); // wait for the ADC/DMA do their work - more than a single (circular) buffer may be transferred
   
   
   BSP_LED_Off(LED1); // turn off indicator that DMA is completed
  // SERIALX.println("Stopped");
   
    /*SERIALX.print("Started ");
    SERIALX.print(started);
    SERIALX.print(", finished ");
    SERIALX.println(finished);
    */
    elapsed = finished - started;
    SERIALX.print("Capture took ");
    SERIALX.print(elapsed);
    SERIALX.print(" uS, time per sample = ");
    tsamp = (float)elapsed/NSAMPLES;
    SERIALX.print(tsamp);
    SERIALX.print(", sample frequency ");
    SERIALX.print(1/tsamp);
    SERIALX.print(" MHz\nValues:\n");
   for(i=0; i < min(NPRINT, NSAMPLES); i++){
     SERIALX.print(convBuffer[i]);
     SERIALX.print(", ");
     if(i % 8 == 7) SERIALX.println("");
   }
   SERIALX.println("");
   
   delay(2000);
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
 /* Short pulses */
   while(1) { 
     BSP_LED_On(LED2);
     delay (100);
     BSP_LED_Off(LED2);
     delay (500);
    } 
}

/**
  * @brief  Conversion complete callback in non blocking mode 
  * @param  AdcHandle : AdcHandle handle
  * @note   This example shows a simple way to report end of conversion, and 
  *         you can add your own implementation.    
  * @retval None
  */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* AdcHandle)
{
  finished = micros();
 
  /* Turn LED1 on: Transfer process is correct */
  BSP_LED_On(LED1);
  
  // stop the DMA. 
  HAL_ADC_Stop_DMA(AdcHandle); // comment this line for continuous conversion
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

 
   SERIALX.print("Assert failed! ");
   SERIALX.print("File '");
   SERIALX.print((char*)file);
   SERIALX.print("', Line ");
   SERIALX.println(line);
  
  /* Rapid blink */
   while(1) { 
     BSP_LED_On(LED2);
     delay (100);
     BSP_LED_Off(LED2);
     delay (100);
    } 
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "variant.h"

#ifdef __cplusplus
extern "C" {
#endif

// Pin number
const PinName digital_arduino[] = {
//J2 connector Right side - USB side, inside row
  PE3,  //D0 - BUTTON K1 (USE INPUT_PULLUP)
  PE5,  //D1
  PC13, //D2
  PC1,  //D3
  PC3,  //D4
  PA1,  //D5
  PA3,  //D6
  PA5,  //D7
  PA7,  //D8 - BUILTIN LED D3
  PC5,  //D9
  PB1,  //D10
  PE8,  //D11
  PE10, //D12
  PE12, //D13
  PE14, //D14
  PB10, //D15
  PB12, //D16
  PB14, //D17
//J3 connector Left side  - SDIO side, inside row  
  PE1,  //D18
  PB9,  //D19
  PB7,  //D20
  PB5,  //D21
  PD7,  //D22
  PD5,  //D23
  PD3,  //D24
  PD1,  //D25
  PC12, //D26
  PC10, //D27
  PA12, //D28
  PA10, //D29 - RX1
  PA8,  //D30
  PC8,  //D31
  PC6,  //D32
  PD14, //D33
  PD12, //D34
  PD10, //D35
  PD8,  //D36
//J2 Connector Left Side - USB side, outside row
  PE2,  //D37
  PE4,  //D38 - BUTTON K0 (USE INPUT_PULLUP)
  PE6,  //D39
  PC0,  //D40
  PC2,  //D41
  PA0,  //D42 - BUTTON WK_UP (USE INPUT_PULLDOWN)
  PA2,  //D43
  PA4,  //D44
  PA6,  //D45 - BUILTIN LED D2
  PC4,  //D46
  PB0,  //D47
  PE7,  //D48
  PE9,  //D49
  PE11, //D50
  PE13, //D51
  PE15, //D52
  PB11, //D53
  PB13, //D54
//J3 connector Right side - SDIO side, outside row
  PE0,  //D55
  PB8,  //D56
  PB6,  //D57
  PB3,  //D58
  PD6,  //D59
  PD4,  //D60
  PD2,  //D61
  PD0,  //D62
  PC11, //D63
  PA15, //D64
  PA11, //D65
  PA9,  //D66 - TX1
  PC9,  //D67
  PC7,  //D68
  PD15, //D69
  PD13, //D70
  PD11, //D71
  PD9,  //D72
  PB15, //D73
//Duplicated to have A0-A5 as F407 do not have Uno like connector
  PA0,  //D74/A0
  PA1,  //D75/A1
  PA2,  //D76/A2
  PA3,  //D77/A3
  PB0,  //D78/A4
  PB1   //D79/A5
// Here we could continue to define Analog pin if we want A6,...
// need to add J1 (TFT connector)
};

#ifdef __cplusplus
}
#endif

/*
 * UART objects
 */

UARTClass Serial(USART3_E);    //available on PD8/PD9

void serialEvent() __attribute__((weak));
void serialEvent() { }

void serialEventRun(void)
{
  if (Serial.available()) serialEvent();
}

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

void __libc_init_array(void);

uint32_t pinNametoPinNumber(PinName p)
{
  uint32_t i = 0;
  for(i = 0; i < NUM_DIGITAL_PINS; i++) {
	  if (digital_arduino[i] == p)
		  break;
  }
  return i;
}

void init( void )
{
  hw_config_init();
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 168000000
  *            HCLK(Hz)                       = 168000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 336
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
                                  RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

  /* STM32F405x/407x/415x/417x Revision Z devices: prefetch is supported  */
  if (HAL_GetREVID() == 0x1001)
  {
    /* Enable the Flash prefetch */
    __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
  }
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

#ifdef __cplusplus
}
#endif

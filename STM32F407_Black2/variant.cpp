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
//J2 connector Left, Right side - USB side, 
  PE2,  //D0
  PE3,  //D1 - BUTTON K1 (USE INPUT_PULLUP)   
  PE4,  //D2 - BUTTON K0 (USE INPUT_PULLUP)
  PE5,  //D3
  PE6,  //D4
  PC13, //D5
  PC0,  //D6
  PC1,  //D7
  PC2,  //D8 - SPI2
  PC3,  //D9 - SPI2
  PA0,  //D10 - BUTTON WK_UP (USE INPUT_PULLDOWN for GP button)
  PA1,  //D11
  PA2,  //D12
  PA3,  //D13
  PA4,  //D14
  PA5,  //D15 - SPI1 (or SPI3)
  PA6,  //D16 - BUILTIN LED D2 - SPI1 (or SPI3)
  PA7,  //D17 - BUILTIN LED D3 - SPI1 (or SPI3)
  PC4,  //D18
  PC5,  //D19
  PB0,  //D20 - Flash_CS
  PB1,  //D21 - LCD_BL driver
  PE7,  //D22
  PE8,  //D23
  PE9,  //D24 - SPI2
  PE10, //D25 - SPI2
  PE11, //D26 - SPI2
  PE12, //D27
  PE13, //D28
  PE14, //D29
  PE15, //D30
  PB10, //D31 - I2C2
  PB11, //D32 - I2C2
  PB12, //D33 - SPI2
  PB13, //D34 - SPI2
  PB14, //D35 - SPI3 (or SPI1) - FLASH/NRF 
//J3 connector Left, Right side - SDIO side
  PE1,  //D36
  PE0,  //D37
  PB9,  //D38
  PB8,  //D39 - I2C1
  PB7,  //D40 - I2C1
  PB6,  //D41
  PB5,  //D42 - SPI3 (or SPI1) - FLASH/NRF
  PB3,  //D43 - SPI3 (or SPI1) - FLASH/NRF
  PD7,  //D44
  PD6,  //D45 - USART2
  PD5,  //D46 - USART2
  PD4,  //D47
  PD3,  //D48
  PD2,  //D49 - SDIO
  PD1,  //D50
  PD0,  //D51
  PC12, //D52 - SDIO
  PC11, //D53 - SDIO
  PC10, //D54 - SDIO
  PA15, //D55
  PA12, //D56 - USB DM
  PA11, //D57 - USB DP
  PA10, //D58 - RX1
  PA9,  //D59 - TX1
  PA8,  //D60
  PC9,  //D61 - SDIO
  PC8,  //D62 - SDIO
  PC7,  //D63
  PC6,  //D64
  PD15, //D65
  PD14, //D66
  PD13, //D67
  PD12, //D68
  PD11, //D69
  PD10, //D70
  PD9,  //D71 - USART3
  PD8,  //D72 - USART3
  PB15, //D73
  PA13, //D74 SWDIO (JTAG)
  PA14, //D75 SWCLK (JTAG)
  PB4,  //D76 CONNECTED TO NRF HEADER Pin 7, Winbond Flash Pin 2, NRST JTAG Pin 3
  PB2,  //D77 BOOT1 - J3
//  PC14,	// XTAL
//  PC15, // XTAL
// PortPins duplicated to have A0-A9 as F407 do not have Uno like connector
// Update PeripheralPins.c to match
  PA0,  //D78/A0
  PA1,  //D79/A1
  PA2,  //D80/A2
  PA3,  //D81/A3
  PB0,  //D82/A4
  PB1,  //D83/A5
  PC0,	//D84/A6
  PC1,  //D85/A7
  PC4,  //D86/A8
  PC5,  //D87/A9
  PC2,  //D88/A10 
  PC3,  //D89/A11
//  PA4,  //D82/A4
//  PA5,  //D83/A5
//  PA6,  //D84/A6
//  PA7,  //D85/A7  //  PC2,  //D90/A12

//  PC14, //D87 32.768K XTAL
//  PC15, //D88 32.768K XTAL

// need to add J1 (TFT connector)?
};

#ifdef __cplusplus
}
#endif

/*
 * UART objects
 */

UARTClass Serial(USART3_E);    //available on PD8/PD9
//UARTClass Serial(USART1_E);    //available on 

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

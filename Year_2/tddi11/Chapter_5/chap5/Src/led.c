/**
  ******************************************************************************
  * @file    led.c
  * @author  MCD Application Team
  * @brief   This example code shows how to use the led display feature in the 
  *          STM32L562E-DK driver
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32L5xx_HAL_Examples
  * @{
  */

/** @addtogroup TicTacToe
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void Led_SetHint(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Led demo
  * @param  None
  * @retval None
  */
void Led_demo(void)
{
  uint32_t index = 0;
  
  Led_SetHint();
  
  /* Init and turn on LED 1 to 4  */
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_BLUE);
  UTIL_LCD_DisplayStringAt(0, 120, (uint8_t *)"Initialize then turn on", CENTER_MODE);
  UTIL_LCD_DisplayStringAt(0, 135, (uint8_t *)"each led after 500 ms", CENTER_MODE);

  HAL_Delay(500);
  if (TicTacToe_LED_On(LED9) != TicTacToe_ERROR_NONE)
  {
    Error_Handler();
  }
  
  HAL_Delay(500);
  if (TicTacToe_LED_On(LED10) != TicTacToe_ERROR_NONE)
  {
    Error_Handler();
  }
  
  /* Keep the LEDs on for two seconds */
  HAL_Delay(2000);
  
  /* Turn off the LEDs */ 
  UTIL_LCD_DisplayStringAt(0, 120, (uint8_t *)"        Turn off        ", CENTER_MODE);
  UTIL_LCD_DisplayStringAt(0, 135, (uint8_t *)"each led after 500 ms", CENTER_MODE);
  HAL_Delay(500);
  if (TicTacToe_LED_Off(LED9) != TicTacToe_ERROR_NONE)
  {
    Error_Handler();
  }
  HAL_Delay(500);
  if (TicTacToe_LED_Off(LED10) != TicTacToe_ERROR_NONE)
  {
    Error_Handler();
  }
  
  HAL_Delay(2000);
  
  /* After two seconds, turn on LED10 and LED9 */
  UTIL_LCD_DisplayStringAt(0, 120, (uint8_t *)"      Turn on led 10      ", CENTER_MODE);
  UTIL_LCD_DisplayStringAt(0, 135, (uint8_t *)"                      ", CENTER_MODE);
  if (TicTacToe_LED_On(LED10) != TicTacToe_ERROR_NONE)
  {
    Error_Handler();
  }
  HAL_Delay(500);
  
  UTIL_LCD_DisplayStringAt(0, 120, (uint8_t *)"      Turn on led 9      ", CENTER_MODE);
  if (TicTacToe_LED_On(LED9) != TicTacToe_ERROR_NONE)
  {
    Error_Handler();
  }
  HAL_Delay(500);
  
  /* For about five seconds, toggle all the LEDs */
  UTIL_LCD_DisplayStringAt(0, 120, (uint8_t *)"     Toggle all leds     ", CENTER_MODE);
  while (index < 25)
  {
    HAL_Delay(200);
    index++;
    if (TicTacToe_LED_Toggle(LED9) != TicTacToe_ERROR_NONE)
    {
      Error_Handler();
    }
    if (TicTacToe_LED_Toggle(LED10) != TicTacToe_ERROR_NONE)
    {
      Error_Handler();
    }
  }
}

/**
  * @brief  Display Led demo hint
  * @param  None
  * @retval None
  */
static void Led_SetHint(void)
{
  /* Clear the LCD */ 
  UTIL_LCD_Clear(UTIL_LCD_COLOR_WHITE);
  
  /* Set Led Demo description */
  UTIL_LCD_FillRect(0, 0, 240, 80, UTIL_LCD_COLOR_BLUE);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_BLUE);
  UTIL_LCD_SetFont(&Font24);
  UTIL_LCD_DisplayStringAt(0, 0, (uint8_t *)"Led", CENTER_MODE);
  UTIL_LCD_SetFont(&Font12);
  UTIL_LCD_DisplayStringAt(0, 30, (uint8_t *)"This example shows how to", CENTER_MODE);
  UTIL_LCD_DisplayStringAt(0, 45, (uint8_t *)"initialize, turn on, turn off", CENTER_MODE);
  UTIL_LCD_DisplayStringAt(0, 60, (uint8_t *)"and toggle the leds", CENTER_MODE);
  
  UTIL_LCD_DrawRect(10, 90, 220, 140, UTIL_LCD_COLOR_BLUE);
  UTIL_LCD_DrawRect(11, 91, 218, 138, UTIL_LCD_COLOR_BLUE);
}
/**
  * @}
  */ 

/**
  * @}
  */ 

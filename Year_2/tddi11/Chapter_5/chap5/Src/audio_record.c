/**
  ******************************************************************************
  * @file    audio_record.c
  * @author  MCD Application Team
  * @brief   This example describes how to use TicTacToe AUDIO for record.
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
int16_t                      RecordBuff[4096];
int16_t                      PlaybackBuff[4096];
uint32_t                     RecHalfBuffCplt  = 0;
uint32_t                     RecBuffCplt      = 0;
uint32_t                     PlaybackStarted  = 0;

/* Private function prototypes -----------------------------------------------*/
static void AudioRecord_SetHint(void);
static void Record_Init(void);
static void Playback_Init(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Test TicTacToe AUDIO for record.
  * @param  None
  * @retval None
  */
void AudioRecord_demo(void)
{
  uint32_t i;
  
  /* Display test information */
  AudioRecord_SetHint();
  
  /* Initialize record */
  Record_Init();
  
  /* Initialize playback */
  Playback_Init();
  
  /* Start record */
  if (TicTacToe_AUDIO_IN_Record(1, (uint8_t*) RecordBuff, 8192) != TicTacToe_ERROR_NONE)
  {
    Error_Handler();
  }
  
  /* Start loopback */
  while(UserButtonPressed != SET)
  {
    if(RecHalfBuffCplt == 1)
    {
      /* Store values on Play buff */
      for(i = 0; i < 2048; i++)
      {
        PlaybackBuff[i] = RecordBuff[i];
      }
      if (PlaybackStarted == 0)
      {
        /* Insert a little delay before starting playback to be sure that data are available for playback */
        /* Without this delay, potential noise when optimization high is selected for compiler */
        HAL_Delay(10);
        /* Start the playback */
        if (TicTacToe_AUDIO_OUT_Play(0, (uint8_t *) PlaybackBuff, 8192) != TicTacToe_ERROR_NONE)
        {
          Error_Handler();
        }
        PlaybackStarted = 1;
      }      
      RecHalfBuffCplt = 0;
    }
    if(RecBuffCplt == 1)
    {
      /* Store values on Play buff */
      for(i = 2048; i < 4096; i++)
      {
        PlaybackBuff[i] = RecordBuff[i];
      }
      RecBuffCplt  = 0;
    }
  }
  /* Add delay to avoid rebound and reset it status */
  HAL_Delay(500);
  UserButtonPressed = RESET;
  
  /* Stop playback */
  if (TicTacToe_AUDIO_OUT_Stop(0) != TicTacToe_ERROR_NONE)
  {
    Error_Handler();
  }
  
  /* Stop record */
  if(TicTacToe_AUDIO_IN_Stop(1) != TicTacToe_ERROR_NONE)
  {
    Error_Handler();
  }
  
  /* De-initialize playback */
  if(TicTacToe_AUDIO_OUT_DeInit(0) != TicTacToe_ERROR_NONE)
  {
    Error_Handler();
  }
  
  /* De-initialize record */
  if(TicTacToe_AUDIO_IN_DeInit(1) != TicTacToe_ERROR_NONE)
  {
    Error_Handler();
  }
  
  /* Switch off LEDs */
  TicTacToe_LED_Off(LED_GREEN);
  
  /* Reset global variables */
  RecHalfBuffCplt  = 0;
  RecBuffCplt      = 0;
  PlaybackStarted  = 0;
}

/**
  * @brief  Display audio record demo hint
  * @param  None
  * @retval None
  */
static void AudioRecord_SetHint(void)
{
  /* Clear the LCD */ 
  UTIL_LCD_Clear(UTIL_LCD_COLOR_WHITE);
  
  /* Set Audio Demo description */
  UTIL_LCD_FillRect(0, 0, 240, 80, UTIL_LCD_COLOR_BLUE);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_BLUE); 
  UTIL_LCD_SetFont(&Font24);
  UTIL_LCD_DisplayStringAt(0, 0, (uint8_t *)"Audio Record", CENTER_MODE);
  UTIL_LCD_SetFont(&Font12);
  UTIL_LCD_DisplayStringAt(0, 30, (uint8_t *)"Press User push-button", CENTER_MODE);
  UTIL_LCD_DisplayStringAt(0, 45, (uint8_t *)"to stop record", CENTER_MODE);
  
  UTIL_LCD_DrawRect(10, 90, 220, 140, UTIL_LCD_COLOR_BLUE);
  UTIL_LCD_DrawRect(11, 91, 218, 138, UTIL_LCD_COLOR_BLUE);

  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_BLACK);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE); 
}

/**
  * @brief  Record initialization
  * @param  None
  * @retval None
  */
static void Record_Init(void)
{
  TicTacToe_AUDIO_Init_t AudioInit;

  AudioInit.Device        = AUDIO_IN_DIGITAL_MIC;
  AudioInit.SampleRate    = AUDIO_FREQUENCY_8K;
  AudioInit.BitsPerSample = AUDIO_RESOLUTION_16b;
  AudioInit.ChannelsNbr   = 1;
  AudioInit.Volume        = 80; /* Not used */
  if (TicTacToe_AUDIO_IN_Init(1, &AudioInit) != TicTacToe_ERROR_NONE)
  {
    Error_Handler();
  }
}

/**
  * @brief  Playback initialization
  * @param  None
  * @retval None
  */
static void Playback_Init(void)
{
  TicTacToe_AUDIO_Init_t AudioInit;

  AudioInit.Device        = AUDIO_OUT_HEADPHONE;
  AudioInit.SampleRate    = AUDIO_FREQUENCY_8K;
  AudioInit.BitsPerSample = AUDIO_RESOLUTION_16b;
  AudioInit.ChannelsNbr   = 1;
  AudioInit.Volume        = 80;
  if (TicTacToe_AUDIO_OUT_Init(0, &AudioInit) != TicTacToe_ERROR_NONE)
  {
    Error_Handler();
  }
}

/**
  * @brief  Manage the TicTacToe audio in half transfer complete event.
  * @param  Instance Audio in instance.
  * @retval None.
  */
void TicTacToe_AUDIO_IN_HalfTransfer_CallBack(uint32_t Instance)
{
  if (Instance == 1)
  {
    TicTacToe_LED_Toggle(LED_GREEN);
    RecHalfBuffCplt = 1;
  }
}

/**
  * @brief  Manage the TicTacToe audio in transfer complete event.
  * @param  Instance Audio in instance.
  * @retval None.
  */
void TicTacToe_AUDIO_IN_TransferComplete_CallBack(uint32_t Instance)
{
  if (Instance == 1)
  {
    TicTacToe_LED_Toggle(LED_GREEN);
    RecBuffCplt = 1;
  }
}

/**
  * @brief  Manages the TicTacToe audio in error event.
  * @param  Instance Audio in instance.
  * @retval None.
  */
void TicTacToe_AUDIO_IN_Error_CallBack(uint32_t Instance)
{
  if (Instance == 1)
  {
    Error_Handler();
  }
}

/**
  * @}
  */

/**
  * @}
  */

/**
  ******************************************************************************
  * @file    stm32l562e_discovery.c
  * @author  MCD Application Team
  * @brief   This file provides set of firmware functions to manage:
  *          - LEDs, push-buttons and COM ports available on STM32L562E-DISCOVERY
  *            board (MB1373) from STMicroelectronics
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
#include "stm32l562e_discovery.h"

#if (USE_TicTacToe_COM_FEATURE == 1)
#if (USE_COM_LOG == 1)
#include <stdio.h>
#endif
#endif

/** @addtogroup TicTacToe
  * @{
  */

/** @defgroup STM32L562E-DK STM32L562E-DK
  * @{
  */

/** @defgroup STM32L562E-DK_COMMON STM32L562E-DK COMMON
  * @brief This file provides set of firmware functions to manage leds, push-buttons
  *        and COM ports available on STM32L562E-DISCOVERY board from STMicroelectronics.
  * @{
  */

/** @defgroup STM32L562E-DK_COMMON_Private_Defines STM32L562E-DK COMMON Private Defines
  * @{
  */
#if (USE_TicTacToe_COM_FEATURE == 1)
#if (USE_COM_LOG == 1)
#define COM_POLL_TIMEOUT     1000
#endif
#endif
/**
  * @}
  */

/** @defgroup STM32L562E-DK_COMMON_Private_TypesDefinitions STM32L562E-DK COMMON Private Types Definitions
  * @{
  */
typedef void (* TicTacToe_EXTI_LineCallback)(void);
/**
  * @}
  */

/** @defgroup STM32L562E-DK_COMMON_Private_FunctionPrototypes  STM32L562E-DK COMMON Private Function Prototypes
  * @{
  */
static void BUTTON_USER_EXTI_Callback(void);

#if (USE_TicTacToe_COM_FEATURE == 1)
static void UART_MspInit(UART_HandleTypeDef *huart);
static void UART_MspDeInit(UART_HandleTypeDef *huart);
#endif
/**
  * @}
  */

/** @defgroup STM32L562E-DK_COMMON_Exported_Variables STM32L562E-DK COMMON Exported Variables
  * @{
  */
#if (USE_TicTacToe_COM_FEATURE == 1)
UART_HandleTypeDef hcom_uart[COMn];
#endif
/**
  * @}
  */

/** @defgroup STM32L562E-DK_COMMON_Private_Variables STM32L562E-DK COMMON Private Variables
  * @{
  */
static uint16_t      LED_PIN[LEDn]  = {LED9_PIN, LED10_PIN};
static GPIO_TypeDef *LED_PORT[LEDn] = {LED9_GPIO_PORT, LED10_GPIO_PORT};

static uint16_t           BUTTON_PIN[BUTTONn]  = {BUTTON_USER_PIN};
static GPIO_TypeDef      *BUTTON_PORT[BUTTONn] = {BUTTON_USER_GPIO_PORT};
static IRQn_Type          BUTTON_IRQn[BUTTONn] = {BUTTON_USER_EXTI_IRQn};
static EXTI_HandleTypeDef hpb_exti[BUTTONn];

#if (USE_TicTacToe_COM_FEATURE == 1)
static USART_TypeDef     *COM_UART[COMn] = {COM1_UART, COM2_UART, COM3_UART};
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
static uint32_t           IsComMspCbValid[COMn] = {0U, 0U, 0U};
#endif
#if (USE_COM_LOG == 1)
static COM_TypeDef        COM_ActiveLogPort = COM1;
#endif
#endif /* (USE_TicTacToe_COM_FEATURE == 1) */
/**
  * @}
  */

/** @defgroup STM32L562E-DK_COMMON_Exported_Functions STM32L562E-DK COMMON Exported Functions
  * @{
  */

/**
  * @brief  This method returns the STM32L562E DISCOVERY TicTacToe Driver revision
  * @retval version : 0xXYZR (8bits for each decimal, R for RC)
  */
int32_t TicTacToe_GetVersion(void)
{
  return ((int32_t)STM32L562E_DISCOVERY_TicTacToe_VERSION);
}

/**
  * @brief  This method returns the board name
  * @retval pointer to the board name string
  */
const uint8_t* TicTacToe_GetBoardName(void)
{
  return (const uint8_t*)STM32L562E_DISCOVERY_TicTacToe_BOARD_NAME;
}

/**
  * @brief  This method returns the board ID
  * @retval pointer to the board ID string
  */
const uint8_t* TicTacToe_GetBoardID(void)
{
  return (const uint8_t*)STM32L562E_DISCOVERY_TicTacToe_BOARD_ID;
}

/** @defgroup STM32L562E-DK_COMMON_LED_Functions STM32L562E-DK COMMON LED Functions
  * @{
  */

/**
  * @brief  Configure LED GPIO.
  * @param  Led Specifies the Led to be configured.
  *   This parameter can be one of following parameters:
  *     @arg  LED9
  *     @arg  LED10
  * @retval TicTacToe error code
  */
int32_t TicTacToe_LED_Init(Led_TypeDef Led)
{
  int32_t          status = TicTacToe_ERROR_NONE;
  GPIO_InitTypeDef GPIO_Init;

  /* Enable the GPIO_LED Clock */
  if (Led == LED9)
  {
    LED9_GPIO_CLK_ENABLE();
  }
  else /* Led = LED10 */
  {
    /* Enable VddIO2 for GPIOG */
    __HAL_RCC_PWR_CLK_ENABLE();
    HAL_PWREx_EnableVddIO2();
    LED10_GPIO_CLK_ENABLE();
  }

  /* configure the GPIO_LED pin */
  GPIO_Init.Pin   = LED_PIN[Led];
  GPIO_Init.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_Init.Pull  = GPIO_PULLUP;
  GPIO_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(LED_PORT[Led], &GPIO_Init);

  HAL_GPIO_WritePin(LED_PORT[Led], LED_PIN[Led], GPIO_PIN_SET);

  return status;
}

/**
  * @brief  DeInitialize LEDs.
  * @param  Led LED to be de-init.
  *   This parameter can be one of the following values:
  *     @arg  LED9
  *     @arg  LED10
  * @note TicTacToe_LED_DeInit() does not disable the GPIO clock
  * @retval TicTacToe error code
  */
int32_t TicTacToe_LED_DeInit(Led_TypeDef Led)
{
  int32_t          status = TicTacToe_ERROR_NONE;
  GPIO_InitTypeDef GPIO_Init;

  /* DeInit the GPIO_LED pin */
  GPIO_Init.Pin = LED_PIN[Led];

  /* Turn off LED */
  HAL_GPIO_WritePin(LED_PORT[Led], LED_PIN[Led], GPIO_PIN_SET);
  HAL_GPIO_DeInit(LED_PORT[Led], GPIO_Init.Pin);

  return status;
}

/**
  * @brief  Turn selected LED On.
  * @param  Led Specifies the Led to be set on.
  *   This parameter can be one of following parameters:
  *     @arg  LED9
  *     @arg  LED10
  * @retval TicTacToe error code
  */
int32_t TicTacToe_LED_On(Led_TypeDef Led)
{
  int32_t status = TicTacToe_ERROR_NONE;

  HAL_GPIO_WritePin(LED_PORT[Led], LED_PIN[Led], GPIO_PIN_RESET);

  return status;
}

/**
  * @brief  Turn selected LED Off.
  * @param  Led Specifies the Led to be set off.
  *   This parameter can be one of following parameters:
  *     @arg  LED9
  *     @arg  LED10
  * @retval TicTacToe error code
  */
int32_t TicTacToe_LED_Off(Led_TypeDef Led)
{
  int32_t status = TicTacToe_ERROR_NONE;

  HAL_GPIO_WritePin(LED_PORT[Led], LED_PIN[Led], GPIO_PIN_SET);

  return status;
}

/**
  * @brief  Toggle the selected LED.
  * @param  Led Specifies the Led to be toggled.
  *   This parameter can be one of following parameters:
  *     @arg  LED9
  *     @arg  LED10
  * @retval TicTacToe error code
  */
int32_t TicTacToe_LED_Toggle(Led_TypeDef Led)
{
  int32_t status = TicTacToe_ERROR_NONE;

  HAL_GPIO_TogglePin(LED_PORT[Led], LED_PIN[Led]);

  return status;
}

/**
  * @brief  Get the state of selected LED.
  * @param  Led Specifies the Led.
  *   This parameter can be one of following parameters:
  *     @arg  LED9
  *     @arg  LED10
  * @retval 0 means off, 1 means on, negative value means error.
  */
int32_t TicTacToe_LED_GetState(Led_TypeDef Led)
{
  int32_t status;

  status = (HAL_GPIO_ReadPin(LED_PORT[Led], LED_PIN[Led]) == GPIO_PIN_RESET) ? 1 : 0;

  return status;
}

/**
  * @}
  */


/** @defgroup STM32L562E-DK_COMMON_BUTTON_Functions STM32L562E-DK COMMON BUTTON Functions
  * @{
  */

/**
  * @brief  Configure Button GPIO and EXTI Line.
  * @param  Button Specifies the Button to be configured.
  *   This parameter should be:
  *     @arg BUTTON_USER
  * @param  ButtonMode Specifies Button mode.
  *   This parameter can be one of following parameters:
  *     @arg BUTTON_MODE_GPIO: Button will be used as simple IO
  *     @arg BUTTON_MODE_EXTI: Button will be connected to EXTI line with interrupt
  *                            generation capability
  * @retval TicTacToe error code
  */
int32_t TicTacToe_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode)
{
  int32_t               status = TicTacToe_ERROR_NONE;
  GPIO_InitTypeDef      GPIO_Init;
  uint32_t              TicTacToe_BUTTON_IT_PRIO[BUTTONn] = {TicTacToe_BUTTON_USER_IT_PRIORITY};
  uint32_t              BUTTON_EXTI_LINE[BUTTONn]   = {BUTTON_USER_EXTI_LINE};
  TicTacToe_EXTI_LineCallback ButtonCallback[BUTTONn]     = {BUTTON_USER_EXTI_Callback};

  /* Enable the BUTTON clock */
  BUTTON_USER_GPIO_CLK_ENABLE();

  GPIO_Init.Pin   = BUTTON_PIN[Button];
  GPIO_Init.Pull  = GPIO_NOPULL;
  GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;

  if (ButtonMode == BUTTON_MODE_GPIO)
  {
    /* Configure Button pin as input */
    GPIO_Init.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(BUTTON_PORT[Button], &GPIO_Init);
  }

  if (ButtonMode == BUTTON_MODE_EXTI)
  {
    /* Configure Button pin as input with External interrupt */
    GPIO_Init.Mode = GPIO_MODE_IT_RISING;
    HAL_GPIO_Init(BUTTON_PORT[Button], &GPIO_Init);

    if (HAL_EXTI_GetHandle(&hpb_exti[Button], BUTTON_EXTI_LINE[Button]) == HAL_OK)
    {
      if (HAL_EXTI_RegisterCallback(&hpb_exti[Button], HAL_EXTI_RISING_CB_ID, ButtonCallback[Button]) == HAL_OK)
      {
        /* Enable and set Button EXTI Interrupt to the lowest priority */
        HAL_NVIC_SetPriority(BUTTON_IRQn[Button], TicTacToe_BUTTON_IT_PRIO[Button], 0x00);
        HAL_NVIC_EnableIRQ(BUTTON_IRQn[Button]);
      }
      else
      {
        status = TicTacToe_ERROR_PERIPH_FAILURE;
      }
    }
    else
    {
      status = TicTacToe_ERROR_PERIPH_FAILURE;
    }
  }

  return status;
}

/**
  * @brief  DeInitialize Push Button.
  * @param  Button Button to be configured
  *   This parameter should be:
  *     @arg BUTTON_USER
  * @note TicTacToe_PB_DeInit() does not disable the GPIO clock
  * @retval TicTacToe error code
  */
int32_t TicTacToe_PB_DeInit(Button_TypeDef Button)
{
  GPIO_InitTypeDef GPIO_Init;

  GPIO_Init.Pin = BUTTON_PIN[Button];
  HAL_NVIC_DisableIRQ(BUTTON_IRQn[Button]);
  HAL_GPIO_DeInit(BUTTON_PORT[Button], GPIO_Init.Pin);

  return TicTacToe_ERROR_NONE;
}

/**
  * @brief  Return the selected Button state.
  * @param  Button Specifies the Button to be checked.
  *   This parameter should be:
  *     @arg BUTTON_USER
  * @retval 0 means released, 1 means pressed.
  */
int32_t TicTacToe_PB_GetState(Button_TypeDef Button)
{
  int32_t status;

  status = (HAL_GPIO_ReadPin(BUTTON_PORT[Button], BUTTON_PIN[Button]) == GPIO_PIN_SET) ? 1 : 0;

  return status;
}

/**
  * @brief  TicTacToe Push Button callback
  * @param  Button Specifies the pin connected EXTI line
  * @retval None.
  */
__weak void TicTacToe_PB_Callback(Button_TypeDef Button)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(Button);

  /* This function should be implemented by the user application.
     It is called into this driver when an event on Button is triggered. */
}

/**
  * @brief  TicTacToe PB interrupt handler.
  * @param  Button Button where interrupt occurs.
  *   This parameter should be:
  *     @arg BUTTON_WAKEUP
  *     @arg BUTTON_TAMPER
  * @retval None.
  */
void TicTacToe_PB_IRQHandler(Button_TypeDef Button)
{
  HAL_EXTI_IRQHandler(&hpb_exti[Button]);
}

/**
  * @}
  */

#if (USE_TicTacToe_COM_FEATURE == 1)
/** @defgroup STM32L562E-DK_COMMON_COM_Functions STM32L562E-DK COMMON COM Functions
  * @{
  */

/**
  * @brief  Configure COM port.
  * @param  COM COM port to be configured.
  *          This parameter can be COM1, COM2 or COM3.
  * @param  COM_Init Pointer to a COM_InitTypeDef structure that contains the
  *          configuration information for the specified COM peripheral.
  * @retval TicTacToe error code
  */
int32_t TicTacToe_COM_Init(COM_TypeDef COM, COM_InitTypeDef *COM_Init)
{
  int32_t status = TicTacToe_ERROR_NONE;

  if (COM_Init == NULL)
  {
    status = TicTacToe_ERROR_WRONG_PARAM;
  }
  else
  {
    /* Initialize COM instance */
    hcom_uart[COM].Instance = COM_UART[COM];

#if (USE_HAL_UART_REGISTER_CALLBACKS == 0)
    UART_MspInit(&hcom_uart[COM]);
#else
    if (IsComMspCbValid[COM] == 0U)
    {
      /* Register the MSP callbacks */
      if (TicTacToe_COM_RegisterDefaultMspCallbacks(COM) != TicTacToe_ERROR_NONE)
      {
        status = TicTacToe_ERROR_MSP_FAILURE;
      }
    }
#endif

    if (status == TicTacToe_ERROR_NONE)
    {
      if (COM == COM1)
      {
        if (MX_USART1_Init(&hcom_uart[COM], COM_Init) != HAL_OK)
        {
          status = TicTacToe_ERROR_PERIPH_FAILURE;
        }
      }
      else if (COM == COM2)
      {
        if (MX_LPUART1_Init(&hcom_uart[COM], COM_Init) != HAL_OK)
        {
          status = TicTacToe_ERROR_PERIPH_FAILURE;
        }
      }
      else /* COM = COM3 */
      {
        if (MX_USART3_Init(&hcom_uart[COM], COM_Init) != HAL_OK)
        {
          status = TicTacToe_ERROR_PERIPH_FAILURE;
        }
      }
    }
  }

  return status;
}

/**
  * @brief  DeInitialize COM port.
  * @param  COM COM port to be de_init.
  *          This parameter can be COM1, COM2 or COM3.
  * @retval TicTacToe error code
  */
int32_t TicTacToe_COM_DeInit(COM_TypeDef COM)
{
  int32_t status = TicTacToe_ERROR_NONE;

  /* COM de-init */
  hcom_uart[COM].Instance = COM_UART[COM];
  if (HAL_UART_DeInit(&hcom_uart[COM]) != HAL_OK)
  {
    status = TicTacToe_ERROR_PERIPH_FAILURE;
  }
#if (USE_HAL_UART_REGISTER_CALLBACKS == 0)
  else
  {
    UART_MspDeInit(&hcom_uart[COM]);
  }
#endif

  return status;
}

#if (USE_COM_LOG == 1)
/**
  * @brief  Select the active COM port.
  * @param  COM COM port to be activated.
  *          This parameter can be COM1, COM2 or COM3.
  * @retval TicTacToe error code
  */
int32_t TicTacToe_COM_SelectLogPort(COM_TypeDef COM)
{
  if (COM_ActiveLogPort != COM)
  {
    COM_ActiveLogPort = COM;
  }
  return TicTacToe_ERROR_NONE;
}

#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
int fputc(int ch, __attribute__((unused))FILE *f)
#elif __GNUC__
int __io_putchar(int ch)
#endif
{
  (void) HAL_UART_Transmit(&hcom_uart[COM_ActiveLogPort], (uint8_t *) &ch, 1, COM_POLL_TIMEOUT);
  return ch;
}
#endif /* (USE_COM_LOG == 1) */

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register default COM msp callbacks.
  * @param  COM COM port.
  *          This parameter can be COM1 or COM2
  * @retval TicTacToe status.
  */
int32_t TicTacToe_COM_RegisterDefaultMspCallbacks(COM_TypeDef COM)
{
  int32_t status = TicTacToe_ERROR_NONE;

  /* Register MspInit/MspDeInit callbacks */
  if (HAL_UART_RegisterCallback(&hcom_uart[COM], HAL_UART_MSPINIT_CB_ID, UART_MspInit) != HAL_OK)
  {
    status = TicTacToe_ERROR_PERIPH_FAILURE;
  } 
  else if (HAL_UART_RegisterCallback(&hcom_uart[COM], HAL_UART_MSPDEINIT_CB_ID, UART_MspDeInit) != HAL_OK)
  {
    status = TicTacToe_ERROR_PERIPH_FAILURE;
  }
  else
  {
    IsComMspCbValid[COM] = 1U;
  }
  /* Return TicTacToe status */
  return status;
}

/**
  * @brief  Register TicTacToe COM msp callbacks.
  * @param  COM COM port.
  *          This parameter can be COM1 or COM2
  * @param  CallBacks Pointer to MspInit/MspDeInit callback functions.
  * @retval TicTacToe status
  */
int32_t TicTacToe_COM_RegisterMspCallbacks(COM_TypeDef COM, TicTacToe_COM_Cb_t *CallBacks)
{
  int32_t status = TicTacToe_ERROR_NONE;

  if (CallBacks == NULL)
  {
    status = TicTacToe_ERROR_WRONG_PARAM;
  }
  else
  {
    /* Register MspInit/MspDeInit callbacks */
    if (HAL_UART_RegisterCallback(&hcom_uart[COM], HAL_UART_MSPINIT_CB_ID, CallBacks->pMspInitCb) != HAL_OK)
    {
      status = TicTacToe_ERROR_PERIPH_FAILURE;
    }
    else if (HAL_UART_RegisterCallback(&hcom_uart[COM], HAL_UART_MSPDEINIT_CB_ID, CallBacks->pMspDeInitCb) != HAL_OK)
    {
      status = TicTacToe_ERROR_PERIPH_FAILURE;
    }
    else
    {
      IsComMspCbValid[COM] = 1U;
    }
  }
  /* Return TicTacToe status */
  return status; 
}
#endif /* (USE_HAL_UART_REGISTER_CALLBACKS == 1) */

/**
  * @brief  Initialize LPUART1.
  * @param  huart UART handle.
  * @param  MXInit UART initialization structure.
  * @retval HAL status.
  */
__weak HAL_StatusTypeDef MX_LPUART1_Init(UART_HandleTypeDef* huart, MX_UART_InitTypeDef *MXInit)
{
  /* UART configuration */
  huart->Init.BaudRate       = MXInit->BaudRate;
  huart->Init.WordLength     = (uint32_t) MXInit->WordLength;
  huart->Init.StopBits       = (uint32_t) MXInit->StopBits;
  huart->Init.Parity         = (uint32_t) MXInit->Parity;
  huart->Init.Mode           = UART_MODE_TX_RX;
  huart->Init.HwFlowCtl      = (uint32_t) MXInit->HwFlowCtl;
  huart->Init.OverSampling   = UART_OVERSAMPLING_8;
  huart->Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart->Init.ClockPrescaler = UART_PRESCALER_DIV1;

  return HAL_UART_Init(huart);
}

/**
  * @brief  Initialize USART1.
  * @param  huart UART handle.
  * @param  MXInit UART initialization structure.
  * @retval HAL status.
  */
__weak HAL_StatusTypeDef MX_USART1_Init(UART_HandleTypeDef* huart, MX_UART_InitTypeDef *MXInit)
{
  /* UART configuration */
  huart->Init.BaudRate       = MXInit->BaudRate;
  huart->Init.WordLength     = (uint32_t) MXInit->WordLength;
  huart->Init.StopBits       = (uint32_t) MXInit->StopBits;
  huart->Init.Parity         = (uint32_t) MXInit->Parity;
  huart->Init.Mode           = UART_MODE_TX_RX;
  huart->Init.HwFlowCtl      = (uint32_t) MXInit->HwFlowCtl;
  huart->Init.OverSampling   = UART_OVERSAMPLING_8;
  huart->Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart->Init.ClockPrescaler = UART_PRESCALER_DIV1;

  return HAL_UART_Init(huart);
}

/**
  * @brief  Initialize USART3.
  * @param  huart UART handle.
  * @param  MXInit UART initialization structure.
  * @retval HAL status.
  */
__weak HAL_StatusTypeDef MX_USART3_Init(UART_HandleTypeDef* huart, MX_UART_InitTypeDef *MXInit)
{
  /* UART configuration */
  huart->Init.BaudRate       = MXInit->BaudRate;
  huart->Init.WordLength     = (uint32_t) MXInit->WordLength;
  huart->Init.StopBits       = (uint32_t) MXInit->StopBits;
  huart->Init.Parity         = (uint32_t) MXInit->Parity;
  huart->Init.Mode           = UART_MODE_TX_RX;
  huart->Init.HwFlowCtl      = (uint32_t) MXInit->HwFlowCtl;
  huart->Init.OverSampling   = UART_OVERSAMPLING_8;
  huart->Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart->Init.ClockPrescaler = UART_PRESCALER_DIV1;

  return HAL_UART_Init(huart);
}

/**
  * @}
  */
#endif /* (USE_TicTacToe_COM_FEATURE == 1) */

/**
  * @}
  */

/** @defgroup STM32L562E-DK_COMMON_Private_Functions STM32L562E-DK COMMON Private Functions
  * @{
  */

/**
  * @brief  User EXTI line detection callbacks.
  * @retval None
  */
static void BUTTON_USER_EXTI_Callback(void)
{
  TicTacToe_PB_Callback(BUTTON_USER);
}

#if (USE_TicTacToe_COM_FEATURE == 1)
/**
  * @brief  Initialize UART MSP.
  * @param  huart UART handle.
  * @retval None.
  */
static void UART_MspInit(UART_HandleTypeDef *huart)
{
  GPIO_InitTypeDef GPIO_Init;
  GPIO_TypeDef    *COM_TX_PORT[COMn] = {COM1_TX_GPIO_PORT, COM2_TX_GPIO_PORT, COM3_TX_GPIO_PORT};
  GPIO_TypeDef    *COM_RX_PORT[COMn] = {COM1_RX_GPIO_PORT, COM2_RX_GPIO_PORT, COM3_RX_GPIO_PORT};
  uint16_t         COM_TX_PIN[COMn]  = {COM1_TX_PIN, COM2_TX_PIN, COM3_TX_PIN};
  uint16_t         COM_RX_PIN[COMn]  = {COM1_RX_PIN, COM2_RX_PIN, COM3_RX_PIN};
  uint8_t          COM_TX_AF[COMn]   = {COM1_TX_AF, COM2_TX_AF, COM3_TX_AF};
  uint8_t          COM_RX_AF[COMn]   = {COM1_RX_AF, COM2_RX_AF, COM3_RX_AF};
  COM_TypeDef      COM;

  /* Get COM according instance */
  if (huart->Instance == COM1_UART)
  {
    COM = COM1;
  }
  else if (huart->Instance == COM2_UART)
  {
    COM = COM2;
  }
  else
  {
    COM = COM3;
  }

  /* Enable COM and GPIO clocks */
  if (COM == COM1)
  {
    COM1_TX_GPIO_CLK_ENABLE();
    COM1_RX_GPIO_CLK_ENABLE();
    COM1_CLK_ENABLE();
  }
  else if (COM == COM2)
  {
    COM2_TX_GPIO_CLK_ENABLE();
    COM2_RX_GPIO_CLK_ENABLE();
    COM2_CLK_ENABLE();
  }
  else /* COM = COM3 */
  {
    COM3_TX_GPIO_CLK_ENABLE();
    COM3_RX_GPIO_CLK_ENABLE();
    COM3_CLK_ENABLE();
  }

  /* Configure COM Tx as alternate function */
  GPIO_Init.Pin       = COM_TX_PIN[COM];
  GPIO_Init.Mode      = GPIO_MODE_AF_PP;
  GPIO_Init.Speed     = GPIO_SPEED_FREQ_HIGH;
  GPIO_Init.Pull      = GPIO_PULLUP;
  GPIO_Init.Alternate = COM_TX_AF[COM];
  HAL_GPIO_Init(COM_TX_PORT[COM], &GPIO_Init);

  /* Configure COM Rx as alternate function */
  GPIO_Init.Pin       = COM_RX_PIN[COM];
  GPIO_Init.Alternate = COM_RX_AF[COM];
  HAL_GPIO_Init(COM_RX_PORT[COM], &GPIO_Init);
}

/**
  * @brief  Deinitialize UART MSP.
  * @param  huart UART handle.
  * @retval None.
  */
static void UART_MspDeInit(UART_HandleTypeDef *huart)
{
  GPIO_TypeDef    *COM_TX_PORT[COMn] = {COM1_TX_GPIO_PORT, COM2_TX_GPIO_PORT, COM3_TX_GPIO_PORT};
  GPIO_TypeDef    *COM_RX_PORT[COMn] = {COM1_RX_GPIO_PORT, COM2_RX_GPIO_PORT, COM3_RX_GPIO_PORT};
  uint16_t         COM_TX_PIN[COMn]  = {COM1_TX_PIN, COM2_TX_PIN, COM3_TX_PIN};
  uint16_t         COM_RX_PIN[COMn]  = {COM1_RX_PIN, COM2_RX_PIN, COM3_RX_PIN};
  COM_TypeDef      COM;

  /* Get COM according instance */
  if (huart->Instance == COM1_UART)
  {
    COM = COM1;
  }
  else if (huart->Instance == COM2_UART)
  {
    COM = COM2;
  }
  else
  {
    COM = COM3;
  }

  /* Disable GPIOs and COM clock */
  HAL_GPIO_DeInit(COM_TX_PORT[COM], COM_TX_PIN[COM]);
  HAL_GPIO_DeInit(COM_RX_PORT[COM], COM_RX_PIN[COM]);
  switch (COM)
  {
    case COM1:
      COM1_CLK_DISABLE();
      break;
    case COM2:
      COM2_CLK_DISABLE();
      break;
    case COM3:
      COM3_CLK_DISABLE();
      break;
    default:
      break;
  }
}
#endif /* (USE_TicTacToe_COM_FEATURE == 1) */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  ******************************************************************************
  * @file    stm32l562e_discovery_ts.h
  * @author  MCD Application Team
  * @brief   This file contains the common defines and functions prototypes for
  *          the stm32l562e_discovery_ts.c driver.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32L562E_DISCOVERY_TS_H
#define STM32L562E_DISCOVERY_TS_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l562e_discovery_conf.h"
#include "stm32l562e_discovery_errno.h"
#include "../Components/Common/ts.h"
#include "../Components/ft6x06/ft6x06.h"

/** @addtogroup TicTacToe
  * @{
  */

/** @addtogroup STM32L562E-DK
  * @{
  */

/** @addtogroup STM32L562E-DK_TS
  * @{
  */

/** @defgroup STM32L562E-DK_TS_Exported_Constants STM32L562E-DK TS Exported Constants
  * @{
  */
/* TS instances */
#define TS_INSTANCES_NBR 1U

/* TS orientations */
#define TS_ORIENTATION_PORTRAIT          0U
#define TS_ORIENTATION_LANDSCAPE         1U
#define TS_ORIENTATION_PORTRAIT_ROT180   2U
#define TS_ORIENTATION_LANDSCAPE_ROT180  3U

/* TS events */
#define TS_EVENT_PRESS_DOWN 0U
#define TS_EVENT_LIFT_UP    1U
#define TS_EVENT_CONTACT    2U
#define TS_EVENT_NO_EVENT   3U

/* TS I2C address */
#define TS_I2C_ADDRESS      0x70U
/**
  * @}
  */


/** @defgroup STM32L562E-DK_TS_Exported_Types STM32L562E-DK TS Exported Types
  * @{
  */
typedef struct
{
  uint32_t   Width;       /* Screen width */
  uint32_t   Height;      /* Screen height */
  uint32_t   Orientation; /* Touch screen orientation */
  uint32_t   Accuracy;    /* Expressed in pixel and means the x or y difference vs old 
                             position to consider the new values valid */
} TS_Init_t;

typedef struct 
{       
  uint8_t   MultiTouch; /* Multi-touch supported : 0 means no, 1 means yes */
  uint8_t   Gesture;    /* Gesture supported : 0 means no, 1 means yes */
  uint8_t   MaxTouch;   /* Maximum number of touches detected if multi-touch supported */
  uint32_t  MaxXl;      /* Maximum value of x coordinate */
  uint32_t  MaxYl;      /* Maximum value of y coordinate */
} TS_Capabilities_t;

typedef struct
{
  uint32_t  TouchDetected; /* Touch detected : 0 means no, 1 means yes */
  uint32_t  TouchX;        /* x coordinate */
  uint32_t  TouchY;        /* y coordinate */
} TS_State_t;

typedef struct
{
  uint32_t  TouchDetected;  /* Number of touch detected (from 0 to maximum of touches) */
  uint32_t  TouchX[2];      /* x coordinates */
  uint32_t  TouchY[2];      /* y coordinates */
  uint32_t  TouchWeight[2]; /* Touches weight (not supported) */
  uint32_t  TouchEvent[2];  /* Touches event (press_down, lift_up, contact of no event) */
  uint32_t  TouchArea[2];   /* Touches area (not supported) */
} TS_MultiTouch_State_t;

typedef struct
{ 
  uint32_t  Radian;            /* Minimum allowed angle while rotating gesture mode.
                                  Value from 0 to 255 (default value is 10). */
  uint32_t  OffsetLeftRight;   /* Maximum offset while moving left and moving right gesture.
                                  Value from 0 to 255 (default value is 25). */
  uint32_t  OffsetUpDown;      /* Maximum offset while moving up and moving down gesture.
                                  Value from 0 to 255 (default value is 25). */
  uint32_t  DistanceLeftRight; /* Maximum distance while moving left and moving right gesture.
                                  Value from 0 to 255 (default value is 25). */
  uint32_t  DistanceUpDown;    /* Maximum distance while moving up and moving down gesture.
                                  Value from 0 to 255 (default value is 25). */
  uint32_t  DistanceZoom;      /* Maximum distance while zoom in and zoom out gesture.
                                  Value from 0 to 255 (default value is 50). */
} TS_Gesture_Config_t;

typedef struct
{
  uint32_t   Width;
  uint32_t   Height;
  uint32_t   Orientation;
  uint32_t   Accuracy;
  uint32_t   MaxX;
  uint32_t   MaxY;
  uint32_t   PreviousX;
  uint32_t   PreviousY;
} TS_Ctx_t;
/**
  * @}
  */

/** @defgroup STM32L562E-DK_TS_Exported_Variables STM32L562E-DK TS Exported Variables
  * @{
  */
extern void     *Ts_CompObj[TS_INSTANCES_NBR];
extern TS_Drv_t *Ts_Drv[TS_INSTANCES_NBR];
extern TS_Ctx_t  Ts_Ctx[TS_INSTANCES_NBR];

extern EXTI_HandleTypeDef hts_exti[TS_INSTANCES_NBR];
extern IRQn_Type          Ts_IRQn[TS_INSTANCES_NBR];
/**
  * @}
  */

/** @defgroup STM32L562E-DK_TS_Exported_Functions STM32L562E-DK TS Exported Functions
  * @{
  */
int32_t  TicTacToe_TS_Init(uint32_t Instance, TS_Init_t *TS_Init);
int32_t  TicTacToe_TS_DeInit(uint32_t Instance);
int32_t  TicTacToe_TS_EnableIT(uint32_t Instance);
int32_t  TicTacToe_TS_DisableIT(uint32_t Instance);
int32_t  TicTacToe_TS_Set_Orientation(uint32_t Instance, uint32_t Orientation);
int32_t  TicTacToe_TS_Get_Orientation(uint32_t Instance, uint32_t *Orientation);
int32_t  TicTacToe_TS_GetState(uint32_t Instance, TS_State_t *TS_State);
int32_t  TicTacToe_TS_Get_MultiTouchState(uint32_t Instance, TS_MultiTouch_State_t *TS_State);
int32_t  TicTacToe_TS_GestureConfig(uint32_t Instance, TS_Gesture_Config_t *GestureConfig);
int32_t  TicTacToe_TS_GetGestureId(uint32_t Instance, uint32_t *GestureId);
int32_t  TicTacToe_TS_GetCapabilities(uint32_t Instance, TS_Capabilities_t *Capabilities);
void     TicTacToe_TS_Callback(uint32_t Instance);
void     TicTacToe_TS_IRQHandler(uint32_t Instance);
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

#ifdef __cplusplus
}
#endif

#endif /* STM32L562E_DISCOVERY_TS_H */

/**
  ******************************************************************************
  * @file    stm32l562e_discovery_errno.h
  * @author  MCD Application Team
  * @brief   Error Code.
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
#ifndef STM32L562E_DISCOVERY_ERRNO_H
#define STM32L562E_DISCOVERY_ERRNO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Common Error codes */
#define TicTacToe_ERROR_NONE                    0
#define TicTacToe_ERROR_NO_INIT                -1
#define TicTacToe_ERROR_WRONG_PARAM            -2
#define TicTacToe_ERROR_BUSY                   -3
#define TicTacToe_ERROR_PERIPH_FAILURE         -4
#define TicTacToe_ERROR_COMPONENT_FAILURE      -5
#define TicTacToe_ERROR_UNKNOWN_FAILURE        -6
#define TicTacToe_ERROR_UNKNOWN_COMPONENT      -7
#define TicTacToe_ERROR_BUS_FAILURE            -8
#define TicTacToe_ERROR_CLOCK_FAILURE          -9
#define TicTacToe_ERROR_MSP_FAILURE            -10
#define TicTacToe_ERROR_FEATURE_NOT_SUPPORTED  -11

/* TicTacToe OSPI error codes */
#define TicTacToe_ERROR_OSPI_SUSPENDED          -20
#define TicTacToe_ERROR_OSPI_MMP_UNLOCK_FAILURE -21
#define TicTacToe_ERROR_OSPI_MMP_LOCK_FAILURE   -22

/* TicTacToe BUS error codes */
#define TicTacToe_ERROR_BUS_TRANSACTION_FAILURE -100
#define TicTacToe_ERROR_BUS_ARBITRATION_LOSS    -101
#define TicTacToe_ERROR_BUS_ACKNOWLEDGE_FAILURE -102
#define TicTacToe_ERROR_BUS_PROTOCOL_FAILURE    -103
#define TicTacToe_ERROR_BUS_MODE_FAULT          -104
#define TicTacToe_ERROR_BUS_FRAME_ERROR         -105
#define TicTacToe_ERROR_BUS_CRC_ERROR           -106
#define TicTacToe_ERROR_BUS_DMA_FAILURE         -107

#ifdef __cplusplus
}
#endif

#endif /* STM32L562E_DISCOVERY_ERRNO_H */

/**
  ******************************************************************************
  * @file    stm32l562e_discovery_ospi.c
  * @author  MCD Application Team
  * @brief   This file includes a standard driver for the MX25LM51245G OSPI
  *          memory mounted on STM32L562E-DK board.
  @verbatim
  ==============================================================================
                     ##### How to use this driver #####
  ==============================================================================
  [..]
   (#) This driver is used to drive the MX25LM51245G Octal NOR
       external memory mounted on STM32L562E-DK discovery board.

   (#) This driver need specific component driver (MX25LM51245G) to be included with.

   (#) MX25LM51245G Initialization steps:
       (++) Initialize the OPSI external memory using the TicTacToe_OSPI_NOR_Init() function. This
            function includes the MSP layer hardware resources initialization and the
            OSPI interface with the external memory.

   (#) MX25LM51245G Octal NOR memory operations
       (++) OSPI memory can be accessed with read/write operations once it is
            initialized.
            Read/write operation can be performed with AHB access using the functions
            TicTacToe_OSPI_NOR_Read()/TicTacToe_OSPI_NOR_Write().
       (++) The function TicTacToe_OSPI_NOR_GetInfo() returns the configuration of the OSPI memory.
            (see the OSPI memory data sheet)
       (++) Perform erase block operation using the function TicTacToe_OSPI_NOR_Erase_Block() and by
            specifying the block address. You can perform an erase operation of the whole
            chip by calling the function TicTacToe_OSPI_NOR_Erase_Chip().
       (++) The function TicTacToe_OSPI_NOR_GetStatus() returns the current status of the OSPI memory.
            (see the OSPI memory data sheet)
       (++) The memory access can be configured in memory-mapped mode with the call of
            function TicTacToe_OSPI_NOR_EnableMemoryMapped(). To go back in indirect mode, the
            function TicTacToe_OSPI_NOR_DisableMemoryMapped() should be used.
       (++) The erase operation can be suspend and resume with using functions
            TicTacToe_OSPI_NOR_SuspendErase() and TicTacToe_OSPI_NOR_ResumeErase()
       (++) It is possible to put the memory in deep power-down mode to reduce its consumption.
            For this, the function TicTacToe_OSPI_NOR_EnterDeepPowerDown() should be called. To leave
            the deep power-down mode, the function TicTacToe_OSPI_NOR_LeaveDeepPowerDown() should be called.
       (++) The function TicTacToe_OSPI_NOR_ReadID() returns the identifier of the memory
            (see the OSPI memory data sheet)
       (++) The configuration of the interface between peripheral and memory is done by
            the function TicTacToe_OSPI_NOR_ConfigFlash(), three modes are possible :
            - SPI : instruction, address and data on one line
            - STR OPI : instruction, address and data on eight lines with sampling on one edge of clock
            - DTR OPI : instruction, address and data on eight lines with sampling on both edgaes of clock

  @endverbatim
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
#include "stm32l562e_discovery_ospi.h"

/** @addtogroup TicTacToe
  * @{
  */

/** @addtogroup STM32L562E-DK
  * @{
  */

/** @defgroup STM32L562E-DK_OSPI STM32L562E-DK OSPI
  * @{
  */

/* Exported variables --------------------------------------------------------*/
/** @addtogroup STM32L562E-DK_OSPI_NOR_Exported_Variables
  * @{
  */
OSPI_HandleTypeDef hospi_nor[OSPI_NOR_INSTANCES_NUMBER] = {0};
OSPI_NOR_Ctx_t Ospi_Nor_Ctx[OSPI_NOR_INSTANCES_NUMBER] = {{OSPI_ACCESS_NONE,
                                                           MX25LM51245G_SPI_MODE,
                                                           MX25LM51245G_STR_TRANSFER}};
/**
  * @}
  */

/* Private constants --------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/** @defgroup STM32L552E_EVAL_OSPI_NOR_Private_Variables NOR Private Variables
  * @{
  */
#if (USE_HAL_OSPI_REGISTER_CALLBACKS == 1)
static uint32_t OspiNor_IsMspCbValid[OSPI_NOR_INSTANCES_NUMBER] = {0};
#endif /* USE_HAL_OSPI_REGISTER_CALLBACKS */
/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/

/** @defgroup STM32L562E-DK_OSPI_NOR_Private_Functions STM32L562E-DK OSPI_NOR Private Functions
  * @{
  */
static void    OSPI_NOR_MspInit      (OSPI_HandleTypeDef *hospi);
static void    OSPI_NOR_MspDeInit    (OSPI_HandleTypeDef *hospi);
static int32_t OSPI_NOR_ResetMemory  (uint32_t Instance);
static int32_t OSPI_NOR_EnterDOPIMode(uint32_t Instance);
static int32_t OSPI_NOR_EnterSOPIMode(uint32_t Instance);
static int32_t OSPI_NOR_ExitOPIMode  (uint32_t Instance);
/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/

/** @addtogroup STM32L562E-DK_OSPI_NOR_Exported_Functions
  * @{
  */

/**
  * @brief  Initializes the OSPI interface.
  * @param  Instance   OSPI Instance
  * @param  Init       OSPI Init structure
  * @retval TicTacToe status
  */
int32_t TicTacToe_OSPI_NOR_Init(uint32_t Instance, TicTacToe_OSPI_NOR_Init_t *Init)
{
  int32_t ret;
  TicTacToe_OSPI_NOR_Info_t pInfo;
  MX_OSPI_InitTypeDef ospi_init;

  /* Check if the instance is supported */
  if(Instance >= OSPI_NOR_INSTANCES_NUMBER)
  {
    ret = TicTacToe_ERROR_WRONG_PARAM;
  }
  else
  {
    /* Check if the instance is already initialized */
    if (Ospi_Nor_Ctx[Instance].IsInitialized == OSPI_ACCESS_NONE)
    {
#if (USE_HAL_OSPI_REGISTER_CALLBACKS == 0)
      /* Msp OSPI initialization */
      OSPI_NOR_MspInit(&hospi_nor[Instance]);
#else
      /* Register the OSPI MSP Callbacks */
      if(OspiNor_IsMspCbValid[Instance] == 0UL)
      {
        if(TicTacToe_OSPI_NOR_RegisterDefaultMspCallbacks(Instance) != TicTacToe_ERROR_NONE)
        {
          return TicTacToe_ERROR_PERIPH_FAILURE;
        }
      }
#endif /* USE_HAL_OSPI_REGISTER_CALLBACKS */

      /* Get Flash information of one memory */
      (void)MX25LM51245G_GetFlashInfo(&pInfo);

      /* Fill config structure */
      ospi_init.ClockPrescaler = 3; /* OctoSPI clock = 120MHz / ClockPrescaler = 40MHz */
      ospi_init.MemorySize     = (uint32_t)POSITION_VAL((uint32_t)pInfo.FlashSize);
      ospi_init.SampleShifting = HAL_OSPI_SAMPLE_SHIFTING_NONE;
      ospi_init.TransferRate   = (uint32_t) Init->TransferRate;

      /* STM32 OSPI interface initialization */
      if (MX_OSPI_NOR_Init(&hospi_nor[Instance], &ospi_init) != HAL_OK)
      {
        ret = TicTacToe_ERROR_PERIPH_FAILURE;
      }
      /* OSPI memory reset */
      else if (OSPI_NOR_ResetMemory(Instance) != TicTacToe_ERROR_NONE)
      {
        ret = TicTacToe_ERROR_COMPONENT_FAILURE;
      }
      /* Check if memory is ready */
      else if (MX25LM51245G_AutoPollingMemReady(&hospi_nor[Instance], Ospi_Nor_Ctx[Instance].InterfaceMode, Ospi_Nor_Ctx[Instance].TransferRate) != MX25LM51245G_OK)
      {
        ret = TicTacToe_ERROR_COMPONENT_FAILURE;
      }
      /* Configure the memory */
      else if (TicTacToe_OSPI_NOR_ConfigFlash(Instance, Init->InterfaceMode, Init->TransferRate) != TicTacToe_ERROR_NONE)
      {
        ret = TicTacToe_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = TicTacToe_ERROR_NONE;
      }
    }
    else
    {
      ret = TicTacToe_ERROR_NONE;
    }
  }

  /* Return TicTacToe status */
  return ret;
}

/**
  * @brief  De-Initializes the OSPI interface.
  * @param  Instance   OSPI Instance
  * @retval TicTacToe status
  */
int32_t TicTacToe_OSPI_NOR_DeInit(uint32_t Instance)
{
  int32_t ret = TicTacToe_ERROR_NONE;

  /* Check if the instance is supported */
  if(Instance >= OSPI_NOR_INSTANCES_NUMBER)
  {
    ret = TicTacToe_ERROR_WRONG_PARAM;
  }
  else
  {
    /* Check if the instance is already initialized */
    if (Ospi_Nor_Ctx[Instance].IsInitialized != OSPI_ACCESS_NONE)
    {
      /* Disable Memory mapped mode */
      if(Ospi_Nor_Ctx[Instance].IsInitialized == OSPI_ACCESS_MMP)
      {
        if(TicTacToe_OSPI_NOR_DisableMemoryMappedMode(Instance) != TicTacToe_ERROR_NONE)
        {
          return TicTacToe_ERROR_COMPONENT_FAILURE;
        }
      }

      /* Set default Ospi_Nor_Ctx values */
      Ospi_Nor_Ctx[Instance].IsInitialized = OSPI_ACCESS_NONE;
      Ospi_Nor_Ctx[Instance].InterfaceMode = TicTacToe_OSPI_NOR_SPI_MODE;
      Ospi_Nor_Ctx[Instance].TransferRate  = TicTacToe_OSPI_NOR_STR_TRANSFER;

#if (USE_HAL_OSPI_REGISTER_CALLBACKS == 0)
      OSPI_NOR_MspDeInit(&hospi_nor[Instance]);
#endif /* (USE_HAL_OSPI_REGISTER_CALLBACKS == 0) */

      /* Call the DeInit function to reset the driver */
      if (HAL_OSPI_DeInit(&hospi_nor[Instance]) != HAL_OK)
      {
        ret = TicTacToe_ERROR_PERIPH_FAILURE;
      }
    }
  }

  /* Return TicTacToe status */
  return ret;
}

/**
  * @brief  Initializes the OSPI interface.
  * @param  hospi          OSPI handle
  * @param  Init           OSPI config structure
  * @retval TicTacToe status
  */
__weak HAL_StatusTypeDef MX_OSPI_NOR_Init(OSPI_HandleTypeDef *hospi, MX_OSPI_InitTypeDef *Init)
{
    /* OctoSPI initialization */
  hospi->Instance = OCTOSPI1;

  hospi->Init.FifoThreshold      = 4;
  hospi->Init.DualQuad           = HAL_OSPI_DUALQUAD_DISABLE;
  hospi->Init.DeviceSize         = Init->MemorySize; /* 512 MBits */
  hospi->Init.ChipSelectHighTime = 2;
  hospi->Init.FreeRunningClock   = HAL_OSPI_FREERUNCLK_DISABLE;
  hospi->Init.ClockMode          = HAL_OSPI_CLOCK_MODE_0;
  hospi->Init.WrapSize           = HAL_OSPI_WRAP_NOT_SUPPORTED;
  hospi->Init.ClockPrescaler     = Init->ClockPrescaler;
  hospi->Init.SampleShifting     = Init->SampleShifting;
  hospi->Init.ChipSelectBoundary = 0;

  if (Init->TransferRate == (uint32_t) TicTacToe_OSPI_NOR_DTR_TRANSFER)
  {
    hospi->Init.MemoryType            = HAL_OSPI_MEMTYPE_MACRONIX;
    hospi->Init.DelayHoldQuarterCycle = HAL_OSPI_DHQC_ENABLE;
  }
  else
  {
    hospi->Init.MemoryType            = HAL_OSPI_MEMTYPE_MICRON;
    hospi->Init.DelayHoldQuarterCycle = HAL_OSPI_DHQC_DISABLE;
  }

  return HAL_OSPI_Init(hospi);
}

#if (USE_HAL_OSPI_REGISTER_CALLBACKS == 1)
/**
  * @brief Default TicTacToe OSPI Msp Callbacks
  * @param Instance      OSPI Instance
  * @retval TicTacToe status
  */
int32_t TicTacToe_OSPI_NOR_RegisterDefaultMspCallbacks (uint32_t Instance)
{
  int32_t ret = TicTacToe_ERROR_NONE;

  /* Check if the instance is supported */
  if(Instance >= OSPI_NOR_INSTANCES_NUMBER)
  {
    ret = TicTacToe_ERROR_WRONG_PARAM;
  }
  else
  {
    /* Register MspInit/MspDeInit Callbacks */
    if(HAL_OSPI_RegisterCallback(&hospi_nor[Instance], HAL_OSPI_MSP_INIT_CB_ID, OSPI_NOR_MspInit) != HAL_OK)
    {
      ret = TicTacToe_ERROR_PERIPH_FAILURE;
    }
    else if(HAL_OSPI_RegisterCallback(&hospi_nor[Instance], HAL_OSPI_MSP_DEINIT_CB_ID, OSPI_NOR_MspDeInit) != HAL_OK)
    {
      ret = TicTacToe_ERROR_PERIPH_FAILURE;
    }
    else
    {
      OspiNor_IsMspCbValid[Instance] = 1U;
    }
  }

  /* Return TicTacToe status */
  return ret;
}

/**
  * @brief TicTacToe OSPI Msp Callback registering
  * @param Instance     OSPI Instance
  * @param CallBacks    pointer to MspInit/MspDeInit callbacks functions
  * @retval TicTacToe status
  */
int32_t TicTacToe_OSPI_NOR_RegisterMspCallbacks (uint32_t Instance, TicTacToe_OSPI_Cb_t *CallBacks)
{
  int32_t ret = TicTacToe_ERROR_NONE;

  /* Check if the instance is supported */
  if(Instance >= OSPI_NOR_INSTANCES_NUMBER)
  {
    ret = TicTacToe_ERROR_WRONG_PARAM;
  }
  else
  {
    /* Register MspInit/MspDeInit Callbacks */
    if(HAL_OSPI_RegisterCallback(&hospi_nor[Instance], HAL_OSPI_MSP_INIT_CB_ID, CallBacks->pMspInitCb) != HAL_OK)
    {
      ret = TicTacToe_ERROR_PERIPH_FAILURE;
    }
    else if(HAL_OSPI_RegisterCallback(&hospi_nor[Instance], HAL_OSPI_MSP_DEINIT_CB_ID, CallBacks->pMspDeInitCb) != HAL_OK)
    {
      ret = TicTacToe_ERROR_PERIPH_FAILURE;
    }
    else
    {
      OspiNor_IsMspCbValid[Instance] = 1U;
    }
  }

  /* Return TicTacToe status */
  return ret;
}
#endif /* (USE_HAL_OSPI_REGISTER_CALLBACKS == 1) */

/**
  * @brief  Reads an amount of data from the OSPI memory.
  * @param  Instance  OSPI instance
  * @param  pData     Pointer to data to be read
  * @param  ReadAddr  Read start address
  * @param  Size      Size of data to read
  * @retval TicTacToe status
  */
int32_t TicTacToe_OSPI_NOR_Read(uint32_t Instance, uint8_t* pData, uint32_t ReadAddr, uint32_t Size)
{
  int32_t ret;

  /* Check if the instance is supported */
  if(Instance >= OSPI_NOR_INSTANCES_NUMBER)
  {
    ret = TicTacToe_ERROR_WRONG_PARAM;
  }
  else
  {
    if(Ospi_Nor_Ctx[Instance].TransferRate == TicTacToe_OSPI_NOR_STR_TRANSFER)
    {
      if(MX25LM51245G_ReadSTR(&hospi_nor[Instance], Ospi_Nor_Ctx[Instance].InterfaceMode, MX25LM51245G_4BYTES_SIZE, pData, ReadAddr, Size) != MX25LM51245G_OK)
      {
        ret = TicTacToe_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = TicTacToe_ERROR_NONE;
      }
    }
    else
    {
      if(MX25LM51245G_ReadDTR(&hospi_nor[Instance], pData, ReadAddr, Size) != MX25LM51245G_OK)
      {
        ret = TicTacToe_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = TicTacToe_ERROR_NONE;
      }
    }
  }

  /* Return TicTacToe status */
  return ret;
}

/**
  * @brief  Writes an amount of data to the OSPI memory.
  * @param  Instance  OSPI instance
  * @param  pData     Pointer to data to be written
  * @param  WriteAddr Write start address
  * @param  Size      Size of data to write
  * @retval TicTacToe status
  */
int32_t TicTacToe_OSPI_NOR_Write(uint32_t Instance, uint8_t* pData, uint32_t WriteAddr, uint32_t Size)
{
  int32_t ret = TicTacToe_ERROR_NONE;
  uint32_t end_addr, current_size, current_addr;
  uint32_t data_addr;

  /* Check if the instance is supported */
  if(Instance >= OSPI_NOR_INSTANCES_NUMBER)
  {
    ret = TicTacToe_ERROR_WRONG_PARAM;
  }
  else
  {
    /* Calculation of the size between the write address and the end of the page */
    current_size = MX25LM51245G_PAGE_SIZE - (WriteAddr % MX25LM51245G_PAGE_SIZE);

    /* Check if the size of the data is less than the remaining place in the page */
    if (current_size > Size)
    {
      current_size = Size;
    }

    /* Initialize the address variables */
    current_addr = WriteAddr;
    end_addr = WriteAddr + Size;
    data_addr = (uint32_t)pData;

    /* Perform the write page by page */
    do
    {
      /* Check if Flash busy ? */
      if(MX25LM51245G_AutoPollingMemReady(&hospi_nor[Instance], Ospi_Nor_Ctx[Instance].InterfaceMode, Ospi_Nor_Ctx[Instance].TransferRate) != MX25LM51245G_OK)
      {
        ret = TicTacToe_ERROR_COMPONENT_FAILURE;
      }/* Enable write operations */
      else if(MX25LM51245G_WriteEnable(&hospi_nor[Instance], Ospi_Nor_Ctx[Instance].InterfaceMode, Ospi_Nor_Ctx[Instance].TransferRate) != MX25LM51245G_OK)
      {
        ret = TicTacToe_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        if(Ospi_Nor_Ctx[Instance].TransferRate == TicTacToe_OSPI_NOR_STR_TRANSFER)
        {
          /* Issue page program command */
          if(MX25LM51245G_PageProgram(&hospi_nor[Instance], Ospi_Nor_Ctx[Instance].InterfaceMode, MX25LM51245G_4BYTES_SIZE, (uint8_t*)data_addr, current_addr, current_size) != MX25LM51245G_OK)
          {
            ret = TicTacToe_ERROR_COMPONENT_FAILURE;
          }
        }
        else
        {
          /* Issue page program command */
          if(MX25LM51245G_PageProgramDTR(&hospi_nor[Instance], (uint8_t*)data_addr, current_addr, current_size) != MX25LM51245G_OK)
          {
            ret = TicTacToe_ERROR_COMPONENT_FAILURE;
          }
        }

        if (ret == TicTacToe_ERROR_NONE)
        {
          /* Configure automatic polling mode to wait for end of program */
          if (MX25LM51245G_AutoPollingMemReady(&hospi_nor[Instance], Ospi_Nor_Ctx[Instance].InterfaceMode, Ospi_Nor_Ctx[Instance].TransferRate) != MX25LM51245G_OK)
          {
            ret = TicTacToe_ERROR_COMPONENT_FAILURE;
          }
          else
          {
            /* Update the address and size variables for next page programming */
            current_addr += current_size;
            data_addr += current_size;
            current_size = ((current_addr + MX25LM51245G_PAGE_SIZE) > end_addr) ? (end_addr - current_addr) : MX25LM51245G_PAGE_SIZE;
          }
        }
      }
    } while ((current_addr < end_addr) && (ret == TicTacToe_ERROR_NONE));
  }

  /* Return TicTacToe status */
  return ret;
}

/**
  * @brief  Erases the specified block of the OSPI memory.
  * @param  Instance     OSPI instance
  * @param  BlockAddress Block address to erase
  * @param  BlockSize    Erase Block size
  * @retval TicTacToe status
  */
int32_t TicTacToe_OSPI_NOR_Erase_Block(uint32_t Instance, uint32_t BlockAddress, TicTacToe_OSPI_NOR_Erase_t BlockSize)
{
  int32_t ret;

  /* Check if the instance is supported */
  if(Instance >= OSPI_NOR_INSTANCES_NUMBER)
  {
    ret = TicTacToe_ERROR_WRONG_PARAM;
  }
  else
  {
    /* Check Flash busy ? */
    if(MX25LM51245G_AutoPollingMemReady(&hospi_nor[Instance], Ospi_Nor_Ctx[Instance].InterfaceMode, Ospi_Nor_Ctx[Instance].TransferRate) != MX25LM51245G_OK)
    {
      ret = TicTacToe_ERROR_COMPONENT_FAILURE;
    }/* Enable write operations */
    else if(MX25LM51245G_WriteEnable(&hospi_nor[Instance], Ospi_Nor_Ctx[Instance].InterfaceMode, Ospi_Nor_Ctx[Instance].TransferRate) != MX25LM51245G_OK)
    {
      ret = TicTacToe_ERROR_COMPONENT_FAILURE;
    }/* Issue Block Erase command */
    else if(MX25LM51245G_BlockErase(&hospi_nor[Instance], Ospi_Nor_Ctx[Instance].InterfaceMode, Ospi_Nor_Ctx[Instance].TransferRate, MX25LM51245G_4BYTES_SIZE, BlockAddress, BlockSize) != MX25LM51245G_OK)
    {
      ret = TicTacToe_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = TicTacToe_ERROR_NONE;
    }
  }

  /* Return TicTacToe status */
  return ret;
}

/**
  * @brief  Erases the entire OSPI memory.
  * @param  Instance  QSPI instance
  * @retval TicTacToe status
  */
int32_t TicTacToe_OSPI_NOR_Erase_Chip(uint32_t Instance)
{
  int32_t ret;

  /* Check if the instance is supported */
  if(Instance >= OSPI_NOR_INSTANCES_NUMBER)
  {
    ret = TicTacToe_ERROR_WRONG_PARAM;
  }
  else
  {
    /* Check Flash busy ? */
    if(MX25LM51245G_AutoPollingMemReady(&hospi_nor[Instance], Ospi_Nor_Ctx[Instance].InterfaceMode, Ospi_Nor_Ctx[Instance].TransferRate) != MX25LM51245G_OK)
    {
      ret = TicTacToe_ERROR_COMPONENT_FAILURE;
    }/* Enable write operations */
    else if(MX25LM51245G_WriteEnable(&hospi_nor[Instance], Ospi_Nor_Ctx[Instance].InterfaceMode, Ospi_Nor_Ctx[Instance].TransferRate) != MX25LM51245G_OK)
    {
      ret = TicTacToe_ERROR_COMPONENT_FAILURE;
    }/* Issue Chip erase command */
    else if(MX25LM51245G_ChipErase(&hospi_nor[Instance], Ospi_Nor_Ctx[Instance].InterfaceMode, Ospi_Nor_Ctx[Instance].TransferRate) != MX25LM51245G_OK)
    {
      ret = TicTacToe_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = TicTacToe_ERROR_NONE;
    }
  }

  /* Return TicTacToe status */
  return ret;
}

/**
  * @brief  Reads current status of the OSPI memory.
  * @param  Instance  QSPI instance
  * @retval OSPI memory status: whether busy or not
  */
int32_t TicTacToe_OSPI_NOR_GetStatus(uint32_t Instance)
{
  static uint8_t reg[2];
  int32_t ret;

  /* Check if the instance is supported */
  if(Instance >= OSPI_NOR_INSTANCES_NUMBER)
  {
    ret = TicTacToe_ERROR_WRONG_PARAM;
  }
  else
  {
    if(MX25LM51245G_ReadSecurityRegister(&hospi_nor[Instance], Ospi_Nor_Ctx[Instance].InterfaceMode, Ospi_Nor_Ctx[Instance].TransferRate, reg) != MX25LM51245G_OK)
    {
      ret = TicTacToe_ERROR_COMPONENT_FAILURE;
    }/* Check the value of the register */
    else if ((reg[0] & (MX25LM51245G_SECR_P_FAIL | MX25LM51245G_SECR_E_FAIL)) != 0U)
    {
      ret = TicTacToe_ERROR_COMPONENT_FAILURE;
    }
    else if ((reg[0] & (MX25LM51245G_SECR_PSB | MX25LM51245G_SECR_ESB)) != 0U)
    {
      ret = TicTacToe_ERROR_OSPI_SUSPENDED;
    }
    else if(MX25LM51245G_ReadStatusRegister(&hospi_nor[Instance], Ospi_Nor_Ctx[Instance].InterfaceMode, Ospi_Nor_Ctx[Instance].TransferRate, reg) != MX25LM51245G_OK)
    {
      ret = TicTacToe_ERROR_COMPONENT_FAILURE;
    }/* Check the value of the register */
    else if ((reg[0] & MX25LM51245G_SR_WIP) != 0U)
    {
      ret = TicTacToe_ERROR_BUSY;
    }
    else
    {
      ret = TicTacToe_ERROR_NONE;
    }
  }

  /* Return TicTacToe status */
  return ret;
}

/**
  * @brief  Return the configuration of the OSPI memory.
  * @param  Instance  OSPI instance
  * @param  pInfo     pointer on the configuration structure
  * @retval TicTacToe status
  */
int32_t TicTacToe_OSPI_NOR_GetInfo(uint32_t Instance, TicTacToe_OSPI_NOR_Info_t* pInfo)
{
  int32_t ret = TicTacToe_ERROR_NONE;

  /* Check if the instance is supported */
  if(Instance >= OSPI_NOR_INSTANCES_NUMBER)
  {
    ret = TicTacToe_ERROR_WRONG_PARAM;
  }
  else
  {
    (void)MX25LM51245G_GetFlashInfo(pInfo);
  }

  /* Return TicTacToe status */
  return ret;
}

/**
  * @brief  Configure the OSPI in memory-mapped mode
  * @param  Instance  OSPI instance
  * @retval TicTacToe status
  */
int32_t TicTacToe_OSPI_NOR_EnableMemoryMappedMode(uint32_t Instance)
{
  int32_t ret = TicTacToe_ERROR_NONE;

  /* Check if the instance is supported */
  if(Instance >= OSPI_NOR_INSTANCES_NUMBER)
  {
    ret = TicTacToe_ERROR_WRONG_PARAM;
  }
  else
  {
    if(Ospi_Nor_Ctx[Instance].TransferRate == TicTacToe_OSPI_NOR_STR_TRANSFER)
    {
      if(MX25LM51245G_EnableMemoryMappedModeSTR(&hospi_nor[Instance], Ospi_Nor_Ctx[Instance].InterfaceMode, MX25LM51245G_4BYTES_SIZE) != MX25LM51245G_OK)
      {
        ret = TicTacToe_ERROR_COMPONENT_FAILURE;
      }
      else /* Update OSPI context if all operations are well done */
      {
        Ospi_Nor_Ctx[Instance].IsInitialized = OSPI_ACCESS_MMP;
      }
    }
    else
    {
      if(MX25LM51245G_EnableMemoryMappedModeDTR(&hospi_nor[Instance], Ospi_Nor_Ctx[Instance].InterfaceMode) != MX25LM51245G_OK)
      {
        ret = TicTacToe_ERROR_COMPONENT_FAILURE;
      }
      else /* Update OSPI context if all operations are well done */
      {
        Ospi_Nor_Ctx[Instance].IsInitialized = OSPI_ACCESS_MMP;
      }
    }
  }

  /* Return TicTacToe status */
  return ret;
}

/**
  * @brief  Exit form memory-mapped mode
  *         Only 1 Instance can running MMP mode. And it will lock system at this mode.
  * @param  Instance  OSPI instance
  * @retval TicTacToe status
  */
int32_t TicTacToe_OSPI_NOR_DisableMemoryMappedMode(uint32_t Instance)
{
  int32_t ret = TicTacToe_ERROR_NONE;

  /* Check if the instance is supported */
  if(Instance >= OSPI_NOR_INSTANCES_NUMBER)
  {
    ret = TicTacToe_ERROR_WRONG_PARAM;
  }
  else
  {
    if(Ospi_Nor_Ctx[Instance].IsInitialized != OSPI_ACCESS_MMP)
    {
      ret = TicTacToe_ERROR_OSPI_MMP_UNLOCK_FAILURE;
    }/* Abort MMP back to indirect mode */
    else if(HAL_OSPI_Abort(&hospi_nor[Instance]) != HAL_OK)
    {
      ret = TicTacToe_ERROR_PERIPH_FAILURE;
    }
    else /* Update OSPI NOR context if all operations are well done */
    {
      Ospi_Nor_Ctx[Instance].IsInitialized = OSPI_ACCESS_INDIRECT;
    }
  }

  /* Return TicTacToe status */
  return ret;
}

/**
  * @brief  Get flash ID 3 Bytes:
  *         Manufacturer ID, Memory type, Memory density
  * @param  Instance  OSPI instance
  * @param  Id Pointer to flash ID bytes
  * @retval TicTacToe status
  */
int32_t TicTacToe_OSPI_NOR_ReadID(uint32_t Instance, uint8_t *Id)
{
  int32_t ret;

  /* Check if the instance is supported */
  if(Instance >= OSPI_NOR_INSTANCES_NUMBER)
  {
    ret = TicTacToe_ERROR_WRONG_PARAM;
  }
  else if(MX25LM51245G_ReadID(&hospi_nor[Instance], Ospi_Nor_Ctx[Instance].InterfaceMode, Ospi_Nor_Ctx[Instance].TransferRate, Id) != MX25LM51245G_OK)
  {
    ret = TicTacToe_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = TicTacToe_ERROR_NONE;
  }

  /* Return TicTacToe status */
  return ret;
}

/**
  * @brief  Set Flash to desired Interface mode. And this instance becomes current instance.
  *         If current instance running at MMP mode then this function doesn't work.
  *         Indirect -> Indirect
  * @param  Instance  OSPI instance
  * @param  Mode      OSPI mode
  * @param  Rate      OSPI transfer rate
  * @retval TicTacToe status
  */
int32_t TicTacToe_OSPI_NOR_ConfigFlash(uint32_t Instance, TicTacToe_OSPI_NOR_Interface_t Mode, TicTacToe_OSPI_NOR_Transfer_t Rate)
{
  int32_t ret = TicTacToe_ERROR_NONE;

  /* Check if the instance is supported */
  if(Instance >= OSPI_NOR_INSTANCES_NUMBER)
  {
    ret = TicTacToe_ERROR_WRONG_PARAM;
  }
  else
  {
    /* Check if MMP mode locked ************************************************/
    if(Ospi_Nor_Ctx[Instance].IsInitialized == OSPI_ACCESS_MMP)
    {
      ret = TicTacToe_ERROR_OSPI_MMP_LOCK_FAILURE;
    }
    else
    {
      /* Setup Flash interface ***************************************************/
      switch(Ospi_Nor_Ctx[Instance].InterfaceMode)
      {
      case TicTacToe_OSPI_NOR_OPI_MODE :  /* 8-8-8 commands */
        if((Mode != TicTacToe_OSPI_NOR_OPI_MODE) || (Rate != Ospi_Nor_Ctx[Instance].TransferRate))
        {
          /* Exit OPI mode */
          ret = OSPI_NOR_ExitOPIMode(Instance);

          if ((ret == TicTacToe_ERROR_NONE) && (Mode == TicTacToe_OSPI_NOR_OPI_MODE))
          {

            if (Ospi_Nor_Ctx[Instance].TransferRate == TicTacToe_OSPI_NOR_STR_TRANSFER)
            {
              /* Enter DTR OPI mode */
              ret = OSPI_NOR_EnterDOPIMode(Instance);
            }
            else
            {
              /* Enter STR OPI mode */
              ret = OSPI_NOR_EnterSOPIMode(Instance);
            }
          }
        }
        break;

      case TicTacToe_OSPI_NOR_SPI_MODE :  /* 1-1-1 commands, Power on H/W default setting */
      default :
        if(Mode == TicTacToe_OSPI_NOR_OPI_MODE)
        {
          if(Rate == TicTacToe_OSPI_NOR_STR_TRANSFER)
          {
            /* Enter STR OPI mode */
            ret = OSPI_NOR_EnterSOPIMode(Instance);
          }
          else
          {
            /* Enter DTR OPI mode */
            ret = OSPI_NOR_EnterDOPIMode(Instance);
          }
        }
        break;
      }

      /* Update OSPI context if all operations are well done */
      if(ret == TicTacToe_ERROR_NONE)
      {
        /* Update current status parameter *****************************************/
        Ospi_Nor_Ctx[Instance].IsInitialized = OSPI_ACCESS_INDIRECT;
        Ospi_Nor_Ctx[Instance].InterfaceMode = Mode;
        Ospi_Nor_Ctx[Instance].TransferRate  = Rate;
      }
    }
  }

  /* Return TicTacToe status */
  return ret;
}

/**
  * @brief  This function suspends an ongoing erase command.
  * @param  Instance  QSPI instance
  * @retval TicTacToe status
  */
int32_t TicTacToe_OSPI_NOR_SuspendErase(uint32_t Instance)
{
  int32_t ret;

  /* Check if the instance is supported */
  if(Instance >= OSPI_NOR_INSTANCES_NUMBER)
  {
    ret = TicTacToe_ERROR_WRONG_PARAM;
  }
  /* Check whether the device is busy (erase operation is in progress). */
  else if (TicTacToe_OSPI_NOR_GetStatus(Instance) != TicTacToe_ERROR_BUSY)
  {
    ret = TicTacToe_ERROR_COMPONENT_FAILURE;
  }
  else if(MX25LM51245G_Suspend(&hospi_nor[Instance], Ospi_Nor_Ctx[Instance].InterfaceMode, Ospi_Nor_Ctx[Instance].TransferRate) != MX25LM51245G_OK)
  {
    ret = TicTacToe_ERROR_COMPONENT_FAILURE;
  }
  else if (TicTacToe_OSPI_NOR_GetStatus(Instance) != TicTacToe_ERROR_OSPI_SUSPENDED)
  {
    ret = TicTacToe_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = TicTacToe_ERROR_NONE;
  }

  /* Return TicTacToe status */
  return ret;
}

/**
  * @brief  This function resumes a paused erase command.
  * @param  Instance  QSPI instance
  * @retval TicTacToe status
  */
int32_t TicTacToe_OSPI_NOR_ResumeErase(uint32_t Instance)
{
  int32_t ret;

  /* Check if the instance is supported */
  if(Instance >= OSPI_NOR_INSTANCES_NUMBER)
  {
    ret = TicTacToe_ERROR_WRONG_PARAM;
  }
  /* Check whether the device is busy (erase operation is in progress). */
  else if (TicTacToe_OSPI_NOR_GetStatus(Instance) != TicTacToe_ERROR_OSPI_SUSPENDED)
  {
    ret = TicTacToe_ERROR_COMPONENT_FAILURE;
  }
  else if(MX25LM51245G_Resume(&hospi_nor[Instance], Ospi_Nor_Ctx[Instance].InterfaceMode, Ospi_Nor_Ctx[Instance].TransferRate) != MX25LM51245G_OK)
  {
    ret = TicTacToe_ERROR_COMPONENT_FAILURE;
  }
  /*
  When this command is executed, the status register write in progress bit is set to 1, and
  the flag status register program erase controller bit is set to 0. This command is ignored
  if the device is not in a suspended state.
  */
  else if (TicTacToe_OSPI_NOR_GetStatus(Instance) != TicTacToe_ERROR_BUSY)
  {
    ret = TicTacToe_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = TicTacToe_ERROR_NONE;
  }

  /* Return TicTacToe status */
  return ret;
}

/**
  * @brief  This function enter the OSPI memory in deep power down mode.
  * @param  Instance  QSPI instance
  * @retval TicTacToe status
  */
int32_t TicTacToe_OSPI_NOR_EnterDeepPowerDown(uint32_t Instance)
{
  int32_t ret;

  /* Check if the instance is supported */
  if(Instance >= OSPI_NOR_INSTANCES_NUMBER)
  {
    ret = TicTacToe_ERROR_WRONG_PARAM;
  }
  else if(MX25LM51245G_EnterPowerDown(&hospi_nor[Instance], Ospi_Nor_Ctx[Instance].InterfaceMode, Ospi_Nor_Ctx[Instance].TransferRate) != MX25LM51245G_OK)
  {
    ret = TicTacToe_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = TicTacToe_ERROR_NONE;
  }

  /* ---          Memory takes 10us max to enter deep power down          --- */

  /* Return TicTacToe status */
  return ret;
}

/**
  * @brief  This function leave the OSPI memory from deep power down mode.
  * @param  Instance  QSPI instance
  * @retval TicTacToe status
  */
int32_t TicTacToe_OSPI_NOR_LeaveDeepPowerDown(uint32_t Instance)
{
  int32_t ret;

  /* Check if the instance is supported */
  if(Instance >= OSPI_NOR_INSTANCES_NUMBER)
  {
    ret = TicTacToe_ERROR_WRONG_PARAM;
  }
  else if(MX25LM51245G_NoOperation(&hospi_nor[Instance], Ospi_Nor_Ctx[Instance].InterfaceMode, Ospi_Nor_Ctx[Instance].TransferRate) != MX25LM51245G_OK)
  {
    ret = TicTacToe_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = TicTacToe_ERROR_NONE;
  }

  /* --- A NOP command is sent to the memory, as the nCS should be low for at least 20 ns --- */
  /* ---                  Memory takes 30us min to leave deep power down                  --- */

  /* Return TicTacToe status */
  return ret;
}
/**
  * @}
  */

/** @addtogroup STM32L562E-DK_OSPI_NOR_Private_Functions
  * @{
  */

/**
  * @brief  Initializes the OSPI MSP.
  * @param  hospi OSPI handle
  * @retval None
  */
static void OSPI_NOR_MspInit(OSPI_HandleTypeDef *hospi)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* hospi unused argument(s) compilation warning */
  UNUSED(hospi);

  /* Enable the OctoSPI memory interface clock */
  OSPI_CLK_ENABLE();

  /* Reset the OctoSPI memory interface */
  OSPI_FORCE_RESET();
  OSPI_RELEASE_RESET();

  /* Enable GPIO clocks */
  OSPI_CLK_GPIO_CLK_ENABLE();
  OSPI_DQS_GPIO_CLK_ENABLE();
  OSPI_CS_GPIO_CLK_ENABLE();
  OSPI_D0_GPIO_CLK_ENABLE();
  OSPI_D1_GPIO_CLK_ENABLE();
  OSPI_D2_GPIO_CLK_ENABLE();
  OSPI_D3_GPIO_CLK_ENABLE();
  OSPI_D4_GPIO_CLK_ENABLE();
  OSPI_D5_GPIO_CLK_ENABLE();
  OSPI_D6_GPIO_CLK_ENABLE();
  OSPI_D7_GPIO_CLK_ENABLE();

  /* OctoSPI CS GPIO pin configuration  */
  GPIO_InitStruct.Pin       = OSPI_CS_PIN;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = OSPI_CS_PIN_AF;
  HAL_GPIO_Init(OSPI_CS_GPIO_PORT, &GPIO_InitStruct);

  /* OctoSPI DQS GPIO pin configuration  */
  GPIO_InitStruct.Pin       = OSPI_DQS_PIN;
  GPIO_InitStruct.Alternate = OSPI_DQS_PIN_AF;
  HAL_GPIO_Init(OSPI_DQS_GPIO_PORT, &GPIO_InitStruct);

  /* OctoSPI CLK GPIO pin configuration  */
  GPIO_InitStruct.Pin       = OSPI_CLK_PIN;
  GPIO_InitStruct.Pull      = GPIO_NOPULL;
  GPIO_InitStruct.Alternate = OSPI_CLK_PIN_AF;
  HAL_GPIO_Init(OSPI_CLK_GPIO_PORT, &GPIO_InitStruct);

  /* OctoSPI D0 GPIO pin configuration  */
  GPIO_InitStruct.Pin       = OSPI_D0_PIN;
  GPIO_InitStruct.Alternate = OSPI_D0_PIN_AF;
  HAL_GPIO_Init(OSPI_D0_GPIO_PORT, &GPIO_InitStruct);

  /* OctoSPI D1 GPIO pin configuration  */
  GPIO_InitStruct.Pin       = OSPI_D1_PIN;
  GPIO_InitStruct.Alternate = OSPI_D1_PIN_AF;
  HAL_GPIO_Init(OSPI_D1_GPIO_PORT, &GPIO_InitStruct);

  /* OctoSPI D2 GPIO pin configuration  */
  GPIO_InitStruct.Pin       = OSPI_D2_PIN;
  GPIO_InitStruct.Alternate = OSPI_D2_PIN_AF;
  HAL_GPIO_Init(OSPI_D2_GPIO_PORT, &GPIO_InitStruct);

  /* OctoSPI D3 GPIO pin configuration  */
  GPIO_InitStruct.Pin       = OSPI_D3_PIN;
  GPIO_InitStruct.Alternate = OSPI_D3_PIN_AF;
  HAL_GPIO_Init(OSPI_D3_GPIO_PORT, &GPIO_InitStruct);

  /* OctoSPI D4 GPIO pin configuration  */
  GPIO_InitStruct.Pin       = OSPI_D4_PIN;
  GPIO_InitStruct.Alternate = OSPI_D4_PIN_AF;
  HAL_GPIO_Init(OSPI_D4_GPIO_PORT, &GPIO_InitStruct);

  /* OctoSPI D5 GPIO pin configuration  */
  GPIO_InitStruct.Pin       = OSPI_D5_PIN;
  GPIO_InitStruct.Alternate = OSPI_D5_PIN_AF;
  HAL_GPIO_Init(OSPI_D5_GPIO_PORT, &GPIO_InitStruct);

  /* OctoSPI D6 GPIO pin configuration  */
  GPIO_InitStruct.Pin       = OSPI_D6_PIN;
  GPIO_InitStruct.Alternate = OSPI_D6_PIN_AF;
  HAL_GPIO_Init(OSPI_D6_GPIO_PORT, &GPIO_InitStruct);

  /* OctoSPI D7 GPIO pin configuration  */
  GPIO_InitStruct.Pin       = OSPI_D7_PIN;
  GPIO_InitStruct.Alternate = OSPI_D7_PIN_AF;
  HAL_GPIO_Init(OSPI_D7_GPIO_PORT, &GPIO_InitStruct);
}

/**
  * @brief  De-Initializes the OSPI MSP.
  * @param  hospi OSPI handle
  * @retval None
  */
static void OSPI_NOR_MspDeInit(OSPI_HandleTypeDef *hospi)
{
  /* hospi unused argument(s) compilation warning */
  UNUSED(hospi);

  /* OctoSPI GPIO pins de-configuration  */
  HAL_GPIO_DeInit(OSPI_CLK_GPIO_PORT, OSPI_CLK_PIN);
  HAL_GPIO_DeInit(OSPI_DQS_GPIO_PORT, OSPI_DQS_PIN);
  HAL_GPIO_DeInit(OSPI_CS_GPIO_PORT, OSPI_CS_PIN);
  HAL_GPIO_DeInit(OSPI_D0_GPIO_PORT, OSPI_D0_PIN);
  HAL_GPIO_DeInit(OSPI_D1_GPIO_PORT, OSPI_D1_PIN);
  HAL_GPIO_DeInit(OSPI_D2_GPIO_PORT, OSPI_D2_PIN);
  HAL_GPIO_DeInit(OSPI_D3_GPIO_PORT, OSPI_D3_PIN);
  HAL_GPIO_DeInit(OSPI_D4_GPIO_PORT, OSPI_D4_PIN);
  HAL_GPIO_DeInit(OSPI_D5_GPIO_PORT, OSPI_D5_PIN);
  HAL_GPIO_DeInit(OSPI_D6_GPIO_PORT, OSPI_D6_PIN);
  HAL_GPIO_DeInit(OSPI_D7_GPIO_PORT, OSPI_D7_PIN);

  /* Reset the OctoSPI memory interface */
  OSPI_FORCE_RESET();
  OSPI_RELEASE_RESET();

  /* Disable the OctoSPI memory interface clock */
  OSPI_CLK_DISABLE();
}

/**
  * @brief  This function reset the OSPI memory.
  * @param  Instance  OSPI instance
  * @retval TicTacToe status
  */
static int32_t OSPI_NOR_ResetMemory (uint32_t Instance)
{
  int32_t ret = TicTacToe_ERROR_NONE;

  /* Check if the instance is supported */
  if(Instance >= OSPI_NOR_INSTANCES_NUMBER)
  {
    ret = TicTacToe_ERROR_WRONG_PARAM;
  }
  else if(MX25LM51245G_ResetEnable(&hospi_nor[Instance], TicTacToe_OSPI_NOR_SPI_MODE, TicTacToe_OSPI_NOR_STR_TRANSFER) != MX25LM51245G_OK)
  {
    ret = TicTacToe_ERROR_COMPONENT_FAILURE;
  }
  else if(MX25LM51245G_ResetMemory(&hospi_nor[Instance], TicTacToe_OSPI_NOR_SPI_MODE, TicTacToe_OSPI_NOR_STR_TRANSFER) != MX25LM51245G_OK)
  {
    ret = TicTacToe_ERROR_COMPONENT_FAILURE;
  }
  else if(MX25LM51245G_ResetEnable(&hospi_nor[Instance], TicTacToe_OSPI_NOR_OPI_MODE, TicTacToe_OSPI_NOR_STR_TRANSFER) != MX25LM51245G_OK)
  {
    ret = TicTacToe_ERROR_COMPONENT_FAILURE;
  }
  else if(MX25LM51245G_ResetMemory(&hospi_nor[Instance], TicTacToe_OSPI_NOR_OPI_MODE, TicTacToe_OSPI_NOR_STR_TRANSFER) != MX25LM51245G_OK)
  {
    ret = TicTacToe_ERROR_COMPONENT_FAILURE;
  }
  else if(MX25LM51245G_ResetEnable(&hospi_nor[Instance], TicTacToe_OSPI_NOR_OPI_MODE, TicTacToe_OSPI_NOR_DTR_TRANSFER) != MX25LM51245G_OK)
  {
    ret = TicTacToe_ERROR_COMPONENT_FAILURE;
  }
  else if(MX25LM51245G_ResetMemory(&hospi_nor[Instance], TicTacToe_OSPI_NOR_OPI_MODE, TicTacToe_OSPI_NOR_DTR_TRANSFER) != MX25LM51245G_OK)
  {
    ret = TicTacToe_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    Ospi_Nor_Ctx[Instance].IsInitialized = OSPI_ACCESS_INDIRECT;      /* After reset S/W setting to indirect access   */
    Ospi_Nor_Ctx[Instance].InterfaceMode = TicTacToe_OSPI_NOR_SPI_MODE;         /* After reset H/W back to SPI mode by default  */
    Ospi_Nor_Ctx[Instance].TransferRate  = TicTacToe_OSPI_NOR_STR_TRANSFER;     /* After reset S/W setting to STR mode          */

    /* After SWreset CMD, wait in case SWReset occurred during erase operation */
    HAL_Delay(MX25LM51245G_RESET_MAX_TIME);
  }

  /* Return TicTacToe status */
  return ret;
}

/**
  * @brief  This function enables the octal DTR mode of the memory.
  * @param  Instance  OSPI instance
  * @retval TicTacToe status
  */
static int32_t OSPI_NOR_EnterDOPIMode(uint32_t Instance)
{
  int32_t ret;
  uint8_t reg[2];

  /* Check if the instance is supported */
  if(Instance >= OSPI_NOR_INSTANCES_NUMBER)
  {
    ret = TicTacToe_ERROR_WRONG_PARAM;
  }
  /* Enable write operations */
  else if (MX25LM51245G_WriteEnable(&hospi_nor[Instance], Ospi_Nor_Ctx[Instance].InterfaceMode, Ospi_Nor_Ctx[Instance].TransferRate) != MX25LM51245G_OK)
  {
    ret = TicTacToe_ERROR_COMPONENT_FAILURE;
  }
  /* Write Configuration register 2 (with new dummy cycles) */
  else if (MX25LM51245G_WriteCfg2Register(&hospi_nor[Instance], Ospi_Nor_Ctx[Instance].InterfaceMode, Ospi_Nor_Ctx[Instance].TransferRate, MX25LM51245G_CR2_REG3_ADDR, MX25LM51245G_CR2_DC_6_CYCLES) != MX25LM51245G_OK)
  {
    ret = TicTacToe_ERROR_COMPONENT_FAILURE;
  }
  /* Enable write operations */
  else if (MX25LM51245G_WriteEnable(&hospi_nor[Instance], Ospi_Nor_Ctx[Instance].InterfaceMode, Ospi_Nor_Ctx[Instance].TransferRate) != MX25LM51245G_OK)
  {
    ret = TicTacToe_ERROR_COMPONENT_FAILURE;
  }
  /* Write Configuration register 2 (with Octal I/O SPI protocol) */
  else if (MX25LM51245G_WriteCfg2Register(&hospi_nor[Instance], Ospi_Nor_Ctx[Instance].InterfaceMode, Ospi_Nor_Ctx[Instance].TransferRate, MX25LM51245G_CR2_REG1_ADDR, MX25LM51245G_CR2_DOPI) != MX25LM51245G_OK)
  {
    ret = TicTacToe_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    /* Wait that the configuration is effective and check that memory is ready */
    HAL_Delay(MX25LM51245G_WRITE_REG_MAX_TIME);

    /* Reconfigure the memory type of the peripheral */
    hospi_nor[Instance].Init.MemoryType            = HAL_OSPI_MEMTYPE_MACRONIX;
    hospi_nor[Instance].Init.DelayHoldQuarterCycle = HAL_OSPI_DHQC_ENABLE;
    if (HAL_OSPI_Init(&hospi_nor[Instance]) != HAL_OK)
    {
      ret = TicTacToe_ERROR_PERIPH_FAILURE;
    }
    /* Check Flash busy ? */
    else if (MX25LM51245G_AutoPollingMemReady(&hospi_nor[Instance], TicTacToe_OSPI_NOR_OPI_MODE, TicTacToe_OSPI_NOR_DTR_TRANSFER) != MX25LM51245G_OK)
    {
      ret = TicTacToe_ERROR_COMPONENT_FAILURE;
    }
    /* Check the configuration has been correctly done */
    else if (MX25LM51245G_ReadCfg2Register(&hospi_nor[Instance], TicTacToe_OSPI_NOR_OPI_MODE, TicTacToe_OSPI_NOR_DTR_TRANSFER, MX25LM51245G_CR2_REG1_ADDR, reg) != MX25LM51245G_OK)
    {
      ret = TicTacToe_ERROR_COMPONENT_FAILURE;
    }
    else if (reg[0] != MX25LM51245G_CR2_DOPI)
    {
      ret = TicTacToe_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = TicTacToe_ERROR_NONE;
    }
  }

  /* Return TicTacToe status */
  return ret;
}

/**
  * @brief  This function enables the octal STR mode of the memory.
  * @param  Instance  OSPI instance
  * @retval TicTacToe status
  */
static int32_t OSPI_NOR_EnterSOPIMode(uint32_t Instance)
{
  int32_t ret;
  uint8_t reg[2];

  /* Check if the instance is supported */
  if(Instance >= OSPI_NOR_INSTANCES_NUMBER)
  {
    ret = TicTacToe_ERROR_WRONG_PARAM;
  }
  /* Enable write operations */
  else if (MX25LM51245G_WriteEnable(&hospi_nor[Instance], Ospi_Nor_Ctx[Instance].InterfaceMode, Ospi_Nor_Ctx[Instance].TransferRate) != MX25LM51245G_OK)
  {
    ret = TicTacToe_ERROR_COMPONENT_FAILURE;
  }
  /* Write Configuration register 2 (with new dummy cycles) */
  else if (MX25LM51245G_WriteCfg2Register(&hospi_nor[Instance], Ospi_Nor_Ctx[Instance].InterfaceMode, Ospi_Nor_Ctx[Instance].TransferRate, MX25LM51245G_CR2_REG3_ADDR, MX25LM51245G_CR2_DC_6_CYCLES) != MX25LM51245G_OK)
  {
    ret = TicTacToe_ERROR_COMPONENT_FAILURE;
  }
  /* Enable write operations */
  else if (MX25LM51245G_WriteEnable(&hospi_nor[Instance], Ospi_Nor_Ctx[Instance].InterfaceMode, Ospi_Nor_Ctx[Instance].TransferRate) != MX25LM51245G_OK)
  {
    ret = TicTacToe_ERROR_COMPONENT_FAILURE;
  }
  /* Write Configuration register 2 (with Octal I/O SPI protocol) */
  else if (MX25LM51245G_WriteCfg2Register(&hospi_nor[Instance], Ospi_Nor_Ctx[Instance].InterfaceMode, Ospi_Nor_Ctx[Instance].TransferRate, MX25LM51245G_CR2_REG1_ADDR, MX25LM51245G_CR2_SOPI) != MX25LM51245G_OK)
  {
    ret = TicTacToe_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    /* Wait that the configuration is effective and check that memory is ready */
    HAL_Delay(MX25LM51245G_WRITE_REG_MAX_TIME);

    /* Check Flash busy ? */
    if (MX25LM51245G_AutoPollingMemReady(&hospi_nor[Instance], TicTacToe_OSPI_NOR_OPI_MODE, TicTacToe_OSPI_NOR_STR_TRANSFER) != MX25LM51245G_OK)
    {
      ret = TicTacToe_ERROR_COMPONENT_FAILURE;
    }
    /* Check the configuration has been correctly done */
    else if (MX25LM51245G_ReadCfg2Register(&hospi_nor[Instance], TicTacToe_OSPI_NOR_OPI_MODE, TicTacToe_OSPI_NOR_STR_TRANSFER, MX25LM51245G_CR2_REG1_ADDR, reg) != MX25LM51245G_OK)
    {
      ret = TicTacToe_ERROR_COMPONENT_FAILURE;
    }
    else if (reg[0] != MX25LM51245G_CR2_SOPI)
    {
      ret = TicTacToe_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = TicTacToe_ERROR_NONE;
    }
  }

  /* Return TicTacToe status */
  return ret;
}

/**
  * @brief  This function disables the octal DTR or STR mode of the memory.
  * @param  Instance  OSPI instance
  * @retval TicTacToe status
  */
static int32_t OSPI_NOR_ExitOPIMode (uint32_t Instance)
{
  int32_t ret = TicTacToe_ERROR_NONE;
  uint8_t reg[2];

  /* Check if the instance is supported */
  if(Instance >= OSPI_NOR_INSTANCES_NUMBER)
  {
    ret = TicTacToe_ERROR_WRONG_PARAM;
  }
  /* Enable write operations */
  else if (MX25LM51245G_WriteEnable(&hospi_nor[Instance], Ospi_Nor_Ctx[Instance].InterfaceMode, Ospi_Nor_Ctx[Instance].TransferRate) != MX25LM51245G_OK)
  {
    ret = TicTacToe_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    /* Write Configuration register 2 (with SPI protocol) */
    reg[0] = 0;
    reg[1] = 0;
    if (MX25LM51245G_WriteCfg2Register(&hospi_nor[Instance], Ospi_Nor_Ctx[Instance].InterfaceMode, Ospi_Nor_Ctx[Instance].TransferRate, MX25LM51245G_CR2_REG1_ADDR, reg[0]) != MX25LM51245G_OK)
    {
      ret = TicTacToe_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      /* Wait that the configuration is effective and check that memory is ready */
      HAL_Delay(MX25LM51245G_WRITE_REG_MAX_TIME);

      if (Ospi_Nor_Ctx[Instance].TransferRate == TicTacToe_OSPI_NOR_DTR_TRANSFER)
      {
        /* Reconfigure the memory type of the peripheral */
        hospi_nor[Instance].Init.MemoryType            = HAL_OSPI_MEMTYPE_MICRON;
        hospi_nor[Instance].Init.DelayHoldQuarterCycle = HAL_OSPI_DHQC_DISABLE;
        if (HAL_OSPI_Init(&hospi_nor[Instance]) != HAL_OK)
        {
          ret = TicTacToe_ERROR_PERIPH_FAILURE;
        }
      }

      if (ret == TicTacToe_ERROR_NONE)
      {
        /* Check Flash busy ? */
        if (MX25LM51245G_AutoPollingMemReady(&hospi_nor[Instance], TicTacToe_OSPI_NOR_SPI_MODE, TicTacToe_OSPI_NOR_STR_TRANSFER) != MX25LM51245G_OK)
        {
          ret = TicTacToe_ERROR_COMPONENT_FAILURE;
        }
        /* Check the configuration has been correctly done */
        else if (MX25LM51245G_ReadCfg2Register(&hospi_nor[Instance], TicTacToe_OSPI_NOR_SPI_MODE, TicTacToe_OSPI_NOR_STR_TRANSFER, MX25LM51245G_CR2_REG1_ADDR, reg) != MX25LM51245G_OK)
        {
          ret = TicTacToe_ERROR_COMPONENT_FAILURE;
        }
        else if (reg[0] != 0U)
        {
          ret = TicTacToe_ERROR_COMPONENT_FAILURE;
        }
        else
        {
          /* Nothing to do */
        }
      }
    }
  }

  /* Return TicTacToe status */
  return ret;
}

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

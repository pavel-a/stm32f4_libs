/**
  ******************************************************************************
  * @file    USB_Host/FWupgrade_Standalone/Src/iap_menu.c
  * @author  MCD Application Team
  * @brief   COMMAND IAP Execute Application
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright � 2017 STMicroelectronics International N.V.
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice,
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other
  *    contributors to this software may be used to endorse or promote products
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under
  *    this license is void and will automatically terminate your rights under
  *    this license.
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------ */
#include "main.h"

/* Private typedef ----------------------------------------------------------- */
/* Private define ------------------------------------------------------------ */
/* State Machine for the DEMO State */
#define DEMO_INIT       ((uint8_t)0x00)
#define DEMO_IAP        ((uint8_t)0x01)

/* Private macro ------------------------------------------------------------- */
/* Private variables --------------------------------------------------------- */
__IO uint32_t UploadCondition = 0x00;
DIR dir;
FILINFO fno;
static uint8_t Demo_State = DEMO_INIT;
extern char USBDISKPath[4];

/* Private function prototypes ----------------------------------------------- */
static void IAP_UploadTimeout(void);
static void USBH_USR_BufferSizeControl(void);

/* Private functions --------------------------------------------------------- */

/**
  * @brief  Demo application for IAP through USB mass storage.
  * @param  None
  * @retval None
  */
void FW_UPGRADE_Process(void)
{
  switch (Demo_State)
  {
  case DEMO_INIT:
    /* Register the file system object to the FatFs module */
	if (FATFS_LinkDriver(&USBH_Driver, USBDISKPath) == 0)
    {
      if (f_mount(&USBH_fatfs, "", 0) != FR_OK)
      {
        /* FatFs initialization fails */
        /* Toggle LED3 and LED4 in infinite loop */
        FatFs_Fail_Handler();
      }
    }

    /* Go to IAP menu */
    Demo_State = DEMO_IAP;
    break;

  case DEMO_IAP:
    while (USBH_MSC_IsReady(&hUSBHost))
    {
      /* Control BUFFER_SIZE value */
      USBH_USR_BufferSizeControl();

      /* Keep LED1 and LED3 Off when Device connected */
      BSP_LED_Off(LED3);
      BSP_LED_Off(LED4);

      /* USER Button pressed Delay */
      IAP_UploadTimeout();

      /* Writes Flash memory */
      COMMAND_Download();

      /* Check if USER Button is already pressed */
      if ((UploadCondition == 0x01))
      {
        /* Reads all flash memory */
        COMMAND_Upload();
      }
      else
      {
        /* Turn LED4 Off: Download Done */
        BSP_LED_Off(LED4);
        /* Turn LED3 On: Waiting KEY button pressed */
        BSP_LED_On(LED3);
      }

      /* Waiting USER Button Released */
      while ((BSP_PB_GetState(BUTTON_KEY) == GPIO_PIN_RESET) &&
             (Appli_state == APPLICATION_READY))
      {
      }

      /* Waiting USER Button Pressed */
      while ((BSP_PB_GetState(BUTTON_KEY) != GPIO_PIN_RESET) &&
             (Appli_state == APPLICATION_READY))
      {
      }

      /* Waiting USER Button Released */
      while ((BSP_PB_GetState(BUTTON_KEY) == GPIO_PIN_RESET) &&
             (Appli_state == APPLICATION_READY))
      {
      }

      if (Appli_state == APPLICATION_READY)
      {
        /* Jump to user application code located in the internal Flash memory */
        COMMAND_Jump();
      }
    }
    break;

  default:
    break;
  }
  if (Appli_state == APPLICATION_DISCONNECT)
  {
    /* Toggle LED3: USB device disconnected */
    BSP_LED_Toggle(LED4);
    HAL_Delay(100);
  }
}

/**
  * @brief  Button state time control.
  * @param  None
  * @retval None
  */
static void IAP_UploadTimeout(void)
{
  /* Check if KEY button is pressed */
  if (BSP_PB_GetState(BUTTON_KEY) == GPIO_PIN_RESET)
  {
    /* To execute the UPLOAD command the KEY button should be kept pressed 3s
     * just after a board reset, at firmware startup */
    HAL_Delay(3000);

    if (BSP_PB_GetState(BUTTON_KEY) == GPIO_PIN_SET)
    {
      /* UPLOAD command will be executed immediately after completed execution
       * of the DOWNLOAD command */

      UploadCondition = 0x01;

      /* Turn LED3 and LED4 on : Upload condition Verified */
      BSP_LED_On(LED3);
      BSP_LED_On(LED4);

      /* Waiting USER Button Pressed */
      while (BSP_PB_GetState(BUTTON_KEY) == GPIO_PIN_SET)
      {
      }

    }
    else
    {
      /* Only the DOWNLOAD command is executed */
      UploadCondition = 0x00;
    }
  }
}

/**
  * @brief  Handles the program fail.
  * @param  None
  * @retval None
  */
void Fail_Handler(void)
{
  while (1)
  {
    /* Toggle LED4 */
    BSP_LED_Toggle(LED4);
    HAL_Delay(100);
  }
}

/**
  * @brief  Handles the Flash Erase fail.
  * @param  None
  * @retval None
  */
void Erase_Fail_Handler(void)
{
  while (1)
  {
    /* Toggle LED4 */
    BSP_LED_Toggle(LED4);
    HAL_Delay(100);
  }
}

/**
  * @brief  Handles the FatFs fail.
  * @param  None
  * @retval None
  */
void FatFs_Fail_Handler(void)
{
  while (1)
  {
    /* Toggle LED4 */
    BSP_LED_Toggle(LED4);
    HAL_Delay(100);
  }
}

/**
  * @brief  Controls Buffer size value.
  * @param  None
  * @retval None
  */
static void USBH_USR_BufferSizeControl(void)
{
  /* Control BUFFER_SIZE and limit this value to 32Kbyte maximum */
  if ((BUFFER_SIZE % 4 != 0x00) || (BUFFER_SIZE / 4 > 8192))
  {
    while (1)
    {
      /* Toggle LED4 */
      BSP_LED_Toggle(LED4);
      HAL_Delay(100);
    }
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

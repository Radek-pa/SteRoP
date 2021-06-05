/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file            : usb_host.c
  * @version         : v1.0_Cube
  * @brief           : This file implements the USB Host
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/

#include "usb_host.h"
#include "usbh_core.h"
#include "usbh_msc.h"
#include <stdio.h>
/* USER CODE BEGIN Includes */
#include "fatfs.h"
/* USER CODE END Includes */

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USB Host core handle declaration */
USBH_HandleTypeDef hUsbHostFS;
ApplicationTypeDef Appli_state = APPLICATION_IDLE;

/*
 * -- Insert your variables declaration here --
 */
/* USER CODE BEGIN 0 */
FATFS USBDISKFatFs;           /* File system object for USB disk logical drive */
FIL MyFile;  				/* File object */
FILE* rFILE;
char USBDISKPath[4];          /* USB Host logical drive path */
USBH_HandleTypeDef hUSB_Host; /* USB Host handle */
uint8_t wtext[] = "This is STM32 working with FatFs"; /* File write buffer */
uint8_t rtext[100];
volatile int flag_usb = 0;
/* USER CODE END 0 */

/*
 * user callback declaration
 */
static void USBH_UserProcess(USBH_HandleTypeDef *phost, uint8_t id);

/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 1 */
void USB_Error_Handler(void)
{
  /* USER CODE BEGIN USB_Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
 HAL_GPIO_WritePin(LD5_GPIO_Port,LD5_Pin,GPIO_PIN_SET);
  while(1)
  {
  }
  /* USER CODE END USB_Error_Handler */
}

void Write_usb(uint8_t* write, int size)
{
  FRESULT res;                                          /* FatFs function common result code */
  uint32_t byteswritten;                     /* File write/read counts */
  /* File read buffer */

  if (flag_usb == 1){
  /* Register the file system object to the FatFs module */
  if(f_mount(&USBDISKFatFs, (TCHAR const*)USBDISKPath, 0) != FR_OK)
  {
    /* FatFs Initialization Error */
    USB_Error_Handler();
  }
  else
  {
      /* Create and Open a new text file object with write access */
      if(f_open(&MyFile, "Even.TXT", FA_CREATE_ALWAYS | FA_WRITE) != FR_OK)
      {
        /* 'STM32.TXT' file Open for write Error */
        USB_Error_Handler();
      }
      else
      {
        /* Write data to the text file */
        res = f_write(&MyFile, write, size, (void *)&byteswritten);

        if((byteswritten == 0) || (res != FR_OK))
        {
          /* 'STM32.TXT' file Write or EOF Error */
          USB_Error_Handler();
        }
        else
        {
          /* Close the open text file */
          f_close(&MyFile);
          HAL_GPIO_WritePin(LD4_GPIO_Port,LD4_Pin,GPIO_PIN_SET);

        }
    }
  }

  /* Unlink the USB disk I/O driver */
  FATFS_UnLinkDriver(USBDISKPath);
  }
}

FILE* open_r(char* name){
	if (flag_usb == 1){
	  /* Register the file system object to the FatFs module */
	  if(f_mount(&USBDISKFatFs, (TCHAR const*)USBDISKPath, 0) != FR_OK)
	  {
	    /* FatFs Initialization Error */
	    USB_Error_Handler();
	  }
	  rFILE = fopen(name,"r");
	}
	return rFILE;
}

void Read_usb(uint8_t* read, int size)
{
  FRESULT res;                                          /* FatFs function common result code */
  uint32_t bytesread;                     /* File write/read counts */
  /* File read buffer */
if(flag_usb == 1){
  /* Register the file system object to the FatFs module */
  if(f_mount(&USBDISKFatFs, (TCHAR const*)USBDISKPath, 0) != FR_OK)
  {
    /* FatFs Initialization Error */
    USB_Error_Handler();
  }
  else
  {
  /* Open the text file object with read access */
	  if(f_open(&MyFile, "Even.TXT", FA_READ) != FR_OK)
      {
         /* 'STM32.TXT' file Open for read Error */
           USB_Error_Handler();
      }
      else
      {
           /* Read data from the text  file */
    	  res = f_read(&MyFile, read, size, (void *)&bytesread);

    	  if((bytesread == 0) || (res != FR_OK))
    	  {
             /* 'STM32.TXT' file Read or EOF Error */
             USB_Error_Handler();
    	  }
    	  else
    	  {
    		  /* Close the open text file */
    		  f_close(&MyFile);
    		  /* Success of the demo: no error occurrence */
    		  //BSP_LED_On(LED4);
    		  HAL_GPIO_WritePin(LD4_GPIO_Port,LD4_Pin,GPIO_PIN_SET);
    	  }
      }
  }
  FATFS_UnLinkDriver(USBDISKPath);
}
}
/* USER CODE END 1 */

/**
  * Init USB host library, add supported class and start the library
  * @retval None
  */
void MX_USB_HOST_Init(void)
{
  /* USER CODE BEGIN USB_HOST_Init_PreTreatment */

  /* USER CODE END USB_HOST_Init_PreTreatment */

  /* Init host Library, add supported class and start the library. */
  if (USBH_Init(&hUsbHostFS, USBH_UserProcess, HOST_FS) != USBH_OK)
  {
    Error_Handler();
  }
  if (USBH_RegisterClass(&hUsbHostFS, USBH_MSC_CLASS) != USBH_OK)
  {
    Error_Handler();
  }
  if (USBH_Start(&hUsbHostFS) != USBH_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_HOST_Init_PostTreatment */

  /* USER CODE END USB_HOST_Init_PostTreatment */
}

/*
 * Background task
 */
void MX_USB_HOST_Process(void)
{
  /* USB Host Background task */
  USBH_Process(&hUsbHostFS);
}
/*
 * user callback definition
 */
static void USBH_UserProcess  (USBH_HandleTypeDef *phost, uint8_t id)
{
  /* USER CODE BEGIN CALL_BACK_1 */
  switch(id)
  {
  case HOST_USER_SELECT_CONFIGURATION:
  break;

  case HOST_USER_DISCONNECTION:
  Appli_state = APPLICATION_DISCONNECT;
  break;

  case HOST_USER_CLASS_ACTIVE:
  Appli_state = APPLICATION_READY;
  flag_usb = 1;
  break;

  case HOST_USER_CONNECTION:
  Appli_state = APPLICATION_START;
  break;

  default:
  break;
  }
  /* USER CODE END CALL_BACK_1 */
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

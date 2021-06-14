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
//uint8_t ltext[] = "This is STM32 working with FatFs"; /* File write buffer */
//uint8_t rtext[100];
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

int open_to_write(char* name){
	if (flag_usb == 1){
		if(f_mount(&USBDISKFatFs, (TCHAR const*)USBDISKPath, 0) != FR_OK)
		{
			/* FatFs Initialization Error */
			USB_Error_Handler();
		}
		else
		{
			/* Create and Open a new text file object with write access */
			if(f_open(&MyFile, name, FA_CREATE_ALWAYS | FA_WRITE) != FR_OK)
			{
				/* 'STM32.TXT' file Open for write Error */
				USB_Error_Handler();
			}
			else
			{
				return 1;
			}
		}
	}
	return 0;
}


int open_to_read(){
	if (flag_usb == 1){
		if(f_mount(&USBDISKFatFs, (TCHAR const*)USBDISKPath, 0) != FR_OK)
		{
			/* FatFs Initialization Error */
			USB_Error_Handler();
		}
		else
		{
			/* Create and Open a new text file object with write access */
			if(f_open(&MyFile, "Nag.wav", FA_READ) != FR_OK)
			{
				/* 'STM32.TXT' file Open for write Error */
				USB_Error_Handler();
			}
			else
			{
				return 1;
			}
		}
	}
	return 0;
}


void Read_with_open(uint8_t* read, int size){
	FRESULT res;                                          /* FatFs function common result code */
	uint32_t bytesread;                     /* File */
	res = f_read(&MyFile, read, size, (void *)&bytesread);

	if((bytesread == 0) || (res != FR_OK))
	{
		/* 'STM32.TXT' file Read or EOF Error */
		USB_Error_Handler();
	}
}

void Write_with_open(uint8_t* write, int size){
	FRESULT res;                                          /* FatFs function common result code */
	uint32_t byteswritten;

	/* Write data to the text file */
	res = f_write(&MyFile, write, size, (void *)&byteswritten);

	if((byteswritten == 0) || (res != FR_OK))
	{
		/* 'STM32.TXT' file Write or EOF Error */
		USB_Error_Handler();
	}

}

void Close_usb(){
	f_close(&MyFile);
	FATFS_UnLinkDriver(USBDISKPath);
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

void Write_the_header(){
	FRESULT res;                                          /* FatFs function common result code */
	uint32_t byteswritten;
	uint8_t pHeader[44];

	/* write chunkID, must be 'RIFF'  ------------------------------------------*/
	pHeader[0] = 'R';
	pHeader[1] = 'I';
	pHeader[2] = 'F';
	pHeader[3] = 'F';

	/* Write the file length ----------------------------------------------------*/
	/* The sampling time: thiue will bes val be written back at the end of the
	   recording opearation.  Example: 661500 Btyes = 0x000A17FC, byte[7]=0x00, byte[4]=0xFC */
	pHeader[4] = 0x8A;
	pHeader[5] = 0x02;
	pHeader[6] = 0x01;
	pHeader[7] = 0x00;
	/* Write the file format, must be 'WAVE' -----------------------------------*/
	pHeader[8]  = 'W';
	pHeader[9]  = 'A';
	pHeader[10] = 'V';
	pHeader[11] = 'E';

	/* Write the format chunk, must be'fmt ' -----------------------------------*/
	pHeader[12]  = 'f';
	pHeader[13]  = 'm';
	pHeader[14]  = 't';
	pHeader[15]  = ' ';

	/* Write the length of the 'fmt' data, must be 0x10 ------------------------*/
	pHeader[16]  = 0x10;
	pHeader[17]  = 0x00;
	pHeader[18]  = 0x00;
	pHeader[19]  = 0x00;

	/* Write the audio format, must be 0x01 (PCM) ------------------------------*/
	pHeader[20]  = 0x01;
	pHeader[21]  = 0x00;

	/* Write the number of channels, ie. 0x01 (Mono) ---------------------------*/
	pHeader[22]  = 0x01;
	pHeader[23]  = 0x00;

	/* Write the Sample Rate in Hz ---------------------------------------------*/
	/* Write Little Endian ie. 8000 = 0x00001F40 => byte[24]=0x40, byte[27]=0x00*/
	pHeader[24]  = 0x80;
	pHeader[25]  = 0x3E;
	pHeader[26]  = 0x00;
	pHeader[27]  = 0x00;

	/* Write the Byte Rate -----------------------------------------------------*/
	pHeader[28]  = 0x22;
	pHeader[29]  = 0x56;
	pHeader[30]  = 0x00;
	pHeader[31]  = 0x00;

	/* Write the block alignment -----------------------------------------------*/
	pHeader[32]  = 0x01;
	pHeader[33]  = 0x00;

	/* Write the number of bits per sample -------------------------------------*/
	pHeader[34]  = 0x08;
	pHeader[35]  = 0x00;

	/* Write the Data chunk, must be 'data' ------------------------------------*/
	pHeader[36]  = 'd';
	pHeader[37]  = 'a';
	pHeader[38]  = 't';
	pHeader[39]  = 'a';

	/* Write the number of sample data -----------------------------------------*/
	/* This variable will be written back at the end of the recording operation */
	pHeader[40]  = 0x66;
	pHeader[41]  = 0x02;
	pHeader[42]  = 0x01;
	pHeader[43]  = 0x00;

	/* Write data to the text file */
	res = f_write(&MyFile, pHeader, 44, (void *)&byteswritten);

	if((byteswritten == 0) || (res != FR_OK))
	{
		/* 'STM32.TXT' file Write or EOF Error */
		USB_Error_Handler();
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

FILE* open_w(char* name){
	FILE* wFILE;
	if (flag_usb == 1){
	  /* Register the file system object to the FatFs module */

	if(f_mount(&USBDISKFatFs, (TCHAR const*)USBDISKPath, 0) != FR_OK)
	  {

	    /* FatFs Initialization Error */

		USB_Error_Handler();
	  }

	  wFILE = fopen(name,"r");
	  if(wFILE == NULL){
		  HAL_GPIO_WritePin(LD4_GPIO_Port,LD4_Pin,GPIO_PIN_SET);
	  }
	}
	return wFILE;
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

int usb_ready(){
	if(flag_usb == 1){
		return 1;
	}
	return 0;
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

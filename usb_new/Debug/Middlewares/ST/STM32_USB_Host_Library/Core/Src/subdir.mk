################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_core.c \
../Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.c \
../Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ioreq.c \
../Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_pipes.c 

C_DEPS += \
./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_core.d \
./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.d \
./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ioreq.d \
./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_pipes.d 

OBJS += \
./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_core.o \
./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.o \
./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ioreq.o \
./Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_pipes.o 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_core.o: ../Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_core.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DDEBUG -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I"C:/Users/rprch/STM32Cube/Repository/STM32Cube_FW_F4_V1.25.2/Middlewares/ST/STM32_Audio/Addons/PDM/Inc" -I"C:/Users/rprch/STM32Cube/Repository/STM32Cube_FW_F4_V1.25.2/Drivers/BSP/STM32F411E-Discovery" -I"C:/Users/rprch/STM32CubeIDE/SteRoP/Spectogram/Inc" -I"C:/Users/rprch/STM32CubeIDE/SteRoP/Simple-FFT-master/include/simple_fft" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_core.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.o: ../Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DDEBUG -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I"C:/Users/rprch/STM32Cube/Repository/STM32Cube_FW_F4_V1.25.2/Middlewares/ST/STM32_Audio/Addons/PDM/Inc" -I"C:/Users/rprch/STM32Cube/Repository/STM32Cube_FW_F4_V1.25.2/Drivers/BSP/STM32F411E-Discovery" -I"C:/Users/rprch/STM32CubeIDE/SteRoP/Spectogram/Inc" -I"C:/Users/rprch/STM32CubeIDE/SteRoP/Simple-FFT-master/include/simple_fft" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ioreq.o: ../Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ioreq.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DDEBUG -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I"C:/Users/rprch/STM32Cube/Repository/STM32Cube_FW_F4_V1.25.2/Middlewares/ST/STM32_Audio/Addons/PDM/Inc" -I"C:/Users/rprch/STM32Cube/Repository/STM32Cube_FW_F4_V1.25.2/Drivers/BSP/STM32F411E-Discovery" -I"C:/Users/rprch/STM32CubeIDE/SteRoP/Spectogram/Inc" -I"C:/Users/rprch/STM32CubeIDE/SteRoP/Simple-FFT-master/include/simple_fft" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ioreq.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_pipes.o: ../Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_pipes.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DDEBUG -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I"C:/Users/rprch/STM32Cube/Repository/STM32Cube_FW_F4_V1.25.2/Middlewares/ST/STM32_Audio/Addons/PDM/Inc" -I"C:/Users/rprch/STM32Cube/Repository/STM32Cube_FW_F4_V1.25.2/Drivers/BSP/STM32F411E-Discovery" -I"C:/Users/rprch/STM32CubeIDE/SteRoP/Spectogram/Inc" -I"C:/Users/rprch/STM32CubeIDE/SteRoP/Simple-FFT-master/include/simple_fft" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_pipes.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"


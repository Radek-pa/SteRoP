################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Spectogram/Src/spectogram.cpp 

OBJS += \
./Spectogram/Src/spectogram.o 

CPP_DEPS += \
./Spectogram/Src/spectogram.d 


# Each subdirectory must supply rules for building sources it contributes
Spectogram/Src/spectogram.o: ../Spectogram/Src/spectogram.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DDEBUG -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I"C:/Users/rprch/STM32Cube/Repository/STM32Cube_FW_F4_V1.25.2/Middlewares/ST/STM32_Audio/Addons/PDM/Inc" -I"C:/Users/rprch/STM32Cube/Repository/STM32Cube_FW_F4_V1.25.2/Drivers/BSP/STM32F411E-Discovery" -I"C:/Users/rprch/STM32CubeIDE/SteRoP/Spectogram/Inc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Spectogram/Src/spectogram.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"


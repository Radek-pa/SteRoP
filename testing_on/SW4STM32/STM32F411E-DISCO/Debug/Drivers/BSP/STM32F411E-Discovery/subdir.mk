################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/rprch/STM32Cube/Repository/STM32Cube_FW_F4_V1.25.2/Drivers/BSP/STM32F411E-Discovery/stm32f411e_discovery.c \
C:/Users/rprch/STM32Cube/Repository/STM32Cube_FW_F4_V1.25.2/Drivers/BSP/STM32F411E-Discovery/stm32f411e_discovery_accelerometer.c \
C:/Users/rprch/STM32Cube/Repository/STM32Cube_FW_F4_V1.25.2/Drivers/BSP/STM32F411E-Discovery/stm32f411e_discovery_audio.c 

OBJS += \
./Drivers/BSP/STM32F411E-Discovery/stm32f411e_discovery.o \
./Drivers/BSP/STM32F411E-Discovery/stm32f411e_discovery_accelerometer.o \
./Drivers/BSP/STM32F411E-Discovery/stm32f411e_discovery_audio.o 

C_DEPS += \
./Drivers/BSP/STM32F411E-Discovery/stm32f411e_discovery.d \
./Drivers/BSP/STM32F411E-Discovery/stm32f411e_discovery_accelerometer.d \
./Drivers/BSP/STM32F411E-Discovery/stm32f411e_discovery_audio.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32F411E-Discovery/stm32f411e_discovery.o: C:/Users/rprch/STM32Cube/Repository/STM32Cube_FW_F4_V1.25.2/Drivers/BSP/STM32F411E-Discovery/stm32f411e_discovery.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DUSE_STM32F411E_DISCO -c -I../../../Inc -I../../../../../../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../../../../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../../../../../../Drivers/BSP/STM32F411E-Discovery -I../../../../../../../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../../../../../../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../../../../../../../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../../../../../../../../Middlewares/ST/STM32_Audio/Addons/PDM/Inc -I../../../../../../../../Middlewares/Third_Party/FatFs/src -I../../../../../../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP/STM32F411E-Discovery/stm32f411e_discovery.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM32F411E-Discovery/stm32f411e_discovery_accelerometer.o: C:/Users/rprch/STM32Cube/Repository/STM32Cube_FW_F4_V1.25.2/Drivers/BSP/STM32F411E-Discovery/stm32f411e_discovery_accelerometer.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DUSE_STM32F411E_DISCO -c -I../../../Inc -I../../../../../../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../../../../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../../../../../../Drivers/BSP/STM32F411E-Discovery -I../../../../../../../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../../../../../../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../../../../../../../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../../../../../../../../Middlewares/ST/STM32_Audio/Addons/PDM/Inc -I../../../../../../../../Middlewares/Third_Party/FatFs/src -I../../../../../../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP/STM32F411E-Discovery/stm32f411e_discovery_accelerometer.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM32F411E-Discovery/stm32f411e_discovery_audio.o: C:/Users/rprch/STM32Cube/Repository/STM32Cube_FW_F4_V1.25.2/Drivers/BSP/STM32F411E-Discovery/stm32f411e_discovery_audio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F411xE -DUSE_STM32F411E_DISCO -c -I../../../Inc -I../../../../../../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../../../../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../../../../../../Drivers/BSP/STM32F411E-Discovery -I../../../../../../../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../../../../../../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../../../../../../../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../../../../../../../../Middlewares/ST/STM32_Audio/Addons/PDM/Inc -I../../../../../../../../Middlewares/Third_Party/FatFs/src -I../../../../../../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP/STM32F411E-Discovery/stm32f411e_discovery_audio.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"


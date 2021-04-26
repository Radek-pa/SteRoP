################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
C:/Users/rprch/STM32Cube/Repository/STM32Cube_FW_F4_V1.25.2/Projects/STM32F411E-Discovery/Applications/Audio/Audio_playback_and_record/SW4STM32/startup_stm32f411xe.s 

OBJS += \
./Application/SW4STM32/startup_stm32f411xe.o 

S_DEPS += \
./Application/SW4STM32/startup_stm32f411xe.d 


# Each subdirectory must supply rules for building sources it contributes
Application/SW4STM32/startup_stm32f411xe.o: C:/Users/rprch/STM32Cube/Repository/STM32Cube_FW_F4_V1.25.2/Projects/STM32F411E-Discovery/Applications/Audio/Audio_playback_and_record/SW4STM32/startup_stm32f411xe.s
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -x assembler-with-cpp -MMD -MP -MF"Application/SW4STM32/startup_stm32f411xe.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"


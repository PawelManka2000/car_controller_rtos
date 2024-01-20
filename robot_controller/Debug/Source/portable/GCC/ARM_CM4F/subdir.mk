################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/portable/GCC/ARM_CM4F/port.c 

OBJS += \
./Source/portable/GCC/ARM_CM4F/port.o 

C_DEPS += \
./Source/portable/GCC/ARM_CM4F/port.d 


# Each subdirectory must supply rules for building sources it contributes
Source/portable/GCC/ARM_CM4F/%.o Source/portable/GCC/ARM_CM4F/%.su: ../Source/portable/GCC/ARM_CM4F/%.c Source/portable/GCC/ARM_CM4F/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I"C:/Users/Admin/STM32CubeIDE/robot_ws1/robot_controller/Source/include" -I"C:/Users/Admin/STM32CubeIDE/robot_ws1/robot_controller/Source/portable/GCC/ARM_CM4F" -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Source-2f-portable-2f-GCC-2f-ARM_CM4F

clean-Source-2f-portable-2f-GCC-2f-ARM_CM4F:
	-$(RM) ./Source/portable/GCC/ARM_CM4F/port.d ./Source/portable/GCC/ARM_CM4F/port.o ./Source/portable/GCC/ARM_CM4F/port.su

.PHONY: clean-Source-2f-portable-2f-GCC-2f-ARM_CM4F


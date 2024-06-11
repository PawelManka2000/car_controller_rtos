################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Features/motor_features.c \
../Core/Src/Features/parser_features.c \
../Core/Src/Features/timers_features.c 

OBJS += \
./Core/Src/Features/motor_features.o \
./Core/Src/Features/parser_features.o \
./Core/Src/Features/timers_features.o 

C_DEPS += \
./Core/Src/Features/motor_features.d \
./Core/Src/Features/parser_features.d \
./Core/Src/Features/timers_features.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Features/%.o Core/Src/Features/%.su Core/Src/Features/%.cyclo: ../Core/Src/Features/%.c Core/Src/Features/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I"C:/Users/Admin/STM32CubeIDE/robot_new_ws/car_controller_rtos/robot_controller/Core/Inc/Drivers" -I"C:/Users/Admin/STM32CubeIDE/robot_new_ws/car_controller_rtos/robot_controller/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Users/Admin/STM32CubeIDE/robot_new_ws/car_controller_rtos/robot_controller/FreeRTOS/Source/include" -I"C:/Users/Admin/STM32CubeIDE/robot_ws1/robot_controller/FreeRTOS/Source/include" -I"C:/Users/Admin/STM32CubeIDE/robot_ws1/robot_controller/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Admin/STM32CubeIDE/robot_new_ws/car_controller_rtos/robot_controller/Core/Inc/Features" -I"C:/Users/Admin/STM32CubeIDE/robot_new_ws/car_controller_rtos/robot_controller/Core/Inc/Configuration" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Features

clean-Core-2f-Src-2f-Features:
	-$(RM) ./Core/Src/Features/motor_features.cyclo ./Core/Src/Features/motor_features.d ./Core/Src/Features/motor_features.o ./Core/Src/Features/motor_features.su ./Core/Src/Features/parser_features.cyclo ./Core/Src/Features/parser_features.d ./Core/Src/Features/parser_features.o ./Core/Src/Features/parser_features.su ./Core/Src/Features/timers_features.cyclo ./Core/Src/Features/timers_features.d ./Core/Src/Features/timers_features.o ./Core/Src/Features/timers_features.su

.PHONY: clean-Core-2f-Src-2f-Features


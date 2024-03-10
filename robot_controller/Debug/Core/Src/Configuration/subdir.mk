################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Configuration/clock_configuration.c \
../Core/Src/Configuration/gpio_configuration.c \
../Core/Src/Configuration/timers_configuration.c \
../Core/Src/Configuration/uart_configuration.c 

OBJS += \
./Core/Src/Configuration/clock_configuration.o \
./Core/Src/Configuration/gpio_configuration.o \
./Core/Src/Configuration/timers_configuration.o \
./Core/Src/Configuration/uart_configuration.o 

C_DEPS += \
./Core/Src/Configuration/clock_configuration.d \
./Core/Src/Configuration/gpio_configuration.d \
./Core/Src/Configuration/timers_configuration.d \
./Core/Src/Configuration/uart_configuration.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Configuration/%.o Core/Src/Configuration/%.su Core/Src/Configuration/%.cyclo: ../Core/Src/Configuration/%.c Core/Src/Configuration/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I"C:/Users/pawel/Documents/projects/stm_workspace/ws1/car_controller_rtos/robot_controller/Core/Inc/Drivers" -I"C:/Users/pawel/Documents/projects/stm_workspace/ws1/car_controller_rtos/robot_controller/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Users/pawel/Documents/projects/stm_workspace/ws1/car_controller_rtos/robot_controller/FreeRTOS/Source/include" -I"C:/Users/Admin/STM32CubeIDE/robot_ws1/robot_controller/FreeRTOS/Source/include" -I"C:/Users/Admin/STM32CubeIDE/robot_ws1/robot_controller/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/pawel/Documents/projects/stm_workspace/ws1/car_controller_rtos/robot_controller/Core/Inc/Features" -I"C:/Users/pawel/Documents/projects/stm_workspace/ws1/car_controller_rtos/robot_controller/Core/Inc/Configuration" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Configuration

clean-Core-2f-Src-2f-Configuration:
	-$(RM) ./Core/Src/Configuration/clock_configuration.cyclo ./Core/Src/Configuration/clock_configuration.d ./Core/Src/Configuration/clock_configuration.o ./Core/Src/Configuration/clock_configuration.su ./Core/Src/Configuration/gpio_configuration.cyclo ./Core/Src/Configuration/gpio_configuration.d ./Core/Src/Configuration/gpio_configuration.o ./Core/Src/Configuration/gpio_configuration.su ./Core/Src/Configuration/timers_configuration.cyclo ./Core/Src/Configuration/timers_configuration.d ./Core/Src/Configuration/timers_configuration.o ./Core/Src/Configuration/timers_configuration.su ./Core/Src/Configuration/uart_configuration.cyclo ./Core/Src/Configuration/uart_configuration.d ./Core/Src/Configuration/uart_configuration.o ./Core/Src/Configuration/uart_configuration.su

.PHONY: clean-Core-2f-Src-2f-Configuration


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Drivers/clock_configuration.c \
../Core/Src/Drivers/encoder_driver.c \
../Core/Src/Drivers/engine_driver.c \
../Core/Src/Drivers/gpio_configuration.c \
../Core/Src/Drivers/timer_configuration.c \
../Core/Src/Drivers/uart_configuration.c 

OBJS += \
./Core/Src/Drivers/clock_configuration.o \
./Core/Src/Drivers/encoder_driver.o \
./Core/Src/Drivers/engine_driver.o \
./Core/Src/Drivers/gpio_configuration.o \
./Core/Src/Drivers/timer_configuration.o \
./Core/Src/Drivers/uart_configuration.o 

C_DEPS += \
./Core/Src/Drivers/clock_configuration.d \
./Core/Src/Drivers/encoder_driver.d \
./Core/Src/Drivers/engine_driver.d \
./Core/Src/Drivers/gpio_configuration.d \
./Core/Src/Drivers/timer_configuration.d \
./Core/Src/Drivers/uart_configuration.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Drivers/%.o Core/Src/Drivers/%.su Core/Src/Drivers/%.cyclo: ../Core/Src/Drivers/%.c Core/Src/Drivers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I"C:/Users/pawel/Documents/projects/stm_workspace/ws1/car_controller_rtos/robot_controller/Core/Inc/Drivers" -I"C:/Users/pawel/Documents/projects/stm_workspace/ws1/car_controller_rtos/robot_controller/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Users/pawel/Documents/projects/stm_workspace/ws1/car_controller_rtos/robot_controller/FreeRTOS/Source/include" -I"C:/Users/Admin/STM32CubeIDE/robot_ws1/robot_controller/FreeRTOS/Source/include" -I"C:/Users/Admin/STM32CubeIDE/robot_ws1/robot_controller/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Drivers

clean-Core-2f-Src-2f-Drivers:
	-$(RM) ./Core/Src/Drivers/clock_configuration.cyclo ./Core/Src/Drivers/clock_configuration.d ./Core/Src/Drivers/clock_configuration.o ./Core/Src/Drivers/clock_configuration.su ./Core/Src/Drivers/encoder_driver.cyclo ./Core/Src/Drivers/encoder_driver.d ./Core/Src/Drivers/encoder_driver.o ./Core/Src/Drivers/encoder_driver.su ./Core/Src/Drivers/engine_driver.cyclo ./Core/Src/Drivers/engine_driver.d ./Core/Src/Drivers/engine_driver.o ./Core/Src/Drivers/engine_driver.su ./Core/Src/Drivers/gpio_configuration.cyclo ./Core/Src/Drivers/gpio_configuration.d ./Core/Src/Drivers/gpio_configuration.o ./Core/Src/Drivers/gpio_configuration.su ./Core/Src/Drivers/timer_configuration.cyclo ./Core/Src/Drivers/timer_configuration.d ./Core/Src/Drivers/timer_configuration.o ./Core/Src/Drivers/timer_configuration.su ./Core/Src/Drivers/uart_configuration.cyclo ./Core/Src/Drivers/uart_configuration.d ./Core/Src/Drivers/uart_configuration.o ./Core/Src/Drivers/uart_configuration.su

.PHONY: clean-Core-2f-Src-2f-Drivers


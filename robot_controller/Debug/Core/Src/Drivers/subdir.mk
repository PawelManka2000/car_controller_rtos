################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Drivers/L298N_driver.c \
../Core/Src/Drivers/cmd_listener.c \
../Core/Src/Drivers/driving_system.c \
../Core/Src/Drivers/encoder_driver.c \
../Core/Src/Drivers/motor_driver.c \
../Core/Src/Drivers/pid_controller.c 

OBJS += \
./Core/Src/Drivers/L298N_driver.o \
./Core/Src/Drivers/cmd_listener.o \
./Core/Src/Drivers/driving_system.o \
./Core/Src/Drivers/encoder_driver.o \
./Core/Src/Drivers/motor_driver.o \
./Core/Src/Drivers/pid_controller.o 

C_DEPS += \
./Core/Src/Drivers/L298N_driver.d \
./Core/Src/Drivers/cmd_listener.d \
./Core/Src/Drivers/driving_system.d \
./Core/Src/Drivers/encoder_driver.d \
./Core/Src/Drivers/motor_driver.d \
./Core/Src/Drivers/pid_controller.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Drivers/%.o Core/Src/Drivers/%.su Core/Src/Drivers/%.cyclo: ../Core/Src/Drivers/%.c Core/Src/Drivers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I"C:/Users/Admin/STM32CubeIDE/robot_ws1/robot_controller/Core/Inc/Drivers" -I"C:/Users/Admin/STM32CubeIDE/robot_ws1/robot_controller/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Users/Admin/STM32CubeIDE/robot_ws1/robot_controller/FreeRTOS/Source/include" -I"C:/Users/Admin/STM32CubeIDE/robot_ws1/robot_controller/FreeRTOS/Source/include" -I"C:/Users/Admin/STM32CubeIDE/robot_ws1/robot_controller/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Admin/STM32CubeIDE/robot_ws1/robot_controller/Core/Inc/Features" -I"C:/Users/Admin/STM32CubeIDE/robot_ws1/robot_controller/Core/Inc/Configuration" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Drivers

clean-Core-2f-Src-2f-Drivers:
	-$(RM) ./Core/Src/Drivers/L298N_driver.cyclo ./Core/Src/Drivers/L298N_driver.d ./Core/Src/Drivers/L298N_driver.o ./Core/Src/Drivers/L298N_driver.su ./Core/Src/Drivers/cmd_listener.cyclo ./Core/Src/Drivers/cmd_listener.d ./Core/Src/Drivers/cmd_listener.o ./Core/Src/Drivers/cmd_listener.su ./Core/Src/Drivers/driving_system.cyclo ./Core/Src/Drivers/driving_system.d ./Core/Src/Drivers/driving_system.o ./Core/Src/Drivers/driving_system.su ./Core/Src/Drivers/encoder_driver.cyclo ./Core/Src/Drivers/encoder_driver.d ./Core/Src/Drivers/encoder_driver.o ./Core/Src/Drivers/encoder_driver.su ./Core/Src/Drivers/motor_driver.cyclo ./Core/Src/Drivers/motor_driver.d ./Core/Src/Drivers/motor_driver.o ./Core/Src/Drivers/motor_driver.su ./Core/Src/Drivers/pid_controller.cyclo ./Core/Src/Drivers/pid_controller.d ./Core/Src/Drivers/pid_controller.o ./Core/Src/Drivers/pid_controller.su

.PHONY: clean-Core-2f-Src-2f-Drivers


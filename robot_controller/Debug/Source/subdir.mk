################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/croutine.c \
../Source/event_groups.c \
../Source/list.c \
../Source/queue.c \
../Source/stream_buffer.c \
../Source/tasks.c \
../Source/timers.c 

OBJS += \
./Source/croutine.o \
./Source/event_groups.o \
./Source/list.o \
./Source/queue.o \
./Source/stream_buffer.o \
./Source/tasks.o \
./Source/timers.o 

C_DEPS += \
./Source/croutine.d \
./Source/event_groups.d \
./Source/list.d \
./Source/queue.d \
./Source/stream_buffer.d \
./Source/tasks.d \
./Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Source/%.o Source/%.su: ../Source/%.c Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I"C:/Users/Admin/STM32CubeIDE/robot_ws1/robot_controller/Source/include" -I"C:/Users/Admin/STM32CubeIDE/robot_ws1/robot_controller/Source/portable/GCC/ARM_CM4F" -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Source

clean-Source:
	-$(RM) ./Source/croutine.d ./Source/croutine.o ./Source/croutine.su ./Source/event_groups.d ./Source/event_groups.o ./Source/event_groups.su ./Source/list.d ./Source/list.o ./Source/list.su ./Source/queue.d ./Source/queue.o ./Source/queue.su ./Source/stream_buffer.d ./Source/stream_buffer.o ./Source/stream_buffer.su ./Source/tasks.d ./Source/tasks.o ./Source/tasks.su ./Source/timers.d ./Source/timers.o ./Source/timers.su

.PHONY: clean-Source


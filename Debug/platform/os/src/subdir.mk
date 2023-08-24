################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../platform/os/src/croutine.c \
../platform/os/src/event_groups.c \
../platform/os/src/list.c \
../platform/os/src/queue.c \
../platform/os/src/stream_buffer.c \
../platform/os/src/tasks.c \
../platform/os/src/timers.c 

C_DEPS += \
./platform/os/src/croutine.d \
./platform/os/src/event_groups.d \
./platform/os/src/list.d \
./platform/os/src/queue.d \
./platform/os/src/stream_buffer.d \
./platform/os/src/tasks.d \
./platform/os/src/timers.d 

OBJS += \
./platform/os/src/croutine.o \
./platform/os/src/event_groups.o \
./platform/os/src/list.o \
./platform/os/src/queue.o \
./platform/os/src/stream_buffer.o \
./platform/os/src/tasks.o \
./platform/os/src/timers.o 


# Each subdirectory must supply rules for building sources it contributes
platform/os/src/%.o platform/os/src/%.su platform/os/src/%.cyclo: ../platform/os/src/%.c platform/os/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/bsp/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/os/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/osSupport/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/framework/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/os/src/portable/GCC/ARM_CM4F" -I../Drivers/Ethernet/W5500 -I../Drivers/Internet/httpServer -I../Drivers/Ethernet -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Middlewares/Third_Party/LwIP/src/include/ipv4 -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/posix -I../Middlewares/Third_Party/LwIP/src/include/posix/sys -I../Middlewares/Third_Party/LwIP/system/arch -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../template -I../Core/Startup -I../Drivers/Application/loopback -I../Drivers/Internet -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-platform-2f-os-2f-src

clean-platform-2f-os-2f-src:
	-$(RM) ./platform/os/src/croutine.cyclo ./platform/os/src/croutine.d ./platform/os/src/croutine.o ./platform/os/src/croutine.su ./platform/os/src/event_groups.cyclo ./platform/os/src/event_groups.d ./platform/os/src/event_groups.o ./platform/os/src/event_groups.su ./platform/os/src/list.cyclo ./platform/os/src/list.d ./platform/os/src/list.o ./platform/os/src/list.su ./platform/os/src/queue.cyclo ./platform/os/src/queue.d ./platform/os/src/queue.o ./platform/os/src/queue.su ./platform/os/src/stream_buffer.cyclo ./platform/os/src/stream_buffer.d ./platform/os/src/stream_buffer.o ./platform/os/src/stream_buffer.su ./platform/os/src/tasks.cyclo ./platform/os/src/tasks.d ./platform/os/src/tasks.o ./platform/os/src/tasks.su ./platform/os/src/timers.cyclo ./platform/os/src/timers.d ./platform/os/src/timers.o ./platform/os/src/timers.su

.PHONY: clean-platform-2f-os-2f-src


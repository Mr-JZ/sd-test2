################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../platform/os/src/portable/GCC/ARM_CM4F/port.c \
../platform/os/src/portable/GCC/ARM_CM4F/runTimeStats.c 

C_DEPS += \
./platform/os/src/portable/GCC/ARM_CM4F/port.d \
./platform/os/src/portable/GCC/ARM_CM4F/runTimeStats.d 

OBJS += \
./platform/os/src/portable/GCC/ARM_CM4F/port.o \
./platform/os/src/portable/GCC/ARM_CM4F/runTimeStats.o 


# Each subdirectory must supply rules for building sources it contributes
platform/os/src/portable/GCC/ARM_CM4F/%.o platform/os/src/portable/GCC/ARM_CM4F/%.su platform/os/src/portable/GCC/ARM_CM4F/%.cyclo: ../platform/os/src/portable/GCC/ARM_CM4F/%.c platform/os/src/portable/GCC/ARM_CM4F/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/bsp/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/os/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/osSupport/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/framework/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/os/src/portable/GCC/ARM_CM4F" -I../Drivers/Ethernet/W5500 -I../Drivers/Internet/httpServer -I../Drivers/Ethernet -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Middlewares/Third_Party/LwIP/src/include/ipv4 -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/posix -I../Middlewares/Third_Party/LwIP/src/include/posix/sys -I../Middlewares/Third_Party/LwIP/system/arch -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../template -I../Core/Startup -I../Drivers/Application/loopback -I../Drivers/Internet -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-platform-2f-os-2f-src-2f-portable-2f-GCC-2f-ARM_CM4F

clean-platform-2f-os-2f-src-2f-portable-2f-GCC-2f-ARM_CM4F:
	-$(RM) ./platform/os/src/portable/GCC/ARM_CM4F/port.cyclo ./platform/os/src/portable/GCC/ARM_CM4F/port.d ./platform/os/src/portable/GCC/ARM_CM4F/port.o ./platform/os/src/portable/GCC/ARM_CM4F/port.su ./platform/os/src/portable/GCC/ARM_CM4F/runTimeStats.cyclo ./platform/os/src/portable/GCC/ARM_CM4F/runTimeStats.d ./platform/os/src/portable/GCC/ARM_CM4F/runTimeStats.o ./platform/os/src/portable/GCC/ARM_CM4F/runTimeStats.su

.PHONY: clean-platform-2f-os-2f-src-2f-portable-2f-GCC-2f-ARM_CM4F


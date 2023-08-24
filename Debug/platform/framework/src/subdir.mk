################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../platform/framework/src/sbrk.c 

CPP_SRCS += \
../platform/framework/src/TermColor.cpp \
../platform/framework/src/crc32.cpp \
../platform/framework/src/crc32slow.cpp \
../platform/framework/src/systeminfo.cpp 

C_DEPS += \
./platform/framework/src/sbrk.d 

OBJS += \
./platform/framework/src/TermColor.o \
./platform/framework/src/crc32.o \
./platform/framework/src/crc32slow.o \
./platform/framework/src/sbrk.o \
./platform/framework/src/systeminfo.o 

CPP_DEPS += \
./platform/framework/src/TermColor.d \
./platform/framework/src/crc32.d \
./platform/framework/src/crc32slow.d \
./platform/framework/src/systeminfo.d 


# Each subdirectory must supply rules for building sources it contributes
platform/framework/src/%.o platform/framework/src/%.su platform/framework/src/%.cyclo: ../platform/framework/src/%.cpp platform/framework/src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++17 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/bsp/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/os/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/osSupport/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/framework/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/os/src/portable/GCC/ARM_CM4F" -I../Drivers/Ethernet/W5500 -I../Drivers/Ethernet -I../Drivers/Internet -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/ipv4 -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/posix -I../Middlewares/Third_Party/LwIP/src/include/posix/sys -I../Middlewares/Third_Party/LwIP/system/arch -I../Middlewares/Third_Party/LwIP/src/core -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../template -I../Drivers/Internet/httpServer -I../Drivers/Application/loopback -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
platform/framework/src/%.o platform/framework/src/%.su platform/framework/src/%.cyclo: ../platform/framework/src/%.c platform/framework/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/bsp/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/os/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/osSupport/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/framework/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/os/src/portable/GCC/ARM_CM4F" -I../Drivers/Ethernet/W5500 -I../Drivers/Internet/httpServer -I../Drivers/Ethernet -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Middlewares/Third_Party/LwIP/src/include/ipv4 -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/posix -I../Middlewares/Third_Party/LwIP/src/include/posix/sys -I../Middlewares/Third_Party/LwIP/system/arch -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../template -I../Core/Startup -I../Drivers/Application/loopback -I../Drivers/Internet -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-platform-2f-framework-2f-src

clean-platform-2f-framework-2f-src:
	-$(RM) ./platform/framework/src/TermColor.cyclo ./platform/framework/src/TermColor.d ./platform/framework/src/TermColor.o ./platform/framework/src/TermColor.su ./platform/framework/src/crc32.cyclo ./platform/framework/src/crc32.d ./platform/framework/src/crc32.o ./platform/framework/src/crc32.su ./platform/framework/src/crc32slow.cyclo ./platform/framework/src/crc32slow.d ./platform/framework/src/crc32slow.o ./platform/framework/src/crc32slow.su ./platform/framework/src/sbrk.cyclo ./platform/framework/src/sbrk.d ./platform/framework/src/sbrk.o ./platform/framework/src/sbrk.su ./platform/framework/src/systeminfo.cyclo ./platform/framework/src/systeminfo.d ./platform/framework/src/systeminfo.o ./platform/framework/src/systeminfo.su

.PHONY: clean-platform-2f-framework-2f-src


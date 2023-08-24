################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../platform/osSupport/src/cmsis_os.c 

CPP_SRCS += \
../platform/osSupport/src/Mutex.cpp \
../platform/osSupport/src/PeriodicTaskBase.cpp \
../platform/osSupport/src/PostOffice.cpp \
../platform/osSupport/src/Semaphore.cpp \
../platform/osSupport/src/TaskBase.cpp \
../platform/osSupport/src/TimerBase.cpp 

C_DEPS += \
./platform/osSupport/src/cmsis_os.d 

OBJS += \
./platform/osSupport/src/Mutex.o \
./platform/osSupport/src/PeriodicTaskBase.o \
./platform/osSupport/src/PostOffice.o \
./platform/osSupport/src/Semaphore.o \
./platform/osSupport/src/TaskBase.o \
./platform/osSupport/src/TimerBase.o \
./platform/osSupport/src/cmsis_os.o 

CPP_DEPS += \
./platform/osSupport/src/Mutex.d \
./platform/osSupport/src/PeriodicTaskBase.d \
./platform/osSupport/src/PostOffice.d \
./platform/osSupport/src/Semaphore.d \
./platform/osSupport/src/TaskBase.d \
./platform/osSupport/src/TimerBase.d 


# Each subdirectory must supply rules for building sources it contributes
platform/osSupport/src/%.o platform/osSupport/src/%.su platform/osSupport/src/%.cyclo: ../platform/osSupport/src/%.cpp platform/osSupport/src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++17 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/bsp/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/os/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/osSupport/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/framework/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/os/src/portable/GCC/ARM_CM4F" -I../Drivers/Ethernet/W5500 -I../Drivers/Ethernet -I../Drivers/Internet -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/ipv4 -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/posix -I../Middlewares/Third_Party/LwIP/src/include/posix/sys -I../Middlewares/Third_Party/LwIP/system/arch -I../Middlewares/Third_Party/LwIP/src/core -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../template -I../Drivers/Internet/httpServer -I../Drivers/Application/loopback -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
platform/osSupport/src/%.o platform/osSupport/src/%.su platform/osSupport/src/%.cyclo: ../platform/osSupport/src/%.c platform/osSupport/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/bsp/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/os/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/osSupport/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/framework/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/os/src/portable/GCC/ARM_CM4F" -I../Drivers/Ethernet/W5500 -I../Drivers/Internet/httpServer -I../Drivers/Ethernet -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Middlewares/Third_Party/LwIP/src/include/ipv4 -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/posix -I../Middlewares/Third_Party/LwIP/src/include/posix/sys -I../Middlewares/Third_Party/LwIP/system/arch -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../template -I../Core/Startup -I../Drivers/Application/loopback -I../Drivers/Internet -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-platform-2f-osSupport-2f-src

clean-platform-2f-osSupport-2f-src:
	-$(RM) ./platform/osSupport/src/Mutex.cyclo ./platform/osSupport/src/Mutex.d ./platform/osSupport/src/Mutex.o ./platform/osSupport/src/Mutex.su ./platform/osSupport/src/PeriodicTaskBase.cyclo ./platform/osSupport/src/PeriodicTaskBase.d ./platform/osSupport/src/PeriodicTaskBase.o ./platform/osSupport/src/PeriodicTaskBase.su ./platform/osSupport/src/PostOffice.cyclo ./platform/osSupport/src/PostOffice.d ./platform/osSupport/src/PostOffice.o ./platform/osSupport/src/PostOffice.su ./platform/osSupport/src/Semaphore.cyclo ./platform/osSupport/src/Semaphore.d ./platform/osSupport/src/Semaphore.o ./platform/osSupport/src/Semaphore.su ./platform/osSupport/src/TaskBase.cyclo ./platform/osSupport/src/TaskBase.d ./platform/osSupport/src/TaskBase.o ./platform/osSupport/src/TaskBase.su ./platform/osSupport/src/TimerBase.cyclo ./platform/osSupport/src/TimerBase.d ./platform/osSupport/src/TimerBase.o ./platform/osSupport/src/TimerBase.su ./platform/osSupport/src/cmsis_os.cyclo ./platform/osSupport/src/cmsis_os.d ./platform/osSupport/src/cmsis_os.o ./platform/osSupport/src/cmsis_os.su

.PHONY: clean-platform-2f-osSupport-2f-src


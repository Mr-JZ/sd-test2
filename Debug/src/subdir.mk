################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Application.cpp \
../src/SDTask.cpp \
../src/SensorTask.cpp \
../src/WebserverTask.cpp 

OBJS += \
./src/Application.o \
./src/SDTask.o \
./src/SensorTask.o \
./src/WebserverTask.o 

CPP_DEPS += \
./src/Application.d \
./src/SDTask.d \
./src/SensorTask.d \
./src/WebserverTask.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o src/%.su src/%.cyclo: ../src/%.cpp src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++17 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/bsp/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/os/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/osSupport/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/framework/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/os/src/portable/GCC/ARM_CM4F" -I../Drivers/Ethernet/W5500 -I../Drivers/Ethernet -I../Drivers/Internet -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/ipv4 -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/posix -I../Middlewares/Third_Party/LwIP/src/include/posix/sys -I../Middlewares/Third_Party/LwIP/system/arch -I../Middlewares/Third_Party/LwIP/src/core -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../template -I../Drivers/Internet/httpServer -I../Drivers/Application/loopback -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-src

clean-src:
	-$(RM) ./src/Application.cyclo ./src/Application.d ./src/Application.o ./src/Application.su ./src/SDTask.cyclo ./src/SDTask.d ./src/SDTask.o ./src/SDTask.su ./src/SensorTask.cyclo ./src/SensorTask.d ./src/SensorTask.o ./src/SensorTask.su ./src/WebserverTask.cyclo ./src/WebserverTask.d ./src/WebserverTask.o ./src/WebserverTask.su

.PHONY: clean-src


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../platform/bsp/src/font5x7.c \
../platform/bsp/src/fontNum24_24.c \
../platform/bsp/src/stm32xx_iap.c 

CPP_SRCS += \
../platform/bsp/src/LTR303ALS01.cpp \
../platform/bsp/src/OneWire.cpp \
../platform/bsp/src/adc.cpp \
../platform/bsp/src/dac.cpp \
../platform/bsp/src/digitalinout.cpp \
../platform/bsp/src/errorlog.cpp \
../platform/bsp/src/i2cdevice.cpp \
../platform/bsp/src/interrupt.cpp \
../platform/bsp/src/lis3dh.cpp \
../platform/bsp/src/lis3dhh.cpp \
../platform/bsp/src/lm8411.cpp \
../platform/bsp/src/mc24lc08.cpp \
../platform/bsp/src/pca9531.cpp \
../platform/bsp/src/pwm.cpp \
../platform/bsp/src/ssd1306.cpp \
../platform/bsp/src/sspdevice.cpp 

C_DEPS += \
./platform/bsp/src/font5x7.d \
./platform/bsp/src/fontNum24_24.d \
./platform/bsp/src/stm32xx_iap.d 

OBJS += \
./platform/bsp/src/LTR303ALS01.o \
./platform/bsp/src/OneWire.o \
./platform/bsp/src/adc.o \
./platform/bsp/src/dac.o \
./platform/bsp/src/digitalinout.o \
./platform/bsp/src/errorlog.o \
./platform/bsp/src/font5x7.o \
./platform/bsp/src/fontNum24_24.o \
./platform/bsp/src/i2cdevice.o \
./platform/bsp/src/interrupt.o \
./platform/bsp/src/lis3dh.o \
./platform/bsp/src/lis3dhh.o \
./platform/bsp/src/lm8411.o \
./platform/bsp/src/mc24lc08.o \
./platform/bsp/src/pca9531.o \
./platform/bsp/src/pwm.o \
./platform/bsp/src/ssd1306.o \
./platform/bsp/src/sspdevice.o \
./platform/bsp/src/stm32xx_iap.o 

CPP_DEPS += \
./platform/bsp/src/LTR303ALS01.d \
./platform/bsp/src/OneWire.d \
./platform/bsp/src/adc.d \
./platform/bsp/src/dac.d \
./platform/bsp/src/digitalinout.d \
./platform/bsp/src/errorlog.d \
./platform/bsp/src/i2cdevice.d \
./platform/bsp/src/interrupt.d \
./platform/bsp/src/lis3dh.d \
./platform/bsp/src/lis3dhh.d \
./platform/bsp/src/lm8411.d \
./platform/bsp/src/mc24lc08.d \
./platform/bsp/src/pca9531.d \
./platform/bsp/src/pwm.d \
./platform/bsp/src/ssd1306.d \
./platform/bsp/src/sspdevice.d 


# Each subdirectory must supply rules for building sources it contributes
platform/bsp/src/%.o platform/bsp/src/%.su platform/bsp/src/%.cyclo: ../platform/bsp/src/%.cpp platform/bsp/src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++17 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/bsp/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/os/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/osSupport/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/framework/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/os/src/portable/GCC/ARM_CM4F" -I../Drivers/Ethernet/W5500 -I../Drivers/Ethernet -I../Drivers/Internet -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/ipv4 -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/posix -I../Middlewares/Third_Party/LwIP/src/include/posix/sys -I../Middlewares/Third_Party/LwIP/system/arch -I../Middlewares/Third_Party/LwIP/src/core -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../template -I../Drivers/Internet/httpServer -I../Drivers/Application/loopback -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
platform/bsp/src/%.o platform/bsp/src/%.su platform/bsp/src/%.cyclo: ../platform/bsp/src/%.c platform/bsp/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/bsp/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/os/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/osSupport/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/framework/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/os/src/portable/GCC/ARM_CM4F" -I../Drivers/Ethernet/W5500 -I../Drivers/Internet/httpServer -I../Drivers/Ethernet -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Middlewares/Third_Party/LwIP/src/include/ipv4 -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/posix -I../Middlewares/Third_Party/LwIP/src/include/posix/sys -I../Middlewares/Third_Party/LwIP/system/arch -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../template -I../Core/Startup -I../Drivers/Application/loopback -I../Drivers/Internet -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-platform-2f-bsp-2f-src

clean-platform-2f-bsp-2f-src:
	-$(RM) ./platform/bsp/src/LTR303ALS01.cyclo ./platform/bsp/src/LTR303ALS01.d ./platform/bsp/src/LTR303ALS01.o ./platform/bsp/src/LTR303ALS01.su ./platform/bsp/src/OneWire.cyclo ./platform/bsp/src/OneWire.d ./platform/bsp/src/OneWire.o ./platform/bsp/src/OneWire.su ./platform/bsp/src/adc.cyclo ./platform/bsp/src/adc.d ./platform/bsp/src/adc.o ./platform/bsp/src/adc.su ./platform/bsp/src/dac.cyclo ./platform/bsp/src/dac.d ./platform/bsp/src/dac.o ./platform/bsp/src/dac.su ./platform/bsp/src/digitalinout.cyclo ./platform/bsp/src/digitalinout.d ./platform/bsp/src/digitalinout.o ./platform/bsp/src/digitalinout.su ./platform/bsp/src/errorlog.cyclo ./platform/bsp/src/errorlog.d ./platform/bsp/src/errorlog.o ./platform/bsp/src/errorlog.su ./platform/bsp/src/font5x7.cyclo ./platform/bsp/src/font5x7.d ./platform/bsp/src/font5x7.o ./platform/bsp/src/font5x7.su ./platform/bsp/src/fontNum24_24.cyclo ./platform/bsp/src/fontNum24_24.d ./platform/bsp/src/fontNum24_24.o ./platform/bsp/src/fontNum24_24.su ./platform/bsp/src/i2cdevice.cyclo ./platform/bsp/src/i2cdevice.d ./platform/bsp/src/i2cdevice.o ./platform/bsp/src/i2cdevice.su ./platform/bsp/src/interrupt.cyclo ./platform/bsp/src/interrupt.d ./platform/bsp/src/interrupt.o ./platform/bsp/src/interrupt.su ./platform/bsp/src/lis3dh.cyclo ./platform/bsp/src/lis3dh.d ./platform/bsp/src/lis3dh.o ./platform/bsp/src/lis3dh.su ./platform/bsp/src/lis3dhh.cyclo ./platform/bsp/src/lis3dhh.d ./platform/bsp/src/lis3dhh.o ./platform/bsp/src/lis3dhh.su ./platform/bsp/src/lm8411.cyclo ./platform/bsp/src/lm8411.d ./platform/bsp/src/lm8411.o ./platform/bsp/src/lm8411.su ./platform/bsp/src/mc24lc08.cyclo ./platform/bsp/src/mc24lc08.d ./platform/bsp/src/mc24lc08.o ./platform/bsp/src/mc24lc08.su ./platform/bsp/src/pca9531.cyclo ./platform/bsp/src/pca9531.d ./platform/bsp/src/pca9531.o ./platform/bsp/src/pca9531.su ./platform/bsp/src/pwm.cyclo ./platform/bsp/src/pwm.d ./platform/bsp/src/pwm.o ./platform/bsp/src/pwm.su ./platform/bsp/src/ssd1306.cyclo ./platform/bsp/src/ssd1306.d ./platform/bsp/src/ssd1306.o ./platform/bsp/src/ssd1306.su ./platform/bsp/src/sspdevice.cyclo ./platform/bsp/src/sspdevice.d ./platform/bsp/src/sspdevice.o ./platform/bsp/src/sspdevice.su ./platform/bsp/src/stm32xx_iap.cyclo ./platform/bsp/src/stm32xx_iap.d ./platform/bsp/src/stm32xx_iap.o ./platform/bsp/src/stm32xx_iap.su

.PHONY: clean-platform-2f-bsp-2f-src


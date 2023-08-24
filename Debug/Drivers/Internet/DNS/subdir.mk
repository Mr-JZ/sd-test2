################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Internet/DNS/dns.c 

C_DEPS += \
./Drivers/Internet/DNS/dns.d 

OBJS += \
./Drivers/Internet/DNS/dns.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Internet/DNS/%.o Drivers/Internet/DNS/%.su Drivers/Internet/DNS/%.cyclo: ../Drivers/Internet/DNS/%.c Drivers/Internet/DNS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/tobeh/Desktop/Uni/Gitlab/SD_Test/inc" -I"C:/Users/tobeh/Desktop/Uni/Gitlab/SD_Test/platform/bsp/inc" -I"C:/Users/tobeh/Desktop/Uni/Gitlab/SD_Test/platform/os/inc" -I"C:/Users/tobeh/Desktop/Uni/Gitlab/SD_Test/platform/osSupport/inc" -I"C:/Users/tobeh/Desktop/Uni/Gitlab/SD_Test/platform/framework/inc" -I"C:/Users/tobeh/Desktop/Uni/Gitlab/SD_Test/platform/os/src/portable/GCC/ARM_CM4F" -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/ipv4 -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/posix -I../Middlewares/Third_Party/LwIP/src/include/posix/sys -I../Middlewares/Third_Party/LwIP/system/arch -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Drivers/Ethernet/W5500 -I../Drivers/Ethernet -I../Drivers/Internet -I../template -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Internet-2f-DNS

clean-Drivers-2f-Internet-2f-DNS:
	-$(RM) ./Drivers/Internet/DNS/dns.cyclo ./Drivers/Internet/DNS/dns.d ./Drivers/Internet/DNS/dns.o ./Drivers/Internet/DNS/dns.su

.PHONY: clean-Drivers-2f-Internet-2f-DNS


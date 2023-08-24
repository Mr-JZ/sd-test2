################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Internet/SNMP/snmp.c \
../Drivers/Internet/SNMP/snmp_custom.c 

C_DEPS += \
./Drivers/Internet/SNMP/snmp.d \
./Drivers/Internet/SNMP/snmp_custom.d 

OBJS += \
./Drivers/Internet/SNMP/snmp.o \
./Drivers/Internet/SNMP/snmp_custom.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Internet/SNMP/%.o Drivers/Internet/SNMP/%.su Drivers/Internet/SNMP/%.cyclo: ../Drivers/Internet/SNMP/%.c Drivers/Internet/SNMP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/tobeh/Desktop/Uni/Gitlab/SD_Test/inc" -I"C:/Users/tobeh/Desktop/Uni/Gitlab/SD_Test/platform/bsp/inc" -I"C:/Users/tobeh/Desktop/Uni/Gitlab/SD_Test/platform/os/inc" -I"C:/Users/tobeh/Desktop/Uni/Gitlab/SD_Test/platform/osSupport/inc" -I"C:/Users/tobeh/Desktop/Uni/Gitlab/SD_Test/platform/framework/inc" -I"C:/Users/tobeh/Desktop/Uni/Gitlab/SD_Test/platform/os/src/portable/GCC/ARM_CM4F" -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/ipv4 -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/posix -I../Middlewares/Third_Party/LwIP/src/include/posix/sys -I../Middlewares/Third_Party/LwIP/system/arch -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Drivers/Ethernet/W5500 -I../Drivers/Ethernet -I../Drivers/Internet -I../template -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Internet-2f-SNMP

clean-Drivers-2f-Internet-2f-SNMP:
	-$(RM) ./Drivers/Internet/SNMP/snmp.cyclo ./Drivers/Internet/SNMP/snmp.d ./Drivers/Internet/SNMP/snmp.o ./Drivers/Internet/SNMP/snmp.su ./Drivers/Internet/SNMP/snmp_custom.cyclo ./Drivers/Internet/SNMP/snmp_custom.d ./Drivers/Internet/SNMP/snmp_custom.o ./Drivers/Internet/SNMP/snmp_custom.su

.PHONY: clean-Drivers-2f-Internet-2f-SNMP


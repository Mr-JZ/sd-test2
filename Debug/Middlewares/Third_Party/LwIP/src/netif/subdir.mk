################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/LwIP/src/netif/etharp.c \
../Middlewares/Third_Party/LwIP/src/netif/ethernetif.c \
../Middlewares/Third_Party/LwIP/src/netif/slipif.c 

C_DEPS += \
./Middlewares/Third_Party/LwIP/src/netif/etharp.d \
./Middlewares/Third_Party/LwIP/src/netif/ethernetif.d \
./Middlewares/Third_Party/LwIP/src/netif/slipif.d 

OBJS += \
./Middlewares/Third_Party/LwIP/src/netif/etharp.o \
./Middlewares/Third_Party/LwIP/src/netif/ethernetif.o \
./Middlewares/Third_Party/LwIP/src/netif/slipif.o 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/LwIP/src/netif/%.o Middlewares/Third_Party/LwIP/src/netif/%.su Middlewares/Third_Party/LwIP/src/netif/%.cyclo: ../Middlewares/Third_Party/LwIP/src/netif/%.c Middlewares/Third_Party/LwIP/src/netif/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/bsp/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/os/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/osSupport/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/framework/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/os/src/portable/GCC/ARM_CM4F" -I../Drivers/Ethernet/W5500 -I../Drivers/Internet/httpServer -I../Drivers/Ethernet -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Middlewares/Third_Party/LwIP/src/include/ipv4 -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/posix -I../Middlewares/Third_Party/LwIP/src/include/posix/sys -I../Middlewares/Third_Party/LwIP/system/arch -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../template -I../Core/Startup -I../Drivers/Application/loopback -I../Drivers/Internet -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-LwIP-2f-src-2f-netif

clean-Middlewares-2f-Third_Party-2f-LwIP-2f-src-2f-netif:
	-$(RM) ./Middlewares/Third_Party/LwIP/src/netif/etharp.cyclo ./Middlewares/Third_Party/LwIP/src/netif/etharp.d ./Middlewares/Third_Party/LwIP/src/netif/etharp.o ./Middlewares/Third_Party/LwIP/src/netif/etharp.su ./Middlewares/Third_Party/LwIP/src/netif/ethernetif.cyclo ./Middlewares/Third_Party/LwIP/src/netif/ethernetif.d ./Middlewares/Third_Party/LwIP/src/netif/ethernetif.o ./Middlewares/Third_Party/LwIP/src/netif/ethernetif.su ./Middlewares/Third_Party/LwIP/src/netif/slipif.cyclo ./Middlewares/Third_Party/LwIP/src/netif/slipif.d ./Middlewares/Third_Party/LwIP/src/netif/slipif.o ./Middlewares/Third_Party/LwIP/src/netif/slipif.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-LwIP-2f-src-2f-netif


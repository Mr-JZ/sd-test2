################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Ethernet/socket.c \
../Drivers/Ethernet/wizchip_conf.c 

C_DEPS += \
./Drivers/Ethernet/socket.d \
./Drivers/Ethernet/wizchip_conf.d 

OBJS += \
./Drivers/Ethernet/socket.o \
./Drivers/Ethernet/wizchip_conf.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Ethernet/%.o Drivers/Ethernet/%.su Drivers/Ethernet/%.cyclo: ../Drivers/Ethernet/%.c Drivers/Ethernet/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/bsp/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/os/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/osSupport/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/framework/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/os/src/portable/GCC/ARM_CM4F" -I../Drivers/Ethernet/W5500 -I../Drivers/Internet/httpServer -I../Drivers/Ethernet -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Middlewares/Third_Party/LwIP/src/include/ipv4 -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/posix -I../Middlewares/Third_Party/LwIP/src/include/posix/sys -I../Middlewares/Third_Party/LwIP/system/arch -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../template -I../Core/Startup -I../Drivers/Application/loopback -I../Drivers/Internet -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Ethernet

clean-Drivers-2f-Ethernet:
	-$(RM) ./Drivers/Ethernet/socket.cyclo ./Drivers/Ethernet/socket.d ./Drivers/Ethernet/socket.o ./Drivers/Ethernet/socket.su ./Drivers/Ethernet/wizchip_conf.cyclo ./Drivers/Ethernet/wizchip_conf.d ./Drivers/Ethernet/wizchip_conf.o ./Drivers/Ethernet/wizchip_conf.su

.PHONY: clean-Drivers-2f-Ethernet


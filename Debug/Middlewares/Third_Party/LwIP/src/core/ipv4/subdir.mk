################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/LwIP/src/core/ipv4/autoip.c \
../Middlewares/Third_Party/LwIP/src/core/ipv4/icmp.c \
../Middlewares/Third_Party/LwIP/src/core/ipv4/igmp.c \
../Middlewares/Third_Party/LwIP/src/core/ipv4/inet.c \
../Middlewares/Third_Party/LwIP/src/core/ipv4/inet_chksum.c \
../Middlewares/Third_Party/LwIP/src/core/ipv4/ip.c \
../Middlewares/Third_Party/LwIP/src/core/ipv4/ip_addr.c \
../Middlewares/Third_Party/LwIP/src/core/ipv4/ip_frag.c 

C_DEPS += \
./Middlewares/Third_Party/LwIP/src/core/ipv4/autoip.d \
./Middlewares/Third_Party/LwIP/src/core/ipv4/icmp.d \
./Middlewares/Third_Party/LwIP/src/core/ipv4/igmp.d \
./Middlewares/Third_Party/LwIP/src/core/ipv4/inet.d \
./Middlewares/Third_Party/LwIP/src/core/ipv4/inet_chksum.d \
./Middlewares/Third_Party/LwIP/src/core/ipv4/ip.d \
./Middlewares/Third_Party/LwIP/src/core/ipv4/ip_addr.d \
./Middlewares/Third_Party/LwIP/src/core/ipv4/ip_frag.d 

OBJS += \
./Middlewares/Third_Party/LwIP/src/core/ipv4/autoip.o \
./Middlewares/Third_Party/LwIP/src/core/ipv4/icmp.o \
./Middlewares/Third_Party/LwIP/src/core/ipv4/igmp.o \
./Middlewares/Third_Party/LwIP/src/core/ipv4/inet.o \
./Middlewares/Third_Party/LwIP/src/core/ipv4/inet_chksum.o \
./Middlewares/Third_Party/LwIP/src/core/ipv4/ip.o \
./Middlewares/Third_Party/LwIP/src/core/ipv4/ip_addr.o \
./Middlewares/Third_Party/LwIP/src/core/ipv4/ip_frag.o 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/LwIP/src/core/ipv4/%.o Middlewares/Third_Party/LwIP/src/core/ipv4/%.su Middlewares/Third_Party/LwIP/src/core/ipv4/%.cyclo: ../Middlewares/Third_Party/LwIP/src/core/ipv4/%.c Middlewares/Third_Party/LwIP/src/core/ipv4/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/bsp/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/os/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/osSupport/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/framework/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/os/src/portable/GCC/ARM_CM4F" -I../Drivers/Ethernet/W5500 -I../Drivers/Internet/httpServer -I../Drivers/Ethernet -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Middlewares/Third_Party/LwIP/src/include/ipv4 -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/posix -I../Middlewares/Third_Party/LwIP/src/include/posix/sys -I../Middlewares/Third_Party/LwIP/system/arch -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../template -I../Core/Startup -I../Drivers/Application/loopback -I../Drivers/Internet -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-LwIP-2f-src-2f-core-2f-ipv4

clean-Middlewares-2f-Third_Party-2f-LwIP-2f-src-2f-core-2f-ipv4:
	-$(RM) ./Middlewares/Third_Party/LwIP/src/core/ipv4/autoip.cyclo ./Middlewares/Third_Party/LwIP/src/core/ipv4/autoip.d ./Middlewares/Third_Party/LwIP/src/core/ipv4/autoip.o ./Middlewares/Third_Party/LwIP/src/core/ipv4/autoip.su ./Middlewares/Third_Party/LwIP/src/core/ipv4/icmp.cyclo ./Middlewares/Third_Party/LwIP/src/core/ipv4/icmp.d ./Middlewares/Third_Party/LwIP/src/core/ipv4/icmp.o ./Middlewares/Third_Party/LwIP/src/core/ipv4/icmp.su ./Middlewares/Third_Party/LwIP/src/core/ipv4/igmp.cyclo ./Middlewares/Third_Party/LwIP/src/core/ipv4/igmp.d ./Middlewares/Third_Party/LwIP/src/core/ipv4/igmp.o ./Middlewares/Third_Party/LwIP/src/core/ipv4/igmp.su ./Middlewares/Third_Party/LwIP/src/core/ipv4/inet.cyclo ./Middlewares/Third_Party/LwIP/src/core/ipv4/inet.d ./Middlewares/Third_Party/LwIP/src/core/ipv4/inet.o ./Middlewares/Third_Party/LwIP/src/core/ipv4/inet.su ./Middlewares/Third_Party/LwIP/src/core/ipv4/inet_chksum.cyclo ./Middlewares/Third_Party/LwIP/src/core/ipv4/inet_chksum.d ./Middlewares/Third_Party/LwIP/src/core/ipv4/inet_chksum.o ./Middlewares/Third_Party/LwIP/src/core/ipv4/inet_chksum.su ./Middlewares/Third_Party/LwIP/src/core/ipv4/ip.cyclo ./Middlewares/Third_Party/LwIP/src/core/ipv4/ip.d ./Middlewares/Third_Party/LwIP/src/core/ipv4/ip.o ./Middlewares/Third_Party/LwIP/src/core/ipv4/ip.su ./Middlewares/Third_Party/LwIP/src/core/ipv4/ip_addr.cyclo ./Middlewares/Third_Party/LwIP/src/core/ipv4/ip_addr.d ./Middlewares/Third_Party/LwIP/src/core/ipv4/ip_addr.o ./Middlewares/Third_Party/LwIP/src/core/ipv4/ip_addr.su ./Middlewares/Third_Party/LwIP/src/core/ipv4/ip_frag.cyclo ./Middlewares/Third_Party/LwIP/src/core/ipv4/ip_frag.d ./Middlewares/Third_Party/LwIP/src/core/ipv4/ip_frag.o ./Middlewares/Third_Party/LwIP/src/core/ipv4/ip_frag.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-LwIP-2f-src-2f-core-2f-ipv4


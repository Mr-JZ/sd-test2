################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/LwIP/src/netif/ppp/auth.c \
../Middlewares/Third_Party/LwIP/src/netif/ppp/chap.c \
../Middlewares/Third_Party/LwIP/src/netif/ppp/chpms.c \
../Middlewares/Third_Party/LwIP/src/netif/ppp/fsm.c \
../Middlewares/Third_Party/LwIP/src/netif/ppp/ipcp.c \
../Middlewares/Third_Party/LwIP/src/netif/ppp/lcp.c \
../Middlewares/Third_Party/LwIP/src/netif/ppp/magic.c \
../Middlewares/Third_Party/LwIP/src/netif/ppp/md5.c \
../Middlewares/Third_Party/LwIP/src/netif/ppp/pap.c \
../Middlewares/Third_Party/LwIP/src/netif/ppp/ppp.c \
../Middlewares/Third_Party/LwIP/src/netif/ppp/ppp_oe.c \
../Middlewares/Third_Party/LwIP/src/netif/ppp/randm.c \
../Middlewares/Third_Party/LwIP/src/netif/ppp/vj.c 

C_DEPS += \
./Middlewares/Third_Party/LwIP/src/netif/ppp/auth.d \
./Middlewares/Third_Party/LwIP/src/netif/ppp/chap.d \
./Middlewares/Third_Party/LwIP/src/netif/ppp/chpms.d \
./Middlewares/Third_Party/LwIP/src/netif/ppp/fsm.d \
./Middlewares/Third_Party/LwIP/src/netif/ppp/ipcp.d \
./Middlewares/Third_Party/LwIP/src/netif/ppp/lcp.d \
./Middlewares/Third_Party/LwIP/src/netif/ppp/magic.d \
./Middlewares/Third_Party/LwIP/src/netif/ppp/md5.d \
./Middlewares/Third_Party/LwIP/src/netif/ppp/pap.d \
./Middlewares/Third_Party/LwIP/src/netif/ppp/ppp.d \
./Middlewares/Third_Party/LwIP/src/netif/ppp/ppp_oe.d \
./Middlewares/Third_Party/LwIP/src/netif/ppp/randm.d \
./Middlewares/Third_Party/LwIP/src/netif/ppp/vj.d 

OBJS += \
./Middlewares/Third_Party/LwIP/src/netif/ppp/auth.o \
./Middlewares/Third_Party/LwIP/src/netif/ppp/chap.o \
./Middlewares/Third_Party/LwIP/src/netif/ppp/chpms.o \
./Middlewares/Third_Party/LwIP/src/netif/ppp/fsm.o \
./Middlewares/Third_Party/LwIP/src/netif/ppp/ipcp.o \
./Middlewares/Third_Party/LwIP/src/netif/ppp/lcp.o \
./Middlewares/Third_Party/LwIP/src/netif/ppp/magic.o \
./Middlewares/Third_Party/LwIP/src/netif/ppp/md5.o \
./Middlewares/Third_Party/LwIP/src/netif/ppp/pap.o \
./Middlewares/Third_Party/LwIP/src/netif/ppp/ppp.o \
./Middlewares/Third_Party/LwIP/src/netif/ppp/ppp_oe.o \
./Middlewares/Third_Party/LwIP/src/netif/ppp/randm.o \
./Middlewares/Third_Party/LwIP/src/netif/ppp/vj.o 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/LwIP/src/netif/ppp/%.o Middlewares/Third_Party/LwIP/src/netif/ppp/%.su Middlewares/Third_Party/LwIP/src/netif/ppp/%.cyclo: ../Middlewares/Third_Party/LwIP/src/netif/ppp/%.c Middlewares/Third_Party/LwIP/src/netif/ppp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/bsp/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/os/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/osSupport/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/framework/inc" -I"C:/Users/Jan/gitlab/embedded/sd-jan-2/platform/os/src/portable/GCC/ARM_CM4F" -I../Drivers/Ethernet/W5500 -I../Drivers/Internet/httpServer -I../Drivers/Ethernet -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Middlewares/Third_Party/LwIP/src/include/ipv4 -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/posix -I../Middlewares/Third_Party/LwIP/src/include/posix/sys -I../Middlewares/Third_Party/LwIP/system/arch -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../template -I../Core/Startup -I../Drivers/Application/loopback -I../Drivers/Internet -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-LwIP-2f-src-2f-netif-2f-ppp

clean-Middlewares-2f-Third_Party-2f-LwIP-2f-src-2f-netif-2f-ppp:
	-$(RM) ./Middlewares/Third_Party/LwIP/src/netif/ppp/auth.cyclo ./Middlewares/Third_Party/LwIP/src/netif/ppp/auth.d ./Middlewares/Third_Party/LwIP/src/netif/ppp/auth.o ./Middlewares/Third_Party/LwIP/src/netif/ppp/auth.su ./Middlewares/Third_Party/LwIP/src/netif/ppp/chap.cyclo ./Middlewares/Third_Party/LwIP/src/netif/ppp/chap.d ./Middlewares/Third_Party/LwIP/src/netif/ppp/chap.o ./Middlewares/Third_Party/LwIP/src/netif/ppp/chap.su ./Middlewares/Third_Party/LwIP/src/netif/ppp/chpms.cyclo ./Middlewares/Third_Party/LwIP/src/netif/ppp/chpms.d ./Middlewares/Third_Party/LwIP/src/netif/ppp/chpms.o ./Middlewares/Third_Party/LwIP/src/netif/ppp/chpms.su ./Middlewares/Third_Party/LwIP/src/netif/ppp/fsm.cyclo ./Middlewares/Third_Party/LwIP/src/netif/ppp/fsm.d ./Middlewares/Third_Party/LwIP/src/netif/ppp/fsm.o ./Middlewares/Third_Party/LwIP/src/netif/ppp/fsm.su ./Middlewares/Third_Party/LwIP/src/netif/ppp/ipcp.cyclo ./Middlewares/Third_Party/LwIP/src/netif/ppp/ipcp.d ./Middlewares/Third_Party/LwIP/src/netif/ppp/ipcp.o ./Middlewares/Third_Party/LwIP/src/netif/ppp/ipcp.su ./Middlewares/Third_Party/LwIP/src/netif/ppp/lcp.cyclo ./Middlewares/Third_Party/LwIP/src/netif/ppp/lcp.d ./Middlewares/Third_Party/LwIP/src/netif/ppp/lcp.o ./Middlewares/Third_Party/LwIP/src/netif/ppp/lcp.su ./Middlewares/Third_Party/LwIP/src/netif/ppp/magic.cyclo ./Middlewares/Third_Party/LwIP/src/netif/ppp/magic.d ./Middlewares/Third_Party/LwIP/src/netif/ppp/magic.o ./Middlewares/Third_Party/LwIP/src/netif/ppp/magic.su ./Middlewares/Third_Party/LwIP/src/netif/ppp/md5.cyclo ./Middlewares/Third_Party/LwIP/src/netif/ppp/md5.d ./Middlewares/Third_Party/LwIP/src/netif/ppp/md5.o ./Middlewares/Third_Party/LwIP/src/netif/ppp/md5.su ./Middlewares/Third_Party/LwIP/src/netif/ppp/pap.cyclo ./Middlewares/Third_Party/LwIP/src/netif/ppp/pap.d ./Middlewares/Third_Party/LwIP/src/netif/ppp/pap.o ./Middlewares/Third_Party/LwIP/src/netif/ppp/pap.su ./Middlewares/Third_Party/LwIP/src/netif/ppp/ppp.cyclo ./Middlewares/Third_Party/LwIP/src/netif/ppp/ppp.d ./Middlewares/Third_Party/LwIP/src/netif/ppp/ppp.o ./Middlewares/Third_Party/LwIP/src/netif/ppp/ppp.su ./Middlewares/Third_Party/LwIP/src/netif/ppp/ppp_oe.cyclo ./Middlewares/Third_Party/LwIP/src/netif/ppp/ppp_oe.d ./Middlewares/Third_Party/LwIP/src/netif/ppp/ppp_oe.o ./Middlewares/Third_Party/LwIP/src/netif/ppp/ppp_oe.su ./Middlewares/Third_Party/LwIP/src/netif/ppp/randm.cyclo ./Middlewares/Third_Party/LwIP/src/netif/ppp/randm.d ./Middlewares/Third_Party/LwIP/src/netif/ppp/randm.o ./Middlewares/Third_Party/LwIP/src/netif/ppp/randm.su ./Middlewares/Third_Party/LwIP/src/netif/ppp/vj.cyclo ./Middlewares/Third_Party/LwIP/src/netif/ppp/vj.d ./Middlewares/Third_Party/LwIP/src/netif/ppp/vj.o ./Middlewares/Third_Party/LwIP/src/netif/ppp/vj.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-LwIP-2f-src-2f-netif-2f-ppp


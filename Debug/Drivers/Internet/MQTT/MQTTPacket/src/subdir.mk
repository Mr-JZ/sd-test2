################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.c \
../Drivers/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.c \
../Drivers/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.c \
../Drivers/Internet/MQTT/MQTTPacket/src/MQTTFormat.c \
../Drivers/Internet/MQTT/MQTTPacket/src/MQTTPacket.c \
../Drivers/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.c \
../Drivers/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.c \
../Drivers/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.c \
../Drivers/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.c \
../Drivers/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.c 

C_DEPS += \
./Drivers/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.d \
./Drivers/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.d \
./Drivers/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.d \
./Drivers/Internet/MQTT/MQTTPacket/src/MQTTFormat.d \
./Drivers/Internet/MQTT/MQTTPacket/src/MQTTPacket.d \
./Drivers/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.d \
./Drivers/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.d \
./Drivers/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.d \
./Drivers/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.d \
./Drivers/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.d 

OBJS += \
./Drivers/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.o \
./Drivers/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.o \
./Drivers/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.o \
./Drivers/Internet/MQTT/MQTTPacket/src/MQTTFormat.o \
./Drivers/Internet/MQTT/MQTTPacket/src/MQTTPacket.o \
./Drivers/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.o \
./Drivers/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.o \
./Drivers/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.o \
./Drivers/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.o \
./Drivers/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Internet/MQTT/MQTTPacket/src/%.o Drivers/Internet/MQTT/MQTTPacket/src/%.su Drivers/Internet/MQTT/MQTTPacket/src/%.cyclo: ../Drivers/Internet/MQTT/MQTTPacket/src/%.c Drivers/Internet/MQTT/MQTTPacket/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/tobeh/Desktop/Uni/Gitlab/SD_Test/inc" -I"C:/Users/tobeh/Desktop/Uni/Gitlab/SD_Test/platform/bsp/inc" -I"C:/Users/tobeh/Desktop/Uni/Gitlab/SD_Test/platform/os/inc" -I"C:/Users/tobeh/Desktop/Uni/Gitlab/SD_Test/platform/osSupport/inc" -I"C:/Users/tobeh/Desktop/Uni/Gitlab/SD_Test/platform/framework/inc" -I"C:/Users/tobeh/Desktop/Uni/Gitlab/SD_Test/platform/os/src/portable/GCC/ARM_CM4F" -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/ipv4 -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/posix -I../Middlewares/Third_Party/LwIP/src/include/posix/sys -I../Middlewares/Third_Party/LwIP/system/arch -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Drivers/Ethernet/W5500 -I../Drivers/Ethernet -I../Drivers/Internet -I../template -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Internet-2f-MQTT-2f-MQTTPacket-2f-src

clean-Drivers-2f-Internet-2f-MQTT-2f-MQTTPacket-2f-src:
	-$(RM) ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.cyclo ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.d ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.o ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.su ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.cyclo ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.d ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.o ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.su ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.cyclo ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.d ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.o ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.su ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTFormat.cyclo ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTFormat.d ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTFormat.o ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTFormat.su ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTPacket.cyclo ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTPacket.d ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTPacket.o ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTPacket.su ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.cyclo ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.d ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.o ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.su ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.cyclo ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.d ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.o ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.su ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.cyclo ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.d ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.o ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.su ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.cyclo ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.d ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.o ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.su ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.cyclo ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.d ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.o ./Drivers/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.su

.PHONY: clean-Drivers-2f-Internet-2f-MQTT-2f-MQTTPacket-2f-src


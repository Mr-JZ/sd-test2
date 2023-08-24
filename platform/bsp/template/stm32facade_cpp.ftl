[#ftl]
[#list configs as dt]
[#assign usedIPs =dt.usedIPs]
/*
 * stm32facade.cpp
 *
 *  Auto created on: ${.now} 
 *      Author: michael
 *
 * *** DON'T CHANGE BY HAND. WILL BE OVERWRITTEN BY CODE GENERATOR ***
 */


#include "stm32facade.h"

[#assign isADC=usedIPs?seq_contains("ADC1")||usedIPs?seq_contains("ADC2")||usedIPs?seq_contains("ADC3")]
[#assign isI2C=usedIPs?seq_contains("I2C1")||usedIPs?seq_contains("I2C2")||usedIPs?seq_contains("I2C3")]
[#assign isSPI=usedIPs?seq_contains("SPI1")||usedIPs?seq_contains("SPI2")||usedIPs?seq_contains("SSP3")]
[#assign isTIM=usedIPs?seq_contains("TIM1")||usedIPs?seq_contains("TIM2")||usedIPs?seq_contains("TIM3")||
	usedIPs?seq_contains("TIM4")||usedIPs?seq_contains("TIM5")||usedIPs?seq_contains("TIM6")||
	usedIPs?seq_contains("TIM7")||usedIPs?seq_contains("TIM8")||usedIPs?seq_contains("TIM15")||
	usedIPs?seq_contains("TIM16")||usedIPs?seq_contains("TIM17")]
[#assign isDAC=usedIPs?seq_contains("DAC1")]
[#assign isRTC=usedIPs?seq_contains("RTC")]
[#assign isCAN=usedIPs?seq_contains("CAN1")]


[#list usedIPs as ip]
[#if ip?contains("TIM")]
extern TIM_HandleTypeDef h${ip?lower_case};
[#elseif ip?contains("DAC")]
extern DAC_HandleTypeDef h${ip?lower_case};
[#elseif ip?contains("SPI")]
extern SPI_HandleTypeDef h${ip?lower_case};
[#elseif ip?contains("I2C")]
extern I2C_HandleTypeDef h${ip?lower_case};
[#elseif ip?contains("ADC")]
extern ADC_HandleTypeDef h${ip?lower_case};
[#elseif ip?contains("RTC")]
extern RTC_HandleTypeDef h${ip?lower_case};
[#elseif ip?contains("CAN")]
extern CAN_HandleTypeDef h${ip?lower_case};
[/#if]
[/#list]	

namespace Platform::BSP {

[#if isADC]
ADC_HandleTypeDef* STM32Facade::instance(ADC_Peripheral device) {
	switch (device) {
[#list usedIPs as ip]
[#if ip?contains("ADC")]
	case ADC_Peripheral::Use${ip} : return &h${ip?lower_case}; break;
[/#if]
[/#list]	
	default:;
	}
	return nullptr;
}
[/#if]
 
[#if isI2C]
I2C_HandleTypeDef* STM32Facade::instance(I2C_Peripheral device) {
	switch (device) {
[#list usedIPs as ip]
[#if ip?contains("I2C")]
	case I2C_Peripheral::Use${ip} : return &h${ip?lower_case}; break;
[/#if]
[/#list]	
	default:;
	}
	return nullptr;
}
[/#if]
 
[#if isSPI]
SPI_HandleTypeDef* STM32Facade::instance(SPI_Peripheral device) {
	switch (device) {
[#list usedIPs as ip]
[#if ip?contains("SPI")]
	case SPI_Peripheral::Use${ip} : return &h${ip?lower_case}; break;
[/#if]
[/#list]	
	default:;
	}
	return nullptr;
}
[/#if]
  
[#if isTIM]
TIM_HandleTypeDef* STM32Facade::instance(Timer_Peripheral device) {
	switch (device) {
[#list usedIPs as ip]
[#if ip?contains("TIM")]
	case Timer_Peripheral::Use${ip} : return &h${ip?lower_case}; break;
[/#if]
[/#list]	
	default:;
	}
	return nullptr;
}
[/#if]


[#if isDAC]
DAC_HandleTypeDef* STM32Facade::instance(DAC_Peripheral device) {
	switch (device) {
[#list usedIPs as ip]
[#if ip?contains("DAC")]
	case DAC_Peripheral::Use${ip} : return &h${ip?lower_case}; break;
[/#if]
[/#list]	
	default:;
	}
	return nullptr;
}
[/#if]

[#if isRTC]
RTC_HandleTypeDef* STM32Facade::instance(RTC_Peripheral device) {
	switch (device) {
[#list usedIPs as ip]
[#if ip?contains("RTC")]
	case RTC_Peripheral::Use${ip} : return &h${ip?lower_case}; break;
[/#if]
[/#list]	
	default:;
	}
	return nullptr;
}
[/#if]
 
[#if isCAN]
CAN_HandleTypeDef* STM32Facade::instance(CAN_Peripheral device) {
	switch (device) {
[#list usedIPs as ip]
[#if ip?contains("CAN")]
	case CAN_Peripheral::Use${ip} : return &h${ip?lower_case}; break;
[/#if]
[/#list]	
	default:;
	}
	return nullptr;
}
[/#if]
 
}
[/#list]

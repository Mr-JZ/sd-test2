/*
 * stm32facade.cpp
 *
 *  Auto created on: Aug 23, 2023, 9:16:01 AM
 *      Author: michael
 *
 * *** DON'T CHANGE BY HAND. WILL BE OVERWRITTEN BY CODE GENERATOR ***
 */

#include "stm32facade.h"

extern I2C_HandleTypeDef hi2c1;
extern RTC_HandleTypeDef hrtc;
extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim8;

namespace Platform::BSP {

I2C_HandleTypeDef* STM32Facade::instance(I2C_Peripheral device) {
	switch (device) {
	case I2C_Peripheral::UseI2C1 : return &hi2c1; break;
	default:;
	}
	return nullptr;
}

SPI_HandleTypeDef* STM32Facade::instance(SPI_Peripheral device) {
	switch (device) {
	case SPI_Peripheral::UseSPI1 : return &hspi1; break;
	case SPI_Peripheral::UseSPI2 : return &hspi2; break;
	default:;
	}
	return nullptr;
}

TIM_HandleTypeDef* STM32Facade::instance(Timer_Peripheral device) {
	switch (device) {
	case Timer_Peripheral::UseTIM5 : return &htim5; break;
	case Timer_Peripheral::UseTIM8 : return &htim8; break;
	default:;
	}
	return nullptr;
}

RTC_HandleTypeDef* STM32Facade::instance(RTC_Peripheral device) {
	switch (device) {
	case RTC_Peripheral::UseRTC : return &hrtc; break;
	default:;
	}
	return nullptr;
}

}

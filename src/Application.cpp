/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : application.cpp
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 HS Osnabruck.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/

#include <cstdio>
#include <cinttypes>
#include "wizchip_conf.h"
#include "socket.h"
#include "stm32L4xx_hal.h"
#include <string.h>
#include "stm32facade.h"

#include "main.h"

#include "cmsis_os.h"

#include <Application.h>


void cs_sel() {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET); //CS LOW
}

void cs_desel() {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET); //CS HIGH
}

uint8_t spi_rb(void) {
	uint8_t rbuf;
	HAL_SPI_Receive(Platform::BSP::STM32Facade::instance(Platform::BSP::STM32Facade::SPI_Peripheral::UseSPI1), &rbuf, 1, 0xFFFFFFFF);
	return rbuf;
}

void spi_wb(uint8_t b) {
	HAL_SPI_Transmit(Platform::BSP::STM32Facade::instance(Platform::BSP::STM32Facade::SPI_Peripheral::UseSPI1), &b, 1, 0xFFFFFFFF);
}

uint16_t stack = 2048;
/* --Project includes. */
Application::Application(): m_sdTask("SD_Task", stack, osPriorityNormal, true)/*m_webserverTask("Webserver_Task",stack,osPriorityNormal,true)*/{
//	uint8_t retVal, sockStatus;
//	int16_t rcvLen;
//	uint8_t rcvBuf[20], bufSize[] = {2, 2, 2, 2};
//
//	const char* greeting_msg = "Well done guys! Welcome to the IoT world. Buy!\r\n";
//
//
//	// Hello message in the terminal
//	std::printf("=============================================\r\n");
//	std::printf("Welcome to STM32Nucleo Ethernet configuration\r\n");
//	std::printf("=============================================\r\n");
//
//	// To get the spi
//	// SPI_HandleTypeDef* spi = Platform::BSP::STM32Facade::instance(Platform::BSP::STM32Facade::SPI_Peripheral::UseSPI2);
//
//	reg_wizchip_cs_cbfunc(cs_sel, cs_desel);
//	reg_wizchip_spi_cbfunc(spi_rb, spi_wb);
//
//	wizchip_init(bufSize, bufSize);
//	wiz_NetInfo netInfo = { .mac 	= {0x2c, 0xf7, 0xf1, 0x08, 0x38, 0xcc},	// Mac address
//	                          .ip 	= {192, 168, 178, 192},					// IP address
//	                          .sn 	= {255, 255, 255, 0},					// Subnet mask
//	                          .gw 	= {192, 168, 178, 1}};					// Gateway address
//	wizchip_setnetinfo(&netInfo);
//	wizchip_getnetinfo(&netInfo);
//
//	// print the set information
//	std::printf("Network configuration:\r\n");
//	std::printf("  MAC ADDRESS: %x:%x:%x:%x:%x:%x\r\n", netInfo.mac[0], netInfo.mac[1], netInfo.mac[2], netInfo.mac[3], netInfo.mac[4], netInfo.mac[5]);
//	std::printf("  IP ADDRESS:  %d.%d.%d.%d\r\n", netInfo.ip[0], netInfo.ip[1], netInfo.ip[2], netInfo.ip[3]);
//	std::printf("  NETMASK:     %d.%d.%d.%d\r\n", netInfo.sn[0], netInfo.sn[1], netInfo.sn[2], netInfo.sn[3]);
//	std::printf("  GATEWAY:     %d.%d.%d.%d\r\n", netInfo.gw[0], netInfo.gw[1], netInfo.gw[2], netInfo.gw[3]);
}

extern "C" {
uint32_t HAL_GetTick(void) {
	return osKernelSysTick();
}
}

static uint8_t appMem[sizeof(Application)];

static Application *appPointer = nullptr;

extern "C" void startApplication() {
	/* --Initialize the kernel. */
	osKernelInitialize();

	appPointer = new (appMem) Application;
	/* --Run the kernel. */
	osKernelStart();

}


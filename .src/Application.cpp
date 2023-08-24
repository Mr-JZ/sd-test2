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
#include <stm32f4xx_hal.h>
#include <string.h>

#include "main.h"

#include "cmsis_os.h"

#include <Application.h>


#define SEPARATOR            "=============================================\r\n"
#define WELCOME_MSG  		 "Welcome to STM32Nucleo Ethernet configuration\r\n"
#define NETWORK_MSG  		 "Network configuration:\r\n"
#define IP_MSG 		 		 "  IP ADDRESS:  %d.%d.%d.%d\r\n"
#define NETMASK_MSG	         "  NETMASK:     %d.%d.%d.%d\r\n"
#define GW_MSG 		 		 "  GATEWAY:     %d.%d.%d.%d\r\n"
#define MAC_MSG		 		 "  MAC ADDRESS: %x:%x:%x:%x:%x:%x\r\n"
#define GREETING_MSG 		 "Well done guys! Welcome to the IoT world. Bye!\r\n"
#define CONN_ESTABLISHED_MSG "Connection established with remote IP: %d.%d.%d.%d:%d\r\n"
#define SENT_MESSAGE_MSG	 "Sent a message. Let's close the socket!\r\n"
#define WRONG_RETVAL_MSG	 "Something went wrong; return value: %d\r\n"
#define WRONG_STATUS_MSG	 "Something went wrong; STATUS: %d\r\n"
#define LISTEN_ERR_MSG		 "LISTEN Error!\r\n"

void cs_sel() {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET); //CS LOW
}

void cs_desel() {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET); //CS HIGH
}

uint8_t spi_rb(void) {
	uint8_t rbuf;
	HAL_SPI_Receive(&hspi2, &rbuf, 1, 0xFFFFFFFF);
	return rbuf;
}

void spi_wb(uint8_t b) {
	HAL_SPI_Transmit(&hspi2, &b, 1, 0xFFFFFFFF);
}

uint16_t stack = 1024;
/* --Project includes. */
Application::Application() /*:
		m_webserverTask("WebserverTask",stack, osPriorityNormal)*/
{
	uint8_t retVal, sockStatus;
	int16_t rcvLen;
	uint8_t rcvBuf[20], bufSize[] = {2, 2, 2, 2};

  // TODO change to printf only.
	PRINT_HEADER();

	reg_wizchip_cs_cbfunc(cs_sel, cs_desel);
	reg_wizchip_spi_cbfunc(spi_rb, spi_wb);

	wizchip_init(bufSize, bufSize);
	wiz_NetInfo netInfo = { .mac 	= {0x00, 0x08, 0xdc, 0xab, 0xcd, 0xef},	// Mac address
	                          .ip 	= {192, 168, 2, 192},					// IP address
	                          .sn 	= {255, 255, 255, 0},					// Subnet mask
	                          .gw 	= {192, 168, 2, 1}};					// Gateway address
	wizchip_setnetinfo(&netInfo);
	wizchip_getnetinfo(&netInfo);
  // TODO printf all the network communication
	PRINT_NETINFO(netInfo);

	reconnect:
	  /* Open socket 0 as TCP_SOCKET with port 5000 */
	  if((retVal = socket(0, Sn_MR_TCP, 5000, 0)) == 0) {
		  /* Put socket in LISTEN mode. This means we are creating a TCP server */
		  if((retVal = listen(0)) == SOCK_OK) {
			  /* While socket is in LISTEN mode we wait for a remote connection */
			  while(sockStatus = getSn_SR(0) == SOCK_LISTEN)
				  HAL_Delay(100);
			  /* OK. Got a remote peer. Let's send a message to it */
			  while(1) {
				  /* If connection is ESTABLISHED with remote peer */
				  if(sockStatus = getSn_SR(0) == SOCK_ESTABLISHED) {
					  uint8_t remoteIP[4];
					  uint16_t remotePort;
					  /* Retrieving remote peer IP and port number */
					  getsockopt(0, SO_DESTIP, remoteIP);
					  getsockopt(0, SO_DESTPORT, (uint8_t*)&remotePort);
					  sprintf(msg, CONN_ESTABLISHED_MSG, remoteIP[0], remoteIP[1], remoteIP[2], remoteIP[3], remotePort);
					  PRINT_STR(msg);
					  /* Let's send a welcome message and closing socket */
					  if(retVal = send(0, GREETING_MSG, strlen(GREETING_MSG)) == (int16_t)strlen(GREETING_MSG))
						  PRINT_STR(SENT_MESSAGE_MSG);
					  else { /* Ops: something went wrong during data transfer */
						  sprintf(msg, WRONG_RETVAL_MSG, retVal);
						  PRINT_STR(msg);
					  }
					  break;
				  }
				  else { /* Something went wrong with remote peer, maybe the connection was closed unexpectedly */
					  sprintf(msg, WRONG_STATUS_MSG, sockStatus);
					  PRINT_STR(msg);
					  break;
				  }
			  }

		  } else /* Ops: socket not in LISTEN mode. Something went wrong */
			  PRINT_STR(LISTEN_ERR_MSG);
	  } else { /* Can't open the socket. This means something is wrong with W5100 configuration: maybe SPI issue? */
		  sprintf(msg, WRONG_RETVAL_MSG, retVal);
		  PRINT_STR(msg);
	  }

	  /* We close the socket and start a connection again */
	  disconnect(0);
	  close(0);
	  goto reconnect;

	  /* Infinite loop */
	  while (1)
	  {
	  }
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


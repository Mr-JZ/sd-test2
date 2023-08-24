/*
 * systeminfo.cpp
 *
 *  Created on: 28.06.2016
 *      Author: Michael
 */

#include "systeminfo.h"

#include "FreeRTOS.h"
#include "task.h"

//#include "ffconf.h"

#ifdef CORE_M3      // NXP MCUXresso defines CORE_M3
#include "core_cm3.h"
#include "board.h"
#else              // Let's assume we compile for STM32
#include "core_cm4.h"
#endif

#include <cstdio>



namespace Platform {

static char buffer[32];

std::string SystemInformation::rtos() { return "FREERTOS " tskKERNEL_VERSION_NUMBER; }

std::string SystemInformation::fatfs() {
//	sprintf(buffer,"CHAN FAT %06u",_FFCONF);
	return buffer;
}

std::string SystemInformation::build() { return __DATE__ " " __TIME__; }

std::string SystemInformation::compiler() { return __VERSION__; }

std::string SystemInformation::hal() {
#if __CORTEX_M == 3
	sprintf(buffer,"CMSIS %X",__CM3_CMSIS_VERSION);
#elif __CORTEX_M == 4
	sprintf(buffer,"CMSIS %X",__CM4_CMSIS_VERSION);
#else
#error "Unkown Cortex Version"
#endif
	return buffer;
}

std::string SystemInformation::mac() {
#ifdef __BOARD_H_
	Board_ENET_GetMacADDR((uint8_t*)buffer);
#else
	sprintf(buffer,"Not available");
#endif
	return std::string("MAC ADDR ") + buffer;
}

void SystemInformation::print() {
		printf("%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n",
				rtos().c_str(),fatfs().c_str(),compiler().c_str(),hal().c_str(),build().c_str(),mac().c_str());
}


}

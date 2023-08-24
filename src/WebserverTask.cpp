/*
 * ReglerTask.cpp
 *
 * Created on 18.07.2023
 * 		Author: Meese
 */

#include <cstdlib>

#include "FreeRTOS.h"
#include "../template/stm32facade.h"

#include "WebserverTask.h"
#include "socket.h"
#include "httpServer.h"
#include "loopback.h"
#include "webpage.h"

using namespace Platform::BSP;
#define MAX_HTTPSOCK	6
#define DATA_BUF_SIZE 1024*6
uint8_t socknumlist[] = {2, 3, 4, 5, 6, 7};
uint8_t RX_BUF[DATA_BUF_SIZE];
uint8_t TX_BUF[DATA_BUF_SIZE];
WebserverTask::WebserverTask(const char *const name, uint16_t stackDepth,
		osPriority priority, bool immidiateStart) :
		Task(name, stackDepth, priority, immidiateStart) {

}



void WebserverTask::m_task() {
	httpServer_init(RX_BUF, TX_BUF, MAX_HTTPSOCK, socknumlist);
	reg_httpServer_cbfunc(NULL, NULL);
	reg_httpServer_webContent((uint8_t *)"index.html", (uint8_t *)index_page);
	while (1) {
		for(uint8_t i = 0; i < MAX_HTTPSOCK; i++){
			httpServer_run(i);
		}
		loopback_tcps(0, RX_BUF, 5000);
		// LwIP-Aufgaben bearbeiten
		//sys_check_timeouts();
	}

}




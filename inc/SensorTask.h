#ifndef SensorTask_H_
#define SensorTask_H_

#include "FreeRTOS.h"
#include <PeriodicTaskBase.h>
#include "../template/stm32facade.h"
class SensorTask: public RTOS::PeriodicTaskBase{
	//Todo: messageQueue definieren
	osMessageQId sensorMessageId;
public:
	SensorTask(const char *const name, uint16_t stackDepth,osPriority priority,
			bool immidiateStart, osMessageQId _SensorMessageId);
	void m_task();
};

#endif /* BALANCER_H_ */

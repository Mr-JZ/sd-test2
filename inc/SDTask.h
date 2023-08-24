/*
 * SDTask.h
 *
 *  Created on: 28.07.2023
 *      Author: tobeh
 */

#ifndef SDTask_H_
#define SDTask_H_
#include <TaskBase.h>
#include "fatfs.h"

#define	SD_CS_GPIO_PORT			GPIOB
#define SD_CS_PIN			GPIO_PIN_5


class SDTask: public RTOS::Task{
	FIL file; 		//File handle
public:
	SDTask(const char * const name,
            uint16_t    stackDepth,
			osPriority priority,
            bool        immidiateStart);
	void write_to_file(const char* filename, const char* data);
	void read_from_file(const char* filename, char* buffer, UINT bufferSize);
    void m_task();
};
#endif /* SDTask_H_ */

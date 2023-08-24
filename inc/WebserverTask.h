#ifndef WebserverTask_H_
#define WebserverTask_H_
#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "lwip/tcp.h"
#include <TaskBase.h>


class WebserverTask: public RTOS::Task{
public:
	WebserverTask(const char * const name,
            uint16_t    stackDepth,
            osPriority  priority,
            bool        immidiateStart);
    void m_task();
};
#endif /* WebserverTask_H_ */

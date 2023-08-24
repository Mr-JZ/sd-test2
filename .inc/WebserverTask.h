#ifndef WebserverTask_H_
#define WebserverTask_H_
#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "lwip/tcp.h"
#include <PeriodicTaskBase.h>

class WebserverTask: public RTOS::PeriodicTaskBase{
public:
	WebserverTask(const char * const name,
            uint16_t    stackDepth,
            osPriority  priority,
            bool        immidiateStart);
    void m_task();
    err_t http_server_callback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
};
#endif /* WebserverTask_H_ */

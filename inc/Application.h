  /*
 * Application.h
 *
 *  Created on: 03.11.2016
 *      Author: Wuebbelmann
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_



/*#include "WebserverTask.h"*/
#include "WebserverTask.h"
#include "SDTask.h"
typedef int32_t Regel_t ;

class Application {
public:
    Application();

private:
    // TODO: Add your Tasks

//    WebserverTask m_webserverTask;
    SDTask m_sdTask;
    Application(const Application&)  = delete;
    Application(const Application&&) = delete;
    Application operator=(const Application &) = delete;
};

#endif /* APPLICATION_H_ */

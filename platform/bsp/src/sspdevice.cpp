/*
 * sspdevice.cpp
 *
 *  Created on: 21.06.2016
 *      Author: Michael
 */

#include "stm32l4xx_hal.h"

/* --Check if SPI is enabled. */
#ifdef HAL_SPI_MODULE_ENABLED

#include "sspdevice.h"


#ifdef DEBUG
//#define LOG_SSP
#define DEBUG_SSP
#include <cstdio>

#endif


namespace Platform::BSP {



SSPDevice::SSPDevice(SPI_HandleTypeDef* intf, Platform::BSP::PortPin select):
        interface(intf), ssel(select) {}

SSPDevice::SSPDevice(SPI_HandleTypeDef* intf, uint8_t port, uint8_t pin):
    interface(intf),
    ssel(Platform::BSP::PortPin(static_cast<Platform::BSP::Port::Select>(port),
                                static_cast<Platform::BSP::Pin::BitMask>(1<<pin)))
     {}

bool SSPDevice::read(uint8_t* buffer, uint32_t& len) const {


    /* --Run read transfer. */
    acquire();
    HAL_StatusTypeDef stat = HAL_SPI_Receive(interface, buffer, len, 0xFFFF);
    release();

 #ifdef LOG_SSP
    printf("\x1b[33mSSP (%d,%d) @ 0X%02X <--",(unsigned)ssel.getPort(),(unsigned)ssel.getPin(),(unsigned)sym_interface);
    for(uint32_t i=0;i<len;i++)
        printf(" %02X",(unsigned)buffer[i]);
    printf(" %s\x1b[0m\r\n",  HAL_OK == stat ? "\x1b[32mOK." : "\x1b[31mFAILED!");
#endif

#ifdef DEBUG_SSP
    if(!(HAL_OK == stat))
    {
        fprintf(stderr,"*** %s %d error SPI read access!\n", __FILE__, __LINE__);
    }
#endif
    return HAL_OK == stat;
}


bool SSPDevice::write(uint8_t* buffer, uint32_t& len) const {
    /* --Run write transfer. */
    acquire();
    HAL_StatusTypeDef stat = HAL_SPI_Transmit(interface, buffer, len,  0xFFFF);
    release();

#ifdef LOG_SSP
    printf("\x1b[33mSSP (%d,%d) @ 0X%02X -->",(unsigned)ssel.getPort(),(unsigned)ssel.getPin(),(unsigned)sym_interface);
    for(uint32_t i=0;i<len;i++)
        printf(" %02X",(unsigned)buffer[i]);
    printf(" %s\x1b[0m\r\n",  HAL_OK == stat ? "\x1b[32mOK." : "\x1b[31mFAILED!");
#endif

#ifdef DEBUG_SSP
    if(!(HAL_OK == stat))
    {
        fprintf(stderr,"*** %s %d error SPI read access!\n", __FILE__, __LINE__);
    }
#endif

    return  HAL_OK == stat;
}

bool SSPDevice::write(uint8_t value) const {
    uint32_t len=1;
    return write(&value,len);
}

bool SSPDevice::assignLockFct(LockFctType l,LockFctType ul) {
    lock   = l;
    unlock = ul;
    return true;
}


void SSPDevice::acquire() const {
    if (lock)      lock();
    ssel.clear();
}


void SSPDevice::release() const {
    ssel.set();
    if (unlock)    unlock();
}


}  // namespace BSP
#endif


#include "stm32l4xx_hal.h"

/* --Check if I2C is enabled. */
#ifdef HAL_I2C_MODULE_ENABLED

#include "i2cdevice.h"

/* --undef if read/write on I2C should not be printed. */
#ifdef DEBUG
#include <cstdio>
//#define LOG_I2C
#define DEBUG_I2C
#endif

namespace Platform::BSP {


I2CDevice::I2CDevice(I2C_HandleTypeDef* ifc, uint8_t addr, uint8_t dc): hi2c(ifc), address(addr) {}


bool I2CDevice::read(uint8_t* buffer, uint32_t& len) const {
    /* --Read buffer. */
    if (lock)      lock();
    HAL_StatusTypeDef received = HAL_I2C_Master_Receive(hi2c,address<<1,buffer,len, 0xFFFF);
    if (unlock)    unlock();
#ifdef LOG_I2C
    printf("\x1b[35mI2C 0X%02X @ 0X%02X \x1b[36m<--",(unsigned)address,(unsigned)interface);
    for(uint32_t i=0;i<len;i++)
        printf(" %02X",(unsigned)buffer[i]);
    printf(" %s\x1b[0m\r\n",  received == HAL_OK ? "\x1b[32mOK." : "\x1b[31mFAILED!");
#endif
//    len=hi2c->XferCount;   // STM Driver does not return number of received bytes
#ifdef DEBUG_I2C
    if(!(received == HAL_OK))
    {
        fprintf(stderr,"*** %s %d error I2C read access!\n", __FILE__, __LINE__);
    }
#endif
    return (HAL_OK == received);
}

bool I2CDevice::write(uint8_t* buffer, uint32_t& len) const {

    /* --Write buffer. */
    if (lock)    lock();
    HAL_StatusTypeDef sent = HAL_I2C_Master_Transmit(hi2c, address<<1, buffer, len, 0xFFFF);
    uint32_t errorCode = hi2c->ErrorCode; // might get overwritten
    if (unlock)    unlock();
#ifdef LOG_I2C
    printf("\x1b[35mI2C 0X%02X @ 0X%02X -->",(unsigned)address,(unsigned)interface);
    for(uint32_t i=0;i<len;i++)
        printf(" %02X",(unsigned)buffer[i]);
    printf(" %s\x1b[0m\r\n",  sent == HAL_OK? "\x1b[32mOK." : "\x1b[31mFAILED!");
#endif
    //len=hi2c->XferCount;    // STM Driver does not return number of received bytes

    if(!(sent == HAL_OK))  // might not be an error, device needs time to handle data
    {
        if (!(errorCode & HAL_I2C_ERROR_AF))
        {
#ifdef DEBUG_I2C
          fprintf(stderr,"*** %s %d error I2C write access!\n", __FILE__, __LINE__);
#endif
          HAL_I2C_Init(hi2c);
        }
    }


    return (HAL_OK == sent);
}

bool I2CDevice::set(uint8_t cmd, uint8_t value) const {
    uint32_t len=2;
    uint8_t buffer[len];
    buffer[0]=cmd;
    buffer[1]=value;
    /* --Write 2 bytes at once. */
    if (write(buffer,len))
        return (2==len);
    return false;
}

bool I2CDevice::set(uint8_t cmd, uint16_t value) const {
    uint32_t len=3;
    uint8_t buffer[len];
    buffer[0]=cmd;
    buffer[1]=value;
    buffer[2]=value>>8;
    /* --Write 3 bytes at once. */
    if (write(buffer,len))
        return (3==len);
    return false;
}

bool I2CDevice::set(uint8_t cmd, uint32_t value) const {
    uint32_t len=5;
    uint8_t buffer[len];
    buffer[0]=cmd;
    buffer[1]=value;
    buffer[2]=value>>8;
    buffer[3]=value>>16;
    buffer[4]=value>>24;
    /* --Write 5 bytes at once. */
    if (write(buffer,len))
        return (5==len);
    return false;
}

bool I2CDevice::get(uint8_t cmd, uint8_t& value) const {
    uint32_t txLen=1, rxLen=1;
    /* --Write/read transfer with single bytes. */
    if (transfer(&cmd,txLen,&value,rxLen))
        return (1==txLen && 1==rxLen);
    return false;
}

bool I2CDevice::get(uint8_t cmd, uint16_t& value) const {
    uint32_t txLen=1, rxLen=2;
    /* --Write/read transfer with single bytes. */
    if (transfer(&cmd,txLen,(uint8_t*)&value,rxLen))
        return (1==txLen && 2==rxLen);
    return false;
}

bool I2CDevice::get(uint8_t cmd, uint32_t& value) const {
    uint32_t txLen=1, rxLen=4;
    /* --Write/read transfer with single bytes. */
    if (transfer(&cmd,txLen,(uint8_t*)&value,rxLen))
        return (1==txLen && 4==rxLen);
    return false;
}

bool I2CDevice::assignLockFct(LockFctType l,LockFctType ul) {
    lock   = l;
    unlock = ul;
    return true;
}


bool I2CDevice::transfer(uint8_t* txBuf, uint32_t& txLen, uint8_t* rxBuf, uint32_t& rxLen) const {
    bool retvalue=false;

    if (true == write(txBuf, txLen))
    {
        if(rxLen)
        {
            if(true == read (rxBuf, rxLen))
            {
                retvalue = true;
            }
        }
        else
        {
            retvalue = true;
        }
    }

    return retvalue;
}

} /* --Namespace BSP. */
#endif

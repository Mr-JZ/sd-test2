/*
 * LM411.cpp
 *
 *  Created on: 10.12.2020
 *      Author: Wuebbelmann
 */


#include "stm32l4xx_hal.h"

/* --Check if DAC is enabled. */
#ifdef HAL_DAC_MODULE_ENABLED

#include "lm4811.h"
#include "dac.h"

namespace Platform::BSP {

// DAC must be enabled in Cube MX and define must be set in main.h

uint32_t LM4811::s_delayFunc(uint32_t d)
{
    volatile uint32_t i = 0;
    uint32_t          waitTime = d*0x1FFFF;
    for (i = 0; i < waitTime; ++i) {}
    return 0;
}


LM4811::LM4811(const Platform::BSP::PortPin& shutdown,
        	   const Platform::BSP::PortPin& clock,
               const Platform::BSP::PortPin& upd,
			   DAC_HandleTypeDef* def,
               Dac::Dac_e    dac,
               delayFunc delay):
    shut(shutdown),
    clck(clock),
    upDown(upd),
    delayMs(delay),
    dac(def,dac)
{
    //Platform::BSP::Dac::initialize();
    shutDown(false);  // power up
    //setVolume(0); // No call to delayed method allowed!
}

void LM4811::shutDown(bool v)
{
    if(v)     shut.set();  // power down
    else    shut.clear();  // power up
}

void LM4811::increaseVolume()
{
     if(volume < 15)
     {
        upDown.set();
        delayMs(2);
        clck.set();
        delayMs(2);
        clck.clear();
        ++volume;
     }
}
void LM4811::decreaseVolume()
{
    if(volume != 0)
    {
        upDown.clear();
        delayMs(2);
        clck.set();
        delayMs(2);
        clck.clear();
        --volume;
    }
}
void LM4811::setVolume(uint8_t vol)
{
    if(0 == vol)   // force volume to 0
    {
       volume = 16;
       do
       {
           decreaseVolume();
       }
       while(volume);
    }
    else
    {
        if (vol  > 15) vol = 15;
        if(vol > volume)
        {
            while(volume != vol)
            {
                increaseVolume();
            }
        }
        else
        {
            while(volume != vol)
            {
               decreaseVolume();
            }
        }
    }
}

void LM4811::out(uint16_t val)
{
    dac.setAnalog(val);
}


} /* namespace Framework */
#endif

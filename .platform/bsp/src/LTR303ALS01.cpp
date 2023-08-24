/*
 * LTR303ALS01.cpp
 *
 *  Created on: 16.09.2021
 *      Author: Wuebbelmann
 */
/* --Check if I2C is enabled. */
#include "stm32l4xx_hal.h"
#ifdef HAL_I2C_MODULE_ENABLED

#include <LTR303ALS01.h>

namespace Platform {

namespace BSP {


LTR303ALS01::LTR303ALS01(I2C_HandleTypeDef* ifc, uint8_t arr):I2CDevice(ifc,arr) {}

bool LTR303ALS01::enable(Gain gain)
{

    uint8_t newgain = static_cast<uint8_t>(gain);
    uint8_t reset = 0;
    uint8_t alsMode = 1;
    uint8_t value=(newgain << 2)  +
                  (reset   << 1)  +
                  (alsMode << 0);

    return cmd(Register::ALS_CONTR,value);

}


bool LTR303ALS01::disable() {

    uint8_t control= 0;

    get(static_cast<uint8_t>(Register::ALS_CONTR),control);
    control &= ~(0xF1); // set mode to standby
    return cmd(Register::ALS_CONTR,control);

}


bool LTR303ALS01::raw(Channel chan, uint16_t& value) const {
    uint32_t data = 0;
    uint8_t reg=static_cast<uint8_t>(Register::ALS_DATA_CH1_0);
    bool ret =  get(reg,data);
    switch (chan)
    {
    case Channel::CH0:
        value = ((data & 0xFF000000) >> 24) + ((data & 0x00FF0000) >> 16);
        break;
    case Channel::CH1:
        value = (data & 0xFF) + (data & 0xFF00);
        break;
    default:
        value = 0;
    }
    return ret;
}


bool LTR303ALS01::raw(uint32_t& value) const {
    uint8_t reg=static_cast<uint8_t>(Register::ALS_DATA_CH1_0);
    bool ret =  get(reg,value);
    return ret;
}



} /* --BSP */
} /* --Platform */
#endif // if defined HAL_I2C_MODULE_ENABLED

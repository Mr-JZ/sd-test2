#include "stm32l4xx_hal.h"
/* --Check if SPI is enabled. */
#if (defined HAL_SPI_MODULE_ENABLED || defined HAL_I2C_MODULE_ENABLED)
#include "lis3dh.h"

#ifdef DEBUG
#include <cstdio>
#endif


namespace Platform {

namespace BSP {

#ifdef HAL_SPI_MODULE_ENABLED
template<>
LIS3DH::LIS3DHTEMPLATE(SPI_HandleTypeDef* intf, Platform::BSP::PortPin select):
         SSPDevice(intf,select) {}

template<>
bool LIS3DH::raw(int16_t& x, int16_t& y, int16_t& z) const {
    /* --Check if new data is available. */
    while (!GETBIT(status(), ZYXDA));

    bool ret = true;
    uint32_t len=7;
    uint8_t buffer[7]; // 2 bytes per channel + register
    buffer[0]=static_cast<uint8_t>(Register::OUT_X_L);
    SETBIT(buffer[0],READBIT);   // set read mode!
    SETBIT(buffer[0],AUTOINC);  // set multiple reads!

    ret = read(buffer, len);
    if(ret)
    {
        uint8_t count = 1;
        x = buffer[count] + (buffer[count+1] << 8);
        count += 2;
        y = buffer[count] + (buffer[count+1] << 8);
        count += 2;
        z = buffer[count] + (buffer[count+1] << 8);

        fit(x);
        fit(y);
        fit(z);
    }
    return ret;
}


#endif

#ifdef HAL_I2C_MODULE_ENABLED
template<>
LIS3DHI2C::LIS3DHTEMPLATE(I2C_HandleTypeDef* intf, uint8_t addr):
         I2CDevice(intf,addr)
{
#if 0    // HW Settings on Baseboard. Set JP 4-8 to I2C
    DigitalInOut ssel(port, pin, DigitalInOut::Direction::OUTPUT);
    ssel.set();   // enable I2C

    // lower Adress bit is A0 / SDO/ MISO Line:
    DigitalInOut a0(GPIOB, PortPin::Pins::PIN14, DigitalInOut::Direction::OUTPUT);
    a0.clear();
#endif
#ifdef DEBUG
    bool ret = true;
    // is Address valid?
    for(uint8_t i = 0; i < 0x80; ++i)
    {
        address = i;
        uint8_t val;
        ret = ctrl(Register::WHO_AM_I, val);
        if(ret) printf("Add: 0x%x Id: 0x%x\n", (int)i, (int)val);
    }
    address = addr;
#endif
}

template<>
bool LIS3DHI2C::raw(int16_t& x, int16_t& y, int16_t& z) const {
    /* --Check if new data is available. */

    while (!GETBIT(status(), ZYXDA));

    bool ret = true;
    uint32_t len=1;
    uint8_t buffer[6]; // 2 bytes per channel
    buffer[0]=static_cast<uint8_t>(Register::OUT_X_L);

    SETBIT(buffer[0],READBIT); // required for continuous address increment
                               // in multiple data read
    write(buffer, len); // send command

    len = 6;
    ret = read(buffer, len);
    if(ret)
    {
        uint8_t count = 0;
        x = buffer[count] + (buffer[count+1] << 8);
        count += 2;
        y = buffer[count] + (buffer[count+1] << 8);
        count += 2;
        z = buffer[count] + (buffer[count+1] << 8);

        fit(x);
        fit(y);
        fit(z);
    }
    return ret;
}


#endif

}  // namespace BSP
}  //
#endif

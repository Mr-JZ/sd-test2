#ifndef LIS3DH_H
#define LIS3DH_H


#ifdef HAL_SPI_MODULE_ENABLED
#include "sspdevice.h"
#endif
#ifdef HAL_I2C_MODULE_ENABLED
#include "i2cdevice.h"
#endif
#include "digitalinout.h"

#define SETBIT(reg, bit)   do {(reg) |=  (bit);} while(0)
#define CLEARBIT(reg, bit) do {(reg) &= ~(bit);} while(0)
#define GETBIT(val, bit)   (((val) & (bit)) != 0)

#define READBIT  (0x1 << 7)
#define AUTOINC  (0x1 << 6)

// CTRL_REG1
#define Xen   (0x01 << 0)
#define Yen   (0x01 << 1)
#define Zen   (0x01 << 2)
#define LPen  (0x01 << 3)

#define ODR(x)   (((x) & 0x0F) << 4)

// CTRL_REG4
#define SIM   (0x01 << 0)          // SIM = 0, 4 wire Interface
#define ST(x) (((x) & 0x03) << 1)  // ST  = 0, self test disabled
#define HR    (0x01 << 3)          // HR = 0. disable, 1 enable
#define FS(x) (((x) & 0x03) << 4)  // FS G selection
#define BLE   (0x01 << 6)          // BLE = 0. Endian LSB @ lower address
#define BDU   (0x01 << 7)          // BDU = 0. Continues update

// Bits of STATUS_REG:
#define XDA   (0x01 << 0)           // X-axis new data available
#define YDA   (0x01 << 1)           // Y-axis new data available
#define ZDA   (0x01 << 2)           // Z-axis new data available
#define ZYXDA (0x01 << 3)           // X, Y, Z-axis new data available
#define XOR   (0x01 << 4)           // X-axis data overrun
#define YOR   (0x01 << 5)           // Y-axis data overrun
#define ZOR   (0x01 << 6)           // Z-axis data overrun
#define ZYXOR (0x01 << 7)           // X, Y, Z-axis data overrun



namespace Platform {

namespace BSP {

/*! @brief Interface class to EA base board accelerator.
 *
 *  This class defines the interface to LI3DH mounted on
 *  the base board (see LIS3DH hardware documentation for details).
 *
 *  \tparam U Class of HW Interface, e.g I2CDevice or SSPDevice
 *
 */
template<typename U>
class LIS3DHTEMPLATE : public U {
protected:
    /**
     * Internal register set.
     */
    enum class Register : uint8_t {
        STATUS_REG_AUX = 0x07,  //!< STATUS_REG_AUX
        OUT_ADC1_L,             //!< OUT_ADC1_L
        OUT_ADC1_H,             //!< OUT_ADC1_H
        OUT_ADC2_L,             //!< OUT_ADC2_L
        OUT_ADC2_H,             //!< OUT_ADC2_H
        OUT_ADC3_L,             //!< OUT_ADC3_L
        OUT_ADC3_H,             //!< OUT_ADC3_H

        WHO_AM_I = 0x0F,        //!< WHO_AM_I  dummy register

        CTRL_REG0 = 0x1E,       //!< CTRL_REG0
        TEMP_CFG_REG,           //!< TEMP_CFG_REG
        CTRL_REG1,              //!< CTRL_REG1
        CTRL_REG2,              //!< CTRL_REG2
        CTRL_REG3,              //!< CTRL_REG3
        CTRL_REG4,              //!< CTRL_REG4
        CTRL_REG5,              //!< CTRL_REG5
        CTRL_REG6,              //!< CTRL_REG6
        REFERENCE,              //!< REFERENCE
        STATUS_REG,             //!< STATUS_REG
        OUT_X_L,                //!< OUT_X_L
        OUT_X_H,                //!< OUT_X_H
        OUT_Y_L,                //!< OUT_Y_L
        OUT_Y_H,                //!< OUT_Y_H
        OUT_Z_L,                //!< OUT_Z_L
        OUT_Z_H,                //!< OUT_Z_H

        FIFO_CTRL_REG,          //!< FIFO_CTRL_REG
        FIFO_SRC_REG,           //!< FIFO_SRC_REG

        INT1_CFG,               //!< INT1_CFG
        INT1_SRC,               //!< INT1_SRC
        INT1_THS,               //!< INT1_THS
        INT1_DURATION,          //!< INT1_DURATION
        INT2_CFG,               //!< INT2_CFG
        INT2_SRC,               //!< INT2_SRC
        INT2_THS,               //!< INT2_THS
        INT2_DURATION,          //!< INT2_DURATION

        CLICK_CFG,              //!< CLICK_CFG
        CLICK_SRC,              //!< CLICK_SRC
        CLICK_THS,              //!< CLICK_THS
        TIME_LIMIT,             //!< TIME_LIMIT
        TIME_LATENCY,           //!< TIME_LATENCY
        TIME_WINDOW,            //!< TIME_WINDOW
        ACT_THS,                //!< ACT_THS
        ACT_DUR                 //!< ACT_DUR
    };

public:
    /*! @brief Mode of operation of LI3DH. */
    enum class Mode:  uint8_t {
        LOWPOWER  = 0,   /*! <Low Power,        8 bit data output */
        NORMAL,          /*! <Normal mode,     10 bit data output */
        HighRes          /*! <High resolution, 12 bit data output */
    };


    /*! @brief timings of LI3DH. */
    enum class Timing:  uint8_t {
        PowerDownMode  = 0,   /*! <PowerDown */
        NORMAL_1,             /*! <HR/Normal/Low-power mode (1Hz)   */
        NORMAL_10,            /*! <HR/Normal/Low-power mode (10Hz)  */
        NORMAL_25,            /*! <HR/Normal/Low-power mode (25Hz)  */
        NORMAL_50,            /*! <HR/Normal/Low-power mode (50Hz)  */
        NORMAL_100,           /*! <HR/Normal/Low-power mode (100Hz) */
        NORMAL_200,           /*! <HR/Normal/Low-power mode (200Hz) */
        NORMAL_400,           /*! <HR/Normal/Low-power mode (400Hz) */
        LowPower,             /*! <Low-power mode (1.6kHz)          */
        NORMAL_1344           /*! <HR/Normal (1.344kHz) Low power (5.376KkHz)*/
    };

    /*! @brief Range of measurement. */
    enum class GRange {
        RANGE_2G  /*! <[-2g,. ..,+2g] Range of measurement. */,
        RANGE_4G  /*! <[-4g,. ..,+4g] Range of measurement. */,
        RANGE_8G  /*! <[-8g,. ..,+8g] Range of measurement. */,
        RANGE_16G /*! <[-16g, .,+16g] Range of measurement. */
    };

#ifdef HAL_SPI_MODULE_ENABLED
    /*! @brief Standard constructor.
     *  @param[in] port defines the port identifier of slave select signal
     *  @param[in] pin defines the pin of slave select signal
     *  @param[in] ifc defines SPI bus.
     */
    LIS3DHTEMPLATE(SPI_HandleTypeDef* intf, Platform::BSP::PortPin select);
#endif

#ifdef HAL_I2C_MODULE_ENABLED
    /*! @brief Standard constructor.
     *  \Note: Device requires High signal at SSEL to enable I2C! See JP4-8
     *  @param[in] addr defines the i2c addressel
     *  @param[in] ifc defines I2C bus.
     */
    LIS3DHTEMPLATE(I2C_HandleTypeDef* intf, uint8_t addr);
#endif

    ~LIS3DHTEMPLATE() = default;
    /*! @brief Set Mode of Operation.
     *  @param[in] m defines the mode.
     *  @param[in] gr defines g-range.
     *  @return @c true if mode was set correctly.
     */
    bool control(Mode m = Mode::NORMAL, GRange gr = GRange::RANGE_2G);

    /*! @brief Set timing of Operation.
     *  @param[in] t defines the mode.
     *  @return @c true if mode was set correctly.
     */
    bool setTiming(Timing t = Timing::NORMAL_10) const;


    /*! @brief Read Data from Sensor.
     *  @param[out] x acceleration in x direction.
     *  @param[out] y acceleration in y direction.
     *  @param[out] z acceleration in z direction.
     *  @return @c true if read was done correctly.
     */
    bool raw(int16_t& x, int16_t& y, int16_t& z) const;

    /*! @brief Read X Data from Sensor.
     *  @param[out] x acceleration in x direction.
     *  @return @c true if read was done correctly.
     */
    bool getXacc(int16_t&x) const;
    /*! @brief Read Y Data from Sensor.
     *  @param[out] y acceleration in y direction.
     *  @return @c true if read was done correctly.
     */
    bool getYacc(int16_t&y) const;
    /*! @brief Read Z Data from Sensor.
     *  @param[out] z acceleration in z direction.
     *  @return @c true if read was done correctly.
     */
    bool getZacc(int16_t&z) const;



    /*! @brief read status register 0x09.
     *  @return content of status register. */
    uint8_t status() const;

    /**
     * Send command to device (1 Byte).
     * @param cmd defines the command (Can be used with enum class values of derived classes).
     * @param value defines the value corresponding to given command.
     * @return @c true if operation succeeded or @c false
     */
    template<typename T> bool cmd(T cmd, uint8_t value) const;


    /**
     * Receive control value from device (1 Byte).
     * @param ctrl defines control register of device.
     * @param value defines control value
     * @return @c true if write/read access succeeded or @c false.
     */
    template<typename T> bool ctrl(T ctrl, uint8_t& value) const;

    /**
     * Receive control value from device (2 Byte).
     * @param ctrl defines control register of device.
     * @param value defines control value
     * @return @c true if write/read access succeeded or @c false.
     */
    template<typename T> bool ctrl(T ctrl, uint16_t& value) const;

    /**
     * Enable temperature measurement on ADC channel 3
     * @Note: The LIS3DH provides no absolute temperature but only a \n
     *  delta. Therefore the user has to provide an ambient temperature, the \n
     *  measured temperature is relative to this temperature.
     *
     */
    void openTemp() const;

    /**
     * Provides the sensor with an ambient temperature at the beginning
     * of the measurement. The measured temperature takes this temperature
     * as the "fixed point"
     * @param[in] t ambient temperature, default is 20 degrees celsius
     */
    void setAmbientTemperature(int16_t t = 20);

    /**
     * disable temperature measurement. Sensor is disconnected from ADC3
     */
    void closeTemp() const;

    /**
     * returns temperature in degrees celsius.
     */
    int16_t getTemperature(void) const;

private:

    void fit(int16_t& value) const;
    Mode mode = Mode::NORMAL;
    int16_t ambientTemperature = 20;
    int16_t tempOffset = 0;
};

#ifdef HAL_SPI_MODULE_ENABLED
/*! @brief Template implementation of \ref LIS3DHTEMPLATE for SPI
 *
 */
using LIS3DH=LIS3DHTEMPLATE<Platform::BSP::SSPDevice>;
#endif
#ifdef HAL_I2C_MODULE_ENABLED
using LIS3DHI2C=LIS3DHTEMPLATE<Platform::BSP::I2CDevice>;
#endif

/**
 * Implementation part:
 */


template<typename U>
bool LIS3DHTEMPLATE<U>::control(Mode m, GRange gr)  {

    bool ret = true;
    /* --Get current mode. */
    uint8_t ctrl_reg1 = 0;
    uint8_t ctrl_reg4 = 0;

     if (ret) ret = ctrl(Register::CTRL_REG1, ctrl_reg1);
    // if (ret) ret = ctrl(Register::CTRL_REG4, ctrl_reg4);
     ctrl_reg1 = 0;

    // Default:
    SETBIT(ctrl_reg1, Xen);
    SETBIT(ctrl_reg1, Yen);
    SETBIT(ctrl_reg1, Zen);

    CLEARBIT(ctrl_reg4, SIM);
    CLEARBIT(ctrl_reg4, ST(3));
    CLEARBIT(ctrl_reg4, BLE);
    CLEARBIT(ctrl_reg4, BDU);
    /* --Ok? */
    if (ret) {
        /* --Set mode  bits in CTRL_REG1[3] and CTRL_REG4[3] */
        uint8_t ctrl_reference = 0;
        switch (m) {
        case Mode::LOWPOWER:
            SETBIT(ctrl_reg1, LPen);
            CLEARBIT(ctrl_reg4, HR);
            break;
        case Mode::NORMAL:
            CLEARBIT(ctrl_reg1, LPen);
            CLEARBIT(ctrl_reg4, HR);
            ctrl(Register::REFERENCE, ctrl_reference);
            break;
        case Mode::HighRes:
            CLEARBIT(ctrl_reg1, LPen);
            SETBIT(ctrl_reg4, HR);
            break;
        default: // switch to normal mode
            CLEARBIT(ctrl_reg1, LPen);
            CLEARBIT(ctrl_reg4, HR);

        }
        mode = m;
        /* --Set g-range CTRL_REG4[4:5] 2 bits. */
        CLEARBIT(ctrl_reg4, FS(3));  // clear bits
        SETBIT(ctrl_reg4, FS(static_cast<uint8_t>(gr)));  // clear bits

        if (ret)  ret = cmd(Register::CTRL_REG4, ctrl_reg4);
        if (ret)  ret = cmd(Register::CTRL_REG1, ctrl_reg1);

        if (ret)  ret = setTiming(Timing::NORMAL_10);
/* FIXME: Dirty Workaround!!!! This fix uses an reserved Register!!!!!
 *        Test showed that the LIS3DH may not produces a x-axis signal
 *        This happened with direct soldered devices when the content of
 *        reserved register 0x10 is unequal 0x9C, which might happen after
 *        reset.
 *        Devices on Adafruit boards have a value of 0x1d in register 0x10
 *        and are not working with other values
 */
        uint8_t reservedValue = 0;
        ctrl(0x10, reservedValue);
        if (0x9C != reservedValue && 0x1D != reservedValue)
        {
            cmd(0x10, 0x9C);
        }

    }

    /* --Done. */
    return ret;
}

template<typename U>
bool LIS3DHTEMPLATE<U>::setTiming(Timing t) const
{
    /* --Get current mode. */
    uint8_t ctrl_reg1 = 0;
    bool ret = ctrl(Register::CTRL_REG1, ctrl_reg1);
    if(ret)
    {
        uint8_t val = static_cast<uint8_t>(t); // Timing contains bit pattern for ODR
        CLEARBIT(ctrl_reg1, ODR(0xF));  // clear bits
        SETBIT(ctrl_reg1, ODR(val));  // set CTRL_REG1[4:7] ODR0-ODR3
        ret = cmd(Register::CTRL_REG1, ctrl_reg1);
    }
    return ret;
}



template<typename U>
uint8_t LIS3DHTEMPLATE<U>::status() const {
    uint8_t value=0xff;
    bool success = ctrl(Register::STATUS_REG,value);
    return success?value: 0x00;
}


template<typename U>
bool LIS3DHTEMPLATE<U>::getXacc(int16_t&x) const
{
    while (!GETBIT(status(), XDA));
    uint8_t buffer[2] = {0}; // 2 bytes per channel + register

    bool    ret = ctrl(Register::OUT_X_L, buffer[0]);
    if(ret) ret = ctrl(Register::OUT_X_H, buffer[1]);
    x = buffer[0] +((uint16_t)buffer[1] << 8 );
    fit(x);
    return ret;
}

template<typename U>
bool LIS3DHTEMPLATE<U>::getYacc(int16_t&y) const
{
	while (!GETBIT(status(), YDA));
	uint8_t buffer[2] = {0}; // 2 bytes per channel + register

    bool    ret = ctrl(Register::OUT_Y_L, buffer[0]);
    if(ret) ret = ctrl(Register::OUT_Y_H, buffer[1]);
    y = buffer[0] +((uint16_t)buffer[1] << 8 );
    fit(y);
    return ret;
}

template<typename U>
bool LIS3DHTEMPLATE<U>::getZacc(int16_t&z) const
{
	while (!GETBIT(status(), ZDA));
	uint8_t buffer[2] = {0}; // 2 bytes per channel + register

    bool    ret = ctrl(Register::OUT_Z_L, buffer[0]);
    if(ret) ret = ctrl(Register::OUT_Z_H, buffer[1]);
    z = buffer[0] +((uint16_t)buffer[1] << 8 );
    fit(z);
    return ret;
}



template<typename U>
void LIS3DHTEMPLATE<U>::openTemp() const
{


    uint8_t config5 = 0xC0;
            //LIS3DHTR_REG_TEMP_ADC_PD_ENABLED |
            //          LIS3DHTR_REG_TEMP_TEMP_EN_ENABLED;

    uint8_t ctrl_reg4 = 0;
    bool ret = true;
    /* --Get current mode. */
    ret = ctrl(Register::CTRL_REG4, ctrl_reg4);
    SETBIT(ctrl_reg4, BDU);
    if (ret)  ret = cmd(Register::CTRL_REG4, ctrl_reg4);

    cmd(Register::TEMP_CFG_REG, config5);
}

template<typename U>
void LIS3DHTEMPLATE<U>::setAmbientTemperature(int16_t t)
{
    ambientTemperature = t;
    tempOffset = 0;
    int16_t act = getTemperature();
    tempOffset = ambientTemperature - act;
}

template<typename U>
void LIS3DHTEMPLATE<U>::closeTemp() const
{
    uint8_t config5 = 0x80;
//                      LIS3DHTR_REG_TEMP_TEMP_EN_DISABLED;

    cmd(Register::TEMP_CFG_REG, config5);
}

template<typename U>
int16_t LIS3DHTEMPLATE<U>::getTemperature(void) const
{
    uint16_t read = 0;
    bool ret = true;

    ret = ctrl(Register::OUT_ADC3_L, read); // / 256;
    (void) ret;
    int16_t result = read;
    // result: 2's complement left-aligned!
    result /= (1<<6);  // remove right 6 bits
//    if (mode == Mode::LOWPOWER)
    {
        result /= 4;   // 1 digit/°C in 8 bit resolution
    }
    result += tempOffset;

    return result;
}




template<typename U>
template<typename T>
bool LIS3DHTEMPLATE<U>::cmd(T cmd, uint8_t value) const{
    uint32_t len=2;
    uint8_t buffer[len];
    buffer[0]=static_cast<uint8_t>(cmd);
    buffer[1]=value;
    /* --Write 2 bytes at once. */

    bool ret =  U::write(buffer,len);
    return ret;
}

template<typename U>

void LIS3DHTEMPLATE<U>::fit(int16_t& value) const
{
    // The value is 2's complement left aligned.
    if (mode == Mode::HighRes)  // 12 bit resolution
    {
        value /= (1<<4);   // remove 4 unused 0 bits on right
    }
    else if (mode == Mode::NORMAL)  // 10 bit resolution
    {
        value /= (1<<6);   // remove 6 unused 0 bits on right
    }
    else if (mode == Mode::LOWPOWER)  // 8 bit resolution
    {
        value /= (1<<8);   // remove 8 unused 0 bits on right
    }
}


// specific methods for SPI or I2C:

#ifdef HAL_SPI_MODULE_ENABLED
template<>
template<typename T>
bool LIS3DH::ctrl(T ctrl, uint8_t& value) const
{
    bool ret = true;
    uint32_t len=2;
    uint8_t buffer[sizeof(value) + 1];
    buffer[0]=static_cast<uint8_t>(ctrl);

    SETBIT(buffer[0],READBIT);  // set read mode!

    if (ret )ret = read((buffer), len);
    if(ret)
    {
       value = buffer[1];
    }

    return ret;
}


template<>
template<typename T>
bool LIS3DH::ctrl(T ctrl, uint16_t& value) const
{
    bool ret = true;
    uint32_t len=3;
    uint8_t buffer[sizeof(value) + 1];
    buffer[0]=static_cast<uint8_t>(ctrl);
    SETBIT(buffer[0],READBIT);   // set read mode!
    SETBIT(buffer[0],AUTOINC);  // set multiple reads!
    ret = read(buffer, len); // send read command
    if (ret)
    {
        value = buffer[1] + (buffer[2] << 8);
    }
    return ret;
}
#endif

#ifdef HAL_I2C_MODULE_ENABLED
template<>
template<typename T>
bool LIS3DHI2C::ctrl(T ctrl, uint8_t& value) const
{
    bool ret = true;
    uint32_t len=1;
    uint8_t buffer[sizeof(value) + 1];
    buffer[0]=static_cast<uint8_t>(ctrl);


    len = 1;
    ret = write(buffer, len); // send command

    if (ret )ret = read((buffer), len);
    if(ret)
    {
       value = buffer[0];
    }

    return ret;
}


template<>
template<typename T>
bool LIS3DHI2C::ctrl(T ctrl, uint16_t& value) const
{
    uint8_t reg = static_cast<uint8_t>(ctrl);
    SETBIT(reg,READBIT);
    return I2CDevice::ctrl(reg, value);
#if 0
    bool ret = true;
    uint32_t len=3;
    uint8_t buffer[sizeof(value) + 1];
    buffer[0]=static_cast<uint8_t>(ctrl);


    len = 1;
    SETBIT(buffer[0],READBIT);
    write(buffer, len); // send command
    len = 2;
    ret = read(buffer, len); // send read command
    if (ret)
    {
        value = buffer[0] + (buffer[1] << 8);
    }
    return ret;
#endif
}
#endif  // HAL_I2C_MODULE_ENABLED

}

}

#endif

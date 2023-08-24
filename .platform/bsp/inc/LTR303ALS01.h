/*
 * LTR303ALS01.h
 *
 *  Created on: 16.09.2021
 *      Author: Wuebbelmann
 */

#ifndef BSP_INC_LTR303ALS01_H_
#define BSP_INC_LTR303ALS01_H_

#include "i2cdevice.h"

namespace Platform {
namespace BSP {

/**
 * This class is an abstraction of the light sensor (see hardware specification).
 */


class LTR303ALS01 : public I2CDevice {


public:
        enum class Gain
        {
            GAIN1X   = 0,   //! Gain 1X  -> 1     lux to  64k lux
            GAIN2X   = 1,   //! Gain 2X  -> 0.5   lux to  32k lux
            GAIN4X   = 2,   //! Gain 4X  -> 0.25  lux to  16k lux
            GAIN8X   = 3,   //! Gain 8X  -> 0.125 lux to   8k lux
            GAIN48X  = 6,   //! Gain 48X -> 0.02  lux to 1.3k lux
            GAIN96X  = 7    //! Gain 96X -> 0.01  lux to  600 lux
        };


        enum class Channel
        {
            CH0,   //! Channel 0
            CH1    //! Channel 1
        };

        /**
         * Constructor.
         * @param ifc defines the I2C bus
         * @param arr defines the I2C address
         */
        LTR303ALS01(I2C_HandleTypeDef* ifc, uint8_t arr =0x29);

        /**
         * Enables the light sensor.
         * @param[in] gain the gain of the sensor
         * @return @c true if enabling was successfully or @c false
         *
         */
        bool enable(Gain gain = Gain::GAIN1X);

        /**
         * Disable the light sensor (not implemented).
         * @return @c true if disabling was successfully or @c false
         */
        bool disable();

        /**
         * Read light sensor.
         * @param[in] channel channel to read.
         * @param value is the variable to store the raw value
         * @return @c true if reading succeeded or @c false
         */
        bool raw(Channel chan, uint16_t& value) const;

        /**
         * Read light sensor.
         *   both channels are read, the lower half is channel1, the upper
         *   half is channel0
         * @param value is the variable to store the raw value
         * @return @c true if reading succeeded or @c false
         */
        bool raw(uint32_t& value) const;



private:
    /**
     * Internal register set.
     */
    enum class Register : uint8_t {
        ALS_CONTR      = 0x80, //! ALS operation control SW reset
        ALS_MEAS_RATE  = 0x85, //! ALS measurement rate in active mode
        PART_ID        = 0x86, //! Part Number ID and Revision ID
        MANUFAC_ID     = 0x87, //! Manufacturer ID
        ALS_DATA_CH1_0 = 0x88, //! ALS measurement CH1 data, lower byte
        ALS_DATA_CH1_1 = 0x89, //! ALS measurement CH1 data, upper byte
        ALS_DATA_CH0_0 = 0x8A, //! ALS measurement CH0 data, lower byte
        ALS_DATA_CH0_1 = 0x8B, //! ALS measurement CH0 data, upper byte
        ALS_STATUS     = 0x8C, //! ALS new data status
        INTERRUPT      = 0x8F, //! Interuppt settings
        ALS_THRES_UP_0 = 0x97, //! ALS interrupt upper threshold, lower byte
        ALS_THRES_UP_1 = 0x98, //! ALS interrupt upper threshold, upper byte
        ALS_THRES_LOW_0= 0x99, //! ALS interrupt lower threshold, lower byte
        ALS_THRES_LOW_1= 0x9A, //! ALS interrupt lower threshold, upper byte
        INTERRUPTPERSIST= 0x9E //! ALS Interrupt persist setting
    };
};

#endif  // #if defined USE I2C1....
}   // namespace BSP
}   // namespace Platform


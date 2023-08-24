#ifndef LIS3DHH_H
#define LIS3DHH_H


#include "sspdevice.h"

namespace Platform {

namespace BSP {

/*! @brief Interface class to EA base board accelerator.
 *
 *  This class defines the interface to MMA7455 mounted on
 *  the EA base board (see MMA7455L hardware documentation for details).
 */


class LIS3DHH : public SSPDevice {
public:

	/**
	 * Internal register set.
	 */
	enum class Register : uint8_t {
		WHO_AM_I = 0x0F,        //!< WHO_AM_I  dummy register

		CTRL_REG1 = 0x20,       //!< CTRL_REG1
		INT1_CTRL,              //!< INT1_CTRL
		INT2_CTRL,              //!< INT2_CTRL
		CTRL_REG4,              //!< CTRL_REG4
		CTRL_REG5,              //!< CTRL_REG5
		OUT_TEMP_L,             //!< OUT_TEMP_L
		OUT_TEMP_H,             //!< OUT_TEMP_H
		STATUS_REG,             //!< STATUS_REG
		OUT_X_L,                //!< OUT_X_L
		OUT_X_H,                //!< OUT_X_H
		OUT_Y_L,                //!< OUT_Y_L
		OUT_Y_H,                //!< OUT_Y_H
		OUT_Z_L,                //!< OUT_Z_L
		OUT_Z_H,                //!< OUT_Z_H

		FIFO_CTRL_REG,          //!< FIFO_CTRL_REG
		FIFO_SRC_REG            //!< FIFO_SRC_REG
	};


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

	/*! @brief Standard constructor.
	 *  @param[in] port defines the port identifier of slave select signal
     *  @param[in] pin defines the pin of slave select signal
	 *  @param[in] ifc defines SPI bus.
	 */
	LIS3DHH(SPI_HandleTypeDef* intf, Platform::BSP::PortPin select);

	bool reset() const;

	/*! @brief Set Mode of Operation.
	 *  @param[in] m defines the mode.
	 *  @param[in] gr defines g-range.
	 *  @return @c true if mode was set correctly.
	 */
	bool control(Mode m = Mode::NORMAL, GRange gr = GRange::RANGE_2G) const;

	/*! @brief Set timing of Operation.
	 *  @param[in] m defines the mode.
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

	/*! @brief Read x Data from Sensor.
	 *  @param[out] x acceleration in x direction.
	 *  @return @c true if read was done correctly.
	 */
	bool getXacc(int16_t&x) const;

	/*! @brief Read y Data from Sensor.
	 *  @param[out] y acceleration in y direction.
	 *  @return @c true if read was done correctly.
	 */
	bool getYacc(int16_t&y) const;

	/*! @brief Read z Data from Sensor.
	 *  @param[out] y acceleration in y direction.
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


	void openTemp() const;
    void closeTemp() const;
	int16_t getTemperature(void) const;
};

}


}

#endif

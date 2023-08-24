/*
 * sspdevice.h
 *
 *  Created on: 21.06.2016
 *      Author: Michael
 */

#ifndef BSP_INC_SSPDEVICE_H_
#define BSP_INC_SSPDEVICE_H_

/* -- includes. */
#include "chip.h"

/* --Include this header only if SPI is enabled by STM32CubeIDE. */
#ifndef HAL_SPI_MODULE_ENABLED
#error Failure! SPI is not enabled by STM32CubeIDE
#endif

#include "digitalinout.h"
#include "bsputil.h"

namespace Platform::BSP {


/**
 * This class is the generalized class of all devices connected to SPI interface.
 */


typedef bool (* LockFctType)(void);  //! < type of callback for mutual exclusion


/*! @brief Base class for Devices using SPI
 *
 */

class SSPDevice : public NonCopyable {
public:

    /**
     * Constructor
     * @param ifc defines the hardware interface connected to
     * @param select defines the of slave select signal
     */
    SSPDevice(SPI_HandleTypeDef* intf, Platform::BSP::PortPin select);

    /**
     * Constructor
     * @param ifc defines the hardware interface connected to
     * @param port defines the port identifier of slave select signal range:0..7
     * @param pin defines the pin of slave select signal range: 0..15
     */
     SSPDevice(SPI_HandleTypeDef* intf, uint8_t port, uint8_t pin);

    /*! @cond HIDDEN_DOXYGEN*/
#if 0
    /* --Forbidden to copy/assign/... any instance of this class. */
    SSPDevice(const SSPDevice&) = delete;
    SSPDevice(SSPDevice&&) = delete;
    SSPDevice& operator=(const SSPDevice&) = delete;
    const SSPDevice& operator=(SSPDevice&&) = delete;
#endif
    /* --Default destructor. */
    virtual ~SSPDevice() = default;

    /*! @endcond */

    /**
     * Read buffer.
     * @param buffer defines buffer
     * @param len defines length of buffer
     * @return @c true if operation was succeeded or @c false
     */
    bool read(uint8_t* buffer, uint32_t& len) const;

    /**
     * Write buffer.
     * @param buffer defines buffer
     * @param len defines length of buffer
     * @return @c true if operation was succeeded or @c false
     */
    bool write(uint8_t* buffer, uint32_t& len) const;

    /**
     * Write single byte.
     * @param value defines value to write to
     * @return @c true if operation was succeeded or @c false
     */
    bool write(uint8_t value) const;


    /**
     * Assign callback functions for lock and unlock in multithreading applications \n
     * Functions must be user provided.
     * @param[in] l pointer to user lock function
     * @param[in] ul pointer to user unlock function
     * @return @c true if operation was succeeded or @c false
     */
    bool assignLockFct(LockFctType l,LockFctType ul);

protected:

    /**
     * Acquire SPI bus for this device.
     */
    void acquire() const;

    /**
     * Release SPI bus for this device.
     */
    void release() const;

    SPI_HandleTypeDef* interface = nullptr;  /**< Internal STM device */

    /** Slave select pin
      \note This pin must be configured as GPIO, do not use HW SSEL function.
       HW function only works in case there is just one slave connected to SPI
     */
    Platform::BSP::DigitalOut ssel;

private:
    LockFctType lock   = nullptr;  /**< user function for lock in multithreading applications   */
    LockFctType unlock = nullptr;  /**< user function for unlock in multithreading applications */

};


}  // namespace BSP


#endif /* BSP_INC_SSPDEVICE_H_ */

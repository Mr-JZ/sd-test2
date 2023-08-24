/**
 *  \file      lm4811.h
 *  \brief     access to audio device on Base board.
 *  \details   Configures HW, allows write access to audio device.
 *             DMA is not implemented\n
 *             requires DAC
 *
 *
 *  \author    J. Wuebbelmann
 *  \version   2.0
 *  \date      12.12.2020
 *  \pre
 *  \copyright HS Osnabrueck
 */

#ifndef PLATFORM_BSP_INC_LM4811_H_
#define PLATFORM_BSP_INC_LM4811_H_

#include "digitalinout.h"
#include "dac.h"
#include "bsputil.h"

namespace Platform::BSP {
// DAC must be enabled in Cube MX and define must be set in main.h

typedef uint32_t (*delayFunc)(uint32_t);   ///< type definition for delay function
/*!
 * \typedef delayFunc
 *  provides a type of which the delay function must be.
 */


/*! @brief  class of to access the LM4811 audio driver using the DAC
 *
 */
class LM4811 : public NonCopyable
{
private:
    static uint32_t s_delayFunc(uint32_t );
public:
    /*! @brief Constructor
     * The LM4811 requires: a shutdown pin, a clock pin and a updown pin
     * to set the volume.\n
     * Therefore, the port and pin numbers must be provided.\n
     * \note When setting the volume, a delay is used for debouncing the clock pin.\n
     * When using a RTOS, the osDelay (in cmsis_os.h) function can be provided.
     * Else the cmsis stopwatch is used, which provides busy waiting and occupies
     * Timer 1,
     *
     * \param [in] shutdownPort Port number of shutdown pin
     * \param [in] shutdownPin  Pin  number of shutdown pin
     * \param [in] clckPort Port number of clock pin
     * \param [in] clckPin  Pin  number of clock pin
     * \param [in] updPort Port number of up/down pin
     * \param [in] updPin  Pin  number of up/down pin
     * \param [in] delay A pointer to a delay function can be provided.\n
     *  This function  must be of signature Platform::BSP::delayFunc and must accept
     *  delays in ms.\n
     *  Default is stopwatch in CMSIS interface, uses Timer1 and busy waiting
    */
    LM4811(const Platform::BSP::PortPin& shutdown,
           const Platform::BSP::PortPin& clock,
           const Platform::BSP::PortPin& upd,
		   DAC_HandleTypeDef* def,
           Dac::Dac_e    dac = Dac::Dac_e::Dac1,
           delayFunc delay = s_delayFunc);

    /*!
     * @brief shuts down LM4811. The device goes in power down mode.
     * @param[in] v true for power down mode, false for operation mode.
     */
    void shutDown(bool v);

    /*!
     * @brief increases volume by 3dB.
     */
    void increaseVolume();

    /*!
     * @brief decreases volume by 3dB.
     */
    void decreaseVolume();


    /*!
     * @brief sets volume between -33dB to 12dB.
     * @param vol volume between 0 and 15 / -33 to 12dB in 3 dB steps
     */

    void setVolume(uint8_t vol);


    /*!
     * @brief sets DAC value for device
     * @param[in] val 10 Bit DAC value
     */
    void out(uint16_t val);

private:
    Platform::BSP::DigitalOut shut;
    Platform::BSP::DigitalOut clck;
    Platform::BSP::DigitalOut upDown;
    uint8_t volume = 0;
    delayFunc delayMs;

    Dac dac;

};
} /* namespace Framework */

#endif /* PLATFORM_BSP_INC_LM4811_H_ */

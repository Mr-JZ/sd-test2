/**
 *  \file      dac.h
 *  \brief     access to DAC of STM32.
 *  \details   Configures HW, allows write access to dac.
 *             DMA is not implemented
 *             The only available DAC channels are mapped to PA4 or PA5!
 *
 *
 *  \author    J. Wuebbelmann
 *  \version   1.0
 *  \date      10.12.2020
 *  \pre
 *  \copyright HS Osnabrueck
 */

#ifndef PLATFORM_BSP_INC_DAC_H_
#define PLATFORM_BSP_INC_DAC_H_
#include <cstdint>

#include "chip.h"

/* --Include this header only if SPI is enabled by STM32CubeIDE. */
#ifndef HAL_DAC_MODULE_ENABLED
#error Failure! DAC is not enabled by STM32CubeIDE
#endif

#include "bsputil.h"


namespace Platform::BSP {

/*! @brief static class of to write to the Digital-to-Analog Converter (DAC)
 *
 *  This class initializes the DAC and provides a setter.\n
 * \note It is not possible to make an object of this class!\n
 *   Only static methods are provided
 */
// DAC must be enabled in Cube MX and define must be set in main.h

class Dac : public NonCopyable
{
public:
    enum class Dac_e
	{
       Dac1,   //!< Channel1, PA4
	   Dac2    //!< Channel2, PA5
	};

    enum class Alignment_e
	{
    	Align12B_r = DAC_ALIGN_12B_R,  //!< 12 Bit right alignment
    	Align12B_l = DAC_ALIGN_12B_L,  //!< 12 Bit left alignment
		Align8B_r  = DAC_ALIGN_8B_R	   //!<  8 Bit right alignment
	};

    /**
     * @brief Constructor
     * @param[in] dac channel of DAC
     * @param[in] al Alignment of data
     *
     */
    Dac(DAC_HandleTypeDef* def, Dac_e dac, Alignment_e al = Alignment_e::Align12B_r);
    ~Dac();


    /**
     * @brief set DAC output  value
     * @param[in] value DAC value to set. Only 10 bits are used
     *
    */
     void setAnalog(std::uint16_t value);

     /**
      * @brief get DAC output  value
      *
      * @returns last value set.
     */
      uint32_t getAnalog();



private:
#if 0
    Dac() = delete;
    Dac(const Dac&) = delete;
    Dac(const Dac&&) = delete;
    Dac& operator=(const Dac&) = delete;
    Dac& operator=(const Dac&&) = delete;
#endif

    DAC_HandleTypeDef* m_dac = nullptr;
    uint32_t           m_channel = 0;
    Alignment_e        m_alignment;
};

} /* namespace Platform */

#endif /* PLATFORM_BSP_INC_DAC_H_ */

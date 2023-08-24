#ifndef PLATFORM_BSP_INC_ADC_H_
#define PLATFORM_BSP_INC_ADC_H_

/* --Platform includes. */
#include "chip.h"

#ifndef HAL_ADC_MODULE_ENABLED
#error Failure! ADC is not enabled by STM32CubeIDE
#endif

#include "bsputil.h"

namespace Platform::BSP {

/*! @brief class of to read the Analog-to-Digital Converter (ADC)
 *
 *  This class initializes the ADC and provides a getter. .
 *  Note: only single ended mode is provides.
 *  Required configuration in Cube MX:\n
 *  Configure channel in single-ended Mode
 *  If just one channel is used:\n
 *    - Set scan conversion more to "disable"\n
 *  If more than one channel are used:\n
 *    - Set scan conversion more to "enable"\n
 *    - Set number of conversion to number of used channels\n
 *    - Configure Rank with number of channels
 *    (the number of Ranks is number of conversions)\n
 *
 */

class Adc : public NonCopyable
{
public:
    /**
     * Available ADC Channels, determines used pin
     */
    enum class Channel_e
    {
        AD11 = 0,     //!< AD1.1  (Port C  Pin 0)
        AD12,         //!< AD1.2  (Port C  Pin 1)
        AD13,         //!< AD1.3  (Port C  Pin 2)
        AD14,         //!< AD1.4  (Port C  Pin 3)
        AD15,         //!< AD1.5  (Port A  Pin 0)
        AD16,         //!< AD1.6  (Port A  Pin 1)
        AD17,         //!< AD1.7  (Port A  Pin 2)
        AD18,         //!< AD1.8  (Port A  Pin 3)

        AD21 = 100,  //!< AD2.1  (Port C  Pin 0)
        AD22,        //!< AD2.2  (Port C  Pin 1)
        AD23,        //!< AD2.3  (Port C  Pin 2)
        AD24,        //!< AD2.4  (Port C  Pin 3)
        AD25,        //!< AD2.5  (Port A  Pin 0)
        AD26,        //!< AD2.6  (Port A  Pin 1)
        AD27,        //!< AD2.7  (Port A  Pin 2)
        AD28,        //!< AD2.8  (Port A  Pin 3)

        AD31 = 200,  //!< AD3.1  (Port C  Pin 0)
        AD32,        //!< AD3.2  (Port C  Pin 1)
        AD33,        //!< AD3.3  (Port C  Pin 2)
        AD34         //!< AD3.4  (Port C  Pin 3)
    };

    /**
     * Constructor to initialize the ADC channel. If more than one channel is used, the ADC goes in burst mode.
     * @param[in]  adPin ADC Channel. A channel is associated with a Pin of the LPC
     */
    Adc(ADC_HandleTypeDef* def, Channel_e adPin);

    /* --Default destructor. */
    virtual ~Adc() = default;

    /*! @brief get ADC value.
     *  @return  conversion result for channel, 0xFFFF in case of error
     */
    uint32_t getValue() const;
private:
    enum class Mode_e
	{
       Continues,   //!< Continues conversion mode
	   Single,      //!< Single conversion
	   Scan
	};

    ADC_HandleTypeDef* m_adc = nullptr;        ///<  pointer to ADC structure
    Channel_e m_channel;                       ///<  channel
    Mode_e    m_mode = Mode_e::Continues;
    uint32_t  m_offset = 0xFa11;  // Fail

};

} /* namespace BSP */


#endif /* PLATFORM_BSP_INC_ADC_H_ */

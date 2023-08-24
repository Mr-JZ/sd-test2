/*
 * Adc.cpp
 *
 *  Created on: 03.07.2019
 *      Author: Wuebbelmann
 */
#include "stm32l4xx_hal.h"

/* --Check if ADC is enabled. */
#ifdef HAL_ADC_MODULE_ENABLED
#include "main.h"
#include "adc.h"
#include "digitalinout.h"

namespace Platform::BSP {


static uint32_t ADC_Data[8];

Adc::Adc(ADC_HandleTypeDef* def, Channel_e adPin) : m_adc(def), m_channel(adPin)
{

	//TODO: Verstehe diese Rechnerei nicht; ggfs. automatisch Zuordnung von ADC zu Channel über Factory?
    if (adPin < Channel_e::AD21)
    {
        m_channel = static_cast<Channel_e>(static_cast<size_t>(m_channel) -
                                          static_cast<size_t>(Channel_e::AD11));
    }
    else if (adPin < Channel_e::AD31)
    {
        m_channel = static_cast<Channel_e>(static_cast<size_t>(m_channel) -
                                          static_cast<size_t>(Channel_e::AD21));
    }
    else if (adPin <= Channel_e::AD34)
    {
        m_channel = static_cast<Channel_e>(static_cast<size_t>(m_channel) -
                                          static_cast<size_t>(Channel_e::AD31));
    }
    else
    {
        Error_Handler();
    }

    if (!(m_adc->Init.ContinuousConvMode == ENABLE))
    {
    	m_mode = Mode_e::Single;
    }
    if(m_adc->Init.ScanConvMode == ADC_SCAN_ENABLE)
    {
        m_mode = Mode_e::Scan;
    	HAL_ADC_Start_DMA(m_adc, ADC_Data, m_adc->Init.NbrOfConversion);
    }
    else
    {
    	HAL_ADC_Start(m_adc);
    }

    // find my channel in conversion order / see Ranks in CubeMX
    if(m_mode == Mode_e::Scan)
    {

    	const uint32_t* sqr = (const uint32_t *)(&(m_adc->Instance->SQR1));

    	// get channel, count in reg starts with 1
    	uint8_t  rank = static_cast<uint8_t>(m_channel) +1;
        uint32_t offset = 1;
        for(uint32_t count = 1; count <= m_adc->Init.NbrOfConversion; ++count)
        {
           uint32_t shift = offset++ * 6;
           uint8_t chan = (*sqr & (0x1F <<  shift)) >> shift;
           if (chan == rank)
           {
        	   m_offset = count-1;
           }
           if (offset > 4)
           {
               offset = 0;
               sqr++;  // next register
           }
        }
        // Everything ok?
        if (0xFa11 == m_offset)
        {
            // selected channel was not configured in CubeMX
            Error_Handler();
        }


    }

}

uint32_t Adc::getValue() const
{
    uint32_t data    = 0xFFFFFFFF;

    switch(m_mode)
    {
    case Mode_e::Single:
        HAL_ADC_Start(m_adc);
        if (HAL_OK == HAL_ADC_PollForConversion(m_adc, 0xFFFF))
        {
            data = HAL_ADC_GetValue(m_adc);
        }
        break;
    case Mode_e::Scan:
        HAL_ADC_Start_DMA(m_adc, ADC_Data, m_adc->Init.NbrOfConversion);
        HAL_ADC_PollForConversion(m_adc, 0xFFFF);
    case Mode_e::Continues:
       data = ADC_Data[m_offset];
       break;
    }


    return data;

}

} /* namespace BSP */

#endif

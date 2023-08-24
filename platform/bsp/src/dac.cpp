/*
 * dac.cpp
 *
 *  Created on: 10.12.2020
 *      Author: Wuebbelmann
 */

#include "stm32l4xx_hal.h"

/* --Check if DAC is enabled. */
#ifdef HAL_DAC_MODULE_ENABLED

#include "dac.h"
#include "main.h"

void Error_Handler();

namespace Platform::BSP {


Dac::Dac(DAC_HandleTypeDef* def, Dac_e dac, Alignment_e al) : m_dac(def), m_alignment(al) {
     switch(dac)
     {
     case Dac_e::Dac1:
    	m_channel = DAC_CHANNEL_1;
        break;
     case Dac_e::Dac2:
        m_channel = DAC_CHANNEL_2;
        break;
     default:
	    Error_Handler();
		break;
     }
     HAL_DAC_Start(m_dac ,m_channel);
}

Dac::~Dac()
{
	//TODO Wollen wir das so? Einschalten über CubeMX und aussachalten über Destruktor? Funktioniert m.E. nicht bei allen Bausteinen (MU)
	HAL_DAC_Stop(m_dac ,m_channel);
}

void Dac::setAnalog(std::uint16_t value)
{
	HAL_DAC_SetValue(m_dac, m_channel, static_cast<uint32_t>(m_alignment), value);

}

uint32_t Dac::getAnalog()
{
	uint32_t val = HAL_DAC_GetValue(m_dac, m_channel);
	return val;
}


} /* namespace Framework */

#endif

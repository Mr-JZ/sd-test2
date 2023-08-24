/**
 *  \brief     PWM implementation / pwm.c
 *  \details   This class defines the interface to PWMund the PWM pins 1 to 6.\n
 *  of type \ref Platform::BSP::PWM
 *
 *  \author    R. Hagemann
 *  \version   1.0
 *  \date      17.10.2016
 *  \copyright HS Osnabrueck
 */
#include "stm32l4xx_hal.h"

/* --Check if TIM is enabled. */
#ifdef HAL_TIM_MODULE_ENABLED

#include "pwm.h"
#include "main.h"

namespace Platform::BSP {

PWM::PWM(TIM_HandleTypeDef* def,
		 PWM_CHANNEL pwmch,
         uint8_t     minPercent,
         uint8_t     maxPercent) :
        		 m_timer(def),
   m_maxPercent(maxPercent),
   m_minPercent(minPercent)

{
    if (pwmch <= PWM_CHANNEL::PWM24)
    {}
    else if (pwmch <= PWM_CHANNEL::PWM34)
    {}
    else if (pwmch <= PWM_CHANNEL::PWM44)
    {}
    else if (pwmch <= PWM_CHANNEL::PWM54)
    {}
    else
    {
        Error_Handler();
    }

    switch(pwmch)
    {
    case PWM_CHANNEL::PWM21:
    case PWM_CHANNEL::PWM31:
    case PWM_CHANNEL::PWM41:
    case PWM_CHANNEL::PWM51:
       m_ccr = &(m_timer->Instance->CCR1);
       m_channel = TIM_CHANNEL_1;
       break;
    case PWM_CHANNEL::PWM22:
    case PWM_CHANNEL::PWM32:
    case PWM_CHANNEL::PWM42:
    case PWM_CHANNEL::PWM52:
       m_ccr = &(m_timer->Instance->CCR2);
       m_channel = TIM_CHANNEL_2;
       break;
    case PWM_CHANNEL::PWM23:
    case PWM_CHANNEL::PWM33:
    case PWM_CHANNEL::PWM43:
    case PWM_CHANNEL::PWM53:
        m_channel = TIM_CHANNEL_3;
       m_ccr = &(m_timer->Instance->CCR3);
       break;
    case PWM_CHANNEL::PWM24:
    case PWM_CHANNEL::PWM34:
    case PWM_CHANNEL::PWM44:
    case PWM_CHANNEL::PWM54:
       m_ccr = &(m_timer->Instance->CCR4);
       m_channel = TIM_CHANNEL_4;
       break;
    default:
        Error_Handler();    // redundant, we should already handle this
    }

    Chip_PWM_Init();
    Chip_PWM_Reset();

}

PWM::~PWM() {
    outputDisable();
}

void PWM::Chip_PWM_Init()
{
}

void PWM::Chip_PWM_Reset(void)
{

}

void PWM::Chip_PWM_Disable(void)
{
}

void PWM::Chip_PWM_Enable(void)
{

}

void PWM::outputEnable(void)
{
    if (HAL_OK != HAL_TIM_PWM_Start(m_timer, m_channel))
        Error_Handler();
}

void PWM::outputDisable(void)
{
    HAL_TIM_PWM_Stop(m_timer, m_channel);
}

void PWM::Chip_PWM_SetPrescale(uint32_t data)
{

    m_timer->Instance->PSC = data;

}

uint32_t PWM::Chip_PWM_GetPrescale(void) const{
   return m_timer->Instance->PSC;
}

void PWM::setFrequency(uint32_t data, bool reset) // in Hz
{
    uint32_t ticksPerSecond = SystemCoreClock;

    uint32_t prescaler = 1;
    uint32_t reg = 0xFFFF;
    if(data)
    {
      while ((reg = ticksPerSecond/(prescaler*data)) > 0xFFFF)
      {
        ++prescaler;
      }
    }
    else
    {
        prescaler = 0x10000;
    }
    --prescaler;
    Chip_PWM_SetPrescale(prescaler);
    m_timer->Instance->ARR = reg;

    // restart counter value!
    if (reset) m_timer->Instance->CNT = 0;

    // set PWMCLK to CCLK! Per default, PWMCLK = CCLK / 4
}


uint32_t PWM::getFrequency(void) const{
    uint32_t ticksPerSecond = SystemCoreClock;
    uint32_t reg = m_timer->Instance->ARR;
    uint32_t prescaler = Chip_PWM_GetPrescale() + 1;
    uint32_t frequency = ticksPerSecond/reg/prescaler;

    return frequency;
}


void PWM::setPulsWidthPercent(uint32_t data)
{
    if (data<m_minPercent) data=m_minPercent;
    if (data>m_maxPercent) data=m_maxPercent;
    uint32_t max = m_timer->Instance->ARR;
    *m_ccr = (max-1)*data / 100;
}

void PWM::setPulsWidth(uint32_t data)
{
    uint32_t max = m_timer->Instance->ARR;
    uint32_t minval =  max      * m_minPercent / 100;
    uint32_t maxval = (max - 1) * m_maxPercent / 100;
    if (data<minval) data=minval;
    if (data>maxval) data=maxval;
    *m_ccr = data;
}


uint32_t PWM::getPulsWidth(void) const{
    return 100 * *m_ccr / m_timer->Instance->ARR;
}

}    // of namespace Platform
#endif

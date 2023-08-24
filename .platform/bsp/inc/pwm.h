/**
 *  \brief     PWM definition / pwm.h
 *  \details   This class defines the interface to PWM1 for the PWM pins 1 to 6.\n
 *  of type \ref Platform::BSP::PWM
 *
 *  \author    R. Hagemann
 *  \version   1.0
 *  \date      17.10.2016
 *  \copyright HS Osnabrueck
 */

/** @file */
#ifndef PWM_H
#define PWM_H

/* --Platform includes. */
#include "chip.h"

#ifndef HAL_TIM_MODULE_ENABLED
#error Failure! TIM is not enabled by STM32CubeIDE
#endif

#include "bsputil.h"


namespace Platform::BSP {

/*! @brief \class PWM pwm.h  "inc/pwm.h"
 *
 *  \brief This class defines the pwm.\n
 *  it can be used for the six pwm channels PWM1.1 - PWM1.6\n
 *  \note For the time being, only PWM_SINGLE_EDGE_CONTROL_MODE is supported
 *
 *  \note USAGE:\n
 *  Special care must be taken to call init methods in the right order:\n
 *  FIRST call \ref Chip_PWM_SetFrequency() This method deactivates PWM timer!\n
 *  THEN call \ref Chip_PWM_Enable() This method activates PWM timer\n
 *  FINALLY call \ref Chip_PWM_OutputEnable() to enable your channel.\n
 *  After initialization, other channels just call \ref Chip_PWM_OutputEnable()\n
 */

class PWM : public NonCopyable {
public:
    /*! \enum PWM_CHANNEL
     * Possible channels of PWM
     */
    enum class PWM_CHANNEL
    {
        PWM21=1,        //!< Channel 2.1, using PA0 / PA5 / PA15
        PWM22,          //!< Channel 2.2, using PA1 / PB3
        PWM23,          //!< Channel 2.3, using PA2 / PB10
        PWM24,          //!< Channel 2.4, using PA3 / PB11

        PWM31,          //!< Channel 3.1, using PA6 / PB4 / PC6 (/ PE3)
        PWM32,          //!< Channel 3.2, using PA7 / PB5 / PC7 (/ PE4)
        PWM33,          //!< Channel 3.3, using       PB0 / PC8 (/ PE5)
        PWM34,          //!< Channel 3.4, using       PB1 / PC9 (/ PE6)

        PWM41,          //!< Channel 4.1, using       PB6       (/ PD12)
        PWM42,          //!< Channel 4.2, using       PB7       (/ PD13)
        PWM43,          //!< Channel 4.3, using       PB8       (/ PD14)
        PWM44,          //!< Channel 4.4, using       PB9       (/ PD15)

        PWM51,          //!< Channel 5.1, using PA0             (/ PF6)
        PWM52,          //!< Channel 5.2, using PA1             (/ PF7)
        PWM53,          //!< Channel 5.3, using PA3             (/ PF8)
        PWM54,          //!< Channel 5.4, using PA4             (/ PF9)

    };

public:
    /*! @brief Constructor
     * @param[in] pwmch channel to be used
     * @param[in] minPercent minimal value of duty cycle in percent
     * @param[in] maxPercent maximal value of duty cycle in percent
     *
     */
    PWM(TIM_HandleTypeDef* def, PWM_CHANNEL pwmch, uint8_t minPercent=25, uint8_t maxPercent=100);

    /*! @brief Destructor disables this PWM channel
     *
     */
    ~PWM();

public:
    /*! @brief Resets all PWM registers
     * \warning be careful, this will effect all PWM channels!
     */
    void Chip_PWM_Reset(void);


    /*! @brief Stops PWM timer
     * \warning be careful, this will effect all PWM channels!
     */
    void Chip_PWM_Disable(void);

    /*! @brief Starts PWM timer
     * \warning be careful, this will effect all PWM channels!
     */
    void Chip_PWM_Enable(void);

    /*! @brief Enables PWM for this channel
     *
     */
    void outputEnable(void);

    /*! @brief Disables PWM for this channel
     *
     */
    void outputDisable(void);

    /*! @brief Sets PWM base frequency
     * \warning be careful, this will effect all PWM channels!
     * @param[in] data frequency in Hz
     * @param[in] reset if true, the timer value is set to 0
     */
    void setFrequency(uint32_t data, bool reset = false);


    /*! @brief Sets PWM duty cycle in percent for this channel
     * @param[in] data duty cycle in percent
     */
    void setPulsWidthPercent(uint32_t data);

    /*! @brief Sets PWM duty cycle for this channel\n
     * value in set in given limits between minPercent and maxPercent
     * @param[in] data duty cycle as absolute value
     */
    void setPulsWidth(uint32_t data);


    /*! @brief Gets PWM base frequency
     * @returns PWM frequency in Hz
     */
    uint32_t getFrequency    (void) const;

    /*! @brief Gets PWM duty cycle of this channel
     * @returns PWM duty cycle in percent
     */
    uint32_t getPulsWidth    (void) const;

    /*! @brief Gets max. input for pulse width
     * @returns max value of timer
     */
    uint32_t getMaxInput() const {return m_timer->Instance->ARR;}

    /*! @brief Gets minimal percentage of duty cycle (internal limitation)
     * @returns minimal duty cycle in Hz
     */
    uint8_t  Chip_PWM_GetMinPercent    (void) const { return m_minPercent; };

    /*! @brief Gets maximal percentage of duty cycle (internal limitation)
     * @returns minimal duty cycle in Hz
     */
    uint8_t  Chip_PWM_GetMaxPercent    (void) const { return m_maxPercent; };

private:

    /**
    * @brief PWM Edge mode
    */
    typedef enum
    {
     PWM_SINGLE_EDGE_CONTROL_MODE=0,        ///< MR0 is used for set and MRx for reset of PWM pin
     PWM_DOUBLE_EDGE_CONTROL_MODE=1,        ///< MR(x-1) is used for set and MRx for reset  of PWM pin
    }PWM_EDGE_CONTROL_MODE;

    /**
    * @brief PWM enable
    */
    typedef enum
    {
        PWM_OUT_DISABLED=0,   ///< Disable PWM
        PWM_OUT_ENABLED=1,    ///< Enable PWM
    }PWM_OUT_CMD;



    uint32_t           m_channel = 0;         ///< Channel!
    TIM_HandleTypeDef* m_timer = nullptr; ///< timer used by channel
    volatile uint32_t* m_ccr   = nullptr; ///< CCRx Register!
    uint8_t            m_maxPercent;      ///< maximum percentage of duty cycle!
    uint8_t            m_minPercent;      ///< minimum percentage of duty cycle!

    void Chip_PWM_Init();


    void Chip_PWM_SetPrescale(uint32_t data);
    uint32_t Chip_PWM_GetPrescale (void) const;
};

}    // of namespace BSP

#endif /* PWM_H */

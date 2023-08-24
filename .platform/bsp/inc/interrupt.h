#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <cstdint>

/* --Local includes. */
#include "digitalinout.h"
#include "chip.h"
#include "bsputil.h"


namespace Platform {

namespace BSP {

/*! @brief Interrupt manager.
 *
 *  This class is the managing instance keeping all interrupt handling objects.
 *  There should be exactly _one_ instance of this class system-wide. In order
 *  to enable an interrupt, attach the interrupt handler object and enable
 *  the manager.
 *
 *  THIS IS ONLY FOR INTERNAL USAGE OF Platform::BSP LIBRARY!
 *
 */

class InterruptManager : public NonCopyable {

public:

    /*! @brief Standard constructor. */
    InterruptManager();


    /*! @cond HIDDEN_DOXYGEN*/
#if 0
    /* --Forbidden to copy/assign/... any instance of this class. */
    InterruptManager(const InterruptManager&) = delete;
    InterruptManager(InterruptManager&&) = delete;
    InterruptManager& operator=(const InterruptManager&) = delete;
    const InterruptManager& operator=(InterruptManager&&) = delete;
#endif
    /* --Default destructor. */
    virtual ~InterruptManager() = default;

    /*! @endcond */

    /**
     * Setting an interrupt handler object under control of the manager.
     * @param gpio defines the associated pin of the interrupt
     * @param ih defines the interrupt handler routine.
     * @return @c true if attach method succeeded.
     */
    bool attach(const DigitalInterrupt& gpio, const DigitalInterrupt::InterruptHandler& ih) const;

    /**
     * release an interrupt handler object from control of the manager.
     * @param gpio defines the associated pin of the interrupt
     * @return @c true if detach method succeeded.
     */
    bool detach(const DigitalInterrupt& gpio) const;


    /**
     * Enable interrupt at pin
     * @param gpio defines the pin to be enabled
     * @param edge defines the trigger
     * @return @c true if succeeded or @c false
     */
    bool enable(const DigitalInterrupt& gpio, DigitalInterrupt::EdgeType edge) const;

    /**
     * Disable interrupt at pin
     * @param gpio defines the pin to be enabled
     * @return @c true if succeeded or @c false
     */
    bool disable(const DigitalInterrupt& gpio) const;

    /**
     * clear interrupt at pin
     * @param gpio defines the interrupt pin to be cleared
     * @return @c true if succeeded or @c false
     */
    bool clear(const DigitalInterrupt& gpio) const;


    /*! @cond HIDDEN_DOXYGEN*/

    /*! @brief resolve the interrupt and call handler
     *  \param[in] port     must be GPIOINT_PORT0
     */
    static void resolve(uint16_t GPIO_Pin);


    /*! @brief get handler number-
     * \ref pin just has one bit set. Position of bit is handler number
     *  \param[in] pin  Bit field containing pin number
     */
    static uint8_t getHandlerNumberFromPin(uint16_t pin);

    /*! @endcond */

private:

    enum  class NUMOFHANDLER
    {
    	NHANDLER = 16
    };
    /* --Error when interrupt handler is missing. */
    static void failure(DigitalInterrupt::EdgeType );





    /*! @brief Checks the associated edge type.
       *  @param[in] e the edge type to be checked.
       *  @returns @c true if given edge is source of interrupt. */
    bool isTrigger(DigitalInterrupt::EdgeType event, DigitalInterrupt::EdgeType e) const
    {
    	return static_cast<uint32_t>(e) & static_cast<uint32_t>(event);
    }


    /* --Interrupt handler array. */
    static DigitalInterrupt::InterruptHandler handler[static_cast<uint16_t>(NUMOFHANDLER::NHANDLER)];

};

}

}

#endif

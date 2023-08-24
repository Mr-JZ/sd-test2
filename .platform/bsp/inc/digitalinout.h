#ifndef DigitalInterruptOUT_H
#define DigitalInterruptOUT_H

#include <cstdint>
#include <functional>

/* --Platform includes. */
#include "chip.h"


/* --BSP includes. */
#include "portpin.h"
#include "bsputil.h"

namespace Platform::BSP {

/*! @brief Class of general purpose input output pins.
 *
 *  This class defines the interface to GPIO pins. This class can be used
 *  as is or as base class of more sophisticated pins. This class also defines
 *  the interface on interrupt handler routines.
 */

class DigitalBase : public NonCopyable {
public:

	explicit DigitalBase(const PortPin& portPin):_portPin(portPin) {}

	const PortPin& io() const { return _portPin; }

	const Port& port() const { return _portPin.first; }
	const Pin& pin() const { return _portPin.second; }


protected:
	PortPin _portPin;
};


class DigitalOut : public DigitalBase {
public:

	/* --Construct by port-pin. */
	explicit DigitalOut(const PortPin& portPin):DigitalBase(portPin) {}

    /*! @brief Sets the pin to true (1) if output.
     */
    void set() const;

    /*! @brief Sets the pin to false (0) if output.
     */
    void clear() const;

};


class DigitalIn : public DigitalBase {
public:

	/* --Construct by port-pin. */
	explicit DigitalIn(const PortPin& portPin):DigitalBase(portPin) {}

	bool get() const;
	bool test() const { return get(); }
	operator bool() const { return get(); }

};



class DigitalInterrupt : public DigitalIn {
public:

	/* --Construct by port-pin. */
	explicit DigitalInterrupt(const PortPin& portPin):DigitalIn(portPin) {}

	/**
	 * The type specifies when handler should be invoked.
	 */
	enum class EdgeType {
		NO_EDGE =0x00,                        	//!< Does not invoke handler
		FALLING_EDGE =0x01,                 	//!< Invoke handler on falling edge
		RISING_EDGE =0x02,                    	//!< Invoke handler on rising edge
		ANY_EDGE =FALLING_EDGE|RISING_EDGE  	//!< Invoke handler on both edges
	};

	/**
	 * Define interrupt handler type.
	 */
	using InterruptHandler = std::function<void(EdgeType)>;


    /**
      * Set Interrupt handler.
      * @param irq defines the interrupt handler routine, e.g. lambda expression
      * @param edge defines the edge(s) triggering the handler
      *            (this enables also the interrupt!)
      * @return returns true when setting up and enabling succeeded
      */
     bool onInterrupt(const InterruptHandler& irq,
                      EdgeType edge =EdgeType::NO_EDGE) const;

     /**
      * Enable interrupt handler.
      * @param edge defines the edge(s) triggering the handler
      * @return return true when enabling succeeded or false
      */
     bool enableInterrupt(EdgeType edge =EdgeType::ANY_EDGE) const;

     /**
      * Disable interrupt handler on all trigger
      * @return true when disabling the interrupt succeeded
      */
     bool disableInterrupt() const;

     /**
      * Clear pending interrupt on all trigger
      * @return true when clearing the pending interrupt succeeded
      */
     bool clearPendingInterrupt() const;

};

}


#endif

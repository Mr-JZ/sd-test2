/*
 * PortPin.h
 *
 *  Created on: 09.09.2016
 *      Author: Michael
 */

#ifndef BSP_INC_PORTPIN_H_
#define BSP_INC_PORTPIN_H_

#include <cstdint>
#include <utility>

/* --STM Driver Includes. */
#include "chip.h"

namespace Platform::BSP {

/**
 * This class defines a single pin that can be multiplexed.
 */

class Pin {
public:

    enum class BitMask:std::uint16_t {
        Pin0   = GPIO_PIN_0,
        Pin1   = GPIO_PIN_1,
        Pin2   = GPIO_PIN_2,
        Pin3   = GPIO_PIN_3,
        Pin4   = GPIO_PIN_4,
        Pin5   = GPIO_PIN_5,
        Pin6   = GPIO_PIN_6,
        Pin7   = GPIO_PIN_7,
        Pin8   = GPIO_PIN_8,
        Pin9   = GPIO_PIN_9,
        Pin10  = GPIO_PIN_10,
        Pin11  = GPIO_PIN_11,
        Pin12  = GPIO_PIN_12,
        Pin13  = GPIO_PIN_13,
        Pin14  = GPIO_PIN_14,
        Pin15  = GPIO_PIN_15,
        PinAll = GPIO_PIN_All
    };

    explicit Pin(BitMask mask):_mask(mask) {}

    BitMask mask() const { return _mask; }

    std::uint16_t bit() const { return __builtin_ffs(static_cast<int>(_mask)); }

    operator std::uint16_t() const { return static_cast<std::uint16_t>(_mask); }

private:
    BitMask _mask;
};



class Port {
public:

    using STM32HalType = GPIO_TypeDef*;


    enum class Select : std::uint16_t {
            PortA,
            PortB,
            PortC,
            PortD,
            PortE,
            PortF,
            PortG,
            PortH
    };


    explicit Port(Select select);

    explicit Port(Port::STM32HalType t):_type(t) {}

    STM32HalType get() const { return _type; }


private:
    STM32HalType _type;
};

inline Port::Port(Select select) {
    /* --Just switch on the port; use global constants. */
    switch (select) {
    case Select::PortA : _type=GPIOA; break;
    case Select::PortB : _type=GPIOB; break;
    case Select::PortC : _type=GPIOC; break;
    case Select::PortD : _type=GPIOD; break;
    case Select::PortE : _type=GPIOE; break;
    case Select::PortF : _type=GPIOF; break;
    case Select::PortG : _type=GPIOG; break;
    case Select::PortH : _type=GPIOH; break;
    default:;
    }
}

using PortPin = std::pair<Port,Pin>;


}

#endif /* BSP_INC_PORTPIN_H_ */

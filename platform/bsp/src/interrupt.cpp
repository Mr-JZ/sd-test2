#include "interrupt.h"

#include "chip.h"

#include <cstdio>
#if __cplusplus >= 201703L
#include <bit>
#endif

namespace Platform::BSP {

DigitalInterrupt::InterruptHandler InterruptManager::handler[static_cast<uint16_t>(NUMOFHANDLER::NHANDLER)] = {nullptr};

InterruptManager::InterruptManager() {
    /* --Setup internals. */
    // set all handlers to failure to catch uninitialized interrupt
    for(size_t i = 0; i < static_cast<uint16_t>(NUMOFHANDLER::NHANDLER); ++i)
    {
       if(handler[i] == nullptr)
       {
            handler[i] = failure;
       }
    }
}

void InterruptManager::failure(DigitalInterrupt::EdgeType t)
{
    (void)t; // to avoid compiler warnings
    /* --This should never happen. */
    while(true);
}


void InterruptManager::resolve(uint16_t GPIO_Pin) {
    /* --Convert set to value. */
#if __cplusplus > 201703L
    std::uint16_t ident = std::bit_width(GPIO_Pin) -1;
#else
    uint8_t ident = getHandlerNumberFromPin(GPIO_Pin);
    //std::uint16_t ident=__builtin_ffs(GPIO_Pin)-1;    /* --Waiting for C++20 and bits.h */
#endif

    if (ident < static_cast<uint16_t>(NUMOFHANDLER::NHANDLER)) {
/* --Disbaled until we know to identify edge of this interrupt. */
#if 0
      /* --Check if rising edge interrupt is enabled. */
      DigitalInterrupt::EdgeType fallingEnabled = EXTI->FTSR1 & GPIO_Pin ? DigitalInterrupt::EdgeType::FALLING_EDGE : DigitalInterrupt::EdgeType::NO_EDGE;
      DigitalInterrupt::EdgeType risingEnabled  = EXTI->RTSR1 & GPIO_Pin ? DigitalInterrupt::EdgeType::RISING_EDGE  : DigitalInterrupt::EdgeType::NO_EDGE;
      DigitalInterrupt::EdgeType edge = static_cast <DigitalInterrupt::EdgeType>
           (static_cast<uint32_t>(fallingEnabled) | static_cast<uint32_t>(risingEnabled));
#endif
      /* --Invoke the handler (hopefully it has been defined...) */
      handler[ident](DigitalInterrupt::EdgeType::ANY_EDGE);
    }
}

bool InterruptManager::attach(const DigitalInterrupt& gpio, const DigitalInterrupt::InterruptHandler& ih) const {
    bool retValue=true;
    /* --Convert set to value. */
    std::uint16_t ident=gpio.pin().bit() - 1;
    if (ident < static_cast<uint16_t>(NUMOFHANDLER::NHANDLER)) {
        /* --Set handler. */
        handler[ident]=ih;
    }
    else
        retValue=false;

    return retValue;
}

bool InterruptManager::detach(const DigitalInterrupt& gpio) const {
    bool retValue=true;
    /* --Convert set to value. */
    std::uint16_t ident=gpio.pin().bit() -1;
    /* --Check port/pin of given GPIO. */
    if (ident < static_cast<uint16_t>(NUMOFHANDLER::NHANDLER))
    {
        /* --Set handler. */
        handler[ident]=failure;
    }
    else
        retValue=false;

    return retValue;
}


bool InterruptManager::enable(const DigitalInterrupt& gpio, DigitalInterrupt::EdgeType edge) const {
    bool retValue=true;

    /* --Check port/pin of given GPIO. */
    // get state of Interrupt and mask new bit...
    uint32_t myMask = static_cast<uint32_t>(gpio.pin().mask());
    uint32_t temp = 0;

    uint32_t position = gpio.pin().bit()-1;

    // set this Port as active interrupt line in EXTI:
    temp = SYSCFG->EXTICR[position >> 2u];
    temp &= ~(0x0FuL << (4u * (position & 0x03u)));
    temp |= (GPIO_GET_INDEX(gpio.port().get()) << (4u * (position & 0x03u)));
    SYSCFG->EXTICR[position >> 2u] = temp;

    // set pin mode to input (required to be generate interrupt):
    temp = gpio.port().get()->MODER;
    temp &= ~(GPIO_MODER_MODE0 << (position * 2u));
    temp |= ((GPIO_MODE_IT_RISING_FALLING & GPIO_MODER_MODE0) << (position * 2u));
    gpio.port().get()->MODER = temp;

    // set edge of interrupt:
    switch(edge)
    {
    case DigitalInterrupt::EdgeType::FALLING_EDGE:
        temp = EXTI->FTSR1;
        temp |= myMask;
        EXTI->FTSR1 = temp;
        break;
    case DigitalInterrupt::EdgeType::RISING_EDGE:
        temp = EXTI->RTSR1;
        temp |= myMask;
        EXTI->RTSR1 = temp;
        break;
    case DigitalInterrupt::EdgeType::ANY_EDGE:
        temp = EXTI->FTSR1;
        temp |= myMask;
        EXTI->FTSR1 = temp;
        temp = EXTI->RTSR1;
        temp |= myMask;
        EXTI->RTSR1 = temp;
        break;
    default:      // disable interrupts
        temp = EXTI->FTSR1;
        temp &= ~myMask;
        EXTI->FTSR1 = temp;
        temp = EXTI->RTSR1;
        temp &= ~myMask;
        EXTI->RTSR1 = temp;
    }

    /* Set EXTI line configuration */
    temp = EXTI->IMR1;
    temp |= myMask;
    EXTI->IMR1 = temp;

    return retValue;

}

bool InterruptManager::disable(const DigitalInterrupt& gpio) const {
    bool retValue=true;
    /* --Check port/pin of given GPIO. */
    /* --Check port/pin of given GPIO. */
    // get state of Interrupt and mask new bit...
    uint32_t myMask = static_cast<uint32_t>(gpio.pin().mask());
    uint32_t temp = 0;

    // disable falling and rising edge:
    temp = EXTI->FTSR1;
    temp &= ~myMask;
       EXTI->FTSR1 = temp;
       temp = EXTI->RTSR1;
    temp &= ~myMask;
       EXTI->RTSR1 = temp;

    /* Set EXTI line configuration */
    temp = EXTI->IMR1;
    temp &= ~myMask;
    EXTI->IMR1 = temp;
    return retValue;
}


uint8_t InterruptManager::getHandlerNumberFromPin(uint16_t pin)
{
    // see https://graphics.stanford.edu/~seander/bithacks.html#IntegerLogLookup
      static const uint8_t LogTable16[16] =
      {0xFF, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3};

      uint_fast16_t r, t, tt;
      if ((tt = pin >> 8))
      {
        r = (t = tt >> 4) ? 12 + LogTable16[t] : 8 + LogTable16[tt];
      }
      else
      {
        r = (t = pin >> 4) ? 4 + LogTable16[t] : LogTable16[pin];
      }
      return r;
}


}     // end of namespace BSP



/* --Bind the interrupt manager to global interrupt handler. */

extern "C" void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) { Platform::BSP::InterruptManager::resolve(GPIO_Pin); }

#include "digitalinout.h"
#include "interrupt.h"

namespace Platform::BSP {

/* --Manager for interrupt handling. */
static InterruptManager iManager;


void DigitalOut::set() const
{
    /* --Set the value to true (1). */
    HAL_GPIO_WritePin(port().get(), pin(), GPIO_PIN_SET);
}

void DigitalOut::clear() const
{
    /* --Clear the value (0). */
    HAL_GPIO_WritePin(port().get(), pin(), GPIO_PIN_RESET);;
}

bool DigitalIn::get() const
{
    /* --Get the value and map to true or false. */
    return HAL_GPIO_ReadPin(port().get(), pin()) == GPIO_PIN_SET;
}



bool DigitalInterrupt::onInterrupt(const InterruptHandler& irq, EdgeType edge) const
{
    if (iManager.attach(*this,irq))
        return (edge!=EdgeType::NO_EDGE ? enableInterrupt(edge) : true);
    else
        return false;
}


bool DigitalInterrupt::enableInterrupt(EdgeType edge) const
{
    return iManager.enable(*this,edge);
}


bool DigitalInterrupt::disableInterrupt() const
{
    return iManager.disable(*this);
}


bool DigitalInterrupt::clearPendingInterrupt() const
{
    //return (iManager ? iManager->clear(*this) : false);
    return false;
}


}    // namespace BSP


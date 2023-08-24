/*
 * one_wire.cpp
 *
 *  Created on: 26.07.2021
 *      Author: Tristan
 */

#include "one_wire.h"

#if (defined USETIM5 && USETIM5 == 1)
void DelayuS(uint32_t delay_value)
{

	TIM_HandleTypeDef *m_timer = &htim5;
	// reset counter value
	__HAL_TIM_SET_COUNTER(m_timer, 0);

	// wait until timer has reached delay_value (timer is incrementing each microsecond (us)!)
	while (__HAL_TIM_GET_COUNTER(m_timer) < delay_value)
		;

}
#else
#warning Delay without timer is not tested!!!!
void DelayuS(uint32_t delay_value)
{
    for(uint32_t t = 0; t < delay_value; ++t)
    	for(uint32_t i = 0; i < 0xff; ++i);   // not tested
}
#endif
namespace Platform
{

namespace BSP
{

// Base class constructor is always called BEFORE the constructor of derived class
// First do the 1-wire reset and then configure the currently addressed device (ds18b20)
one_wire::one_wire(GPIO_TypeDef *port, PortPin::Pins pin) :
		DigitalInOut(port, pin), master_write(port, pin,
				DigitalInOut::Direction::OUTPUT), master_read(port, pin,
				DigitalInOut::Direction::INPUT)
{

	uint8_t ROM_read_buffer[8];

#if (defined USETIM5 && USETIM5 == 1)
		m_timer = &htim5;
#else
	Error_Handler();
#endif

	HAL_TIM_Base_Start(m_timer);


	// initialization flow starts with specified bus reset
	OWInit(&owire, port, (uint16_t) pin);

	one_wire::reset();

	// Read from ROM command
#ifdef ONEWIRE_SEARCH
	OWSearch(&owire, ROM_read_buffer);
#endif
	// set attributes of 1-wire device
	family_code = ROM_read_buffer[0];
	for (uint8_t i = 1; i < 7; i++)
	{
		serial_number[i] = ROM_read_buffer[i];
	}
	CRC_byte = ROM_read_buffer[7];
}

void one_wire::write_bytes(const uint8_t *write_buffer, uint8_t no_of_bytes)
{
	OWWrite_bytes(&owire, write_buffer, no_of_bytes);
}

void one_wire::read_bytes(uint8_t *read_buffer, uint8_t no_of_bytes)
{
	OWRead_bytes(&owire, read_buffer, no_of_bytes);
}

bool one_wire::reset(void)
{

	bool success = false;

	// pull 1-wire output low
	master_write.clear();

	// keep pin pulled down for 480us
	DelayuS(480);

	// set pin
	master_write.set();

	// after data line has been released again after reset pulse...
	// ...slave waits for a maximum of 60us to send response pulse
	DelayuS(60);

	// if there was a presence pulse detected after max. 60us, response from slave is valid!
	if (!master_read.get())
		success = true;
	else
	{
	};

	// total delay after reset pulse from master is another 480us!
	DelayuS(420);

	return success;

}


void one_wire::match()
{
	OWReset(&owire);
	OWSelect(&owire, (uint8_t *)&(owire.ROM_NO));
}

/* Reading & writing from/to devices:
 *
 * Recovery time between read/write-slots > 1us
 * Write 0s: low-time 60-120us
 * Write 1s: low_time 1-15 us, then release bus (pull-up)
 *
 * Slave pulls line low for at least 1us before writing a 1 or 0
 * Master shall sample no earlier than 15 us after bus was pulled down by slave
 * in order to read the valid state of the transmitted bit
 */

// each bit-wise write operation has a limited time slot of max. 120us
void one_wire::write(uint8_t data)
{

	OWWrite(&owire, data);
}

uint8_t one_wire::read(void)
{

	uint8_t value = 0;

	value = OWRead(&owire);

	return value;

}

}

}


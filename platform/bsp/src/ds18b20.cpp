/*
 * ds18b20.cpp
 *
 *  Created on: 26.07.2021
 *      Author: Tristan
 */

#include "DS18B20.h"
#include <cstdint>

// commands:
#define READ_SCRATCHPAD 0xBE  // read the entire memory
#define WRITE_SCRATCHPAD 0x4E // write bytes 2 through 4 of memory
#define COPY_SCRATCHPAD 0x48  // copy bytes 2 through 4 to EEPROM
#define CONVERT_T 0x44        // Temperature conversion

// fixed-point fractional bits of temperature data
#define TEMP_FRACTIONAL_BITS 4

// temp unit:
// 0: celsius
// 1: fahrenheit
#define FAHRENHEIT 0

namespace Platform
{

namespace BSP
{

DS18B20::DS18B20(GPIO_TypeDef *port, PortPin::Pins pin, int32_t th, int32_t tl,
		uint8_t res) :
		one_wire(port, pin), resolution(res)
{

	config(th, tl, res);

}

// write scratch pad memory operation, setting of resolution and min/max temperature thresholds for alarm generation
// functional command, write 4e on 1-wire bus before transmitting data
void DS18B20::config(int32_t th, int32_t tl, uint8_t resolution)
{

	// reset value of config register according to data sheet
	uint8_t resolution_byte = 0x1f;

	switch (resolution)
	{

	case 9:
		resolution_byte |= (0x0 << 5);;
		break;
	case 10:
		resolution_byte |= (0x1 << 5);
		break;
	case 11:
		resolution_byte |= (0x2 << 5);
		break;
	case 12:
		resolution_byte |= (0x3 << 5);
		break;
	default:
		resolution_byte = 0x1f;
		break;

	}

	// since the MSB of resolution_byte is set to 0, conversion to signed type is allowed
	const uint8_t config_data[] =
	{ (uint8_t) th, (uint8_t) tl, resolution_byte };

	// begin by transmitting functional command to device:
	one_wire::match();
	one_wire::write(WRITE_SCRATCHPAD);

	// then write the registers in scratch pad memory
	one_wire::write_bytes(config_data, 3);

	// now copy bytes 2 through 4 into EEPROM memory
	one_wire::match();
	one_wire::write(COPY_SCRATCHPAD);

}

void DS18B20::read_mem(uint8_t *buffer)
{

	// issue read scratch pad command
	one_wire::match();
	one_wire::write((uint8_t) READ_SCRATCHPAD);

	one_wire::read_bytes(buffer, 9);

}

// param format 0: celsius, 1: fahrenheit
float DS18B20::read_temp(void)
{

	int16_t temperature = 0;

	uint8_t buffer[9];

#if (FAHRENHEIT == 1)

  		  // start temperature conversion:
  		  one_wire::write((uint8_t) CONVERT_T);

  		  timer_delay(60, m_timer);

  		  // wait for the conversion to complete
  		  while(!master_read.get());

  		  // conversion done!

#endif

	// read entire scratchpad memory
	DS18B20::read_mem(buffer);

	// now start next conversion....
	one_wire::match();
	one_wire::write((uint8_t) CONVERT_T);

	temperature = buffer[1];
	temperature = ((temperature<<8) | buffer[0]);

	// now delete bits 11 through 14 (additional signed bits)

	switch (getResolution())
	{

	case 9:
		temperature &= 0xFFF8;
		break;
	case 10:
		temperature &= 0xFFFC;
		break;
	case 11:
		temperature &= 0xFFFE;
		break;
	case 12:
		temperature &= 0xFFFF;
		break;
	default:
		temperature &= 0xFFFF;
		break;

	}

	return fixed_to_float(temperature);

}

uint8_t DS18B20::getResolution(void)
{

	return resolution;

}

}

}


/*
 * ds18b20.h
 *
 *  Created on: 26.07.2021
 *      Author: Tristan
 */

#ifndef DS18B20_H
#define DS18B20_H

#define TEMP_FRACTIONAL_BITS 4

#include "one_wire.h"

namespace Platform {

namespace BSP {

/*! @brief Interface class to temperature sensor
 *
 *  This class defines the interface to DS18B20 mounted on
 *  the base board (see DS18B20L hardware documentation for details).
 */
  class DS18B20 : public /*DigitalThermometer<*/one_wire {

  public:

    /**
     * Internal register set.
     */
    enum class Register : uint8_t {
    	TEMPERATURE_LSB = 0x00,
    	TEMPERATURE_MSB,
        TH,
		TL,
		CONFIG,
		RESERVED_06,
		RESERVED_07,
		RESERVED_08,
		CRC_REG
    };

    float read_temp (/*uint8_t format*/);

    void read_mem(uint8_t* buffer);

    void config(int32_t th, int32_t tl, uint8_t resolution);

    uint8_t getResolution (void);

    // Constructor
    DS18B20 (GPIO_TypeDef* port, PortPin::Pins pin, int32_t th, int32_t tl, uint8_t res);

  private:

    uint8_t resolution;

  };

  inline float fixed_to_float(int16_t input) {

	  return ((float)input / (float)(1 << TEMP_FRACTIONAL_BITS));

  }



 }


}






#endif /* DS18B20_H_ */

/*
 * one_wire.h
 *
 *  Created on: 26.07.2021
 *      Author: Hillmann
 */

#ifndef ONE_WIRE_H
#define ONE_WIRE_H

#include <cstdint>

/* --LPCOpen includes. */
#include "chip.h"
#include "DigitalInOut.h"
#include "main.h"
#include "stm32l4xx_hal_tim.h"

#include "OneWire.h"

namespace Platform {
  namespace BSP {

    /*! @brief Base class of all devices connected via 1-wire bus
     *
     *  This class defines the interface to all 1-wire devices available at the
     *  EA base board. Don't use this class directly but define a new derived
     *  class.
     */

    class one_wire : public DigitalInOut {

    public:

      bool reset(void);

      // Send MATCH ROM
      void match();

      void write(uint8_t data);

      void write_bytes(const uint8_t* write_buffer, uint8_t no_of_bytes);

      uint8_t read(void);


      void read_bytes(uint8_t* read_buffer, uint8_t no_of_bytes);

      one_wire();
      one_wire(GPIO_TypeDef* port, PortPin::Pins pin);

      /* --Default destructor. */
      virtual ~one_wire() = default;

    protected:

      DigitalInOut master_write;
      DigitalInOut master_read;

      // 64 bits individual device address
      uint8_t family_code;
      uint8_t serial_number [6];
      uint8_t CRC_byte;

      TIM_HandleTypeDef* m_timer = nullptr; // Timer for write and read delays
      OWire owire;
    };


  }
}




#endif /* BSP_INC_ONE_WIRE_H_ */

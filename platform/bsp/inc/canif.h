/*
 * canif.h
 *
 *  Created on: 13.07.2016
 *      Author: Michael
 */

#ifndef BSP_INC_CANIF_H_
#define BSP_INC_CANIF_H_

#include "chip.h"

/* --Include this header only if I2C is enabled by STM32CubeIDE. */
#ifndef HAL_CAN_MODULE_ENABLED
#error Failure! CAN is not enabled by STM32CubeIDE
#endif

#include <cstdio>
#include <cstdint>
#include <functional>

#include "bsputil.h"
#include "portpin.h"
#include "digitalinout.h"

namespace Platform::BSP {

/** @brief Interface to the CAN bus.
 *
 *  This class defines the interface to the CAN bus.
 *  Note: The jumpers J12 and J13 must be set on pins 2-3 in order to use the CAN bus on the EA base board.
 *  Note: Only LPC_CAN2 can be used on the EA base board.
 */

class ControllerAreaNetwork : public NonCopyable {
public:

	/**
	 * Defines the message type.
	 */
	/*! @brief CAN-Message structure. */
	struct Message {

		enum { Standard, Extended } type = { Standard };		/* --Yes we write Standard with two 'd' ! */

		enum { MaxDataLengthCounter = 8 };


		std::uint32_t identifier = 0x0000;
		std::uint32_t size =0;						/* --Should be between 0 .. 8 */
		std::uint8_t buffer[MaxDataLengthCounter]={0};					//!< CAN-Message Data-Buffer
	};


	enum class FilterBank : std::uint32_t {
		Filter0 = 0x00	/*! <Filter#0.  */,
		Filter1			/*! <Filter#1.  */,
		Filter2			/*! <Filter#2.  */,
		Filter3			/*! <Filter#3.  */,
		Filter4			/*! <Filter#4.  */,
		Filter5			/*! <Filter#5.  */,
		Filter6			/*! <Filter#6.  */,
		Filter7			/*! <Filter#7.  */,
		Filter8			/*! <Filter#8.  */,
		Filter9			/*! <Filter#9.  */,
		Filter10		/*! <Filter#10. */,
		Filter11		/*! <Filter#11. */,
		Filter12		/*! <Filter#12. */,
		Filter13		/*! <Filter#13. */
	};

	/**
	 * Define interrupt handler type (short cut).
	 */
	using MessageHandler = std::function<void(const Message&)>;



	/**
	 * Constructor.
	 * @param ifc defines the interface connected to
	 * @param speed defines the bus speed in bit/s
	 */
	ControllerAreaNetwork(CAN_HandleTypeDef* interface, Platform::BSP::PortPin wakeup);

	bool start();
	bool stop();


	void setMessageHandler(MessageHandler& handler) { _handler=handler; }

	bool enableMessageHandling();
	bool disableMessageHandling();


	void handle(const Message& msg) { _handler(msg); }



	bool filter(FilterBank number, std::uint32_t filterId);

	/**
	 * Send a message using internal buffer (BLOCKING MODE!).
	 * @param msg defines the CAN message to send.
	 * @param useBuffer defines the internal buffer (1..3) to store message.
	 * @return true if sending succeeded or false.
	 */
	bool send(const Message& msg);


private:

	/**
	 * Internal attributes.
	 */
	CAN_HandleTypeDef* _interface;

	Platform::BSP::DigitalOut _wakeupTransceiver;


	std::uint32_t _txMailBox;

	/* --Message handler for incoming messages. */
	MessageHandler _handler=[](const Message& received) { printf("Message received\r\n"); };


};



}


#endif /* BSP_INC_CANIF_H_ */

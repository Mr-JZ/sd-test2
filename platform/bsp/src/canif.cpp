/*
 * canif.cpp
 *
 *  Created on: 13.07.2016
 *      Author: Michael
 */

#include "stm32l4xx_hal.h"

#ifdef HAL_CAN_MODULE_ENABLED
#include "canif.h"


#include "cmsis_os.h"

//#define ENABLE_DEBUG_CAN


#ifdef ENABLE_DEBUG_CAN
#include <cstdio>

/* --Print CAN message. */
static void dump(const Platform::BSP::ControllerAreaNetwork::Message& msg, bool isIncoming = true) {
	static char buffer[64];
	size_t c=0;
	sprintf(buffer+c,"%s",isIncoming?"->":"<-");
	c+=2;
	sprintf(buffer+c,"%04X: ",(unsigned int)msg.identifier);
	c+=6;
	for(size_t i=0;i<8;i++,c+=3)
		if (i<msg.size)
			sprintf(buffer+c,"%02X ",(int)msg.buffer[i]);
		else
			sprintf(buffer+c,".. ");
	printf("%s\r\n",buffer);
}
#endif

/* --Internal pointer to singleton. */
static Platform::BSP::ControllerAreaNetwork* _network = nullptr;


// -- Callback for Receive-FiFo
extern "C" void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan){

	static Platform::BSP::ControllerAreaNetwork::Message message;
	static CAN_RxHeaderTypeDef header;

	HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &header, message.buffer);

	message.size=header.DLC;
	if (header.IDE==CAN_ID_STD) {
		message.type=Platform::BSP::ControllerAreaNetwork::Message::Standard;
		message.identifier=header.StdId;
	}
	else {
		message.type=Platform::BSP::ControllerAreaNetwork::Message::Extended;
		message.identifier=header.ExtId;
	}

#ifdef ENABLE_DEBUG_CAN
	dump(message);
#endif

	/* --Test if network is set (should be!). */
	if (_network) {
		/* --Callback message handler. */
		_network->handle(message);
	}


}


namespace Platform:: BSP {

ControllerAreaNetwork::ControllerAreaNetwork(CAN_HandleTypeDef* interface, Platform::BSP::PortPin wakeup):
		_interface(interface), _wakeupTransceiver(wakeup) {}


bool ControllerAreaNetwork::send(const Message& msg) {
	bool retvalue=false;

	// -- Check if Interface not initialized or message size to big
	if (_interface!=nullptr && msg.size <= msg.MaxDataLengthCounter) {

		/* --Copy data to internal structure. */
		CAN_TxHeaderTypeDef header;

		// -- Define CAN-Message-Header
		header.DLC=msg.size;
		header.RTR = CAN_RTR_DATA;
		header.TransmitGlobalTime = DISABLE;

		if (msg.type==Message::Standard) {
			header.StdId=msg.identifier;
			header.IDE=CAN_ID_STD;
		}
		else {
			header.ExtId=msg.identifier;
			header.IDE=CAN_ID_EXT;
		}

		// -- Add CAN-Message to CAN-Transmit-Buffer
		std::uint8_t* buf=const_cast<std::uint8_t*>(msg.buffer);

		std::uint32_t retry=0;

		bool done=false;
		do {

			/* --Check if at least one tx box is free... */
			if (HAL_CAN_GetTxMailboxesFreeLevel(_interface)) {
				retvalue = HAL_CAN_AddTxMessage(_interface, &header, buf, &_txMailBox)!=HAL_ERROR;
				if (!retvalue)
					printf("FAILURE: CANNOT TX MESSAGE WITH ID 0X%04X!\r\n",(unsigned int)msg.identifier);

				done=true;
			}
			else {
				retry++;
				if (retry>3) {
					printf("FAILURE: ALL CAN TX MAILBOXES ARE FULL!\r\n");
					done=true;
				}
				else
					osDelay(10);
			}

		} while (!done);



#ifdef ENABLE_DEBUG_CAN
		dump(msg,false);
#endif

	}

	return retvalue;
}


bool ControllerAreaNetwork::enableMessageHandling() {
	/* --Set the object to the global variable. */
	_network=this;
	return HAL_CAN_ActivateNotification(_interface, CAN_IT_RX_FIFO0_MSG_PENDING)!=HAL_ERROR;
}


bool ControllerAreaNetwork::disableMessageHandling() {
	bool err = HAL_CAN_DeactivateNotification(_interface, CAN_IT_RX_FIFO0_MSG_PENDING);
	/* --Unset the object to the global variable. */
	_network=nullptr;
	return err;
}


bool ControllerAreaNetwork::filter(FilterBank number, std::uint32_t filterId) {

	CAN_FilterTypeDef filter;

	// -- Define CAN-Filter values
	filter.FilterBank = (uint32_t)number;  		/* FilterBank between 0-13 */
	filter.FilterIdHigh = filterId << 5;		/* Set filter CAN-ID */
	filter.FilterIdLow = 0x0000;
	filter.FilterMaskIdHigh = filterId << 5;	/* Set filter Mask */
	filter.FilterMaskIdLow = 0x0000;

	// -- Default values of CAN-Filter
	filter.FilterActivation = CAN_FILTER_ENABLE;
	filter.FilterFIFOAssignment = CAN_RX_FIFO0;
	filter.FilterMode = CAN_FILTERMODE_IDMASK;
	filter.FilterScale = CAN_FILTERSCALE_32BIT;

	// -- Set CAN-Filter
	return HAL_CAN_ConfigFilter(_interface, &filter)!=HAL_OK;
}


bool ControllerAreaNetwork::start() {
	/* --Wakeup the receiver. */
	_wakeupTransceiver.clear();
	return HAL_CAN_Start(_interface) != HAL_ERROR;
}


bool ControllerAreaNetwork::stop() {
	/* --Set to sendby the transceiver. */
	_wakeupTransceiver.set();

	bool retvalue=HAL_CAN_Stop(_interface) != HAL_ERROR;

	return retvalue;
}

}

#endif

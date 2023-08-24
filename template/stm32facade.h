/*
 * stm32facade.h
 *
 *  Auto created on: Aug 23, 2023, 9:16:01 AM
 *      Author: michael
 *
 * *** DON'T CHANGE BY HAND. WILL BE OVERWRITTEN BY CODE GENERATOR ***
 */

#ifndef STM32FACADE_H_
#define STM32FACADE_H_

#include "stm32l4xx_hal.h"

#include "portpin.h"

namespace Platform::BSP {

class STM32Facade {
public:

	/* --Short-cuts for GPIOs. */
	using _Port=Port::Select;
	using _Pin=Pin::BitMask;

	/* --Port A. */
	inline static const PortPin BaseBoard0{_Port::PortA, _Pin::Pin0};
	inline static const PortPin BaseBoard1{_Port::PortA, _Pin::Pin1};
	inline static const PortPin BaseBoard2{_Port::PortA, _Pin::Pin2};
	inline static const PortPin BaseBoard3{_Port::PortA, _Pin::Pin3};
	inline static const PortPin BaseBoard4{_Port::PortA, _Pin::Pin4};
	inline static const PortPin BaseBoard5{_Port::PortA, _Pin::Pin5};
	inline static const PortPin BaseBoard6{_Port::PortA, _Pin::Pin6};
	inline static const PortPin BaseBoard7{_Port::PortA, _Pin::Pin7};
	inline static const PortPin BaseBoard8{_Port::PortA, _Pin::Pin8};
	inline static const PortPin BaseBoard9{_Port::PortA, _Pin::Pin9};
	inline static const PortPin BaseBoard10{_Port::PortA, _Pin::Pin10};
	inline static const PortPin BaseBoard11{_Port::PortA, _Pin::Pin11};
	inline static const PortPin BaseBoard12{_Port::PortA, _Pin::Pin12};
	inline static const PortPin BaseBoard13{_Port::PortA, _Pin::Pin13};
	inline static const PortPin BaseBoard14{_Port::PortA, _Pin::Pin14};
	inline static const PortPin BaseBoard15{_Port::PortA, _Pin::Pin15};

	/* --Port B. */
	inline static const PortPin BaseBoard16{_Port::PortB, _Pin::Pin0};
	inline static const PortPin BaseBoard17{_Port::PortB, _Pin::Pin1};
	inline static const PortPin BaseBoard18{_Port::PortB, _Pin::Pin2};
	inline static const PortPin BaseBoard19{_Port::PortB, _Pin::Pin3};
	inline static const PortPin BaseBoard20{_Port::PortB, _Pin::Pin4};
	inline static const PortPin BaseBoard21{_Port::PortB, _Pin::Pin5};
	inline static const PortPin BaseBoard24{_Port::PortB, _Pin::Pin8};
	inline static const PortPin BaseBoard25{_Port::PortB, _Pin::Pin9};
	inline static const PortPin BaseBoard26{_Port::PortB, _Pin::Pin10};
	inline static const PortPin BaseBoard27{_Port::PortB, _Pin::Pin11};
	inline static const PortPin BaseBoard28{_Port::PortB, _Pin::Pin12};
	inline static const PortPin BaseBoard29{_Port::PortB, _Pin::Pin13};
	inline static const PortPin BaseBoard30{_Port::PortB, _Pin::Pin14};
	inline static const PortPin BaseBoard31{_Port::PortB, _Pin::Pin15};

	/* --Port C. */
	inline static const PortPin BaseBoard32{_Port::PortC, _Pin::Pin0};
	inline static const PortPin BaseBoard33{_Port::PortC, _Pin::Pin1};
	inline static const PortPin BaseBoard34{_Port::PortC, _Pin::Pin2};
	inline static const PortPin BaseBoard35{_Port::PortC, _Pin::Pin3};
	inline static const PortPin BaseBoard36{_Port::PortC, _Pin::Pin4};
	inline static const PortPin BaseBoard37{_Port::PortC, _Pin::Pin5};
	inline static const PortPin BaseBoard38{_Port::PortC, _Pin::Pin6};
	inline static const PortPin BaseBoard39{_Port::PortC, _Pin::Pin7};
	inline static const PortPin BaseBoard40{_Port::PortC, _Pin::Pin8};
	inline static const PortPin BaseBoard41{_Port::PortC, _Pin::Pin9};
	inline static const PortPin BaseBoard42{_Port::PortC, _Pin::Pin10};
	inline static const PortPin BaseBoard43{_Port::PortC, _Pin::Pin11};
	inline static const PortPin BaseBoard44{_Port::PortC, _Pin::Pin12};
	inline static const PortPin BaseBoard45{_Port::PortC, _Pin::Pin13};
	inline static const PortPin BaseBoard46{_Port::PortC, _Pin::Pin14};
	inline static const PortPin BaseBoard47{_Port::PortC, _Pin::Pin15};

	/* --Port D. */
	inline static const PortPin BaseBoard48{_Port::PortD, _Pin::Pin2};

	/* --Port H. */
	inline static const PortPin BaseBoard49{_Port::PortH, _Pin::Pin0};
	inline static const PortPin BaseBoard50{_Port::PortH, _Pin::Pin1};

	/* --ADC peripheral access. */
	/* --Info: ADC is not configured via CubeIDE. */

	/* --I2C peripheral access. */
	enum class I2C_Peripheral {
		UseUnknown
		,UseI2C1
	};
	static I2C_HandleTypeDef* instance(STM32Facade::I2C_Peripheral device);

	/* --SPI peripheral access. */
	enum class SPI_Peripheral {
		UseUnknown
		,UseSPI1
		,UseSPI2
	};
	static SPI_HandleTypeDef* instance(STM32Facade::SPI_Peripheral device);

	/* --Timer peripheral access. */
	enum class Timer_Peripheral {
		UseUnknown
		,UseTIM5
		,UseTIM8
	};
	static TIM_HandleTypeDef* instance(STM32Facade::Timer_Peripheral device);

	/* --DAC peripheral access. */
	/* --Info: DAC is not configured via CubeIDE. */

	/* --Real Time Clock peripheral access. */
	enum class RTC_Peripheral {
		UseUnknown
		,UseRTC
	};
	static RTC_HandleTypeDef* instance(STM32Facade::RTC_Peripheral device);

	/* --Controller Area Network (CAN) peripheral access. */
	/* --Info: CAN is not configured via CubeIDE. */

};

}

#endif /* STM32FACADE_H_ */

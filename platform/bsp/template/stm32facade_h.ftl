[#ftl]
[#list configs as dt]
[#assign usedIPs =dt.usedIPs]
/*
 * stm32facade.h
 *
 *  Auto created on: ${.now} 
 *      Author: michael
 *
 * *** DON'T CHANGE BY HAND. WILL BE OVERWRITTEN BY CODE GENERATOR ***
 */

#ifndef STM32FACADE_H_
#define STM32FACADE_H_

#include "stm32l4xx_hal.h"

#include "portpin.h"
 
[#assign isADC=usedIPs?seq_contains("ADC1")||usedIPs?seq_contains("ADC2")||usedIPs?seq_contains("ADC3")]
[#assign isI2C=usedIPs?seq_contains("I2C1")||usedIPs?seq_contains("I2C2")||usedIPs?seq_contains("I2C3")]
[#assign isSPI=usedIPs?seq_contains("SPI1")||usedIPs?seq_contains("SPI2")||usedIPs?seq_contains("SSP3")]
[#assign isTIM=usedIPs?seq_contains("TIM1")||usedIPs?seq_contains("TIM2")||usedIPs?seq_contains("TIM3")||
	usedIPs?seq_contains("TIM4")||usedIPs?seq_contains("TIM5")||usedIPs?seq_contains("TIM6")||
	usedIPs?seq_contains("TIM7")||usedIPs?seq_contains("TIM8")||usedIPs?seq_contains("TIM15")||
	usedIPs?seq_contains("TIM16")||usedIPs?seq_contains("TIM17")]
[#assign isDAC=usedIPs?seq_contains("DAC1")]
[#assign isRTC=usedIPs?seq_contains("RTC")]
[#assign isCAN=usedIPs?seq_contains("CAN1")]


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
[#if isADC]	
	enum class ADC_Peripheral { 
		Use_Unknown 
[#list usedIPs as ip]
[#if ip?contains("ADC")]
		,Use${ip}	
[/#if]
[/#list]
	};

	static ADC_HandleTypeDef* instance(STM32Facade::ADC_Peripheral device);
[#else]
	/* --Info: ADC is not configured via CubeIDE. */
[/#if]
	
	/* --I2C peripheral access. */
[#if isI2C]	
	enum class I2C_Peripheral { 
		UseUnknown 
[#list usedIPs as ip]
[#if ip?contains("I2C")]
		,Use${ip}	
[/#if]
[/#list]
	};
	static I2C_HandleTypeDef* instance(STM32Facade::I2C_Peripheral device);
[#else]
	/* --Info: I2C is not configured via CubeIDE. */
[/#if]	
	
	/* --SPI peripheral access. */
[#if isSPI]	
	enum class SPI_Peripheral { 
		UseUnknown 
[#list usedIPs as ip]
[#if ip?contains("SPI")]
		,Use${ip}	
[/#if]
[/#list]
	};
	static SPI_HandleTypeDef* instance(STM32Facade::SPI_Peripheral device);
[#else]
	/* --Info: SPI is not configured via CubeIDE. */
[/#if]	
	
	/* --Timer peripheral access. */
[#if isTIM]	
	enum class Timer_Peripheral { 
		UseUnknown 
[#list usedIPs as ip]
[#if ip?contains("TIM")]
		,Use${ip}	
[/#if]
[/#list]
	};
	static TIM_HandleTypeDef* instance(STM32Facade::Timer_Peripheral device);
[#else]
	/* --Info: Timer is not configured via CubeIDE. */
[/#if]	
	
	/* --DAC peripheral access. */
[#if isDAC]	
	enum class DAC_Peripheral { 
		UseUnknown 
[#list usedIPs as ip]
[#if ip?contains("DAC")]
		,Use${ip}	
[/#if]
[/#list]
	};
	static DAC_HandleTypeDef* instance(STM32Facade::DAC_Peripheral device);
[#else]
	/* --Info: DAC is not configured via CubeIDE. */
[/#if]	
	
	/* --Real Time Clock peripheral access. */
[#if isRTC]	
	enum class RTC_Peripheral { 
		UseUnknown 
[#list usedIPs as ip]
[#if ip?contains("RTC")]
		,Use${ip}	
[/#if]
[/#list]
	};
	static RTC_HandleTypeDef* instance(STM32Facade::RTC_Peripheral device);
[#else]
	/* --Info: RTC is not configured via CubeIDE. */
[/#if]	
	
	/* --Controller Area Network (CAN) peripheral access. */
[#if isCAN]	
	enum class CAN_Peripheral { 
		UseUnknown 
[#list usedIPs as ip]
[#if ip?contains("CAN")]
		,Use${ip}	
[/#if]
[/#list]
	};
	static CAN_HandleTypeDef* instance(STM32Facade::CAN_Peripheral device);
[#else]
	/* --Info: CAN is not configured via CubeIDE. */
[/#if]		
	
	
};

}

#endif /* STM32FACADE_H_ */
[/#list]
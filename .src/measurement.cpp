
#include "measurement.h"

/* --Platform include. */
#include "TaskBase.h"
#include "../template/stm32facade.h"

// Timer defines
static TIM_HandleTypeDef *TIMER_T = nullptr;   // used timer for capture compare

#define IC_CHANNEL TIM_CHANNEL_4      // capture channel

#define OC_CHANNEL_REG CCR3           // compare register for output compare

// HW constants
const uint32_t PulseProUmdr = 2;

const uint32_t maxADC = 4020;  // TODO: check your HW
const uint32_t minADC = 104;  // TODO: check your HW

const uint32_t maxSpeed = 2000;
const uint32_t minSpeed = 750;

uint32_t speed;    ///< istwert
uint32_t soll;     ///< sollwert

// *****************************************************
// *****************************************************

bool initIrqTimer() {
	TIMER_T = Platform::BSP::STM32Facade::instance(
			Platform::BSP::STM32Facade::Timer_Peripheral::UseTIM8);
	bool ret = false;

	ret = (HAL_OK == HAL_TIM_IC_Start_IT(TIMER_T, IC_CHANNEL));
	// Set max overflow at approx. > 1 Sec
	TIMER_T->Init.Prescaler = 1300;
	TIMER_T->Instance->PSC = 1300;
	TIMER_T->Instance->ARR = 0xFFFF;
	if (ret) {
		ret = (HAL_OK == HAL_TIM_OC_Start_IT(TIMER_T, TIM_CHANNEL_3));
		TIMER_T->Instance->OC_CHANNEL_REG = 0x8000;
	}

	return ret;
}

/**
 * @brief calculates timer resolution in ticks per second.
 * @param [in] pTMR Pointer to timer structure.
 * @return ticks per second
 */
uint32_t getTimerTicksPerSecond(TIM_HandleTypeDef *pTMR) {
	uint32_t timPres = pTMR->Init.Prescaler;

	return SystemCoreClock / (timPres + 1);
}

// *****************************************************
// *****************************************************

osThreadId mainTaskId = 0;

extern "C" {
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
	UNUSED(htim);   // prevent compiler warning
	// TODO: Add your code
}

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim) {
	UNUSED(htim);     // 0 revolution Detection, no pulse for 1 second
	// TODO: Add your code
}
}     // end of extern "C"
// *****************************************************

// TODO: Implement your task.


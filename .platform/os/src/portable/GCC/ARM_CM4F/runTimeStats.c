#include "FreeRTOSConfig.h"

#include <stm32l476xx.h>


#ifndef configGENERATE_RUN_TIME_STATS
    #define configGENERATE_RUN_TIME_STATS 0
#endif



#if(configGENERATE_RUN_TIME_STATS == 1)

#include "chip.h"

// Define all possible timers as extern.
// in case the chosen timer in FreeRTOSConfig.h is not configured, we get
// a linker error!
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim8;
extern TIM_HandleTypeDef htim15;
extern TIM_HandleTypeDef htim16;
extern TIM_HandleTypeDef htim17;

static TIM_HandleTypeDef *vRuntimeCounter = NULL;

volatile uint32_t ulHighFrequencyTimerTicks = 0;

void vConfigureTimerForRunTimeStats( void ) {
#ifdef configUsedTimer
    vRuntimeCounter = &configUsedTimer; // defined in FreeRTOSConfig.h
    if(vRuntimeCounter->Instance == TIM2 || vRuntimeCounter->Instance == TIM5)
    {
       HAL_TIM_Base_Start(vRuntimeCounter);
    }
    else
    {
       HAL_TIM_Base_Start_IT(vRuntimeCounter);
    }
#else
#error No Timer specified for runtime stats.
#endif
}

uint32_t vGetRuntimeCounter()
{
    if(vRuntimeCounter->Instance == TIM2 || vRuntimeCounter->Instance == TIM5)
        return __HAL_TIM_GET_COUNTER(vRuntimeCounter);
    else
        return ulHighFrequencyTimerTicks;
}


#else
void vConfigureTimerForRunTimeStats( void ) {}

#endif

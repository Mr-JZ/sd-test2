/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */


/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SW2_Pin GPIO_PIN_0
#define SW2_GPIO_Port GPIOH
#define SW1_Pin GPIO_PIN_1
#define SW1_GPIO_Port GPIOA
#define JoystickLeft_Pin GPIO_PIN_6
#define JoystickLeft_GPIO_Port GPIOA
#define JoystickLeft_EXTI_IRQn EXTI9_5_IRQn
#define JoystickPush_Pin GPIO_PIN_7
#define JoystickPush_GPIO_Port GPIOA
#define JoystickPush_EXTI_IRQn EXTI9_5_IRQn
#define SD_CS_Pin GPIO_PIN_1
#define SD_CS_GPIO_Port GPIOB
#define FAN_INPUT_Capture_Pin GPIO_PIN_9
#define FAN_INPUT_Capture_GPIO_Port GPIOC
#define JoystickUp_Pin GPIO_PIN_8
#define JoystickUp_GPIO_Port GPIOA
#define JoystickUp_EXTI_IRQn EXTI9_5_IRQn
#define JoystickRight_Pin GPIO_PIN_9
#define JoystickRight_GPIO_Port GPIOA
#define JoystickRight_EXTI_IRQn EXTI9_5_IRQn
#define JoyStickDownIRQ_Pin GPIO_PIN_10
#define JoyStickDownIRQ_GPIO_Port GPIOA
#define JoyStickDownIRQ_EXTI_IRQn EXTI15_10_IRQn
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define HW_I2C_SDA_Pin GPIO_PIN_9
#define HW_I2C_SDA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32g4xx_hal.h"

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Green_LED_Pin GPIO_PIN_13
#define Green_LED_GPIO_Port GPIOC
#define Monnayeur_Counter_Pin GPIO_PIN_14
#define Monnayeur_Counter_GPIO_Port GPIOC
#define Monnayeur_Stop_Pin GPIO_PIN_15
#define Monnayeur_Stop_GPIO_Port GPIOC
#define Effect_Hall_Pin GPIO_PIN_0
#define Effect_Hall_GPIO_Port GPIOF
#define _2L9_Pin GPIO_PIN_1
#define _2L9_GPIO_Port GPIOF
#define _1B1_Pin GPIO_PIN_2
#define _1B1_GPIO_Port GPIOC
#define _1B2_Pin GPIO_PIN_3
#define _1B2_GPIO_Port GPIOC
#define _1B3_Pin GPIO_PIN_0
#define _1B3_GPIO_Port GPIOA
#define _1B4_Pin GPIO_PIN_1
#define _1B4_GPIO_Port GPIOA
#define _1B5_Pin GPIO_PIN_2
#define _1B5_GPIO_Port GPIOA
#define _1B6_Pin GPIO_PIN_3
#define _1B6_GPIO_Port GPIOA
#define _1B7_Pin GPIO_PIN_4
#define _1B7_GPIO_Port GPIOA
#define _1B8_Pin GPIO_PIN_5
#define _1B8_GPIO_Port GPIOA
#define _1B9_Pin GPIO_PIN_6
#define _1B9_GPIO_Port GPIOA
#define _1B10_Pin GPIO_PIN_7
#define _1B10_GPIO_Port GPIOA
#define _2B1_Pin GPIO_PIN_4
#define _2B1_GPIO_Port GPIOC
#define _2B2_Pin GPIO_PIN_5
#define _2B2_GPIO_Port GPIOC
#define _2B3_Pin GPIO_PIN_0
#define _2B3_GPIO_Port GPIOB
#define _2B4_Pin GPIO_PIN_1
#define _2B4_GPIO_Port GPIOB
#define _2B5_Pin GPIO_PIN_2
#define _2B5_GPIO_Port GPIOB
#define _2B6_Pin GPIO_PIN_10
#define _2B6_GPIO_Port GPIOB
#define _2B7_Pin GPIO_PIN_11
#define _2B7_GPIO_Port GPIOB
#define _2B8_Pin GPIO_PIN_12
#define _2B8_GPIO_Port GPIOB
#define _2B9_Pin GPIO_PIN_13
#define _2B9_GPIO_Port GPIOB
#define _2B10_Pin GPIO_PIN_14
#define _2B10_GPIO_Port GPIOB
#define Button_Start_Pin GPIO_PIN_15
#define Button_Start_GPIO_Port GPIOB
#define Button_Select_Pin GPIO_PIN_6
#define Button_Select_GPIO_Port GPIOC
#define _1L1_Pin GPIO_PIN_7
#define _1L1_GPIO_Port GPIOC
#define _1L2_Pin GPIO_PIN_8
#define _1L2_GPIO_Port GPIOC
#define _1L3_Pin GPIO_PIN_9
#define _1L3_GPIO_Port GPIOC
#define _1L4_Pin GPIO_PIN_8
#define _1L4_GPIO_Port GPIOA
#define _1L5_Pin GPIO_PIN_9
#define _1L5_GPIO_Port GPIOA
#define _1L6_Pin GPIO_PIN_10
#define _1L6_GPIO_Port GPIOA
#define _1L7_Pin GPIO_PIN_11
#define _1L7_GPIO_Port GPIOA
#define _1L8_Pin GPIO_PIN_12
#define _1L8_GPIO_Port GPIOA
#define _1L9_Pin GPIO_PIN_15
#define _1L9_GPIO_Port GPIOA
#define _1L10_Pin GPIO_PIN_10
#define _1L10_GPIO_Port GPIOC
#define _2L1_Pin GPIO_PIN_11
#define _2L1_GPIO_Port GPIOC
#define _2L2_Pin GPIO_PIN_12
#define _2L2_GPIO_Port GPIOC
#define _2L3_Pin GPIO_PIN_2
#define _2L3_GPIO_Port GPIOD
#define _2L4_Pin GPIO_PIN_3
#define _2L4_GPIO_Port GPIOB
#define _2L5_Pin GPIO_PIN_4
#define _2L5_GPIO_Port GPIOB
#define _2L6_Pin GPIO_PIN_5
#define _2L6_GPIO_Port GPIOB
#define _2L7_Pin GPIO_PIN_6
#define _2L7_GPIO_Port GPIOB
#define _2L8_Pin GPIO_PIN_7
#define _2L8_GPIO_Port GPIOB
#define _2L10_Pin GPIO_PIN_9
#define _2L10_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

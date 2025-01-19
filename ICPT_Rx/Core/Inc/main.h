/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32f3xx_hal.h"

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
#define ADC_VDC_Pin GPIO_PIN_0
#define ADC_VDC_GPIO_Port GPIOA
#define ADC_IIN_Pin GPIO_PIN_4
#define ADC_IIN_GPIO_Port GPIOA
#define LED_R_Pin GPIO_PIN_6
#define LED_R_GPIO_Port GPIOA
#define LED_G_Pin GPIO_PIN_7
#define LED_G_GPIO_Port GPIOA
#define LED_B_Pin GPIO_PIN_0
#define LED_B_GPIO_Port GPIOB
#define TMP_ALERT_Pin GPIO_PIN_12
#define TMP_ALERT_GPIO_Port GPIOB
#define TMP_SCL_Pin GPIO_PIN_13
#define TMP_SCL_GPIO_Port GPIOB
#define TMP_SDA_Pin GPIO_PIN_14
#define TMP_SDA_GPIO_Port GPIOB
#define BUZZER_Pin GPIO_PIN_12
#define BUZZER_GPIO_Port GPIOA
#define KEY2_Pin GPIO_PIN_4
#define KEY2_GPIO_Port GPIOB
#define KEY2_EXTI_IRQn EXTI4_IRQn
#define KEY1_Pin GPIO_PIN_5
#define KEY1_GPIO_Port GPIOB
#define KEY1_EXTI_IRQn EXTI9_5_IRQn
#define OLED_SCL_Pin GPIO_PIN_6
#define OLED_SCL_GPIO_Port GPIOB
#define OLED_SDA_Pin GPIO_PIN_7
#define OLED_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
// LED
#define LED_R(x) HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, x)
#define LED_G(x) HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, x)
#define LED_B(x) HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, x)
// BUZZER
#define BUZZER_TIM htim16
#define BUZZER_TIM_CHANNEL TIM_CHANNEL_1
#define BUZZER_ON HAL_TIM_PWM_Start(&BUZZER_TIM, BUZZER_TIM_CHANNEL)
#define BUZZER_OFF HAL_TIM_PWM_Stop(&BUZZER_TIM, BUZZER_TIM_CHANNEL)
// TEMP
#define TMP_TIM htim6
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

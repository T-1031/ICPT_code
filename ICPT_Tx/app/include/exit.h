#ifndef _EXIT_H
#define _EXIT_H

#include "main.h"
#include "sample.h"
#include "string.h"
#include "connect.h"

extern HRTIM_HandleTypeDef hhrtim1;
extern TIM_HandleTypeDef BUZZER_TIM;
extern UART_HandleTypeDef huart2;
extern uint8_t order_hrtim;

#endif // !_EXIT_H

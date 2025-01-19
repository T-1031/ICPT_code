#ifndef _TEMP_H
#define _TEMP_H

#include "main.h"

#define TMP_ADD 0x90 // 最后一位为 R/#W
#define REG_CONFIG 0x01
#define REG_TLOW 0x02
#define REG_THIGH 0x03

#define TMP_W_SCL(x)   HAL_GPIO_WritePin(TMP_SCL_GPIO_Port, TMP_SCL_Pin, x)
#define TMP_W_SDA(x)   HAL_GPIO_WritePin(TMP_SDA_GPIO_Port, TMP_SDA_Pin, x)

void TMP_Init(void);
void TMP_Alert_Config(uint32_t T_high, uint32_t T_low);

#endif // !_TEMP_H

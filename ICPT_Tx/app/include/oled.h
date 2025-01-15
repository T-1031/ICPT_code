#ifndef _OLED_H
#define __OLED_H

#include "main.h"

#define OLED_W_SCL(x)   HAL_GPIO_WritePin(OLED_SCL_GPIO_Port, OLED_SCL_Pin, x)
#define OLED_W_SDA(x)   HAL_GPIO_WritePin(OLED_SDA_GPIO_Port, OLED_SDA_Pin, x)
#define OLED_GPIO_Init()

void OLED_Init(void);                                                                  //OLED��ʼ��
void OLED_Clear(void);                                                                 //OLED����
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);                           //OLED��ʾ�����ַ�
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);                      //OLED��ʾ�ַ���
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);      //OLED��ʾ�޷�����
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length); //OLED��ʾ�з�����
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);   //OLED��ʾʮ��������
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);   //OLED��ʾ��������

#endif

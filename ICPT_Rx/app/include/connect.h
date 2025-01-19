#ifndef _CONNECT_H
#define _CONNECT_H

#include "main.h"

// 发送ID
#define CAN_ID0  0x030
// 接收ID
#define CAN_ID1  0x02F
#define CAN_ID2  0x02E
#define CAN_ID3  0x000
#define CAN_ID4  0x000

void CAN_Receive_Config(void);
void CAN_Send_Message(uint8_t *data);

extern CAN_HandleTypeDef hcan;

#endif // !_CONNECT_H

#include "connect.h"

/// @brief CAN 接收过滤配置
void CAN_Receive_Config(void)
{
    CAN_FilterTypeDef Filter0;
    CAN_FilterTypeDef Filter1;

    Filter0.FilterBank = 0;                      
    Filter0.FilterMode = CAN_FILTERMODE_IDLIST;  
    Filter0.FilterScale = CAN_FILTERSCALE_16BIT;
    Filter0.FilterIdHigh = CAN_ID1 << 5;              
    Filter0.FilterIdLow = CAN_ID2 << 5;
    Filter0.FilterMaskIdHigh = CAN_ID3 << 5;          
    Filter0.FilterMaskIdLow = CAN_ID4 << 5;
    Filter0.FilterFIFOAssignment = CAN_RX_FIFO0; 
    Filter0.FilterActivation = ENABLE;           

    if (HAL_CAN_ConfigFilter(&hcan, &Filter0) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_CAN_ActivateNotification(&hcan ,CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
    {
        Error_Handler();
    }

    Filter1.FilterBank = 1;                      
    Filter1.FilterMode = CAN_FILTERMODE_IDMASK;  
    Filter0.FilterScale = CAN_FILTERSCALE_16BIT;
    Filter0.FilterIdHigh = 0x000 << 5;              
    Filter0.FilterIdLow = 0x000 << 5;
    Filter0.FilterMaskIdHigh = 0x000 << 5;          
    Filter0.FilterMaskIdLow = 0x000 << 5;
    Filter0.FilterFIFOAssignment = CAN_RX_FIFO1; 
    Filter0.FilterActivation = ENABLE;           

    if (HAL_CAN_ConfigFilter(&hcan, &Filter1) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_CAN_ActivateNotification(&hcan ,CAN_IT_RX_FIFO1_MSG_PENDING) != HAL_OK)
    {
        Error_Handler();
    }
    
    if (HAL_CAN_Start(&hcan) != HAL_OK)
    {
        Error_Handler();
    }
}

/// @brief CAN 发送消息
/// @param data 待发送的消息
void CAN_Send_Message(uint8_t *data)
{
    CAN_TxHeaderTypeDef TxHeader;
    uint32_t Tx_Mailbox;

    TxHeader.StdId = CAN_ID0;
    TxHeader.ExtId = 0;
    TxHeader.IDE = CAN_ID_STD;
    TxHeader.RTR = CAN_RTR_DATA;
    TxHeader.DLC = 4;

    HAL_CAN_AddTxMessage(&hcan, &TxHeader, data, &Tx_Mailbox);
}

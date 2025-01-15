#include "exit.h"

/// @brief HRTIM REP 事件中断回调函数，f = 50kHz
void HAL_HRTIM_RepetitionEventCallback(HRTIM_HandleTypeDef * hhrtim, uint32_t TimerIdx)
{
    if (hhrtim == &hhrtim1)
    {
        if (TimerIdx == HRTIM_TIMERINDEX_TIMER_A)
        {
            Resolve_ADC();
        }
        
    }
    
}

/// @brief 外部中断回调函数
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == KEY1_Pin) // 发送消息
    {
        uint8_t data_to_send[4] = {0};
        int data1 = (int32_t)VIN.ave_value;
        int data2 = (int32_t)IIN.ave_value;

        static uint8_t count = 0;

        if (count == 0)
        {
            count = 1;
            memcpy(data_to_send, &data1, 4);
        }
        else
        {
            count = 0;
            memcpy(data_to_send, &data2, 4);
        }
        LED_G(1);
        HAL_UART_Transmit_IT(&huart2, data_to_send, 4);
        // CAN_Send_Message(data_to_send);
    }
    else if (GPIO_Pin == KEY2_Pin) // BUZZER
    {
       static uint8_t on = 0;
       if (on == 0)
       {
            on = 1;
            BUZZER_ON;
       }
       else
       {
            on = 0;
            BUZZER_OFF;
       } 
    }
}

/// @brief USART 接收中断
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart == &huart2)
    {
        if (order_hrtim == 0x01)
        {
            INVERT_ON;
        }
        else if (order_hrtim == 0x00)
        {
            INVERT_OFF;
        }
    }
    
}
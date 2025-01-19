#include "exit.h"

/// @brief HRTIM REP 事件中断回调函数，f = 50kHz
/// @param hhrtim 
/// @param TimerIdx 
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
/// @param GPIO_Pin 
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
        LED_B(1);
        HAL_UART_Transmit_IT(&huart2, data_to_send, 4);
        // CAN_Send_Message(data_to_send);
    }
    else if (GPIO_Pin == KEY2_Pin) // BUZZER
    {
       static uint8_t on = 0;
       if (on == 0)
       {
            on = 1;
            INVERT_ON;
            LED_B(1);
       }
       else
       {
            on = 0;
            INVERT_OFF;
            LED_B(0);
       } 
    }
}

/// @brief USART 发送中断
/// @param huart 
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart == &huart2)
    {
        LED_B(0);
    }
    
}

/// @brief USART 接收中断
/// @param huart 
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart == &huart2)
    {
        if (order_hrtim == 0x01)
        {
            INVERT_ON;
            LED_B(1);
        }
        else if (order_hrtim == 0x00)
        {
            INVERT_OFF;
            LED_B(0);
        }
    }
    
}

/// @brief 定时器中断
/// @param htim 
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &TMP_TIM) // 读取温度警报
    {
        if (!HAL_GPIO_ReadPin(TMP_ALERT_GPIO_Port, TMP_ALERT_Pin))
        {
            BUZZER_ON;
            LED_R(1);
        }
        else
        {
            BUZZER_OFF;
            LED_R(0);
        }
    }
    
}

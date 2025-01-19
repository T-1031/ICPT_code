#include "temp.h"

/// @brief I2C 启动信号
void TMP_I2C_Start(void)
{
    TMP_W_SDA(1);
    TMP_W_SCL(1);
    TMP_W_SDA(0);
    TMP_W_SCL(0);
}

/// @brief I2C 停止信号
void TMP_I2C_Stop(void)
{
    TMP_W_SDA(0);
    TMP_W_SCL(1);
    TMP_W_SDA(1);
}

/// @brief I2C 发送一个字节
/// @param Byte 待发送数据
void TMP_I2C_SendByte(uint8_t Byte)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        TMP_W_SDA(Byte & (0x80 >> i));
        TMP_W_SCL(1);
        TMP_W_SCL(0);
    }
    // 忽略 ACK
    TMP_W_SCL(1);
    TMP_W_SCL(0);
}

/// @brief 十进制温度转化为 TMP112 格式高八位
/// @param Temp 待转化十进制温度
/// @return 高八位
uint8_t TMP_Invert_MSB(uint32_t Temp)
{
    uint8_t MSB;

    MSB = ((Temp * 16) >> 4) & 0xFF;

    return MSB;
}

/// @brief 十进制温度转化为 TMP112 格式的低八位
/// @param Temp 待转化十进制温度
/// @return 低八位
uint8_t TMP_Invert_LSB(uint32_t Temp)
{
    uint8_t LSB;

    LSB = ((Temp * 16) & 0x0F) << 4;

    return LSB;
}

/// @brief 初始化配置寄存器
void TMP_Init(void)
{
    uint8_t MSB = 0x60;
    uint8_t LSB = 0xA0;
    
    TMP_I2C_Start(); // 启动信号
    TMP_I2C_SendByte(TMP_ADD); // 目标地址
    TMP_I2C_SendByte(REG_CONFIG); // 指针寄存器
    TMP_I2C_SendByte(MSB); // 待配置数据
    TMP_I2C_SendByte(LSB);
    TMP_I2C_Stop(); // 停止信号
}

/// @brief 配置警报温度
/// @param T_high 超过该温度发出警报
/// @param T_low 降到该温度以下解除警报
void TMP_Alert_Config(uint32_t T_high, uint32_t T_low)
{
    uint8_t MSB, LSB;

    // 配置 T_low
    MSB = TMP_Invert_MSB(T_low);
    LSB = TMP_Invert_LSB(T_low);
    TMP_I2C_Start();
    TMP_I2C_SendByte(TMP_ADD);
    TMP_I2C_SendByte(REG_TLOW);
    TMP_I2C_SendByte(MSB);
    TMP_I2C_SendByte(LSB);
    TMP_I2C_Stop();

    // 配置 T_high
    MSB = TMP_Invert_MSB(T_high);
    LSB = TMP_Invert_LSB(T_high);
    TMP_I2C_Start();
    TMP_I2C_SendByte(TMP_ADD);
    TMP_I2C_SendByte(REG_THIGH);
    TMP_I2C_SendByte(MSB);
    TMP_I2C_SendByte(LSB);
    TMP_I2C_Stop();
}

# ICPT 发射端代码
## 外部功能

KET1：按第一下发送 Vin，按第二下发送 Iin  
KEY2：按一下开蜂鸣器，第二下关

蜂鸣器由 TIM16 控制

温度传感器工作在比较器模式，温度大于 T_HIGH 时 ALERT 位被拉低，直至温度小于 T_LOW 时恢复高电平  
ALERT 位的读取放在定时器中断中，频率为 10 Hz

## 逆变器控制

由 HRTIM1 Timer A & B 分别输出两路互补的带死区 PWM  
PWM 频率为 110 kHz  
Timer A 在 CMP1 置位，CMP3 复位；Timer B 在 CMP2 置位，CMP4 复位；CMP 值的设置由导通角和死区时间决定，具体见 `PWM_calculation.m`

Timer A 连接逆变电路 A 相（靠近直流输入），Timer B 连接 B 相（靠近交流输出）

PWM 输出通道的开关由串口控制，串口接收到 `0x00` 时关闭输出，接收到 `0x01` 时开启输出

## 采样

在 HRTIM1 的 REP 中断中进行采样。  
Reptition Counter 设置为 1，从而得到 REP 中断触发频率为 55 kHz。

ADC1 CH1 采 Vin，ADC2 CH1 采 Iin

VIN = 20.6 * ADC_VIN  
IIN = 3.35 * ADC_IIN

now_value = K * ADC_Result + B  
ave_value = now_value * lowpass_a + ave_value * (1 - lowpass_a)
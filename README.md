# ICPT 发射端代码
## 外部功能

KET1：按第一下发送 Vin，按第二下发送 Iin  
KEY2：按一下开蜂鸣器，第二下关

蜂鸣器由 TIM16 控制

## 逆变器控制

由 HRTIM1 Timer A & B 分别输出两路互补的带死区 PWM  
PWM 频率为 110 kHz  
Timer A 在 CMP1 置位，CMP3 复位；Timer B 在 CMP2 置位，CMP4 复位；CMP 值的设置由导通角和死区时间决定，具体见 `PWM_calculation.m`

Timer A 连接逆变电路 A 相（靠近直流输入），Timer B 连接 B 相（靠近交流输出）

## 采样

在 HRTIM1 的 REP 中断中进行采样。  
Reptition Counter 设置为 1，从而得到 REP 中断触发频率为 55 kHz。

ADC1 CH1 采 Vin，ADC2 CH1 采 Iin


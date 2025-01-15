#include "sample.h"

uint16_t ADC1_Result;
uint16_t ADC2_Result;
__attribute__((section("ccmram"))) ADC_Data_t VIN, IIN;

/// @brief 初始化ADC
void Init_ADC(void)
{
    //ADC采样校准
    HAL_ADCEx_Calibration_Start(&hadc1,ADC_SINGLE_ENDED);
	HAL_ADCEx_Calibration_Start(&hadc2,ADC_SINGLE_ENDED);
    //ADC和DMA初始化
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)ADC1_Result, 1);
	HAL_ADC_Start_DMA(&hadc2, (uint32_t *)ADC2_Result, 1);
}

/// @brief 配置ADC参数
/// @param ADC_value ADC数据结构体
/// @param ADC_buffer ADC输出数组
/// @param proportion 线性矫正K值
/// @param offset 线性矫正B值
/// @param lowpass_a 低通滤波值
void ADC_Data_Config(ADC_Data_t *ADC_value, uint16_t *ADC_buffer, float proportion, float offset, float lowpass_a, ADC_type_t type)
{
	ADC_value->ave_value = 0;
	ADC_value->now_value = 0;
	ADC_value->lowpass_a = lowpass_a;
	ADC_value->conversion.offset = offset;
	ADC_value->conversion.proportion = proportion;
	ADC_value->ADC_value = ADC_buffer;
	ADC_value->type = type;
}

/// @brief 初始化ADC数据结构体
void Init_ADC_Data(void)
{
	ADC_Data_Config(&VIN, &ADC1_Result, CAL_VIN_K, CAL_VIN_B, VIN_LOWPASS_A, type_voltage);
	ADC_Data_Config(&IIN, &ADC2_Result, CAL_IIN_K, CAL_IIN_B, IIN_LOWPASS_A, type_voltage);
}

/// @brief 获取ADC数值
/// @param ADC ADC数据存储结构体
__attribute__((section("ccmram"))) void Get_ADC(ADC_Data_t *ADC)
{
	ADC->now_value = ADC->conversion.proportion * *(ADC->ADC_value) + ADC->conversion.offset;
	ADC->ave_value = LowPass(ADC->now_value, ADC->ave_value, ADC->lowpass_a);
}

/// @brief 解算ADC数值
__attribute__((section("ccmram"))) void Resolve_ADC(void)
{
	Get_ADC(&VIN);
	Get_ADC(&IIN);
}


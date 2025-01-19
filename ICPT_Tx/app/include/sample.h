#ifndef _SAMPLE_H
#define _SAMPLE_H

#include "main.h"
#include "adc.h"
#include "mathfun.h"

// ADC矫正参数
#define CAL_VIN_K 20.6f
#define CAL_VIN_B 0.01f
#define CAL_IIN_K 3.35f
#define CAL_IIN_B 0.01f

// 低通滤波系数
#define VIN_LOWPASS_A 0.08f
#define IIN_LOWPASS_A 0.08f

typedef enum
{
    type_voltage,
    type_current
}ADC_type_t;

typedef struct
{
    uint16_t *ADC_value;
    struct
    {
        float proportion;
        float offset;
    }conversion;
    float now_value;
    float ave_value;
    float lowpass_a;
    ADC_type_t type;
}ADC_Data_t;

extern uint16_t ADC1_Result;
extern uint16_t ADC2_Result;
extern ADC_Data_t VIN, IIN;

void Init_ADC(void);
void Init_ADC_Data(void);
void Get_ADC(ADC_Data_t *ADC);
void Resolve_ADC(void);

#endif // !_SAMPLE_H

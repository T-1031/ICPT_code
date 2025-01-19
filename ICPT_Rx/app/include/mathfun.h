#ifndef _MATHFUN_H_
#define _MATHFUN_H_
#include "main.h"
// ͨ�ú���
#define TYPE_LINK(fun, type) fun##_##type
#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))
#define abs(x) ((x) > 0 ? (+(x)) : (-(x)))
#define sign(x) ((x) > 0 ? (+1) : ((x) < 0 ? (-1) : 0))
#if USED_DECIMAL_COMPUTE == 0
#define Floor(x) (int32_t)(x)
#define Mod1(x) (int32_t)(((x)-Floor(x)) * 100)
#define LowPass(now, ave, a) ((now) * (a) + (ave) * (1 - (a)))
#endif
// ����С������
#if USED_DECIMAL_COMPUTE == 1
typedef int32_t DecimalElem_t;
#define DECIMAL_OFFSET 10                                                                         // ����С��ƫ��
#define DECIMAL_OFFSET_VAVLE ((int32_t)(1 << DECIMAL_OFFSET))                                     // ����С��ƫ��ʵ��ֵ
#define FRACTION_PART (DECIMAL_OFFSET_VAVLE - 1)                                                  // ����С����������λ
#define Mul(a, b) (((a) * (b)) >> DECIMAL_OFFSET)                                                 // ����˷�����
#define Div(a, b) (((int64_t)(a) << DECIMAL_OFFSET) / (b))                                        // �����������
#define LowPass(now, ave, a) ((now * (a) + ave * (DECIMAL_OFFSET_VAVLE - (a))) >> DECIMAL_OFFSET) // �����ͨ�˲�
#define Floor(a) ((a) >> DECIMAL_OFFSET)                                                          // ������������
#define Mod1(a) (((a)-Floor(a)) * 100 >> DECIMAL_OFFSET)                                          // ����С������
#define Float2Decimal(a) ((int32_t)((a)*DECIMAL_OFFSET_VAVLE))                                    // ������ת���ɶ���С��
#define Decimal2Float(a) (((a) / (float)DECIMAL_OFFSET_VAVLE))                                    // ����С��ת���ɸ�����
#endif

float Constrain_float(float amt, float high, float low);
int16_t Constrain_int16(int16_t amt, int16_t high, int16_t low);
int32_t Constrain_int32(int32_t amt, int32_t high, int32_t low);

float DeadZone_float(float amt, float high, float low);
int16_t DeadZone_int16(int16_t amt, int16_t high, int16_t low);
int32_t DeadZone_int32(int32_t amt, int32_t high, int32_t low);

float Anti_DeadZone_float(float amt, float positive_offset, float negative_offset);
int16_t Anti_DeadZone_int16(int16_t amt, int16_t positive_offset, int16_t negative_offset);
int32_t Anti_DeadZone_int32(int32_t amt, int32_t positive_offset, int32_t negative_offset);

float Ramp_float(float target_value,float current_value,float step_length);
int32_t Ramp_int32(int32_t target_value,int32_t current_value,int32_t step_length);
int16_t Ramp_int16(int16_t target_value,int16_t current_value,int16_t step_length);

#endif

/*
 * @Descripttion: 滤波函数 
 * @version: 1.0
 * @Author: hxk
 * @Date: 2020-10-08 16:31:56
 * @LastEditors: hxk
 * @LastEditTime: 2020-10-08 16:50:39
 */

#include "filter.h"
#include "main.h"
#include <math.h>

float lowpass_1order(float vi,float vk_1,float sample_freq,float cutfreq)
{
    float rc = 1.0 / 2.0 / 3.1415926535 / cutfreq;
    float cof1 = 1/(1+rc*sample_freq);
    float cof2 = rc*sample_freq/(1+rc*sample_freq);
    float vk = vi * cof1 + vk_1 * cof2;
    return vk;
}

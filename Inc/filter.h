/*
 * @Descripttion: 
 * @version: 1.0
 * @Author: hxk
 * @Date: 2020-10-08 16:32:09
 * @LastEditors: hxk
 * @LastEditTime: 2020-10-08 16:51:27
 */
#ifndef __FILTER_H
#define __FILTER_H

#include "filter.h"
#include "main.h"

float lowpass_1order(float vi,float vk_1,float sample_freq,float cutfreq);

#endif
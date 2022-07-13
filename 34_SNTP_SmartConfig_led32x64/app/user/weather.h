#ifndef __WEATHER_H__
#define __WEATHER_H__
#include <stdio.h>
#include <stdint.h>

#include "c_types.h"			// 变量类型

uint8_t GetHumid();
uint8_t GetTempear();
void SetTempear(uint8_t wea);
void SetHumid(uint8_t humi);
#endif

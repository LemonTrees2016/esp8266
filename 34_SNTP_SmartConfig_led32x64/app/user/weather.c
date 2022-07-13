
#include <math.h>       /* ceil */
#include "LEDMatrix.h"
#include <stdint.h>

#include <stdarg.h>
#include <stdlib.h>

uint8_t tempera = 33;
uint8_t humid = 22;


uint8_t GetTempear()
{
	return tempera;
}

void SetTempear(uint8_t wea)
{
	tempera = wea;
}


uint8_t GetHumid()
{
	return humid;
}

void SetHumid(uint8_t humi)
{
	humid = humi;
}






#ifndef __LED_MATRIX_MAIN_H__
#define __LED_MATRIX_MAIN_H__

#include <stdint.h>

void led_matrix();
void drawNumslot(int x, int y, int num, int slot);
extern uint8_t hour_to_close;
extern uint8_t minit_to_close;
extern uint8_t hour_to_open;
extern uint8_t minit_to_open;
#endif

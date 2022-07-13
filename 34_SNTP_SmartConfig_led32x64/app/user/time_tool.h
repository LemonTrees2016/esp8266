#ifndef __TIME_TOOL_H__
#define __TIME_TOOL_H__
#include <stdio.h>
#include <stdint.h>

#include "c_types.h"			// 变量类型

// 鏃堕棿缁撴瀯
typedef struct TimerStru{
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minit;
	uint8_t sec;
} TimerStrus;

void time_display();
void set_disp_flag(void);
void clear_disp_flag(void);
uint8_t get_disp_flag(void);
TimerStrus* GetTimerAddr(void);
void setTimeLocal(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minit, uint8_t sec);
void get_set_time();
void set_time_sntp(const char *const posix_tz, int server_cnt, ...);

#endif


#include <math.h>       /* ceil */
#include "LEDMatrix.h"
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include "time_tool.h"

#include <stdarg.h>
#include <stdlib.h>


// 闁告帡鏀遍弻濠囧及閸撗佷粵闁汇劌瀚悥锝堢疀濡炲墽绉撮柨娑樿嫰椤┭囧几濠婏拷鐠愶拷1闁挎稑鑻銊╂閿熺晫鎲版担绋跨厱闁哄倻澧楀Ο澶岀矆閻氬骞�
uint8_t display_flag = 1;

// 濞ｅ洦绻傞悺銊╁籍閸洘锛�
TimerStrus timer_disp={2020, 12, 20, 17, 54, 22};

// 闁兼儳鍢茶ぐ鍥捶閺夋寧绲�
uint8_t* get_disp_flag_addr(void)
{
    return &display_flag;
}

// 闁哄秴娲ょ换鏃傜磾閿燂拷1
void set_disp_flag(void)
{
    display_flag = 1;
}

// 闁哄秴娲ょ换鏃傜磾閿燂拷0
void clear_disp_flag(void)
{
    display_flag = 1;
}

// 闁兼儳鍢茶ぐ鍥冀閸パ呯
uint8_t get_disp_flag(void)
{
	return display_flag;
}


// 闁兼儳鍢茶ぐ鍥籍閸洘锛熷ǎ鍥ｅ墲娴硷拷
TimerStrus* GetTimerAddr(void)
{
    return &timer_disp;
}

// 閻犱礁澧介悿鍡涘籍閸洘锛�
void setTimeLocal(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minit, uint8_t sec)
{
    TimerStrus* timer_disp_ptr = GetTimerAddr();
	timer_disp_ptr->year = year;
	timer_disp_ptr->month = month;
	timer_disp_ptr->day = day;
	timer_disp_ptr->hour = hour;
	timer_disp_ptr->minit = minit;
	timer_disp_ptr->sec = sec;
	return;
}


// 閻犲洩顕цぐ鍥╁寲閼姐倗鍩犻柡鍐ㄧ埣濡潡鏁嶇仦鍊熷珯闁告劖鐟ラ崣鍡涘礂閵娿儳婀伴柛娆愶耿閸ｏ拷
void get_set_time()
{
	time_t tNow =time(NULL);
	struct tm* ptm = localtime(&tNow);

	setTimeLocal(ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday, 
				 ptm->tm_hour, ptm->tm_min, ptm->tm_sec);

	//set_disp_flag();
    return;
}


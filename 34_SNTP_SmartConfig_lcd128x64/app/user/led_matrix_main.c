#include <math.h>       /* ceil */

#include "LEDMatrix.h"
#include <stdint.h>

#include <time.h>
#include <sys/time.h>

#include "code_dict.h"
#include "gpio16.h"
#include "eagle_soc.h"			// GPIO鍑芥暟銆佸畯瀹氫箟

#include "c_types.h"			// 鍙橀噺绫诲瀷

#include "osapi.h"  			// os_XXX銆佽蒋浠跺畾鏃跺櫒
#include "time_tool.h"			// 鍙橀噺绫诲瀷
#include "LEDMatrix.h"			// 鍙橀噺绫诲瀷

# if 0
	#define A 15
	#define B 13
	#define C 12 // 16-<
	#define D 14
	#define STB 16
	#define CLK 2 // 25-<14-<17
	#define R1 4
	#define R2 5
#else
	#define A 4 // D2
	#define B 2 // D4
	#define C 5 // D1
	#define D 14// D5
	#define STB 13 // D7
	#define CLK 16 // D0
	#define R1 12  // D6
	#define R2 15  // D8
#endif


#define OE 22

#define WIDTH   64
#define HEIGHT  32

uint8_t blinktime=4;
uint8_t blinkinterval=80;
uint8_t displaybufg[256];


void led_matrix();


/*  
 * 閸旂喕鍏橀敍姘壌閹圭敂閿涘瘔閸ф劖鐖ｉ敍灞惧鐠愭繃鏆熺�涙鍩岄崶鍓у娑擄拷
 * 
 * 鐠囧瓨妲戦敍锟�
 * 		x閿涙俺顢戦崸鎰垼閿涘苯褰ч張锟�1鐞涘矉绱濈�电懓绨叉担宥咁啍娑擄拷16
 * 		y閿涙艾鍨崸鎰垼閿涘本婀�8閸掓绱濈�电懓绨叉担宥咁啍娑擄拷64
 * 		num閿涙碍鏆熺�涙绱濋崣顏呮箒[0,9]
 */
void drawNum(int x, int y, int num)
{
	// 閹风柉绀夐弫鐗堝祦
	int i;
	for (i = 0; i < COLUMN_WID; i++) {
		displaybufg[(x % 2) * 128 + i * 8 + y] = data_bit_dat[num][i];
	}
}

// 閺囧瓨鏌婇弮鍫曟？
void proc_time()
{
	TimerStrus* timer_disp_ptr = GetTimerAddr();

	// 楠炵繝鍞�4娴ｏ拷
	drawNum(1, 0, (timer_disp_ptr->year / 1000));
	drawNum(1, 1, (timer_disp_ptr->year / 100) % 10);
	drawNum(1, 2, (timer_disp_ptr->year % 100) / 10);
	drawNum(1, 3, timer_disp_ptr->year % 10);

	// 閺堝牅鍞ら敍锟�2娴ｏ拷
	drawNum(1, 4, (timer_disp_ptr->month % 100) / 10);
	drawNum(1, 5, timer_disp_ptr->month % 10);

	// 婢垛晜鏆熼敍锟�2娴ｏ拷
	drawNum(1, 6, (timer_disp_ptr->day % 100) / 10);
	drawNum(1, 7, timer_disp_ptr->day % 10);

	// 鐏忓繑妞傞敍锟�2娴ｏ拷
	drawNum(0, 0, (timer_disp_ptr->hour / 10));
	drawNum(0, 1, timer_disp_ptr->hour % 10);
	drawNum(0, 2, 10);


	// 閸掑棴绱�2娴ｏ拷
	drawNum(0, 3, (timer_disp_ptr->minit / 10));
	drawNum(0, 4, timer_disp_ptr->minit % 10);
	drawNum(0, 5, 10);

	// 缁夋帪绱�2娴ｏ拷
	drawNum(0, 6, (timer_disp_ptr->sec / 10));
	drawNum(0, 7, timer_disp_ptr->sec % 10);
	return;
}

void delay_sec(uint8 ms_d)
{
	uint8_t i,j;
	for (i = 0; i < ms_d; i++) {
		for (j = 0; j < 100; j++) {
			os_delay_us(1000);
		}
	}
	return;
}

void led_flash(uint8 cnt)
{
	gpio_set_level(A, (cnt % 2));
	gpio_set_level(B, (cnt % 2));
	gpio_set_level(C, (cnt % 2));
	gpio_set_level(D, (cnt % 2));
	gpio_set_level(STB, (cnt % 2));
	gpio_set_level(CLK, (cnt % 2));
	gpio_set_level(R1, (cnt % 2));
	gpio_set_level(R2, (cnt % 2));
}


extern uint8_t *displaybuf;


void led_matrix()
{
	int ite = 1;
	if (get_disp_flag() == 1) {
		proc_time();
	}
	scan();

	//system_soft_wdt_feed();
}

//
void led_matrix1()
{

	int ite = 1;
	int flag = 0;
	int y = 0;

	// 濞撳懐鎮婇弫鐗堝祦閿涘苯鑻熼弰鍓с仛
	clear();
	proc_time();

	int i,j;
	for (i = 0; i < 256; i++) {
		os_printf("%2x ", displaybufg[i]);
		if ((i % 16 == 0) && (i != 0)) {
			os_printf("\n");
		}
	}

	os_printf("\r\n=========led_matrix333===============\r\n");

	while (1) {
#if 1
		if (get_disp_flag() == 1) {
			clear_disp_flag();
			proc_time();
		}
		scan();
		ite++;
		system_soft_wdt_feed();
#endif



#if 0
		ite++;

		//led_write(flag);

		if (ite == 104) {
			os_printf("\r\n======flag===%d====\r\n", flag);
			flag++;
			drawPoint(flag / 32, flag % 32, 1);
			for (i = 0; i < 256; i++) {
				if ((i % 16 == 0) && (i != 0)) {
					os_printf("\n");
				}
				os_printf("%2x ", displaybuf[i]);
			}
			ite = 0;
		}
		scan();
		system_soft_wdt_feed();
#endif
	}

}


// 娑撶粯婀囬崝锟�
void app_main(void)
{
	os_printf("\r\n=========configure===============\r\n");
	configure(A,B,C,D,OE,R1,R2,STB,CLK);

	os_printf("\r\n=========begin===============\r\n");
	begin(displaybufg, WIDTH, HEIGHT);

	os_printf("\r\n=========get_set_time===============\r\n");
	//get_set_time();

	// 濞撳懐鎮婇弫鐗堝祦閿涘苯鑻熼弰鍓с仛
	clear();
	proc_time();

	os_printf("\r\n=========led_matrix11===============\r\n");

	os_printf("\r\n=========end===============\r\n");
	return;
}


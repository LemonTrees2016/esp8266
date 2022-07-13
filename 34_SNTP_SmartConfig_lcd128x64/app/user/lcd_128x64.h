/*
寮曡剼鍙�  寮曡剼鍚嶇О  	鏂瑰悜  	鍔熻兘璇存槑
1  		GND			-  		妯″潡鐨勭數婧愬湴
2  		VCC		  	-  		妯″潡鐨勭數婧愭绔�
3  		V0  		-  		LCD 椹卞姩鐢靛帇杈撳叆绔�
4) 		RS(CS)  	H/L  	骞惰鐨勬寚浠�/鏁版嵁閫夋嫨淇″彿锛涗覆琛岀殑鐗囬�変俊鍙�
5) 		R/W(SID)  	H/L  	骞惰鐨勮鍐欓�夋嫨淇″彿锛涗覆琛岀殑鏁版嵁鍙�
6) 		E(CLK)  	H/L  	骞惰鐨勪娇鑳戒俊鍙凤紱涓茶鐨勫悓姝ユ椂閽�
7  		DB0  		H/L  	鏁版嵁 0
8  		DB1  		H/L  	鏁版嵁 1
9  		DB2  		H/L  	鏁版嵁 2
10  	DB3  		H/L  	鏁版嵁 3
11  	DB4  		H/L  	鏁版嵁 4
12  	DB5  		H/L  	鏁版嵁 5
13  	DB6  		H/L  	鏁版嵁 6
14  	DB7  		H/L  	鏁版嵁 7
15-<  	PSB  		H/L  	骞�/涓茶鎺ュ彛閫夋嫨锛欻-骞惰锛汱-涓茶
16  	NC  				绌鸿剼
17)  	/RST  		H/L  	澶嶄綅 浣庣數骞虫湁鏁�
18  	VOUT  				鍊嶅帇杈撳嚭鑴� 锛圴DD=+3.3V 鏈夋晥锛�
19  	LED_A  		-  		鑳屽厜婧愭鏋侊紙LED+5V锛�
20  	LED_K  		-  		鑳屽厜婧愯礋鏋侊紙LED-OV锛�

#define A GPIO_NUM_19
#define B GPIO_NUM_21
#define C GPIO_NUM_16 // 16-<
#define D GPIO_NUM_27

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef __LCD_128X64__H__
#define __LCD_128X64__H__
#if 1
/*
引脚号  引脚名称  	方向  	功能说明
1  		GND			-  		模块的电源地
2  		VCC		  	-  		模块的电源正端
3  		V0  		-  		LCD 驱动电压输入端
4) 		RS(CS 黄)  	H/L  	并行的指令/数据选择信号；串行的片选信号
5) 		R/W(SID 橙)  	H/L  	并行的读写选择信号；串行的数据口
6) 		E(CLK 红)  	H/L  	并行的使能信号；串行的同步时钟
7  		DB0  		H/L  	数据 0
8  		DB1  		H/L  	数据 1
9  		DB2  		H/L  	数据 2
10  	DB3  		H/L  	数据 3
11  	DB4  		H/L  	数据 4
12  	DB5  		H/L  	数据 5
13  	DB6  		H/L  	数据 6
14  	DB7  		H/L  	数据 7
15-<  	PSB  		H/L  	并/串行接口选择：H-并行；L-串行
16  	NC  				空脚
17)  	/RST(灰)		H/L  	复位 低电平有效
18  	VOUT  				倍压输出脚 （VDD=+3.3V 有效）
19  	LED_A  		-  		背光源正极（LED+5V）
20  	LED_K  		-  		背光源负极（LED-OV）

#define LCD128x64_CS    12 -> 4 黄 D6
#define LCD128x64_DIN   14 -> 5 橙
#define LCD128x64_CLK   13 -> 6 红
#define LCD128x64_RST   15 -> 17 灰

*/


#define LCD128x64_CS    12 // 黄 D6
#define LCD128x64_CLK   13 // 红 D7
#define LCD128x64_DIN   14 // 橙 D5
#define LCD128x64_RST   5 // 灰 D8

#else
#define NOKIA5110_RST   14
#define NOKIA5110_CE    27
#define NOKIA5110_DC    26
#define NOKIA5110_DIN   25
#define NOKIA5110_CLK   35

#endif

/*
 * GPIO5  - > CE
 * GPIO14 - > DIN
 * GPIO9  - > CLK
 * GPIO25  - > RST
 */
extern void gpio_set_level(unsigned char a, unsigned char b);

#define LCD_CS_0  gpio_set_level(LCD128x64_CS, 0)
#define LCD_CS_1  gpio_set_level(LCD128x64_CS, 1)

#define LCD_SDIN_0    gpio_set_level(LCD128x64_DIN, 0)
#define LCD_SDIN_1    gpio_set_level(LCD128x64_DIN, 1)

#define LCD_SCLK_0    gpio_set_level(LCD128x64_CLK, 0)
#define LCD_SCLK_1    gpio_set_level(LCD128x64_CLK, 1)

#define LCD_RST_0     gpio_set_level(LCD128x64_RST, 0)
#define LCD_RST_1     gpio_set_level(LCD128x64_RST, 1)

void  Lcd12x864_GpioInit(void);
void  Lcd12x864_init(void);
void Lcd12x864_clear(void);
void  Lcd12x864_write_char(unsigned char c);
void  Lcd12x864_write_english_string(unsigned char X,unsigned char Y,char *s);
void  Lcd12x864_write_chinese_string(unsigned char X, unsigned char Y,
                   unsigned char ch_with,unsigned char num,
                   unsigned char line,unsigned char row);
void Lcd12x864_draw_bmp_pixel(uint8_t *img);

void Lcd12864(void);


void Lcd128x64InitTotal();

void DispLcd128x64(void);

#endif

/*
2007-2-1 12:06
nokia 5110 driver program for 51 mcu
by zl0801

zhaoliang0801@gmail.com

*/

#include "c_types.h"			// 变量类型

#define GPIO_OUTPUT(n, flag) GPIO_OUTPUT_SET(GPIO_ID_PIN(n),flag)

/*
 * GPIO4  - > RST
 * GPIO5  - > CE
 * GPIO12 - > DC
 * GPIO14 - > DIN
 * GPIO9  - > CLK
 */
#define LCD_RST_0 GPIO_OUTPUT(GPIO_ID_PIN(4), 0)
#define LCD_RST_1 GPIO_OUTPUT(GPIO_ID_PIN(4), 1)
#define LCD_CE_0  GPIO_OUTPUT(GPIO_ID_PIN(5), 0)
#define LCD_CE_1  GPIO_OUTPUT(GPIO_ID_PIN(5), 1)
#define LCD_DC_0  GPIO_OUTPUT(GPIO_ID_PIN(12), 0)
#define LCD_DC_1  GPIO_OUTPUT(GPIO_ID_PIN(12), 1)
#define SDIN_0    GPIO_OUTPUT(GPIO_ID_PIN(14), 0)
#define SDIN_1    GPIO_OUTPUT(GPIO_ID_PIN(14), 1)
#define SCLK_0    GPIO_OUTPUT(GPIO_ID_PIN(15), 0)
#define SCLK_1    GPIO_OUTPUT(GPIO_ID_PIN(15), 1)




// pin define for n5110lcd_8key board
// change this if your hardware changed!


void ICACHE_FLASH_ATTR LCD_init(void);
void ICACHE_FLASH_ATTR LCD_clear(void);
void ICACHE_FLASH_ATTR LCD_move_chinese_string(unsigned char X, unsigned char Y, unsigned char T);
void ICACHE_FLASH_ATTR LCD_write_english_string(unsigned char X,unsigned char Y,char *s);
void ICACHE_FLASH_ATTR LCD_write_chinese_string(unsigned char X, unsigned char Y,
                   unsigned char ch_with,unsigned char num,
                   unsigned char line,unsigned char row);
void ICACHE_FLASH_ATTR chinese_string(unsigned char X, unsigned char Y, unsigned char T);
void ICACHE_FLASH_ATTR LCD_write_char(unsigned char c);
void ICACHE_FLASH_ATTR LCD_draw_bmp_pixel(unsigned char X,unsigned char Y,unsigned char *map,
                  unsigned char Pix_x,unsigned char Pix_y);
void ICACHE_FLASH_ATTR LCD_write_byte(unsigned char dat, unsigned char dc);
void ICACHE_FLASH_ATTR LCD_set_XY(unsigned char X, unsigned char Y);
void ICACHE_FLASH_ATTR delay_1us(void);
void ICACHE_FLASH_ATTR GpioInit(void);

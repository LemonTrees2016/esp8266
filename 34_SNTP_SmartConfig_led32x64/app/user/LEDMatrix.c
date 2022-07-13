/**
 * LED Matrix library for http://www.seeedstudio.com/depot/ultrathin-16x32-red-led-matrix-panel-p-1582.html
 * The LED Matrix panel has 32x16 pixels. Several panel can be combined together as a large screen.
 *
 * Coordinate & Connection (Arduino -> panel 0 -> panel 1 -> ...)
 *   (0, 0)                                     (0, 0)
 *     +--------+--------+--------+               +--------+--------+
 *     |   5    |    4   |    3   |               |    1   |    0   |
 *     |        |        |        |               |        |        |<----- Arduino
 *     +--------+--------+--------+               +--------+--------+
 *     |   2    |    1   |    0   |                              (64, 16)
 *     |        |        |        |<----- Arduino
 *     +--------+--------+--------+
 *                             (96, 32)
 *  Copyright (c) 2013 Seeed Technology Inc.
 *  @auther     Yihui Xiong
 *  @date       Nov 8, 2013
 *  @license    MIT
 */




#include "gpio16.h"
#include "gpio.h"
#include "eagle_soc.h"			// GPIO函数、宏定义
#include <stdint.h>
#include "LEDMatrix.h"

#include "c_types.h"			// 变量类型
#include "time_tool.h"			// 变量类型

uint8_t a,b,c,d,oe,r1,r2,stb,clk ;
uint16_t width,height;

uint8_t *displaybuf;
uint8_t mask = 0xff;
uint8_t enable = 0xff ;

void gpio_set_level(a,b)
{
	if (a == 16) {
		gpio16_output_set(b);
		return;
	}

	GPIO_OUTPUT_SET(GPIO_ID_PIN(a), b);
	return;
}


void configure(uint8_t ap, uint8_t bp, uint8_t cp, uint8_t dp, uint8_t oep, uint8_t r1p, uint8_t r2p, uint8_t stbp, uint8_t clkp)
{
    clk = clkp;
   r1 = r1p;
   r2 = r2p;
   stb = stbp;
   oe = oep;
    a = ap;
   b = bp;
   c = cp;
   d = dp;


}

void begin(uint8_t *displaybufp, uint16_t widthp, uint16_t heightp)
{
    displaybuf = displaybufp;
    width = widthp;
    height = heightp;


	PIN_PULLUP_EN(PERIPHS_IO_MUX_GPIO2_U);
	PIN_PULLUP_EN(PERIPHS_IO_MUX_GPIO4_U);
	PIN_PULLUP_EN(PERIPHS_IO_MUX_GPIO5_U);
	PIN_PULLUP_EN(PERIPHS_IO_MUX_MTDI_U);
	PIN_PULLUP_EN(PERIPHS_IO_MUX_MTCK_U);
	PIN_PULLUP_EN(PERIPHS_IO_MUX_MTMS_U);
	PIN_PULLUP_EN(PERIPHS_IO_MUX_MTDO_U);

	//PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U,	FUNC_GPIO0);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U,	FUNC_GPIO2);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO4_U,	FUNC_GPIO4);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U,	FUNC_GPIO5);
	gpio16_output_conf();
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, FUNC_GPIO12);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_GPIO13);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U, FUNC_GPIO14);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDO_U, FUNC_GPIO15);


	return;
}

void drawPoint(uint16_t x, uint16_t y, uint8_t pixel)
{

    uint8_t *byte = displaybuf + x / 8 + y * width / 8;
    uint8_t  bit = x % 8;

    if (pixel) {
        *byte |= 0x80 >> bit;
    } else {
        *byte &= ~(0x80 >> bit);
    }
}

void drawRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t pixel)
{
	uint16_t x;
    for (x = x1; x < x2; x++) {
    	uint16_t y;
        for (y = y1; y < y2; y++) {
            drawPoint(x, y, pixel);
        }
    }
}

void drawImage(uint16_t xoffset, uint16_t yoffset, uint16_t width, uint16_t height, const uint8_t *image)
{
	uint16_t y;
    for (y = 0; y < height; y++) {
    	uint16_t x;
        for (x = 0; x < width; x++) {
            const uint8_t *byte = image + (x + y * width) / 8;
            uint8_t  bit = 7 - x % 8;
            uint8_t  pixel = (*byte >> bit) & 1;

            drawPoint(x + xoffset, y + yoffset, pixel);
        }
    }
}

void clear()
{
    uint8_t *ptr = displaybuf;
    uint16_t i;
    for (i = 0; i < 256; i++) {
        ptr[i] = 0x00;
    }
}

void scan()
{
	uint8_t row;
    for(row = 0;row < 16; row++) {
        uint8_t *head = displaybuf + row * (width / 8);
            uint8_t *ptr = head;
            uint8_t *ptr1 = head + 16 * (width / 8);

            uint8_t byte;
            for (byte = 0; byte < (width / 8); byte++) {
                uint8_t pixels = *ptr;
                uint8_t pixels1 = *ptr1;
                pixels = pixels ^ mask;     // reverse: mask = 0xff, normal: mask =0x00
                pixels1 = pixels1 ^ mask;
                ptr++;
                ptr1++;

                uint8_t bit;
                for (bit = 0; bit < 8; bit++) {
                        gpio_set_level(clk, 0);
                        gpio_set_level(r1, ((pixels & (0x80 >> bit) & enable)!=0));
                        gpio_set_level(r2, ((pixels1 & (0x80 >> bit) & enable)!=0));
                        gpio_set_level(clk, 1);
                }
        }

        //gpio_set_level(oe, 1);
        gpio_set_level(a, (row & 0x01));
        gpio_set_level(b, ((row & 0x02)>>1));
        gpio_set_level(c, ((row & 0x04)>>2));
        gpio_set_level(d, ((row & 0x08)>>3));
        gpio_set_level(stb, 0);
        gpio_set_level(stb, 1);
        gpio_set_level(stb, 0);
        //gpio_set_level(oe, 0);              // enable display
    }
}


void led_write(uint8_t bitSet)
{
	uint8_t row;
    for(row = 0; row < 16; row++) {
    	uint8_t byte;
            for (byte = 0; byte < (width / 8); byte++) {
            	uint8_t bit;
                for (bit = 0; bit < 8; bit++) {
                        gpio_set_level(clk, 0);
                        gpio_set_level(r1, bitSet);
                        gpio_set_level(r2, bitSet);
                        gpio_set_level(clk, 1);
                }
        }

        //gpio_set_level(oe, 1);
        gpio_set_level(a, (row & 0x01));
        gpio_set_level(b, ((row & 0x02)>>1));
        gpio_set_level(c, ((row & 0x04)>>2));
        gpio_set_level(d, ((row & 0x08)>>3));
        gpio_set_level(stb, 0);
        gpio_set_level(stb, 1);
        gpio_set_level(stb, 0);
        //gpio_set_level(oe, 0);              // enable display
    }
}


#ifndef __CODE_DICT_H__
#define __CODE_DICT_H__
#include <stdint.h>

uint8_t closed[256] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x3f, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x0f,
  0x7f, 0x87, 0x80, 0x00, 0x00, 0x00, 0x00, 0x0f,
  0xff, 0xc7, 0x80, 0x00, 0x00, 0x00, 0x00, 0x0f,
  0xf3, 0xc7, 0x87, 0xe0, 0x7c, 0x0f, 0x81, 0xef,
  0xf3, 0xc7, 0x8f, 0xf0, 0xfe, 0x1f, 0xe3, 0xff,
  0xf3, 0xc7, 0x9f, 0xf9, 0xff, 0x3f, 0xe3, 0xff,
  0xf3, 0xc7, 0x9e, 0x79, 0xe7, 0x3c, 0xf3, 0xcf,
  0xf0, 0x07, 0x9e, 0x79, 0xe7, 0x3c, 0xf3, 0xcf,
  0xf0, 0x07, 0x9e, 0x79, 0xf0, 0x3c, 0xf3, 0xcf,
  0xf0, 0x07, 0x9e, 0x78, 0xf8, 0x3f, 0xf3, 0xcf,
  0xf3, 0xc7, 0x9e, 0x78, 0x7e, 0x3f, 0xf3, 0xcf, //Closed
  0xf3, 0xc7, 0x9e, 0x78, 0x3f, 0x3c, 0x03, 0xcf,
  0xf3, 0xc7, 0x9e, 0x78, 0x0f, 0x3c, 0xf3, 0xcf,
  0xf3, 0xc7, 0x9e, 0x79, 0xcf, 0x3c, 0xf3, 0xcf,
  0xf3, 0xc7, 0x9e, 0x79, 0xcf, 0x3c, 0xf3, 0xcf,
  0xff, 0x87, 0x9f, 0xf9, 0xff, 0x3f, 0xf3, 0xff,
  0x7f, 0x87, 0x8f, 0xf0, 0xfe, 0x1f, 0xe3, 0xff,
  0x3e, 0x07, 0x87, 0xe0, 0x7c, 0x0f, 0xc1, 0xef,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


uint8_t photo_test[256] = {
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xE0,0x00,0x10,0x00,0x00,0x04,0x00,0x01,
0xE0,0x00,0x10,0x00,0x00,0x04,0x00,0x01,
0x80,0x00,0x10,0x00,0x00,0x04,0x00,0x01,
0x80,0x00,0x10,0x00,0x00,0x04,0x00,0x01,
0x80,0x00,0x10,0x00,0x00,0x04,0x00,0x01,
0x80,0x00,0x10,0x00,0x00,0x04,0x00,0x01,
0x80,0x00,0x10,0x00,0x00,0x04,0x00,0x01,
0x80,0x00,0x10,0x00,0x00,0x04,0x00,0x01,
0x80,0x00,0x10,0x00,0x00,0x04,0x00,0x01,
0x80,0x00,0x10,0x00,0x00,0x04,0x00,0x01,
0x80,0x00,0x10,0x00,0x00,0x04,0x00,0x01,
0x80,0x00,0x10,0x00,0x00,0x04,0x00,0x01,
0x80,0x00,0x10,0x00,0x00,0x04,0x00,0x01,
0x80,0x00,0x10,0x00,0x00,0x04,0x00,0x01,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,/*"F:\绔嬪垱EDA\esp32\projects\lcd32x64.BMP",0*/

};


#define COLUMN_WID 16
// 显示年月日用的信息
uint8_t data_bit_dat[][COLUMN_WID] = {

	{0x00,0x00,0x00,0x18,0x24,0x42,0x42,0x42,
	0x42,0x42,0x42,0x42,0x24,0x18,0x00,0x00},/*"0",9*/

	{0x00,0x00,0x00,0x08,0x38,0x08,0x08,0x08,
	0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00},/*"1",0*/

	{0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x02,
	0x04,0x08,0x10,0x20,0x42,0x7E,0x00,0x00},/*"2",1*/

	{0x00,0x00,0x00,0x3C,0x42,0x42,0x02,0x04,
	0x18,0x04,0x02,0x42,0x42,0x3C,0x00,0x00},/*"3",2*/

	{0x00,0x00,0x00,0x04,0x0C,0x0C,0x14,0x24,
	0x24,0x44,0x7F,0x04,0x04,0x1F,0x00,0x00},/*"4",3*/

	{0x00,0x00,0x00,0x7E,0x40,0x40,0x40,0x78,
	0x44,0x02,0x02,0x42,0x44,0x38,0x00,0x00},/*"5",4*/

	{0x00,0x00,0x00,0x18,0x24,0x40,0x40,0x5C,
	0x62,0x42,0x42,0x42,0x22,0x1C,0x00,0x00},/*"6",5*/

	{0x00,0x00,0x00,0x7E,0x42,0x04,0x04,0x08,
	0x08,0x10,0x10,0x10,0x10,0x10,0x00,0x00},/*"7",6*/

	{0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x24,
	0x18,0x24,0x42,0x42,0x42,0x3C,0x00,0x00},/*"8",7*/

	{0x00,0x00,0x00,0x38,0x44,0x42,0x42,0x42,
	0x46,0x3A,0x02,0x02,0x24,0x18,0x00,0x00},/*"9",8*/

	{0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,
	0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00},/*":",0*/
};


uint8_t data_bit_slit[] = {
	0x00,0x00,0x00,0x18,0x24,0x42,0x42,0x42,
	0x42,0x42,0x42,0x42,0x24,0x18,0x00,0x00,/*"0",9*/
	0x00,0x00,0x00,0x08,0x38,0x08,0x08,0x08,
	0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00,/*"1",0*/
	0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x02,
	0x04,0x08,0x10,0x20,0x42,0x7E,0x00,0x00,/*"2",1*/
	0x00,0x00,0x00,0x3C,0x42,0x42,0x02,0x04,
	0x18,0x04,0x02,0x42,0x42,0x3C,0x00,0x00,/*"3",2*/
	0x00,0x00,0x00,0x04,0x0C,0x0C,0x14,0x24,
	0x24,0x44,0x7F,0x04,0x04,0x1F,0x00,0x00,/*"4",3*/
	0x00,0x00,0x00,0x7E,0x40,0x40,0x40,0x78,
	0x44,0x02,0x02,0x42,0x44,0x38,0x00,0x00,/*"5",4*/
	0x00,0x00,0x00,0x18,0x24,0x40,0x40,0x5C,
	0x62,0x42,0x42,0x42,0x22,0x1C,0x00,0x00,/*"6",5*/
	0x00,0x00,0x00,0x7E,0x42,0x04,0x04,0x08,
	0x08,0x10,0x10,0x10,0x10,0x10,0x00,0x00,/*"7",6*/
	0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x24,
	0x18,0x24,0x42,0x42,0x42,0x3C,0x00,0x00,/*"8",7*/
	0x00,0x00,0x00,0x38,0x44,0x42,0x42,0x42,
	0x46,0x3A,0x02,0x02,0x24,0x18,0x00,0x00,/*"9",8*/
};
// 显示时间和温度用的字体8x8
uint8_t time_and_temp_disp[][8] = {
		{0x7E,0x42,0x42,0x42,0x42,0x42,0x7E,0x00},/*"0",0*/

		{0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00},/*"1",1*/

		{0x7E,0x02,0x02,0x7E,0x40,0x40,0x7E,0x00},/*"2",2*/

		{0x7E,0x02,0x02,0x7E,0x02,0x02,0x7E,0x00},/*"3",3*/

		{0x42,0x42,0x42,0x7E,0x02,0x02,0x02,0x00},/*"4",4*/

		{0x7E,0x40,0x7E,0x02,0x02,0x02,0x7E,0x00},/*"5",5*/

		{0x7E,0x40,0x40,0x7E,0x42,0x42,0x7E,0x00},/*"6",6*/

		{0x7E,0x02,0x02,0x02,0x02,0x02,0x02,0x00},/*"7",7*/

		{0x7E,0x42,0x42,0x7E,0x42,0x42,0x7E,0x00},/*"8",8*/

		{0x7E,0x42,0x42,0x7E,0x02,0x02,0x7E,0x00},/*"9",9*/

		{0xC0,0xDE,0x12,0x10,0x10,0x12,0x1E,0x00},/*"C",10*/

		{0x03,0x67,0x6E,0x1C,0x38,0x76,0xE6,0x00},/*"%",11*/
};

uint8_t fonts[] ={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xe0,0x0f,0xf0,0x1f,0xf8,0x3e,0x7c,0x3e,0x7c,0x3e,0x7c,0x3e,0x7c,0x3e,0x7c,0x3e,0x7c,0x3e,0x7c,0x3e,0x7c,0x3e,0x7c,0x3e,0x7c,0x3e,0x7c,0x3e,0x7c,0x3e,0x7c,0x3e,0x7c,0x3e,0x7c,0x3e,0x7c,0x3e,0x7c,0x1e,0x7c,0x1f,0xf8,0x0f,0xf0,0x07,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0xe0, 0x03, 0xe0, 0x0f, 0xe0, 0x3f, 0xe0, 0x3f, 0xe0, 0x3f, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xe0, 0x0f, 0xf0, 0x0f, 0xf8, 0x1e, 0x78, 0x1e, 0x7c, 0x1e, 0x7c, 0x1e, 0x7c, 0x1e, 0x7c, 0x00, 0x7c, 0x00, 0xfc, 0x00, 0xf8, 0x01, 0xf8, 0x01, 0xf8, 0x03, 0xf0, 0x03, 0xf0, 0x03, 0xe0, 0x07, 0xe0, 0x07, 0xc0, 0x0f, 0xc0, 0x0f, 0x80, 0x1f, 0x80, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x1f, 0xf0, 0x1f, 0xf8, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x00, 0x7c, 0x00, 0x7c, 0x03, 0xf8, 0x03, 0xf0, 0x03, 0xf8, 0x00, 0xfc, 0x00, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x1f, 0xf8, 0x1f, 0xf8, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xfc, 0x03, 0xfc, 0x03, 0xfc, 0x07, 0xfc, 0x07, 0xfc, 0x07, 0xfc, 0x0f, 0x7c, 0x0f, 0x7c, 0x0f, 0x7c, 0x1e, 0x7c, 0x1e, 0x7c, 0x3e, 0x7c, 0x3c, 0x7c, 0x3c, 0x7c, 0x7c, 0x7c, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x00, 0x7c, 0x00, 0x7c, 0x00, 0x7c, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfc, 0x3f, 0xfc, 0x3f, 0xfc, 0x3e, 0x00, 0x3e, 0x00, 0x3e, 0x00, 0x3e, 0xf0, 0x3f, 0xf8, 0x3f, 0xfc, 0x3e, 0x7c, 0x00, 0x7c, 0x00, 0x7c, 0x00, 0x7c, 0x00, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x1e, 0x7c, 0x1f, 0xf8, 0x0f, 0xf0, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x0f, 0xf8, 0x1f, 0xf8, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x00, 0x3e, 0x00, 0x3e, 0xf0, 0x3f, 0xf8, 0x3f, 0xfc, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x1f, 0xf8, 0x0f, 0xf0, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfc, 0x3f, 0xfc, 0x3f, 0xfc, 0x00, 0x7c, 0x00, 0x7c, 0x00, 0x7c, 0x00, 0x78, 0x00, 0xf8, 0x00, 0xf8, 0x00, 0xf8, 0x00, 0xf0, 0x01, 0xf0, 0x01, 0xf0, 0x01, 0xf0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x07, 0xc0, 0x07, 0xc0, 0x07, 0xc0, 0x07, 0xc0, 0x0f, 0x80, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x07, 0xe0, 0x0f, 0xf0, 0x1f, 0xf8, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x1f, 0xf8, 0x0f, 0xf0, 0x1f, 0xf8, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x1f, 0xf8, 0x1f, 0xf8, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x0f, 0xf0, 0x1f, 0xf8, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3f, 0xfc, 0x1f, 0xfc, 0x0f, 0x7c, 0x00, 0x7c, 0x00, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x3e, 0x7c, 0x1f, 0xf8, 0x1f, 0xf0, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xC0,0x03,0xE0,0x03,0xE0,0x03,0xE0,0x03,0xE0,0x03,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xC0,0x03,0xE0,0x03,0xE0,0x03,0xE0,0x03,0xE0,0x03,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xC0,0x03,0xE0,0x03,0xE0,0x03,0xE0,0x03,0xE0,0x03,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xC0,0x03,0xE0,0x03,0xE0,0x03,0xE0,0x03,0xE0,0x03,0xC0,0x03,0xC0,0x03,0x80,0x03,0x80,0x07,0x00,0x07,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x00,0x1E,0x00,0x7E,0x01,0xFE,0x07,0xF8,0x1F,0xE0,0x3F,0x80,0x7E,0x00,0x78,0x00,0x7E,0x00,0x3F,0x80,0x0F,0xF0,0x07,0xFC,0x01,0xFE,0x00,0x7E,0x00,0x1E,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xFE,0x7F,0xFE,0x7F,0xFE,0x7F,0xFE,0x3F,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xFE,0x7F,0xFE,0x7F,0xFE,0x7F,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x00,0x7C,0x00,0x7F,0x00,0x3F,0xC0,0x1F,0xE0,0x07,0xF8,0x00,0xFE,0x00,0x3E,0x00,0x1E,0x00,0x7E,0x01,0xFE,0x07,0xF8,0x1F,0xE0,0x7F,0x80,0x7E,0x00,0x78,0x00,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x01,0xC0,0x0F,0xF0,0x1F,0xF8,0x1F,0xFC,0x1E,0x7C,0x18,0x3C,0x00,0x3C,0x00,0x3C,0x00,0x3C,0x00,0x78,0x00,0xF8,0x00,0xF0,0x01,0xE0,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0x80,0x03,0xC0,0x03,0xC0,0x00,0x00,0x00,0x00,0x03,0x80,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFC,0xFF,0xFC,0xFF,0xFC,0x00,0x00,
    0x00,0x00,
    0x00,0x00,
    0x00,0x00,
    0x00,0x00,
    0x00,0x00,
    0x00,0x00,
    0x00,0x00,
    0x00,0x00,
    0x00,0x00,
    0x00,0x00,
    0x00,0x00,
    0x00,0x00,
    0x00,0x00,
    0x00,0x00
};


#endif

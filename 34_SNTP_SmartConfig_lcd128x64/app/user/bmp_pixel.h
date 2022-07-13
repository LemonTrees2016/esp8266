/*------------------------------------------------------------------------------
;  源文件 / 文字 : AVR
;  宽×高（像素）: 40×24
;  字模格式/大小 : 单色点阵液晶字模，纵向取模，字节倒序/120字节
;  数据转换日期  : 2004-8-13
------------------------------------------------------------------------------*/ 
unsigned char AVR_bmp[]=


  {
/*--  调入了一幅图像：C:\Documents and Settings\armok\桌面\1.bmp  --*/
/*--  宽度x高度=60x47  --*/
/*0x00,0x00,0x00,0x00,0x80,0xE0,0xFC,0xFF,0xFF,0xFF,0x7F,0xFF,0xFE,0xFC,0xF0,0xC1,
0x0F,0x7F,0xFF,0xFF,0xFE,0xF0,0xC0,0x00,0x00,0x00,0xC0,0xF8,0xFE,0xFF,0xFF,0x3F,
0x07,0xC1,0xF0,0xFE,0xFF,0xFF,0xFF,0x1F,0x07,0x8F,0xCF,0xFF,0xFF,0xFF,0xFE,0xFC,
0x00,0x80,0xF0,0xFC,0xFF,0xFF,0xFF,0x7F,0x7F,0x78,0x78,0x79,0x7F,0x7F,0xFF,0xFF,
0xFC,0xF0,0xC1,0x07,0x1F,0xFF,0xFF,0xFE,0xFC,0xFF,0xFF,0xFF,0x1F,0x07,0xC1,0xF0,
0xFE,0xFF,0xFF,0x3F,0x0F,0x0F,0x7F,0xFF,0xFF,0xFF,0xFF,0xE7,0x07,0x03,0x01,0x00,
0x02,0x03,0x03,0x03,0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
0x03,0x03,0x03,0x03,0x00,0x00,0x03,0x1F,0x3F,0x1F,0x07,0x00,0x00,0x02,0x03,0x03,
0x03,0x03,0x01,0x00,0x00,0x00,0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x00,0x00,0x00
*/

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0x40,
0x20,0x00,0x10,0x10,0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x10,0x10,0x00,
0x20,0x40,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x0C,0x02,0x01,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x02,0x0C,0x70,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x00,0x00,0x00,
0x80,0xC0,0xE0,0xE0,0xF0,0xF0,0xF0,0xF0,0xE0,0xC0,0x00,0x00,0x00,0x00,0x00,0xC0,
0xE0,0xF0,0xF0,0xF0,0xF0,0xE0,0xE0,0xC0,0x80,0x00,0x00,0x00,0x7F,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x00,
0x18,0x60,0x83,0x87,0x87,0x87,0x07,0x03,0x03,0x03,0x01,0x40,0xF0,0xF0,0xF0,0xF0,
0xF0,0x40,0x01,0x03,0x03,0x03,0x07,0x87,0x87,0x87,0x83,0x60,0x18,0x00,0x07,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x1F,0x27,0x48,0x88,0x88,0x88,0x88,0x88,0x48,
0x48,0x48,0x88,0x88,0x88,0x88,0x88,0x48,0x27,0x1F,0x00,0xFF,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x02,0x04,0x04,0x08,0x00,0x10,0x10,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x08,0x04,0x04,0x02,0x03,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  };


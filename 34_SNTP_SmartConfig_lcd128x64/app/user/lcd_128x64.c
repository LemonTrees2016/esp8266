

#include <math.h>       /* ceil */

#include "LEDMatrix.h"
#include <stdint.h>
#include <stdio.h>

#include <time.h>
#include <sys/time.h>

#include "code_dict.h"
#include "write_chinese_string_pixel.h"
#include "gpio16.h"
#include "eagle_soc.h"			// GPIO鍑芥暟銆佸畯瀹氫箟

#include "c_types.h"			// 鍙橀噺绫诲瀷

#include "osapi.h"  			// os_XXX銆佽蒋浠跺畾鏃跺櫒
#include "time_tool.h"			// 鍙橀噺绫诲瀷

#include "bmp_pixel.h"
#include "english_6x8_pixel.h"
#include "lcd_128x64.h"


unsigned char  uctech[] = {"大雄电子营业部"};


void  Lcd12x864_delay_1us(void)                 //1us閿熸枻鎷锋椂閿熸枻鎷烽敓鏂ゆ嫹
  {
	os_delay_us(1);
  }

  void  Lcd12x864_delay_1ms(void)                 //1ms閿熸枻鎷锋椂閿熸枻鎷烽敓鏂ゆ嫹
  {
	os_delay_us(1000);
  }
  
void  Lcd12x864_delay_nms(unsigned int n)       //N ms閿熸枻鎷锋椂閿熸枻鎷烽敓鏂ゆ嫹
  {
   unsigned int i=0;
   for (i=0;i<n;i++)
   Lcd12x864_delay_1ms();
  }

void  Lcd12x864_GpioInit(void)
{
	PIN_PULLUP_EN(PERIPHS_IO_MUX_MTDI_U);
	PIN_PULLUP_EN(PERIPHS_IO_MUX_MTCK_U);
	PIN_PULLUP_EN(PERIPHS_IO_MUX_MTMS_U);
	PIN_PULLUP_EN(PERIPHS_IO_MUX_MTDO_U);
	PIN_PULLUP_EN(PERIPHS_IO_MUX_GPIO5_U);

	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, FUNC_GPIO12);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_GPIO13);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U, FUNC_GPIO14);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDO_U, FUNC_GPIO15);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U,	FUNC_GPIO5);
}

void  Lcd12x864_write_8bit(unsigned char dat)
{
	int j = 0;
    for (; j < 8; j++) {
        LCD_SCLK_0;

        if (dat & 0x80) {
            LCD_SDIN_1;
        } else {
            LCD_SDIN_0;
        }
        uint8_t wait_t = 0x20;
        while(wait_t--);
        LCD_SCLK_1;
        dat <<= 1;
    }
    return;
}

void  Lcd12x864_write_byte(unsigned char dat, unsigned char command)
{
    uint8_t base[3] = {0xf8, 0, 0};
    uint16_t delayTime = 10;

    // 濡傛灉鏄暟鎹�
    if (command == 1) {
        Lcd12x864_write_8bit(0xfa);
    } else {
        Lcd12x864_write_8bit(0xf8);
    }

    os_delay_us(delayTime);
    Lcd12x864_write_8bit((0xf0 & dat));
    os_delay_us(delayTime);
    Lcd12x864_write_8bit(0xf0 & (dat << 4));
    os_delay_us(delayTime);
    return;
}



void  Lcd12x864_init(void)
{
    Lcd12x864_delay_nms(50);
	LCD_RST_0;
    Lcd12x864_delay_1us();
    LCD_RST_1;

    LCD_CS_1;
    Lcd12x864_write_byte(0x30, 0);

    Lcd12x864_write_byte(0x0c, 0);	// 娓呯┖LCD 0x01
    Lcd12x864_write_byte(0x01, 0);	// 鍦板潃褰掍綅
}

void Lcd12x864_clear(void)
{
    Lcd12x864_write_byte(0x01, 0);				
}

void  Lcd12x864_set_XY(unsigned char Y, unsigned char X)
{
    uint8_t address;
    switch(X)
    {
        case 0:
            address = 0x80 + Y;
            break;   
        case 1:
            address = 0x80 + Y;
            break;
        case 2:
            address = 0x90 + Y;
            break;
        case 3:
            address = 0x88 + Y;
            break;
        case 4:
            address = 0x98 + Y;
            break;
        default:
            address = 0x80 + Y;
            break;
    }

    Lcd12x864_write_byte(address, 0);
}

void  Lcd12x864_write_char(unsigned char c)
{
    Lcd12x864_write_byte(c, 1);
    Lcd12x864_delay_1ms();
}

void  Lcd12x864_write_english_string(unsigned char X,unsigned char Y,char *s)
{
    Lcd12x864_set_XY(X,Y);
    while (*s) 
    {
        Lcd12x864_write_char(*s);
        s++;
    }
}

void  Lcd12x864_write_chinese_string(unsigned char X, unsigned char Y,
                   unsigned char ch_with,unsigned char num,
                   unsigned char line,unsigned char row)
  {
    unsigned char i,n;

    Lcd12x864_set_XY(X,Y);                             //閿熸枻鎷烽敓鐭鎷峰浣嶉敓鏂ゆ嫹

    for (i=0;i<num;)
      {
      	for (n=0; n<ch_with*2; n++)              //鍐欎竴閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�
      	  {
      	    if (n==ch_with)                      //鍐欓敓鏂ゆ嫹閿熻纰夋嫹閿熼摪鍗婇儴閿熸枻鎷�
      	      {
      	        if (i==0) Lcd12x864_set_XY(X,Y+1);
      	        else
      	           Lcd12x864_set_XY((X+(ch_with+row)*i),Y+1);
              }
      	    Lcd12x864_write_byte(write_chinese[line+i][n],1);
      	  }
      	i++;
      	Lcd12x864_set_XY((X+(ch_with+row)*i),Y);
      }
  }

#if 0
// 鐢诲浘
void Lcd12x864_draw_bmp_pixel(uint8_t *img)
{
   uint8_t i,j;
   
#define LCD_CMD 1
#define LCD_DATA 0
#define x1    0x80
#define x2    0x88
#define y     0x80
#define Write_Char(CD, DATA) Lcd12x864_write_byte((DATA), (CD)) 

	for(j=0;j<32;j++)
	{
		for(i=0;i<8;i++)
		{
			Write_Char(LCD_CMD,0x34);
			Lcd12x864_delay_nms(10);
			Write_Char(LCD_CMD,y+j);
			Lcd12x864_delay_nms(10);
			Write_Char(LCD_CMD,x1+i);
			Lcd12x864_delay_nms(10);
			Write_Char(LCD_CMD,0x30);
			Lcd12x864_delay_nms(10);
			Write_Char(LCD_DATA,img[j*16+i*2]);
			Lcd12x864_delay_nms(10);
			Write_Char(LCD_DATA,img[j*16+i*2+1]);
			Lcd12x864_delay_nms(10);
		}
	}
	for(j=32;j<64;j++)
	{
		for(i=0;i<8;i++)
		{
			Write_Char(LCD_CMD,0x34);
			Lcd12x864_delay_nms(10);
			Write_Char(LCD_CMD,y+j-32);
			Lcd12x864_delay_nms(10);
			Write_Char(LCD_CMD,x2+i);
			Lcd12x864_delay_nms(10);
			Write_Char(LCD_CMD,0x30);
			Lcd12x864_delay_nms(10);
			Write_Char(LCD_DATA,img[j*16+i*2]);
			Lcd12x864_delay_nms(10);
			Write_Char(LCD_DATA,img[j*16+i*2+1]);
			Lcd12x864_delay_nms(10);
		}
	}
	Lcd12x864_delay_nms(10);
	Write_Char(LCD_CMD,0x36);
}
#endif

void WriteCommandLCD(unsigned char dat, unsigned char command)
{
    Lcd12x864_write_byte((dat), (command));
    //Lcd12x864_delay_nms(1);
    return;
}

//鍥惧舰鏄剧ず122*32
void DisplayImage(unsigned char *DData)
{
	unsigned char x, y;
	unsigned char i;
	unsigned int tmp=0;
	for(i = 8; i < 9;) {		//鍒嗕袱灞忥紝涓婂崐灞忓拰涓嬪崐灞忥紝鍥犱负璧峰鍦板潃涓嶅悓锛岄渶瑕佸垎寮�
        tmp=0;
		for(x = 0; x < 32; x++) {				//32琛�
			WriteCommandLCD(0x34, 0);
			WriteCommandLCD((0x80+x), 0);//鍒楀湴鍧�
			WriteCommandLCD((0x80+i), 0);	//琛屽湴鍧�锛屼笅鍗婂睆锛屽嵆绗笁琛屽湴鍧�0X88
			WriteCommandLCD(0x30, 0);	
			
			for(y = 0; y < 16; y++)	{
				WriteCommandLCD(DData[tmp+y], 1);//璇诲彇鏁版嵁鍐欏叆LCD
            }

			tmp+=16;		
		}
		i+=8;
	}
	WriteCommandLCD(0x36, 0);	//鎵╁厖鍔熻兘璁惧畾
	WriteCommandLCD(0x30, 0);

    return;
}


//鍥惧舰鏄剧ず32*32
uint8_t img_buff_32x32[32 * 4] = {0

#if 0

0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xCF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,/*"鏈懡鍚嶆枃浠�",0*/
#endif

};



void DisplayImageXY(unsigned char *DData, uint8_t width, uint8_t height, uint8_t xx, uint8_t yy)
{
    uint8_t col = width / 8;
    uint8_t row = height;
    
    uint8_t startX = xx / 16;
    uint8_t startY = (yy % 2) * 8;

	unsigned char x, y;
	unsigned char i;
	unsigned int tmp = 0;

    for(x = 0; x < row; x++) {				//32琛�
        WriteCommandLCD(0x34, 0);
        WriteCommandLCD((0x80 + x), 0);//鍒楀湴鍧�
        WriteCommandLCD((0x80 + startY + startX), 0);	//琛屽湴鍧�锛屼笅鍗婂睆锛屽嵆绗笁琛屽湴鍧�0X88
        WriteCommandLCD(0x30, 0);	
        
        for(y = 0; y < col; y++)	{
            WriteCommandLCD(DData[tmp+y], 1);//璇诲彇鏁版嵁鍐欏叆LCD
        }

        tmp += col;		
    }

	WriteCommandLCD(0x36, 0);	//鎵╁厖鍔熻兘璁惧畾
	WriteCommandLCD(0x30, 0);

    return;


}

void copyDispDat(uint8_t num)
{
	unsigned char x, y;
#if 0
    for (x = 0; x < 16; x++) {
        img_buff_32x32[x * 4] = num_16x16[num % 10][x];
    }
#endif
    for (x = 0; x < 32; x++) {
        for (y = 0; y < 2; y++) {
            img_buff_32x32[x * 4 + y] = num_32x32[(num % 100) / 10][x * 2 + y];
        }
        for (y = 2; y < 4; y++) {
            img_buff_32x32[x * 4 + y] = num_32x32[(num % 100) % 10][x * 2 + y - 2];
        }
    }
}

void dispNum(uint8_t num)
{

	unsigned char x, y;
#if 0
    for (x = 0; x < 16; x++) {
        img_buff_32x32[x * 4] = num_16x16[num % 10][x];
    }
#endif
    for (x = 0; x < 32; x++) {
        for (y = 0; y < 2; y++) {
            img_buff_32x32[x * 4 + y] = num_32x32[(num % 100) / 10][x * 2 + y];
        }
        for (y = 2; y < 4; y++) {
            img_buff_32x32[x * 4 + y] = num_32x32[(num % 100) % 10][x * 2 + y - 2];
        }
    }

    DisplayImageXY(img_buff_32x32, 32, 32, 96, 0);
    DisplayImageXY(img_buff_32x32, 32, 32, 64, 0);
    DisplayImageXY(img_buff_32x32, 32, 32, 32, 0);
    DisplayImageXY(img_buff_32x32, 32, 32, 0, 0);

    DisplayImageXY(img_buff_32x32, 32, 32, 96, 1);
    DisplayImageXY(img_buff_32x32, 32, 32, 64, 1);
    DisplayImageXY(img_buff_32x32, 32, 32, 32, 1);
    DisplayImageXY(img_buff_32x32, 32, 32, 0, 1);
}

char cntDispBuff[32] = {'c', 'n', 't',':'};
char bldcDispBuff[32] = {'B', 'L',':'};
char dcDispBuff[32] = {'D', 'C',':'};
char DoJDispBuff[32] = {'D', 'J',':'};
int cnt = 0;

void Lcd128x64InitTotal()
{
    // 鍒濆鍖�
    Lcd12x864_GpioInit();
    Lcd12x864_init();
    Lcd12x864_clear();

    //DisplayImage(blackImgData);

	return;
}

void drawCircle(uint8_t num)
{
	int16_t x,y;

	os_memset(img_buff_32x32, 0, 32*4);

	for (x = 0; x < 32; x++) {
		for (y = 0; y < 32; y++) {
			if (pow(abs(x - 16), 2) + pow(abs(y - 16), 2) - 256 < 10) {
				// set bit
				img_buff_32x32[x * 4 + y >> 3] |=  (0x8 >> (y & 0x7));
			}
		}
	}

	DisplayImageXY(img_buff_32x32, 32, 32, 64, 1);
}

void DispLcd128x64(void)
{
	os_sprintf(cntDispBuff + 4, "%d", cnt);
    //Lcd12x864_write_english_string(0, 1, "para:");
    //Lcd12x864_write_english_string(1, 2, cntDispBuff + 4);
    //Lcd12x864_write_english_string(1, 3, cntDispBuff + 4);
    //Lcd12x864_write_english_string(1, 4, cntDispBuff + 4);
	get_set_time();

	TimerStrus* timeStru = GetTimerAddr();

	os_memset(cntDispBuff, 0, 20);
	os_sprintf(cntDispBuff, "%4d/%02d/%02d", timeStru->year, timeStru->month, timeStru->day);
    Lcd12x864_write_english_string(0, 1, cntDispBuff);
	os_memset(cntDispBuff, 0, 20);
	os_sprintf(cntDispBuff, "%02d:%02d:%02d", timeStru->hour, timeStru->minit, timeStru->sec);
    Lcd12x864_write_english_string(0, 2, cntDispBuff);
    //drawCircle(0);

    //vTaskDelay(delayCycle / portTICK_RATE_MS);

    //copyDispDat(timeStru->hour);
    //DisplayImageXY(img_buff_32x32, 32, 32, 0, 1);
    //copyDispDat(timeStru->minit);
    //DisplayImageXY(img_buff_32x32, 32, 32, 64, 1);
    //copyDispDat(timeStru->sec);
    //DisplayImageXY(img_buff_32x32, 32, 32, 96, 1);
	//system_soft_wdt_feed();
    //dispNum(cnt);
    os_printf("cnt1: %d\n", cnt++);


	return;
}

// 娴嬭瘯鎺ュ彛
void Lcd12864(void)
{
    // 鍒濆鍖�
    Lcd12x864_GpioInit();
    Lcd12x864_init();
    Lcd12x864_clear();

    // 鏄剧ず瀛楃涓�
    char cntDispBuff[32] = {'c', 'n', 't',':'};
    char bldcDispBuff[32] = {'B', 'L',':'};
    char dcDispBuff[32] = {'D', 'C',':'};
    char DoJDispBuff[32] = {'D', 'J',':'};

    int cnt = 0;
    int delayCycle = 500;

    DisplayImage(blackImgData);

#if 1
    while(1) {
        //DisplayImage(img_bit);
        //vTaskDelay(delayCycle / portTICK_RATE_MS);
        //DisplayImage(tmp_data_img);
        //vTaskDelay(delayCycle / portTICK_RATE_MS);
        //DisplayImage(blackImgData);
        //vTaskDelay(delayCycle / portTICK_RATE_MS);
        sprintf(cntDispBuff + 4, "%d", cnt);
        Lcd12x864_write_english_string(0, 1, cntDispBuff);
        printf("cnt: %d\n", cnt++);
        //vTaskDelay(delayCycle / portTICK_RATE_MS);
        dispNum(cnt);
        Lcd12x864_delay_nms(delayCycle);
    }

#else
    // 鏄剧ず瀛楃涓�
    while(1) {
        printf("cnt: %d\n", cnt++);
        // 鍒锋柊cnt淇℃伅
        sprintf(cntDispBuff + 4, "%d", cnt);
        sprintf(bldcDispBuff + 3, "%d", cnt);
        sprintf(dcDispBuff + 3, "%d", cnt);
        sprintf(DoJDispBuff + 3, "%d", cnt);
        Lcd12x864_write_english_string(0, 1, cntDispBuff);
        Lcd12x864_write_english_string(0, 2, bldcDispBuff);
        Lcd12x864_write_english_string(0, 3, dcDispBuff);
        Lcd12x864_write_english_string(0, 4, DoJDispBuff);
        vTaskDelay(delayCycle / portTICK_RATE_MS);
    }
#endif
    return;
}

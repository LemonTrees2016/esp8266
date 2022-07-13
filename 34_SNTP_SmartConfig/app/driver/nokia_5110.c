

#include "driver/nokia_5110.h"
#include "driver/write_chinese_string_pixel.h"
#include "driver/bmp_pixel.h"
#include "driver/english_6x8_pixel.h"
#include "gpio.h"
#include "eagle_soc.h"			// GPIO�������궨��

#include "osapi.h"  			// os_XXX��������ʱ��

void ICACHE_FLASH_ATTR GpioInit(void)
{
	/*
	 * GPIO4  - > RST
	 * GPIO5  - > CE
	 * GPIO12 - > DC
	 * GPIO14 - > DIN
	 * GPIO9  - > CLK
	 */
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO4_U,	0);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U,	0);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U,	FUNC_GPIO12);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U,	FUNC_GPIO14);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDO_U,	FUNC_GPIO15);

	/*
	LCD_RST_1;
	LCD_CE_1;
	LCD_DC_1;
	SDIN_1;
	SCLK_1;
	os_delay_us(60000);
	os_delay_us(60000);
	os_delay_us(60000);
	os_delay_us(60000);
	LCD_RST_0;
	LCD_CE_0;
	LCD_DC_0;
	SDIN_0;
	SCLK_0;
	*/
}

/*-----------------------------------------------------------------------
LCD_init          : 3310LCD��ʼ��

��д����          ��2004-8-10 
����޸�����      ��2004-8-10 
-----------------------------------------------------------------------*/

void ICACHE_FLASH_ATTR delay_1us(void)                 //1us��ʱ����
  {
   unsigned int i;
  for(i=0;i<1;i++);
  }

  void ICACHE_FLASH_ATTR delay_1ms(void)                 //1ms��ʱ����
  {
   unsigned int i;
   for (i=0;i<1;i++);
  }
  
void ICACHE_FLASH_ATTR delay_nms(unsigned int n)       //N ms��ʱ����
  {
   unsigned int i=0;
   for (i=0;i<n;i++)
   delay_1ms();
  }


void ICACHE_FLASH_ATTR LCD_init(void)
  {
            // ����һ����LCD��λ�ĵ͵�ƽ����
	LCD_RST_0;
    delay_1us();
    LCD_RST_1;
		// �ر�LCD
    LCD_CE_0;
    delay_1us();
		// ʹ��LCD
    LCD_CE_1;
    delay_1us();

    LCD_write_byte(0x21, 0);	// ʹ����չ��������LCDģʽ
    LCD_write_byte(0xc8, 0);	// ����ƫ�õ�ѹ
    LCD_write_byte(0x06, 0);	// �¶�У��
    LCD_write_byte(0x13, 0);	// 1:48
    LCD_write_byte(0x20, 0);	// ʹ�û�������
    LCD_clear();	        // ����
    LCD_write_byte(0x0c, 0);	// �趨��ʾģʽ��������ʾ
    // �ر�LCD
    LCD_CE_0;
  }

/*-----------------------------------------------------------------------
LCD_clear         : LCD��������

��д����          ��2004-8-10 
����޸�����      ��2004-8-10 
-----------------------------------------------------------------------*/
void ICACHE_FLASH_ATTR LCD_clear(void)
  {
    unsigned int i;

    LCD_write_byte(0x0c, 0);			
    LCD_write_byte(0x80, 0);			

    for (i=0; i<504; i++)
      LCD_write_byte(0, 1);			
  }

/*-----------------------------------------------------------------------
LCD_set_XY        : ����LCD���꺯��

���������X       ��0��83
          Y       ��0��5

��д����          ��2004-8-10 
����޸�����      ��2004-8-10 
-----------------------------------------------------------------------*/
void ICACHE_FLASH_ATTR LCD_set_XY(unsigned char X, unsigned char Y)
  {
    LCD_write_byte(0x40 | Y, 0);		// column
    LCD_write_byte(0x80 | X, 0);          	// row
  }

/*-----------------------------------------------------------------------
LCD_write_char    : ��ʾӢ���ַ�

���������c       ����ʾ���ַ���

��д����          ��2004-8-10 
����޸�����      ��2004-8-10 
-----------------------------------------------------------------------*/
void ICACHE_FLASH_ATTR LCD_write_char(unsigned char c)
  {
    unsigned char line;

    c -= 32;

    for (line=0; line<6; line++)
      LCD_write_byte(font6x8[c][line], 1);
  }

/*-----------------------------------------------------------------------
LCD_write_english_String  : Ӣ���ַ�����ʾ����

���������*s      ��Ӣ���ַ���ָ�룻
          X��Y    : ��ʾ�ַ�����λ��,x 0-83 ,y 0-5

��д����          ��2004-8-10 
����޸�����      ��2004-8-10 		
-----------------------------------------------------------------------*/
void ICACHE_FLASH_ATTR LCD_write_english_string(unsigned char X,unsigned char Y,char *s)
  {
    LCD_set_XY(X,Y);
    while (*s) 
      {
	 LCD_write_char(*s);
	 s++;
      }
  }
/*-----------------------------------------------------------------------
LCD_write_chinese_string: ��LCD����ʾ����

���������X��Y    ����ʾ���ֵ���ʼX��Y���ꣻ
          ch_with �����ֵ���Ŀ���
          num     ����ʾ���ֵĸ�����
          line    �����ֵ��������е���ʼ����
          row     ��������ʾ���м��
��д����          ��2004-8-11
����޸�����      ��2004-8-12
���ԣ�
	LCD_write_chi(0,0,12,7,0,0);
	LCD_write_chi(0,2,12,7,0,0);
	LCD_write_chi(0,4,12,7,0,0);
-----------------------------------------------------------------------*/
void ICACHE_FLASH_ATTR LCD_write_chinese_string(unsigned char X, unsigned char Y,
                   unsigned char ch_with,unsigned char num,
                   unsigned char line,unsigned char row)
  {
    unsigned char i,n;

    LCD_set_XY(X,Y);                             //���ó�ʼλ��

    for (i=0;i<num;)
      {
      	for (n=0; n<ch_with*2; n++)              //дһ������
      	  {
      	    if (n==ch_with)                      //д���ֵ��°벿��
      	      {
      	        if (i==0) LCD_set_XY(X,Y+1);
      	        else
      	           LCD_set_XY((X+(ch_with+row)*i),Y+1);
              }
      	    LCD_write_byte(write_chinese[line+i][n],1);
      	  }
      	i++;
      	LCD_set_XY((X+(ch_with+row)*i),Y);
      }
  }



/*-----------------------------------------------------------------------
LCD_draw_map      : λͼ���ƺ���

���������X��Y    ��λͼ���Ƶ���ʼX��Y���ꣻ
          *map    ��λͼ�������ݣ�
          Pix_x   ��λͼ���أ�����
          Pix_y   ��λͼ���أ�����

��д����          ��2004-8-13
����޸�����      ��2004-8-13 
-----------------------------------------------------------------------*/
void ICACHE_FLASH_ATTR LCD_draw_bmp_pixel(unsigned char X,unsigned char Y,unsigned char *map,
                  unsigned char Pix_x,unsigned char Pix_y)
  {
    unsigned int i,n;
    unsigned char row;
    
    if (Pix_y%8==0) row=Pix_y/8;      //����λͼ��ռ����
      else
        row=Pix_y/8+1;
    
    for (n=0;n<row;n++)
      {
      	LCD_set_XY(X,Y);
        for(i=0; i<Pix_x; i++)
          {
            LCD_write_byte(map[i+n*Pix_x], 1);
          }
        Y++;                         //����
      }      
  }

/*-----------------------------------------------------------------------
LCD_write_byte    : ʹ��SPI�ӿ�д���ݵ�LCD

���������data    ��д������ݣ�
          command ��д����/����ѡ��

��д����          ��2004-8-10 
����޸�����      ��2004-8-13 
-----------------------------------------------------------------------*/
void ICACHE_FLASH_ATTR LCD_write_byte(unsigned char dat, unsigned char command)
  {
    unsigned char i;
    //PORTB &= ~LCD_CE ;		        // ʹ��LCD
    LCD_CE_0;
    //os_printf("\r\n===LCD_CE_0===\r\n");
    if (command == 0)
    {
     // PORTB &= ~LCD_DC ;	        // ��������
    	LCD_DC_0;
    	//os_printf("\r\n===LCD_DC_0===\r\n");
    }
    else
    {
     // PORTB |= LCD_DC ;		        // ��������
    	LCD_DC_1;
    	//os_printf("\r\n===LCD_DC_1===\r\n");
    }
		for(i=0;i<8;i++)
		{
			//os_printf("\r\n===i=%d===\r\n",i);
			if(dat&0x80)
			{
				//os_printf("\r\n===SDIN_1===\r\n");
				SDIN_1;
			}
			else
			{
				//os_printf("\r\n===SDIN_1===\r\n");
				SDIN_0;
			}

			//os_printf("\r\n===SCLK_0===\r\n");
			SCLK_0;
			dat = dat << 1;

			//os_printf("\r\n===SCLK_1===\r\n");
			SCLK_1;
		}
   // SPDR = data;			// �������ݵ�SPI�Ĵ���

    //while ((SPSR & 0x80) == 0);         // �ȴ����ݴ������
	
    //PORTB |= LCD_CE ;			// �ر�LCD
		LCD_CE_1;
		//os_printf("\r\n===LCD_CE_1===\r\n");
  }


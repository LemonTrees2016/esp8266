/* * ESPRESSIF MIT License
 *
 * Copyright (c) 2016 <ESPRESSIF SYSTEMS (SHANGHAI) PTE LTD>
 *
 * Permission is hereby granted for use on ESPRESSIF SYSTEMS ESP8266 only, in which case,
 * it is free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//															//														//
// ���̣�	SNTP_SmartConfig								//		�٣���λ8266��8266��ʼ����WIFI��				//
//															//														//
// ƽ̨��	�����µ��ӡ������������� ESP8266 V1.0			//		�ڣ����WIFI���Ӳ��ϣ������΢������			//
//															//														//
// ���ܣ�	�٣�8266����ΪSTAģʽ������WIFI�ȵ�				//		�ۣ�OLED��ʾ�����ڡ���ʱ�ӡ����¶ȡ���ʪ�ȡ�	//
//															//														//
//			�ڣ����WIFI���ӳ������롾΢��������			//		�ܣ�OLED_1�У����ꡢ�¡��ա�����X��				//
//															//														//
//			�ڣ�����SNTP����������ʼ��SNTP					//		�ݣ�OLED_2�У���Clock = ʱ���֡��롿			//
//															//														//
//			�ۣ�ÿ���ѯInternetʱ��						//		�ޣ�OLED_3�У���Hunid = ʪ�� %RH��				//
//															//														//
//			�ܣ�ÿ5���ȡDHT11������ʪ��					//		�ߣ�OLED_4�У���Temp  = �¶� �桿				//
//															//														//
//			�ݣ�OLED��ʾ��Internetʱ�䡿����������ʪ�ȡ�	//		�ࣺ���DHT11��ȡʧ�ܣ���ʪ����ʾ��----��		//
//															//														//
//	�汾��	V1.0											//		�᣺8266��OLEDͨ��ʱ����ɫOLED��˸				//
//															//														//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// ͷ�ļ�����
//==================================================================================
#include "user_config.h"		// �û�����
#include "driver/uart.h"  		// ����
//#include "driver/oled.h"  		// OLED
#include "driver/dht11.h"		// DHT11

//#include "at_custom.h"
#include "c_types.h"			// ��������
#include "ip_addr.h"			// ��"espconn.h"ʹ�á�
#include "espconn.h"			// TCP/UDP�ӿ�
//#include "espnow.h"
#include "ets_sys.h"			// �ص�����
//#include "gpio.h"
#include "mem.h"				// �ڴ�����Ⱥ���
#include "os_type.h"			// os_XXX
#include "osapi.h"  			// os_XXX�������ʱ��
//#include "ping.h"
//#include "pwm.h"
//#include "queue.h"
#include "smartconfig.h"		// ��������
#include "sntp.h"				// SNTP
//#include "spi_flash.h"
//#include "upgrade.h"
#include "user_interface.h" 	// ϵͳ�ӿڡ�system_param_xxx�ӿڡ�WIFI��RateContro
//#include "user_light.h"
#include "espconn.h"
#include "mem.h"
#include "pwm.h"
#include "user_light.h"
#include "gpio16.h"
#include "eagle_soc.h"			// GPIO�������궨��
#include "led_matrix_main.h"			// GPIO�������궨��
#include "time_tool.h"			//
#include "weather.h"

//==================================================================================


// �궨��
//==================================================================================
#define		ProjectName			"SNTP_SmartConfig"		// �������궨��

#define		Sector_STA_INFO		0x90			// ��STA��������������

#define		ID_SWITCH_NTF 0x01
#define		ID_DELAY_SWITHC_NTF 0x02
#define		ID_MOTOR_CTRL_NTF	0x03
#define		ID_VOIDCE_CTRL_NTF	0x04
#define		ID_VIDEO_CTRL_NTF	0x05
#define		ID_QUERY_TEMP_NTF	0x06 /* ��ѯ�¶���Ϣ */
#define     ID_SET_DISP_INTERV_NTF 0x07 /* ������������  */
#define     ID_SET_DISP_OPEN_CLOSE_TIME_NTF 0x08 /* ���ÿ��ػ�ʱ�� */
#define     ID_SET_DISP_TIME_NTF 0x09 /* ����ʱ�� */
//==================================================================================
void  OS_Timer_DISP_Init_JX(u32 time_ms, u8 time_repetitive);
// ȫ�ֱ���
//==================================================================================
struct station_config STA_INFO;		// ��STA�������ṹ��

u8 C_LED_Flash = 0;					// LED��˸�ƴ�

u8 C_Read_DHT11 = 0;				// ��ȡDHT11��ʱ

os_timer_t OS_Timer_IP;				// ��ʱ��_��ѯIP��ַ
os_timer_t OS_Timer_TIME;				// ��ʱ��_��ѯʱ��
os_timer_t OS_Timer_DISP;				// ��ʱ��_��ʾ

os_timer_t OS_Timer_SNTP;			// ��ʱ��_SNTP

extern struct light_saved_param light_param;

typedef struct
{
	unsigned char  msgId; //��ϢID
	unsigned char  ucModuleId;//ģ��ID
	unsigned char  usValue[4];//��������
}stMsgComm;

typedef struct
{
	unsigned char  msgId; //��ϢID
	unsigned char  ucModuleId;//ģ��ID
	unsigned char  ucPortId;
	unsigned char  ucDirct;
	unsigned char  ucSwitchState;/* off / on */
	unsigned char  reserve;
}SWITCH_NTF_STRU;

//==================================================================================
ETSTimer connect_timer;
void  my_server_init(struct ip_addr *local_ip,int port);
void  Wifi_conned(void){
    static uint8 count=0;
    uint8 opmode;
    struct ip_info info; //���ڻ�ȡIP��ַ����Ϣ
    uint8 status;
    os_timer_disarm(&connect_timer);
    count++;
    status=wifi_station_get_connect_status();
    if(status==STATION_GOT_IP){
        os_printf("Wifi connect success!");

        wifi_get_ip_info(0,&info);
        opmode = wifi_get_opmode_default();
        os_printf("\r\n��ǰ�Ĺ���ģʽ:%d\r\n",opmode);
        //my_station_init((struct ip_addr *)remote_ip,&info.ip,1025);//Client�˳�ʼ��������
        my_server_init(&info.ip,1213);//Server�˳�ʼ��������
        return;
    }else{
        if(count>=7){
        os_printf("Wifi connect fail��");
        return;
        }
    }
    os_timer_arm(&connect_timer, 2000, 0);
}

extern uint8_t g_disp_user_data;
/**************************************
 * ���֣�ESP_ProcSwithcNtf
 * ���ܣ���������صĿ�����Ϣ
 * ��Σ���Ϣ�ṹָ��pdata
 * �������
 *
 **************************************/
void  ESP_ProcSwithcNtf(void *pdata)
{
	SWITCH_NTF_STRU* pstSwithcNtf = (SWITCH_NTF_STRU*)pdata;

	os_printf("mgdid = %d \n", pstSwithcNtf->msgId);
	os_printf("ucModuleId = %d \n", pstSwithcNtf->ucModuleId);
	os_printf("usValue0 = %d \n", pstSwithcNtf->ucPortId);
	os_printf("usValue1 = %d \n", pstSwithcNtf->ucDirct);
	os_printf("usValue2 = %d \n", pstSwithcNtf->ucSwitchState);
	os_printf("usValue3 = %d \n", pstSwithcNtf->reserve);

	// ����ʾ����
	if(1 == pstSwithcNtf->ucPortId)
	{
		if (pstSwithcNtf->ucSwitchState == 0) {
			clear_disp_flag(); // 01 01 01 00 00 00
		} else {
			set_disp_flag();   // 01 01 01 00 01 00
		}
	}

	return;
}

void  server_recv(void *arg,
            char *pdata,
            unsigned short len){//�������ݵĻص�����
	int i;
	unsigned char Iter1;
	uint32 duty=0;
	unsigned char Tmp_Humid_Char[21] = {0};
	os_printf("�յ�PC���������ݣ�%s\r\n",pdata);//���ͻ��˷����������ݴ�ӡ����
	//espconn_sent((struct espconn *)arg,"�����Ѿ��յ�\r\n",strlen("�����Ѿ��յ�"));//���ͻ�����������

	for(i=0;i < len; i++)
	{
		os_printf("\r\n%d\r\n", pdata[i]);
	}

	stMsgComm* pstSocketMsg = (stMsgComm*)(pdata);
	os_printf("mgdid = %d \n", pstSocketMsg->msgId);
	os_printf("ucModuleId = %d \n", pstSocketMsg->ucModuleId);
	os_printf("usValue0 = %d \n", pstSocketMsg->usValue[0]);
	os_printf("usValue1 = %d \n", pstSocketMsg->usValue[1]);
	os_printf("usValue2 = %d \n", pstSocketMsg->usValue[2]);
	os_printf("usValue3 = %d \n", pstSocketMsg->usValue[3]);

	/* ����յ������ݳ��Ȳ����Ա�ʾMSG���ݣ����� */
	os_printf("length��%d\r\n",len);//���ͻ��˷����������ݴ�ӡ����
	if(len < sizeof(stMsgComm))
	{
		os_printf("length eror ��%d\r\n",sizeof(stMsgComm));
		return;
	}

	switch(pstSocketMsg->msgId)
	{
		/*MsgId1��ʾ1����LED�Ƶ����ſ���*/
		case ID_SWITCH_NTF:
			{
				os_printf("ID_SWITCH_NTF\r\n");
				ESP_ProcSwithcNtf(pdata);
				break;
			}
		case ID_DELAY_SWITHC_NTF:
			{
				os_printf("ID_DELAY_SWITHC_NTF0\r\n");
				os_printf("old duty=%d\r\n", user_light_get_duty(0));

				duty = (pstSocketMsg->usValue[1] * 256) + pstSocketMsg->usValue[2];

				os_printf("duty=%d\r\n", duty);
				user_light_set_duty(duty, 0);
				//user_light_set_duty(duty, 1);
				pwm_start();
				break;
			}
		case ID_MOTOR_CTRL_NTF:
			{
				os_printf("ID_MOTOR_CTRL_NTF\r\n");
				break;
			}
		case ID_VOIDCE_CTRL_NTF:
			{
				os_printf("ID_VOIDCE_CTRL_NTF\r\n");
				break;
			}
		case ID_VIDEO_CTRL_NTF:
			{
				os_printf("ID_VIDEO_CTRL_NTF\r\n");
				break;
			}
		case ID_QUERY_TEMP_NTF:
			{
				SetTempear(pstSocketMsg->usValue[0]);
				SetHumid(pstSocketMsg->usValue[1]);

				/* �����¶�Ϊ20�ȣ� ʪ��Ϊ32%��������Ϣ  06 01 14 20 01 01  */
				espconn_send((struct espconn *)arg, Tmp_Humid_Char, 20);
				break;
			}
		case ID_SET_DISP_INTERV_NTF:
		{
			/* ������Ϣ  07 01 32 00 00 00  */
			if (pstSocketMsg->usValue[0] < 10) {
				break;
			}
			OS_Timer_DISP_Init_JX(pstSocketMsg->usValue[0], 1); // 10 ms��ʾ����
			break;
		}
		case ID_SET_DISP_OPEN_CLOSE_TIME_NTF:
		{
			/* ���ùػ�ʱ�� ����11��32�֣�����ʱ��6������������Ϣ  08 01 17 20 05 20  */
			hour_to_close = pstSocketMsg->usValue[0] % 24;
			minit_to_close = pstSocketMsg->usValue[1] % 60;
			hour_to_open = pstSocketMsg->usValue[2] % 24;
			minit_to_open = pstSocketMsg->usValue[3] % 60;
			break;
		}
		default:
			os_printf("default\r\n");
			break;
	}

}
void  server_sent(void *arg){//�������ݳɹ��Ļص�����
    os_printf("�������ݳɹ�����\r\n");
}
void  server_discon(void *arg){//�Ͽ����ӵĻص�����
    os_printf("�����Ѿ��Ͽ�\r\n");
}

void  server_listen(void *arg){//��������������
    struct espconn *pespconn=arg;

    espconn_regist_recvcb(pespconn,server_recv);//ע��һ���������ݵĻص�����
    espconn_regist_sentcb(pespconn,server_sent);//ע��һ���������ݳɹ��Ļص�����
    espconn_regist_disconcb(pespconn,server_discon);//ע��һ���Ͽ����ӵĻص�����
}

void  server_recon(void *arg,sint8 err){//�������ӻص�����
    os_printf("���Ӵ��󣬴������Ϊ��%s\r\n",err);//����������ӵĴ������
}

void  my_server_init(struct ip_addr *local_ip,int port){
    LOCAL struct espconn esp_conn;
    esp_conn.type=ESPCONN_TCP;
    esp_conn.state=ESPCONN_NONE;
    esp_conn.proto.tcp=(esp_tcp *)os_malloc(sizeof(esp_tcp));

    os_memcpy(esp_conn.proto.tcp->local_ip,local_ip,4);
    esp_conn.proto.tcp->local_port=port;


    //ע�����ӳɹ��Ļص�����������ʧ���������ӵĻص�����
    espconn_regist_connectcb(&esp_conn,server_listen);//ע��һ�����ӳɹ��ص�����
    espconn_regist_reconcb(&esp_conn,server_recon);//ע��һ������ʧ���������ӻص�����


    espconn_accept(&esp_conn);
}

// ������ʱ����
//===========================================
void  delay_ms(u32 C_time)
{	for(;C_time>0;C_time--)
		os_delay_us(1000);
}
//===========================================



//	 -----------------------------------------------			 -----------------------------------------------
//	|	  �·�		|	Ӣ�ļ�д	|	Ӣ��ȫ��	|			|	  ����X		|	Ӣ�ļ�д	|	Ӣ��ȫ��	|
//	 -----------------------------------------------			 -----------------------------------------------
//	| 	  һ��		|	  Jan		|	January		|			|	  ��һ		|	  Mon		|	Monday		|
//	 -----------------------------------------------			 -----------------------------------------------
//	|	  ����		|	  Feb		|	February	|			|	  �ܶ�		|	  Tue		|	Tuesday		|
//	 -----------------------------------------------			 -----------------------------------------------
//	| 	  ����		|	  Mar		|	March		|			|	  ����		|	  Wed		|	Wednesday	|
//	 -----------------------------------------------			 -----------------------------------------------
//	| 	  ����		|	  Apr		|	April		|			|	  ����		|	  Thu		|	Thursday	|
//	 -----------------------------------------------			 -----------------------------------------------
//	|  	  ����		|	  May		|	May			|			|	  ����		|	  Fri		|	Friday		|
//	 -----------------------------------------------			 -----------------------------------------------
//	|  	  ����		|	  June		|	June		|			|	  ����		|	  Sat		|	Saturday	|
//	 -----------------------------------------------			 -----------------------------------------------
//	|  	  ����		|	  July		|	July		|			|	  ����		|	  Sun		|	Sunday		|
//	 -----------------------------------------------			 -----------------------------------------------
//	|  	  ����		|	  Aug		|	Aguest		|
//	 -----------------------------------------------
//	|  	  ����		|	  Sept		|	September	|
//	 -----------------------------------------------
//	|  	  ʮ��		|	  Oct		|	October		|
//	 -----------------------------------------------
//	|  	 ʮһ��		|	  Nov		|	November	|
//	 -----------------------------------------------
//	|  	 ʮ����		|	  Dec		|	December	|
//	 -----------------------------------------------


// SNTP��ʱ�ص�����
//===================================================================================================
void  OS_Timer_SNTP_cb(void	 * arg)
{
	// �ַ������� ��ر���
	//------------------------------------------------------

	u8 C_Str = 0;				// �ַ����ֽڼ���

	char A_Str_Data[20] = {0};	// ��"����"���ַ�������

	char *T_A_Str_Data = A_Str_Data;	// ��������ָ��

	char A_Str_Clock[10] = {0};	// ��"ʱ��"���ַ�������


	char * Str_Head_Week;		// ��"����"���ַ����׵�ַ

	char * Str_Head_Month;		// ��"�·�"���ַ����׵�ַ

	char * Str_Head_Day;		// ��"����"���ַ����׵�ַ

	char * Str_Head_Clock;		// ��"ʱ��"���ַ����׵�ַ

	char * Str_Head_Year;		// ��"���"���ַ����׵�ַ

	//------------------------------------------------------


	 uint32	TimeStamp;		// ʱ���

	 char * Str_RealTime;	// ʵ��ʱ����ַ���


	 // ��ѯ��ǰ�����׼ʱ��(1970.01.01 00:00:00 GMT+8)��ʱ���(��λ:��)
	 //-----------------------------------------------------------------
	 TimeStamp = sntp_get_current_timestamp();

	 if(TimeStamp)		// �ж��Ƿ��ȡ��ƫ��ʱ��
	 {
		 //os_timer_disarm(&OS_Timer_SNTP);	// �ر�SNTP��ʱ��

		 // ��ѯʵ��ʱ��(GMT+8):������(����ʱ��)
		 //--------------------------------------------
		 Str_RealTime = sntp_get_real_time(TimeStamp);


		 // ��ʵ��ʱ�䡿�ַ��� == "�� �� �� ʱ:��:�� ��"
		 //------------------------------------------------------------------------
		 os_printf("\r\n----------------------------------------------------\r\n");
		 os_printf("SNTP_TimeStamp = %d\r\n",TimeStamp);		// ʱ���
		 os_printf("\r\nSNTP_InternetTime = %s",Str_RealTime);	// ʵ��ʱ��
		 os_printf("--------------------------------------------------------\r\n");


		 // ʱ���ַ�������OLED��ʾ��"����"������"ʱ��"���ַ���
		 //��������������������������������������������������������������������������������������

		 // ��"���" + ' '��������������
		 //---------------------------------------------------------------------------------
		 Str_Head_Year = Str_RealTime;	// ������ʼ��ַ

		 while( *Str_Head_Year )		// �ҵ���"ʵ��ʱ��"���ַ����Ľ����ַ�'\0'
			 Str_Head_Year ++ ;

		 // ��ע��API���ص�ʵ��ʱ���ַ����������һ�����з����������� -5��
		 //-----------------------------------------------------------------
		 Str_Head_Year -= 5 ;			// ��ȡ��"���"���ַ������׵�ַ

		 T_A_Str_Data[4] = ' ' ;
		 os_memcpy(T_A_Str_Data, Str_Head_Year, 4);		// ��"���" + ' '��������������

		 T_A_Str_Data += 5;				// ָ��"���" + ' '���ַ����ĺ���ĵ�ַ
		 //---------------------------------------------------------------------------------

		 // ��ȡ�����ڡ��ַ������׵�ַ
		 //---------------------------------------------------------------------------------
		 Str_Head_Week 	= Str_RealTime;							// "����" �ַ������׵�ַ
		 Str_Head_Month = os_strstr(Str_Head_Week,	" ") + 1;	// "�·�" �ַ������׵�ַ
		 Str_Head_Day 	= os_strstr(Str_Head_Month,	" ") + 1;	// "����" �ַ������׵�ַ
		 Str_Head_Clock = os_strstr(Str_Head_Day,	" ") + 1;	// "ʱ��" �ַ������׵�ַ


		 // ��"�·�" + ' '��������������
		 //---------------------------------------------------------------------------------
		 C_Str = Str_Head_Day - Str_Head_Month;				// ��"�·�" + ' '�����ֽ���

		 os_memcpy(T_A_Str_Data, Str_Head_Month, C_Str);	// ��"�·�" + ' '��������������

		 T_A_Str_Data += C_Str;		// ָ��"�·�" + ' '���ַ����ĺ���ĵ�ַ


		 // ��"����" + ' '��������������
		 //---------------------------------------------------------------------------------
		 C_Str = Str_Head_Clock - Str_Head_Day;				// ��"����" + ' '�����ֽ���

		 os_memcpy(T_A_Str_Data, Str_Head_Day, C_Str);		// ��"����" + ' '��������������

		 T_A_Str_Data += C_Str;		// ָ��"����" + ' '���ַ����ĺ���ĵ�ַ


		 // ��"����" + ' '��������������
		 //---------------------------------------------------------------------------------
		 C_Str = Str_Head_Month - Str_Head_Week - 1;		// ��"����"�����ֽ���

		 os_memcpy(T_A_Str_Data, Str_Head_Week, C_Str);		// ��"����"��������������

		 T_A_Str_Data += C_Str;		// ָ��"����"���ַ����ĺ���ĵ�ַ


		 // OLED��ʾ��"����"������"ʱ��"���ַ���
		 //---------------------------------------------------------------------------------
		 *T_A_Str_Data = '\0';		// ��"����"���ַ����������'\0'

		 //OLED_ShowString(0,0,A_Str_Data);		// OLED��ʾ����


		 os_memcpy(A_Str_Clock, Str_Head_Clock, 8);		// ��"ʱ��"���ַ�������ʱ������
		 A_Str_Clock[8] = '\0';

		 //OLED_ShowString(64,2,A_Str_Clock);		// OLED��ʾʱ��

		 //��������������������������������������������������������������������������������������
	 }

}
//===================================================================================================


// SNTP��ʱ��ʼ��
//=============================================================================
void  OS_Timer_SNTP_Init_JX(u32 time_ms, u8 time_repetitive)
{
	os_timer_disarm(&OS_Timer_SNTP);
	os_timer_setfn(&OS_Timer_SNTP,(os_timer_func_t *)OS_Timer_SNTP_cb,NULL);
	os_timer_arm(&OS_Timer_SNTP, time_ms, time_repetitive);
}
//=============================================================================


// ��ʼ��SNTP
//=============================================================================
void  ESP8266_SNTP_Init_JX(void)
{
	ip_addr_t * addr = (ip_addr_t *)os_zalloc(sizeof(ip_addr_t));

	sntp_setservername(0, "us.pool.ntp.org");	// ������_0��������
	sntp_setservername(1, "ntp.sjtu.edu.cn");	// ������_1��������

	ipaddr_aton("210.72.145.44", addr);			// ���ʮ���� => 32λ������
	sntp_setserver(2, addr);					// ������_2��IP��ַ��
	os_free(addr);								// �ͷ�addr

	sntp_init();	// SNTP��ʼ��API

	//OS_Timer_SNTP_Init_JX(1000,1);				// 1���ظ���ʱ(SNTP)
}
//=============================================================================


// SmartConfig״̬�����ı�ʱ������˻ص�����
//--------------------------------------------
// ����1��sc_status status / ����2��������ָ�롾�ڲ�ͬ״̬�£�[void *pdata]�Ĵ�������ǲ�ͬ�ġ�
//=================================================================================================================
void  smartconfig_done(sc_status status, void *pdata)
{
	os_printf("\r\n------ smartconfig_done ------\r\n");	// ESP8266����״̬�ı�

    switch(status)
    {
    	// CmartConfig�ȴ�
		//����������������������������������������
		case SC_STATUS_WAIT:		// ��ʼֵ
			os_printf("\r\nSC_STATUS_WAIT\r\n");
		break;
		//����������������������������������������

		// ���֡�WIFI�źš���8266������״̬�µȴ�������
		//��������������������������������������������������������������������������
		case SC_STATUS_FIND_CHANNEL:
			os_printf("\r\nSC_STATUS_FIND_CHANNEL\r\n");

			os_printf("\r\n---- Please Use WeChat to SmartConfig ------\r\n\r\n");

			//OLED_ShowString(0,4,"Use WeChat to   ");
			//OLED_ShowString(0,6,"SmartConfig     ");
		break;
		//��������������������������������������������������������������������������

        // ���ڻ�ȡ��SSID����PSWD��
        //��������������������������������������������������������������������������
        case SC_STATUS_GETTING_SSID_PSWD:
            os_printf("\r\nSC_STATUS_GETTING_SSID_PSWD\r\n");

            // ��SC_STATUS_GETTING_SSID_PSWD��״̬�£�����2==SmartConfig����ָ��
            //-------------------------------------------------------------------
			sc_type *type = pdata;		// ��ȡ��SmartConfig���͡�ָ��

			// ������ʽ == ��ESPTOUCH��
			//-------------------------------------------------
            if (*type == SC_TYPE_ESPTOUCH)
            { os_printf("\r\nSC_TYPE:SC_TYPE_ESPTOUCH\r\n"); }

            // ������ʽ == ��AIRKISS��||��ESPTOUCH_AIRKISS��
            //-------------------------------------------------
            else
            { os_printf("\r\nSC_TYPE:SC_TYPE_AIRKISS\r\n"); }

	    break;
	    //��������������������������������������������������������������������������

	    // �ɹ���ȡ����SSID����PSWD��������STA������������WIFI
	    //��������������������������������������������������������������������������
        case SC_STATUS_LINK:
            os_printf("\r\nSC_STATUS_LINK\r\n");

            // ��SC_STATUS_LINK��״̬�£�����2 == STA����ָ��
            //------------------------------------------------------------------
            struct station_config *sta_conf = pdata;	// ��ȡ��STA������ָ��

            // ����SSID����PASS�����浽���ⲿFlash����
            //--------------------------------------------------------------------------
			spi_flash_erase_sector(Sector_STA_INFO);						// ��������
			spi_flash_write(Sector_STA_INFO*4096, (uint32 *)sta_conf, 96);	// д������
			//--------------------------------------------------------------------------

	        wifi_station_set_config(sta_conf);			// ����STA������Flash��
	        wifi_station_disconnect();					// �Ͽ�STA����
	        wifi_station_connect();						// ESP8266����WIFI

	    	//OLED_ShowString(0,4,"WIFI Connecting ");	// OLED��ʾ��
	    	//OLED_ShowString(0,6,"................");	// ��������WIFI

	    break;
	    //��������������������������������������������������������������������������


        // ESP8266��ΪSTA���ɹ����ӵ�WIFI
	    //��������������������������������������������������������������������������
        case SC_STATUS_LINK_OVER:
            os_printf("\r\nSC_STATUS_LINK_OVER\r\n");

            smartconfig_stop();		// ֹͣSmartConfig

            //**************************************************************************************************
//			wifi_get_ip_info(STATION_IF,&ST_ESP8266_IP);	// ��ȡ8266_STA��IP��ַ

//			ESP8266_IP[0] = ST_ESP8266_IP.ip.addr;		// IP��ַ�߰�λ == addr�Ͱ�λ
//			ESP8266_IP[1] = ST_ESP8266_IP.ip.addr>>8;	// IP��ַ�θ߰�λ == addr�εͰ�λ
//			ESP8266_IP[2] = ST_ESP8266_IP.ip.addr>>16;	// IP��ַ�εͰ�λ == addr�θ߰�λ
//			ESP8266_IP[3] = ST_ESP8266_IP.ip.addr>>24;	// IP��ַ�Ͱ�λ == addr�߰�λ

			// ��ʾESP8266��IP��ַ
			//-----------------------------------------------------------------------------------------------
//			os_printf("ESP8266_IP = %d.%d.%d.%d\n",ESP8266_IP[0],ESP8266_IP[1],ESP8266_IP[2],ESP8266_IP[3]);
//			OLED_ShowIP(24,2,ESP8266_IP);	// OLED��ʾESP8266��IP��ַ
//			//OLED_ShowString(0,4,"Connect to WIFI ");
//			//OLED_ShowString(0,6,"Successfully    ");
			//-----------------------------------------------------------------------------------------------
            //OLED_ShowPicture();
    		//----------------------------------------------------------------
            /* �� ʾ�������� */
    		////OLED_ShowString(0,0,"                ");	// Internet Time
    		////OLED_ShowString(0,2,"Clock =         ");	// Clock��ʱ��
    		////OLED_ShowString(0,4,"Temps =         ");	// Temperature���¶�
    		////OLED_ShowString(0,6,"Humid =         ");	// Humidity��ʪ��
    		//----------------------------------------------------------------

			// ����WIFI�ɹ���LED����3��
			//----------------------------------------------------

			//ESP8266_SNTP_Init_JX();		// ��ʼ��SNTP

			os_printf("\r\n---- ESP8266 Connect to WIFI Successfully ----\r\n");
			//**************************************************************************************************

	    break;
	    //��������������������������������������������������������������������������

    }
}
//=================================================================================================================



// IP��ʱ���Ļص�����
//=========================================================================================================
void  OS_Timer_IP_cb(void)
{
	struct ip_info ST_ESP8266_IP;	// ESP8266��IP��Ϣ
	u8 ESP8266_IP[4];				// ESP8266��IP��ַ
	/*uint32 io_info[][31] = {
	{PERIPHS_IO_MUX_GPIO4_U,PWM_2_OUT_IO_FUNC,GPIO_ID_PIN(4)}};*/

	u8 S_WIFI_STA_Connect = wifi_station_get_connect_status();


	// �ɹ�����WIFI��STAģʽ�£��������DHCP(Ĭ��)����ESO8266��IP��ַ��WIFI·�����Զ����䡿
	//-------------------------------------------------------------------------------------
	if( S_WIFI_STA_Connect == STATION_GOT_IP )	// �ж��Ƿ��ȡIP
	{
		wifi_get_ip_info(STATION_IF,&ST_ESP8266_IP);	// ��ȡSTA��IP��Ϣ
		ESP8266_IP[0] = ST_ESP8266_IP.ip.addr;			// IP��ַ�߰�λ == addr�Ͱ�λ
		ESP8266_IP[1] = ST_ESP8266_IP.ip.addr>>8;		// IP��ַ�θ߰�λ == addr�εͰ�λ
		ESP8266_IP[2] = ST_ESP8266_IP.ip.addr>>16;		// IP��ַ�εͰ�λ == addr�θ߰�λ
		ESP8266_IP[3] = ST_ESP8266_IP.ip.addr>>24;		// IP��ַ�Ͱ�λ == addr�߰�λ

		os_timer_disarm(&OS_Timer_IP);	// �رն�ʱ��
		os_printf("\r\n---- ESP8266 Connect to WIFI Successfully ----\r\n");


		ESP8266_SNTP_Init_JX();			// ��ʼ��SNTP

		Wifi_conned();
	}


	// ESP8266�޷�����WIFI
	//------------------------------------------------------------------------------------------------
	else if(	S_WIFI_STA_Connect==STATION_NO_AP_FOUND 	||		// δ�ҵ�ָ��WIFI
				S_WIFI_STA_Connect==STATION_WRONG_PASSWORD 	||		// WIFI�������
				S_WIFI_STA_Connect==STATION_CONNECT_FAIL		)	// ����WIFIʧ��
	{
		os_timer_disarm(&OS_Timer_IP);			// �رն�ʱ��

		os_printf("\r\n---- ESP8266 Can't Connect to WIFI-----------\r\n");


		// ΢��������������
		//��������������������������������������������������������������������������������������������
		//wifi_set_opmode(STATION_MODE);		// ��ΪSTAģʽ							//���ڢٲ���

		smartconfig_set_type(SC_TYPE_AIRKISS); 	// ESP8266������ʽ��AIRKISS��			//���ڢڲ���

		smartconfig_start(smartconfig_done);	// ���롾��������ģʽ��,�����ûص�����	//���ڢ۲���
		//��������������������������������������������������������������������������������������������
	}
}
//=========================================================================================================

// �����ʱ����ʼ��(ms����)
//========================================================================================
void  OS_Timer_IP_Init_JX(u32 time_ms, u8 time_repetitive)
{
	os_timer_disarm(&OS_Timer_IP);	// �رն�ʱ��
	os_timer_setfn(&OS_Timer_IP,(os_timer_func_t *)OS_Timer_IP_cb, NULL);	// ���ö�ʱ��
	os_timer_arm(&OS_Timer_IP, time_ms, time_repetitive);  // ʹ�ܶ�ʱ��
}


void ICACHE_FLASH_ATTR
pwm_user_light_init(void)
{
	uint32 io_info[][3] = {   {PWM_5_OUT_IO_MUX,PWM_5_OUT_IO_NUM,PWM_5_OUT_IO_FUNC},
		                      };
    uint32 pwm_duty_init[PWM_CHANNEL] = {0};

	light_param.pwm_period = 1000;

    /*PIN FUNCTION INIT FOR PWM OUTPUT*/
    pwm_init(light_param.pwm_period,  pwm_duty_init ,PWM_CHANNEL,io_info);

    pwm_set_period(light_param.pwm_period);
    user_light_set_duty(20000, 0);
    pwm_start();
    return;

}

void KeyInitConfig(void)
{
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, FUNC_GPIO12);	// GPIO0��ΪIO��
	GPIO_DIS_OUTPUT(GPIO_ID_PIN(12));

	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_GPIO13);	// GPIO0��ΪIO��
	GPIO_DIS_OUTPUT(GPIO_ID_PIN(13));
}

int count=100;

//�����ⲿ�жϷ�����--��Ҫ��������
void KeyExtiInterruptFunction(void)
{
	static i = 1;
	uint32 gpio_status;
	uint32 gpio_int=0;
	//1.��ȡGPIO�ж�״̬
	gpio_status = GPIO_REG_READ(GPIO_STATUS_ADDRESS);
	//2.����ж�״̬λ
	GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS, gpio_status);

	gpio_int = GPIO_REG_READ(GPIO_STATUS_ADDRESS);

	if (gpio_int != 0) {
		os_printf("\r\ncheck��%d\r\n", gpio_int);
	}

	//3.�жϰ������ж�״̬
	if (gpio_status == 4096)
	{
		if (GPIO_INPUT_GET(GPIO_ID_PIN(13)) == 0) {
			count++;
			os_printf("\r\n��ת��%d\r\n", count);
		} else {
			count--;
			os_printf("\r\n��ת��%d\r\n",count);
		}
	}
}

void KeyExtiInitConfig(void)
{
	//1.�ر�GPIO�ж�
	ETS_GPIO_INTR_DISABLE();
	//2.ע���жϻص�����
	ETS_GPIO_INTR_ATTACH((ets_isr_t)KeyExtiInterruptFunction, NULL);
	//3.�����ⲿ�ж�IO���Լ�������ʽ
	gpio_pin_intr_state_set(GPIO_ID_PIN(12), GPIO_PIN_INTR_POSEDGE);	// GPIO_12�������ж�
	//4.��GPIO�ж�
	ETS_GPIO_INTR_ENABLE();
}
void user_init_switch()
{
	KeyInitConfig();//������ʼ������
	KeyExtiInitConfig();//���ð����ⲿ�ж�
}

//========================================================================================

// LED��ʼ��
//=============================================================================
void  LED_Init_JX(void)
{
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U,	FUNC_GPIO2);	// GPIO4��ΪIO��

	GPIO_OUTPUT_SET(GPIO_ID_PIN(2),1);						// IO4 = 1
}
//=============================================================================


// �����ʱ����ʼ��(ms����)
//========================================================================================
void  OS_Timer_TIMER_Init_JX(u32 time_ms, u8 time_repetitive)
{
	os_timer_disarm(&OS_Timer_TIME);	// �رն�ʱ��
	os_timer_setfn(&OS_Timer_TIME,(os_timer_func_t *)get_set_time, NULL);	// ���ö�ʱ��
	os_timer_arm(&OS_Timer_TIME, time_ms, time_repetitive);  // ʹ�ܶ�ʱ��
}
// �����ʱ����ʼ��(ms����)
//========================================================================================
void  OS_Timer_DISP_Init_JX(u32 time_ms, u8 time_repetitive)
{
	os_timer_disarm(&OS_Timer_DISP);	// �رն�ʱ��
	os_timer_setfn(&OS_Timer_DISP,(os_timer_func_t *)led_matrix, NULL);	// ���ö�ʱ��
	os_timer_arm(&OS_Timer_DISP, time_ms, time_repetitive);  // ʹ�ܶ�ʱ��
}

// user_init��entry of user application, init user function here
//=================================================================================================
void  user_init(void)
{
	SpiFlashOpResult enSpiFlashRslt;

	system_update_cpu_freq(80); //160M
	uart_init(115200,115200);	// ��ʼ�����ڲ�����
	os_delay_us(10000);			// �ȴ������ȶ�
	os_printf("\r\n===================444==============================\r\n");
	os_printf("\t Project:\t%s\r\n", ProjectName);
	os_printf("\t SDK version:\t%s", system_get_sdk_version());
	os_printf("\r\n=================================================\r\n");

	os_memset(&STA_INFO,0,sizeof(struct station_config));			// STA_INFO = 0
	enSpiFlashRslt = spi_flash_read(Sector_STA_INFO*4096,(uint32 *)&STA_INFO, 96);
	if(SPI_FLASH_RESULT_OK != enSpiFlashRslt)	// ������STA������(SSID/PASS)
	{
		os_printf("\r\nSTA_INFO.ssid=%d\r\n",enSpiFlashRslt);
	}
	os_memcpy(STA_INFO.ssid, "HUAWEI-LGF2BS", 14);
	os_memcpy(STA_INFO.password, "8246030990", 11);

	STA_INFO.ssid[31] = 0;		// SSID�����'\0'
	STA_INFO.password[63] = 0;	// APSS�����'\0'
	os_printf("\r\nSTA_INFO.ssid=%s\r\nSTA_INFO.password=%s\r\n",STA_INFO.ssid,STA_INFO.password);

	wifi_set_opmode(0x01);					// ����ΪSTAģʽ�������浽Flash
	os_printf("wifi_set_opmode\r\n");
	wifi_station_set_config(&STA_INFO);		// ����STA����
	os_printf("wifi_station_set_config\r\n");
//	wifi_station_connect();					// ESP8266����WIFI������˾��ʡ��
//������������������������������������������������������������������������������������������������

	OS_Timer_IP_Init_JX(1000,1);	// ��ʱ��ѯ8266����WIFI���

	OS_Timer_TIMER_Init_JX(1000, 1);// ��ʱ��ѯʱ��


	app_main();

	// ��ʱ���� 10msһ��
	os_printf("start display\r\n");
	OS_Timer_DISP_Init_JX(10, 1); // 10 ms��ʾ����
}
//=================================================================================================


/******************************************************************************
 * FunctionName : user_rf_cal_sector_set
 * Description  : SDK just reversed 4 sectors, used for rf init data and paramters.
 *                We add this function to force users to set rf cal sector, since
 *                we don't know which sector is free in user's application.
 *                sector map for last several sectors : ABCCC
 *                A : rf cal
 *                B : rf init data
 *                C : sdk parameters
 * Parameters   : none
 * Returns      : rf cal sector
*******************************************************************************/
uint32  user_rf_cal_sector_set(void)
{
    enum flash_size_map size_map = system_get_flash_size_map();
    uint32 rf_cal_sec = 0;

    switch (size_map) {
        case FLASH_SIZE_4M_MAP_256_256:
            rf_cal_sec = 128 - 5;
            break;

        case FLASH_SIZE_8M_MAP_512_512:
            rf_cal_sec = 256 - 5;
            break;

        case FLASH_SIZE_16M_MAP_512_512:
        case FLASH_SIZE_16M_MAP_1024_1024:
            rf_cal_sec = 512 - 5;
            break;

        case FLASH_SIZE_32M_MAP_512_512:
        case FLASH_SIZE_32M_MAP_1024_1024:
            rf_cal_sec = 1024 - 5;
            break;

        case FLASH_SIZE_64M_MAP_1024_1024:
            rf_cal_sec = 2048 - 5;
            break;
        case FLASH_SIZE_128M_MAP_1024_1024:
            rf_cal_sec = 4096 - 5;
            break;
        default:
            rf_cal_sec = 0;
            break;
    }

    return rf_cal_sec;
}

void  user_rf_pre_init(void){}

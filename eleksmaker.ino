// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
	Name:       eleksmaker.ino
	Created:	2021/3/29 14:23:10
	Author:     TD01\shihuafeng
*/

// Define User Types below here or use a .h file
//


// Define Function Prototypes that use User Types below here or use a .h file
//

#include <stdarg.h>
#include <TFT_eSPI.h>
#include <ESP32Time.h>
#include "OLED_Animation.h"
#include "OLED_Driver.h"
#include "OLED_GFX.h"
#include "OLED_FFT.h"
#include "OLED_UI.h"
#include "sysmain.h"
#include "motion.h"
#include "Spaceman.h"
#include "bmp.h"
#include "wryh_16x16.h"
#include "SolarAndLuner.h"
#include "network.h"
// Define Functions below here or use other .ino or cpp files
//
uint16_t Display_Mode = MODE_CHROME;
uint16_t Current_Mode = MODE_OFFLINE;

Mydate osolar;
Mydate lunar;
ESP32Time rtc;
OLED_GFX oled = OLED_GFX();
OLED_FFT fft = OLED_FFT();
OLED_Animation motion = OLED_Animation();
OLED_UI ui = OLED_UI();

DEVICE_CMD Device_Cmd = { 1,1,6,100,0xa,250,1,170,250,1,5,0xf };
DEVICE_MSG Device_Msg;
DEVICE_STR Device_Str;
DEVICE_STR Device_NStr;
DEVICE_STR Device_VStr;

char fpschar[50];
bool showfpsflag = true;
int fps = 0;

static uint8_t TimeTHEME = 0;

void MainSysRun()
{
	static int runcount = 0;

	if (Display_Mode == Current_Mode && TimeTHEME == Device_Cmd.commandtimetheme)
	{
		switch (Current_Mode)
		{
		case MODE_GAME:ui.SUIDataPrss(); break;
		case MODE_NORMAL:ui.NUIDataPrss(); break;
		case MODE_MUSIC:ui.MUIDataPrss(); break;
		case MODE_DATE:switch (TimeTHEME)
		{
		case 0:ui.TUIDataPrss(); break;
		case 1:ui.T1UIDataPrss(); break;
		case 2:ui.T2UIDataPrss(); break;
		default:Device_Cmd.commandtimetheme = 0; break;
		}break;
		case MODE_SHOW:ui.HUIDataPrss(); break;
		case MODE_CHROME:ui.GAMEUIDataPrss(); break;
		case MODE_OFFLINE:break;
			//			default:ui.SUIDataPrss();break;
		}

		return;
	}
	else
	{
		runcount++;
		if (runcount == 1)
		{
			switch (Current_Mode)
			{
			case MODE_GAME:ui.SUI_Out();; break;
			case MODE_NORMAL:ui.NUI_Out(); break;
			case MODE_MUSIC: ui.MUI_Out(); break;
			case MODE_DATE:switch (TimeTHEME)
			{
			case 0:ui.TUI_Out(); break;
			case 1:ui.T1UI_Out(); break;
			case 2:ui.T2UI_Out(); break;
			default:Device_Cmd.commandtimetheme = 0; break;
			}break;
			case MODE_SHOW:ui.HUI_Out(); break;
			case MODE_CHROME:ui.GAMEUI_Out(); break;
			case MODE_OFFLINE:break;
				//				default:ui.SUI_Out();break;
			}
		}
		else if (runcount > 60)
		{
			runcount = 0;
			Current_Mode = Display_Mode;
			TimeTHEME = Device_Cmd.commandtimetheme;
			switch (Current_Mode)
			{
			case MODE_GAME:ui.SUI_In();; break;
			case MODE_NORMAL:ui.NUI_In(); break;
			case MODE_MUSIC:ui.MUI_In(); break;
			case MODE_DATE:switch (TimeTHEME)
			{
			case 0:ui.TUI_In(); break;
			case 1:ui.T1UI_In(); break;
			case 2:ui.T2UI_In(); break;
			default:Device_Cmd.commandtimetheme = 0; break;
			}break;
			case MODE_SHOW:ui.HUI_In(); break;
			case MODE_CHROME:ui.GAMEUI_In(); break;
			case MODE_OFFLINE:break;
				//				default:ui.SUI_In();break;
			}
		}
	}
}
hw_timer_t* Timer10ms = NULL;
hw_timer_t* Timer500ms = NULL;

void IRAM_ATTR onTimer10ms()//定义中断函数：【中断应加载到IRAM中，且无返回值】
{
	MainSysRun();
	oled.Calc_Color();
	DampAutoPos(0);
}

void IRAM_ATTR onTimer500ms()//定义中断函数：【中断应加载到IRAM中，且无返回值】
{
	static int runcount = 0;
	oled.Set_Wheel(runcount++ % 96, 31);
	if (runcount % 2)
	{
		snprintf(fpschar, sizeof(fpschar), "%d", fps); fps = 0;
	}
	//	Serial.println(millis());
}


// The setup() function runs once each time the micro-controller starts
void setup()
{
	Serial.begin(115200);
	Serial.setTimeout(1);
	oled.Device_Init();
	motion.OLED_AllMotion_Init();
	rtc.setTime(30, 24, 15, 17, 1, 2021);  // 17th Jan 2021 15:24:30
//	initwifi();
	//Serial.println("Timeok");
	Timer10ms = timerBegin(0, 80, true);//备用知识：定时器的型号选用           预分频【主频：80MHz】                   定时器上下计数【true？】
	timerAttachInterrupt(Timer10ms, &onTimer10ms, true);//初始化完毕候，将定时器连接到中断：                定时器地址指针              中断处理函数                   中断边沿触发类型
	timerAlarmWrite(Timer10ms, 10000, true);//定时：         操作的定时器                  定时时长                数值是否重载【周期定时？】
	timerAlarmEnable(Timer10ms);//开始启动：            启动哪一个定时器？

	Timer500ms = timerBegin(1, 80, true);//备用知识：定时器的型号选用           预分频【主频：80MHz】                   定时器上下计数【true？】
	timerAttachInterrupt(Timer500ms, &onTimer500ms, true);//初始化完毕候，将定时器连接到中断：                定时器地址指针              中断处理函数                   中断边沿触发类型
	timerAlarmWrite(Timer500ms, 500000, true);//定时：         操作的定时器                  定时时长                数值是否重载【周期定时？】
	timerAlarmEnable(Timer500ms);//开始启动：            启动哪一个定时器？
	Serial.println("Initok");
	Serial.println("Refrash_Screen");
	oled.Refrash_Screen();
	Serial.println("Refrash_Screenok");
}
extern TFT_eSPI tft;

// Add the main program code into the continuous loop() function
void loop()
{
	char tempstr[20];
	static int runcount = 0;
	oled.Clear_Screen();
	motion.OLED_CustormMotion(Device_Cmd.commandmotion);
	//fps++;
	//if (showfpsflag)
	//	oled.OLED_SHFAny(0, 0, fpschar, 19, 0xffff);

	switch (Current_Mode)
	{
	case MODE_GAME:ui.SUIMainShow(); break;
	case MODE_NORMAL:ui.NUIMainShow(); break;
	case MODE_MUSIC:ui.MUIMainShow(); break;
	//case MODE_DATE:switch (TimeTHEME)
	//{
	//case 0:ui.TUIMainShow(); break;
	//case 1:ui.T1UIMainShow(); break;
	//case 2:ui.T2UIMainShow(); break;
	//default:Device_Cmd.commandtimetheme = 0; break;
	//	//				case 2:ui.T2UIMainShow();break;
	//}
	//			  break;
	case MODE_SHOW:ui.HUIMainShow(); break;
	//case MODE_CHROME:ui.GAMEUIMainShow(); break;
	case MODE_OFFLINE:break;
		//			default:ui.SUIMainShow();break;
	}
	//
	//oled.Display_hbmp(74, 60, 70, 70, Anim_Spaceman[runcount++ / 2 % 9], 0xffff);
	//
	//snprintf(tempstr,sizeof(tempstr),"%02d",rtc.getHour(true));
	//
	//oled.OLED_SHFAny(40, 10, tempstr, 30, 0xffff);
	//
	//oled.OLED_SHFAny(40 + 30 * 2, 10, ":", 30, 0xffff);
	//snprintf(tempstr, sizeof(tempstr), "%02d", rtc.getMinute());
	//oled.OLED_SHFAny(40 + 30 * 2 + 10, 10, tempstr, 30, 0xffff);
	//snprintf(tempstr, sizeof(tempstr), "%02d", rtc.getSecond());
	//oled.OLED_SHFAny(180, 30, tempstr, 18, 0xffff);

	//osolar.year = rtc.getYear();
	//osolar.month = rtc.getMonth()+1;
	//osolar.day = rtc.getDay();
	//lunar = toLunar(osolar);

	//showdateandweek(160,78, osolar.month, osolar.day, rtc.getDayofWeek(), lunar.month, lunar.day);
	Serial.println("Refrash_Screen");
	oled.Refrash_Screen();
	threadLoop();
}

void showdateandweek(int x,int y,int month,int day,int week,int nmonth,int nday)
{
	char tempstr[10];
	if (nmonth == 1)
		oled.Display_hbmp(5 + 0 + x, 0 + y, 16, 16, image_wryh_16x16[15], 0xffff);//正
	else if (nmonth == 11)
		oled.Display_hbmp(5 + 0 + x, 0 + y, 16, 16, image_wryh_16x16[16], 0xffff);//冬
	else if (nmonth == 1)
		oled.Display_hbmp(5 + 0 + x, 0 + y, 16, 16, image_wryh_16x16[17], 0xffff);//腊
	else
		oled.Display_hbmp(5+0 + x, 0 + y, 16, 16, image_wryh_16x16[month], 0xffff);
	oled.Display_hbmp(5+0 + 16 + x, 0 + y, 16, 16, image_wryh_16x16[12], 0xffff);
	if (nday <= 10)
	{
		oled.Display_hbmp(5+0 + 32 + x, 0 + y, 16, 16, image_wryh_16x16[13], 0xffff);//初
		oled.Display_hbmp(5+0 + 48 + x, 0 + y, 16, 16, image_wryh_16x16[nday], 0xffff);
	}
	else if (nday > 20&&nday<30)
	{
		oled.Display_hbmp(5 + 0 + 32 + x, 0 + y, 16, 16, image_wryh_16x16[14], 0xffff);//廿
		oled.Display_hbmp(5 + 0 + 48 + x, 0 + y, 16, 16, image_wryh_16x16[nday%10], 0xffff);
	}
	else if (nday == 20)
	{
		oled.Display_hbmp(5 + 0 + 32 + x, 0 + y, 16, 16, image_wryh_16x16[14], 0xffff);//廿
		oled.Display_hbmp(5 + 0 + 48 + x, 0 + y, 16, 16, image_wryh_16x16[10], 0xffff);//十
	}
	else if (nday == 30)
	{
		oled.Display_hbmp(5 + 0 + 32 + x, 0 + y, 16, 16, image_wryh_16x16[3], 0xffff);//三
		oled.Display_hbmp(5 + 0 + 48 + x, 0 + y, 16, 16, image_wryh_16x16[10], 0xffff);//十
	}
	else if (nday > 10&& nday < 20)
	{
		oled.Display_hbmp(5 + 0 + 32 + x, 0 + y, 16, 16, image_wryh_16x16[10], 0xffff);//十
		oled.Display_hbmp(5 + 0 + 48 + x, 0 + y, 16, 16, image_wryh_16x16[nday % 10], 0xffff);
	}

	oled.Display_hbmp(0 + 0 + x, 20 + y, 16, 16, image_wryh_16x16[11], 0xffff);//周
	oled.Display_hbmp(0 + 16 + x, 20 + y, 16, 16, image_wryh_16x16[week%7], 0xffff);

	sprintf(tempstr,"%d",month);
	oled.OLED_SHFAny(0 + 36 + x, 22 + y, tempstr, 10, 0xffff);
	oled.OLED_SHFAny(0 + 36 + 10 * (month < 10 ? 1 : 2) - 1 + x, 22 + y, ".", 10, 0xffff);
	sprintf(tempstr, "%d", day);
	oled.OLED_SHFAny(0 + 36 + 10 * (month < 10 ? 2 : 3) - 4 + x, 22 + y, tempstr, 10, 0xffff);

}

#define UART_DATA_BUF_LEN			1024	// 16KB
bool mIsOpen = true;
int mUartID;
// 用于拼接缓存数据，可能存在上一包数据解析未完全，残留有数据
byte mDataBufPtr[UART_DATA_BUF_LEN];
int mDataBufLen;
//#define DEBUG_PRO_DATA 
#define MAKEWORD(low, high)		(((byte)(low)) | (((byte)(high)) << 8))

#define LOBYTE(l)           ((BYTE)(l))

#define HIBYTE(l)           ((BYTE)(l >> 8))

#define TABLESIZE(table)    (sizeof(table)/sizeof(table[0]))

// 需要打印协议数据时，打开以下宏
//#define DEBUG_PRO_DATA

// 支持checksum校验，打开以下宏
//#define PRO_SUPPORT_CHECK_SUM


/* SynchFrame CmdID  DataLen Data CheckSum (可选) */
/*     2Byte  2Byte   1Byte	N Byte  1Byte */
// 有CheckSum情况下最小长度: 2 + 2 + 1 + 1 = 6
// 无CheckSum情况下最小长度: 2 + 2 + 1 = 5

#ifdef PRO_SUPPORT_CHECK_SUM
#define DATA_PACKAGE_MIN_LEN		6
#else
#define DATA_PACKAGE_MIN_LEN		5
#endif

// 同步帧头
#define CMD_HEAD1	0xFF
#define CMD_HEAD2	0x55

char Device_Name[20] = "EleksMaker\0";
byte ReponseID[40] = { 0xFF,0x55,'O','K' };
static void procParse(const byte* pData, uint len) {
	// CmdID
	uint i;
	static uint timeflag = 0;

	switch (MAKEWORD(pData[3], pData[2])) {

	case CPU_Temp:
		Device_Msg.cputemp = MAKEWORD(pData[6], pData[5]);
		break;
	case CPU_Clock:
		Device_Msg.cpuclock = MAKEWORD(pData[6], pData[5]);
		break;
	case CPU_Load:
		Device_Msg.cpuload = MAKEWORD(pData[6], pData[5]);
		break;
	case CPU_Fan:
		Device_Msg.cpufan = MAKEWORD(pData[6], pData[5]);
		break;
	case CPU_POWER:
		Device_Msg.cpupower = MAKEWORD(pData[6], pData[5]);
		break;

	case GPU_Temp:
		Device_Msg.gputemp = MAKEWORD(pData[6], pData[5]);
		break;
	case GPU_Clock:
		Device_Msg.gpuclock = MAKEWORD(pData[6], pData[5]);
		break;
	case GPU_Load:
		Device_Msg.gpuload = MAKEWORD(pData[6], pData[5]);
		break;
	case GPU_Fan:
		Device_Msg.gpufan = MAKEWORD(pData[6], pData[5]);
		break;


	case Main_Temp:
		Device_Msg.maintemp = MAKEWORD(pData[6], pData[5]);
		break;
	case Main_Fan:
		Device_Msg.mainfan = MAKEWORD(pData[6], pData[5]);
		break;
	case Main_Vol:
		Device_Msg.mainvoltage = MAKEWORD(pData[6], pData[5]);
		break;

	case RAM_Load:
		Device_Msg.ramload = MAKEWORD(pData[6], pData[5]);
		break;
	case RAM_Data:
		Device_Msg.ramusrdata = MAKEWORD(pData[6], pData[5]);
		break;

	case HDD_Load:
		Device_Msg.hddload = MAKEWORD(pData[6], pData[5]);
		break;
	case HDD_Temp:
		Device_Msg.hddtemp = MAKEWORD(pData[6], pData[5]);
		break;

	case Uart_Year:
		Device_Msg.uartyear = MAKEWORD(pData[6], pData[5]);
		break;
	case Uart_Month:
		Device_Msg.uartmonth = MAKEWORD(pData[6], pData[5]);
		break;
	case Uart_Day:
		Device_Msg.uartday = MAKEWORD(pData[6], pData[5]);
		break;
	case Uart_Week:
		Device_Msg.uartweek = MAKEWORD(pData[6], pData[5]);
		break;
	case Uart_Hour:
		Device_Msg.uarthour = MAKEWORD(pData[6], pData[5]);
		break;
	case Uart_Minute:
		Device_Msg.uartminute = MAKEWORD(pData[6], pData[5]);
		break;
	case Uart_Second:
		Device_Msg.uartsecond = MAKEWORD(pData[6], pData[5]);

		if (timeflag != Device_Msg.uarthour)
		{
			rtc.setTime(Device_Msg.uartsecond, Device_Msg.uartminute, Device_Msg.uarthour, Device_Msg.uartday, Device_Msg.uartmonth, Device_Msg.uartyear);  // 17th Jan 2021 15:24:30
			timeflag = Device_Msg.uarthour;
		}
		break;
	case End_Frame_ADDR:
		if (MAKEWORD(pData[6], pData[5]) == 0x5A5A) {}
		break;
	case Command_Mode:
		Device_Cmd.commandmode = MAKEWORD(pData[6], pData[5]);
		if (Device_Cmd.commandmode > 1 && Display_Mode != MODE_MENU)
		{
			Display_Mode = Device_Cmd.commandmode;
		}
		break;
	case Command_Motion:
		//					if(Device_Cmd.commandmotion != MAKEWORD(pData[6],pData[5]))
	{
		if (MAKEWORD(pData[6], pData[5]) & 8)
			Device_Cmd.commandmotion = 0;
		else if (MAKEWORD(pData[6], pData[5]) & 4)
			Device_Cmd.commandmotion = 1;
		else if (MAKEWORD(pData[6], pData[5]) & 2)
			Device_Cmd.commandmotion = 2;
		else if (MAKEWORD(pData[6], pData[5]) & 1)
			Device_Cmd.commandmotion = 3;
		else if (MAKEWORD(pData[6], pData[5]) & 0x20)
			Device_Cmd.commandmotion = 4;
		else if (MAKEWORD(pData[6], pData[5]) & 0x10)
			Device_Cmd.commandmotion = 5;
		else if (MAKEWORD(pData[6], pData[5]) & 1)
			Device_Cmd.commandmotion = 6;



	}break;
	case Command_Style:
		if (Device_Cmd.commandstyle != MAKEWORD(pData[6], pData[5]))
		{
			Device_Cmd.commandstyle = MAKEWORD(pData[6], pData[5]);
			//						
		}break;
	case Command_Speed:
		if (Device_Cmd.commandspeed != MAKEWORD(pData[6], pData[5]))
		{
			Device_Cmd.commandspeed = MAKEWORD(pData[6], pData[5]);
			//						
		}break;
	case Command_Brightness:
		if (Device_Cmd.commandbrightness != MAKEWORD(pData[6], pData[5]))
		{
			Device_Cmd.commandbrightness = MAKEWORD(pData[6], pData[5]);
			//						
		}break;
	case Command_Set:
		if (Device_Cmd.commandset != MAKEWORD(pData[6], pData[5]))
		{
			Device_Cmd.commandset = MAKEWORD(pData[6], pData[5]);

		}break;
	case Command_RGBMode:
		if (Device_Cmd.commandrgbmode != MAKEWORD(pData[6], pData[5]))
		{
			Device_Cmd.commandrgbmode = MAKEWORD(pData[6], pData[5]);

		}break;
	case Command_RGBBrightness:
		if (Device_Cmd.commandrgbbrightness != MAKEWORD(pData[6], pData[5]))
		{
			Device_Cmd.commandrgbbrightness = MAKEWORD(pData[6], pData[5]);

		}break;
	case Command_RGBColor:
		if (Device_Cmd.commandrgbcolor != MAKEWORD(pData[6], pData[5]))
		{
			Device_Cmd.commandrgbcolor = MAKEWORD(pData[6], pData[5]);

		}break;
	case Command_TOPTHEME:
		if (Device_Cmd.commandtoptheme != MAKEWORD(pData[6], pData[5]))
		{
			Device_Cmd.commandtoptheme = MAKEWORD(pData[6], pData[5]);
			if (Device_Cmd.commandtoptheme < 2)
				drache_printf("Current top %d\r\n", Device_Cmd.commandtoptheme);
			else
				drache_printf("Current top 1\r\n");

		}break;
	case Command_LOGOTHEME:
		if (Device_Cmd.commandlogotheme != MAKEWORD(pData[6], pData[5]))
		{
			Device_Cmd.commandlogotheme = MAKEWORD(pData[6], pData[5]);
			if (Device_Cmd.commandlogotheme < 6)
				drache_printf("Current logo %d\r\n", Device_Cmd.commandlogotheme);
			else
				drache_printf("Current logo 5\r\n");

		}break;
	case Command_GAMETYPE:
		if (Device_Cmd.commandgametype != MAKEWORD(pData[6], pData[5]))
		{
			Device_Cmd.commandgametype = MAKEWORD(pData[6], pData[5]);
			if (Device_Cmd.commandgametype < 8)
				drache_printf("Mode %d\r\n", Device_Cmd.commandgametype);
			else
			{
				Device_Cmd.commandgametype = 0xF;
				drache_printf("Mode Auto\r\n");
			}

		}break;
	case Command_DEVICENAME:
		memset(&Device_Name, 0, sizeof(Device_Name));

		for (i = 0; i < pData[4]; i++) Device_Name[i] = pData[i + 5];

		break;
	case 0x101:for (i = 0; i < pData[4]; i++) Device_Msg.cpuname[i] = pData[i + 5]; break;
	case 0x102:for (i = 0; i < pData[4]; i++) Device_Msg.gpuname[i] = pData[i + 5]; break;
	case 0x103:for (i = 0; i < pData[4]; i++) Device_Msg.mainname[i] = pData[i + 5]; break;
	case FFT_Data:for (i = 0; i < pData[4]; i++) Device_Msg.fft[i] = pData[i + 5];
		//				CptOnline = 3;
		break;
	case Left_Vol:
		Device_Msg.leftvol = MAKEWORD(pData[6], pData[5]); break;
	case Right_Vol:
		Device_Msg.rightvol = MAKEWORD(pData[6], pData[5]); break;
	case 0x3F3F:
		//				STMFLASH_Read(FLASH_NAME_ADDR,(uint16_t*)Device_Name,20);
		ReponseID[2] = (pData[5] & 0x5A) | (pData[6] & 0xA5);
		ReponseID[3] = (pData[5] ^ 0x57) | (pData[6] & 0x57);
		ReponseID[4] = strlen(Device_Name);
		for (i = 0; i < ReponseID[4]; i++)
			ReponseID[5 + i] = Device_Name[i];

		Serial.write(ReponseID, ReponseID[4] + 5);
		break;
	}
	//for (i = 0; i < len; i++)
	//	Serial.print(pData[i], HEX);
}
/**
 * 功能：解析协议
 * 参数：pData 协议数据，len 数据长度
 * 返回值：实际解析协议的长度
 */
int parseProtocol(byte* pData, uint len) {
	uint remainLen = len;	// 剩余数据长度
	uint dataLen;	// 数据包长度
	uint frameLen;	// 帧长度

	//Serial.println(remainLen);
	/**
	 * 以下部分需要根据协议格式进行相应的修改，解析出每一帧的数据
	 */
	while (remainLen >= DATA_PACKAGE_MIN_LEN) {
		// 找到一帧数据的数据头
		while ((remainLen >= 2) && ((pData[0] != CMD_HEAD1) || (pData[1] != CMD_HEAD2))) {
			pData++;
			remainLen--;
			/*Serial.println("找帧头");*/
			continue;
		}

		if (remainLen < DATA_PACKAGE_MIN_LEN) {
			/*Serial.println("数据太少");*/
			break;
		}

		dataLen = pData[4];
		frameLen = dataLen + DATA_PACKAGE_MIN_LEN;
		if (frameLen > remainLen) {
			/*	Serial.println("数据不全");*/
				// 数据内容不全
			break;
		}

		// 打印一帧数据，需要时在CommDef.h文件中打开DEBUG_PRO_DATA宏
#ifdef DEBUG_PRO_DATA
		for (uint i = 0; i < frameLen; ++i) {
			Serial.print(pData[i], HEX);
		}
#endif

		// 支持checksum校验，需要时在CommDef.h文件中打开PRO_SUPPORT_CHECK_SUM宏
#ifdef PRO_SUPPORT_CHECK_SUM
		// 检测校验码
		if (getCheckSum(pData, frameLen - 1) == pData[frameLen - 1]) {
			// 解析一帧数据
			procParse(pData, frameLen);
		}
		else {
			LOGE("CheckSum error!!!!!!\n");
		}
#else
		// 解析一帧数据
		procParse(pData, frameLen);
#endif

		pData += frameLen;
		remainLen -= frameLen;
	}

	return len - remainLen;
}


bool threadLoop() {
	if (mIsOpen) {
		// 可能上一次解析后有残留数据，需要拼接起来
//		int readNum = read(mUartID, mDataBufPtr + mDataBufLen, UART_DATA_BUF_LEN - mDataBufLen);

		int readNum = Serial.readBytes(mDataBufPtr + mDataBufLen, UART_DATA_BUF_LEN - mDataBufLen);

		if (readNum > 0) {

			mDataBufLen += readNum;
			// 解析协议
			int len = parseProtocol(mDataBufPtr, mDataBufLen);
			if ((len > 0) && (len < mDataBufLen)) {
				// 将未解析的数据移到头部
				memcpy(mDataBufPtr, mDataBufPtr + len, mDataBufLen - len);
			}

			mDataBufLen -= len;
		}
		else {
			/*	delay(1);*/
		}

		return true;
	}

	return false;
}

void drache_cmd(uint16_t addr, uint16_t data)
{
	unsigned char buf[7] = { 0xFF,0x55,0,0,0x02,0,0 };
	buf[2] = (addr >> 8) & 0xFF;
	buf[3] = addr & 0xFF;

	buf[5] = (data >> 8) & 0xFF;
	buf[6] = data & 0xFF;
	Serial.write(buf, 7);
}

int drache_printf(const char* pcFormat, ...)
{
	va_list args;
	int len;
	unsigned char buf[255 + 5] = { 0xFF,0x55,0xC0,0x01,0x00 };

	va_start(args, pcFormat);
	len = vsnprintf((char*)buf + 5, sizeof(buf), pcFormat, args);
	buf[4] = len;
	va_end(args);

	Serial.write(buf, len + 5);
	return len;
}


void drache_clear()
{
	unsigned char buf[] = { 0xFF,0x55,0xC0,0x02 };
	Serial.write(buf, 5);
}
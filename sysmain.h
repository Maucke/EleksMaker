/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#define HIGH 1
#define LOW 0

#define True		1		
#define False		0		
 
typedef struct{
	uint8_t autotimeset;
	char addr[7];
	uint8_t hour;
	uint8_t min;
	char hourc[3];
	char minc[3];
	uint16_t motionset;
	uint16_t rgbcolor;
	uint16_t rgbmode;
	char uid[20];
	uint8_t autoswdis;
	uint8_t autoswtime;
	char autoswtimec[3];
	uint8_t fanswdis;
}ConfigSet;
extern ConfigSet set;
	
#define Radius 60
#define RadiusC 56
#define RadiusB 53
#define HourRadius 30+2
#define MinRadius 40+2
#define SecRadius 50+2
#define RLV Radius/2
	
extern uint16_t Display_Mode;
extern uint16_t Current_Mode ;
#define MODE_DEFALUT      	0x00
#define MODE_OFFLINE    	  0x01
#define MODE_DATE    	  		0x02
#define MODE_MUSIC     			0x03
#define MODE_NORMAL   		  0x04
#define MODE_GAME  					0x05
#define MODE_SHOW		  		0x06
#define MODE_TIME		  		  0x07
#define MODE_BILI		  		  0x08
#define MODE_WEATH		  		  0x09
#define MODE_WEATH_1		  		  0x0A
#define MODE_WEATH_2		  		  0x0B
#define MODE_DATE_1    	  		0x0C
#define MODE_MENU    	  		0x0D
#define MODE_CHROME    	  		0x0E

#define CPU_Temp 						0x1
#define CPU_Clock 					0x2
#define CPU_Load 						0x3
#define CPU_Fan 						0x4

#define GPU_Temp 						0x11
#define GPU_Clock 					0x12
#define GPU_Load 						0x13
#define GPU_Fan 						0x14

#define Main_Temp 					0x21
#define Main_Fan 						0x22
#define Main_Vol						0x23

#define RAM_Load 	  				0x31
#define RAM_Data 						0x32

#define HDD_Load 	  				0x41
#define HDD_Temp 						0x42

#define Uart_Year 	 			 	0x201
#define Uart_Month 					0x202
#define Uart_Day 	  				0x203
#define Uart_Week 					0x204
#define Uart_Hour 	  			0x205
#define Uart_Minute 				0x206
#define Uart_Second 	  		0x207
#define CPU_POWER 	  			0x208

#define CPU_NAME 	 		 		0x101
#define GPU_NAME 	 		 		0x102
#define Main_NAME 	 		 	0x103
#define Uart_END	 	  		0x55AA

#define Command_Mode      0x8001
#define Command_Motion    0x8002
#define Command_Style     0x8003
#define Command_Speed     0x8004
#define Command_Brightness 0x8005
#define Command_Set       0x8006
#define Command_RGBMode   0x8007
#define Command_RGBColor  0x8008
#define Command_RGBBrightness 0x8009

#define Command_TOPTHEME 	0x800A
#define Command_LOGOTHEME 0x800B
#define Command_GAMETYPE 0x800C
#define Command_DEVICENAME 0x400A

#define End_Frame_ADDR 0x55AA

#define FFT_Data 0x0301
#define Left_Vol 0x0302
#define Right_Vol 0x0303

#define Uart_FFT_Length 192

typedef struct
{
	uint16_t cputemp;
	uint16_t cpuclock;
	uint16_t cpuload;
	uint16_t cpufan;
	uint16_t cpupower;

	uint16_t gputemp;
	uint16_t gpuclock;
	uint16_t gpuload;
	uint16_t gpufan;

	uint16_t maintemp;
	uint16_t mainfan;
	uint16_t mainvoltage;

	uint16_t ramload;
	uint16_t ramusrdata;

	uint16_t hddload;
	uint16_t hddtemp;

	uint16_t uartyear;
	uint16_t uartmonth;
	uint16_t uartday;
	uint16_t uartweek;
	uint16_t uarthour;
	uint16_t uartminute;
	uint16_t uartsecond;

	char cpuname[40];
	char gpuname[40];
	char mainname[40];
	uint8_t fft[Uart_FFT_Length];
	uint16_t leftvol;
	uint16_t rightvol;
}DEVICE_MSG;

typedef struct
{
	uint16_t commandmode;
	uint16_t commandmotion;
	uint16_t commandstyle;
	uint16_t commandspeed;
	uint16_t commandset;
	uint16_t commandbrightness;
	uint16_t commandrgbmode;
	uint16_t commandrgbcolor;
	uint16_t commandrgbbrightness;
	uint16_t commandtoptheme;
	uint16_t commandlogotheme;
	uint16_t commandgametype;
	uint16_t commandtimetheme;
}DEVICE_CMD;

typedef struct
{
	char cputemp[10];
	char cpuclock[10];
	char cpuload[10];
	char cpufan[10];

	char gputemp[10];
	char gpuclock[10];
	char gpuload[10];
	char gpufan[10];

	char maintemp[10];
	char mainfan[10];

	char ramload[10];
	char ramusrdata[10];


	//	char vtime[10];
	//	char vhour[10];
	//	char vmin[10];	
	//	char vsec[10];	
	//	char date[10];	

}DEVICE_STR;

extern DEVICE_STR Device_Str;
extern DEVICE_STR Device_NStr;
extern DEVICE_STR Device_VStr;
extern DEVICE_MSG Device_Msg;
extern DEVICE_CMD Device_Cmd;

typedef enum
{
 online,offline
}STA;
extern STA systemstatus;
extern uint16_t offlinecount;

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

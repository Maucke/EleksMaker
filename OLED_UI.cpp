#include "OLED_UI.h"
#include "OLED_FFT.h"
#include "stdlib.h"
#include "sysmain.h"
#include "math.h"
#include "image.h"
#include "string.h"
#include "motion.h"

#ifdef __cplusplus
extern "C" {
#endif


	OLED_UI::OLED_UI(void) {
	}
	//uint16_t randcolor[100];
	//uint8_t pointercolor=0;
	void OLED_UI::OLED_LFPixel(int x, int y, int w, int h, int psize, int pinterval, uint8_t Num, const unsigned char* ch, uint16_t color)
	{
		uint16_t i, j, k;
		uint16_t bnum = ((h + 7) / 8) * w;
		for (k = 0; k < (h + 7) / 8; k++)//8*k层
			for (j = 0; j < w; j++)//w
				for (i = 0; i < 8; i++)
					if ((ch[Num * bnum + w * k + j] >> i) & 1)
					{
						Fill_Rect(x + j * (psize + pinterval), y + i * (psize + pinterval) + k * 8 * (psize + pinterval), psize, psize, color);
					}
	}
	//	randcolor[(Num*bnum+w*k+j)*8+i]
	void OLED_UI::OLED_SLFAny(int x, int y, int psize, int pinterval, char* ch, int w, uint16_t color)
	{
		uint8_t c = 0, j = 0;
		while (ch[j] != '\0')
		{
			c = ch[j] - ' ';

			switch (w)
			{
			case 8:OLED_LFPixel(x, y, 8, 16, psize, pinterval, c, OCRB_F8x16, color); break;
			case 9:OLED_LFPixel(x, y, 9, 16, psize, pinterval, c, Self_F9x16, color); break;
			case 10:OLED_LFPixel(x, y, 10, 16, psize, pinterval, c, OCR_F10x16, color); break;
			case 12:OLED_LFPixel(x, y, 12, 16, psize, pinterval, c, OCR_F12x16, color); break;
				//			case 12:OLED_LFPixel(x,y,12,16,psize,pinterval,c,OCRB_F12x16,color);break;
			case 16:OLED_LFPixel(x, y, 16, 24, psize, pinterval, c, OCR_F16x24, color); break;
				//			case 16:OLED_LFPixel(x,y,16,psize,pinterval,24,c,OCRB_F16x24,color);break;
			default:OLED_LFPixel(x, y, 8, 16, psize, pinterval, c, OCRB_F8x16, color); break;
			}
			x += w * (psize + pinterval);
			j++;
		}
	}

	void OLED_UI::TUI_In() {
		int i;
		for (i = 40; i < 50; i++)
			SetCurrent(i, 0);
		SetTarget(40, 128);
		SetTarget(41, -128);
		SetTarget(42, rand() % 10 - 10);
	}
	void OLED_UI::TUI_Out() {
		int i;
		for (i = 40; i < 50; i++)
			SetTarget(i, 0);
	}
	void OLED_UI::TUIDataPrss() {
		//	static int oldmin;
		//	if(oldmin!=BCD2HEX(DS3231_US_Buf[2]))
		//	{
		//		oldmin=BCD2HEX(DS3231_US_Buf[2]);
		//		SetTarget(40,rand()%5-5+128);
		//		SetTarget(41,rand()%10-128);
		//		SetTarget(42,rand()%10-10);
		////		for(i=0;i<sizeof(randcolor);i++)
		////			randcolor[i]=RandomColor();
		//	}
	}
	OLED_STATUS OLED_UI::TUIMainShow() {
		//OLED_SLFAny(pit[40].current-128,-10+pit[42].current,4,2,ds3231.Hour,8,~color_now);
		//OLED_SLFAny(128+pit[41].current+74,55+pit[42].current,3,2,ds3231.Min,8,color_now);
		//return OLED_IDLE;
	}

	void OLED_UI::T1UI_In() {
		//int i;
		//for(i=10;i<30;i++)
		//	SetCurrent(i,0);
		//pit[RDHourColor].target = oled.WheelPw(rand()%96);
		//pit[RDMinColor].target = oled.WheelPw(rand()%96);
		//pit[RDSecColor].target = oled.WheelP(rand()%96);
		//SetCurrent(RDRadius, Radius*2);
		//SetCurrent(RDRadiusC, RadiusC*2);
		//SetCurrent(RDRadiusB, RadiusB*2);
		//SetTarget(RDRadius, Radius);
		//SetTarget(RDRadiusC, RadiusC);
		//SetTarget(RDRadiusB, RadiusB);
		//SetTarget(RDHourRadius, HourRadius);
		//SetTarget(RDMinRadius, MinRadius);
		//SetTarget(RDSecRadius, SecRadius);
		//SetTarget(RDRuleDelaut, 0);
		//if(BCD2HEX(DS3231_US_Buf[2])%12<6)
		//{
		//	SetTarget(PNTTIME,22+16);
		//	SetCurrent(PNTTIME, -60);
		//}
		//else
		//{
		//	SetTarget(PNTTIME,22+76);
		//	if(pit[PNTTIME].target!=22+76)
		//		SetCurrent(PNTTIME,160+50);
		//}
	}
	void OLED_UI::T1UI_Out() {
		int i;
		for (i = 10; i < 30; i++)
			SetTarget(i, 0);
		SetTarget(RDRadius, Radius * 2);
		SetTarget(RDRadiusC, RadiusC * 2);
		SetTarget(RDRadiusB, RadiusB * 2);
		SetTarget(RDRuleDelaut, 180);
		{
			SetTarget(RDHourRadius, 0);
			SetTarget(RDMinRadius, 0);
			SetTarget(RDSecRadius, 0);
			SetTarget(PNTHOUR, -90);
			SetTarget(PNTMIN, -90);
			SetTarget(PNTSEC, -90);
			if (pit[PNTTIME].current < 60)
			{
				SetTarget(PNTTIME, -50);
			}
			else
			{
				SetTarget(PNTTIME, 160 + 50);
			}
		}
	}
	void OLED_UI::T1UIDataPrss() {

		//pit[PNTHOUR].target = (BCD2HEX(DS3231_US_Buf[2])%12-3)*30+BCD2HEX(DS3231_US_Buf[1])/2;
		//pit[PNTMIN].target = (BCD2HEX(DS3231_US_Buf[1])-15)*6+BCD2HEX(DS3231_US_Buf[0])/2/5;
		//pit[PNTSEC].target = (BCD2HEX(DS3231_US_Buf[0])-15)*6;
		//if(pit[PNTHOUR].target == -90)
		//	pit[PNTHOUR].target = 270;
		//else if(pit[PNTHOUR].current == 270)
		//	pit[PNTHOUR].current = -90;
		//if(pit[PNTMIN].target == -90)
		//	pit[PNTMIN].target = 270;
		//else if(pit[PNTMIN].current == 270)
		//	pit[PNTMIN].current = -90;
		//if(pit[PNTSEC].target == -90)
		//	pit[PNTSEC].target = 270;
		//else if(pit[PNTSEC].current == 270)
		//{
		//	pit[RDHourColor].target = oled.WheelPw(rand()%96);
		//	pit[RDMinColor].target = oled.WheelPw(rand()%96);
		//	pit[RDSecColor].target = oled.WheelP(rand()%96);
		//	
		//	pit[PNTSEC].current = -90;
		//}

		//if(BCD2HEX(DS3231_US_Buf[2])%12<6)
		//{
		//	SetTarget(PNTTIME,22+16);
		//}
		//else
		//{
		//	SetTarget(PNTTIME,22+76);
		//}
	}
	OLED_STATUS OLED_UI::T1UIMainShow() {
		//	int i;
		//	for(i=0;i<60;i++)
		//	{
		//		if(i%5==0)
		//			oled.Draw_Line((OCX+(pit[RDRadius].current*cos((i*6+pit[RDRuleDelaut].current)*PI/180))),(OCY+(pit[RDRadius].current*sin((i*6+pit[RDRuleDelaut].current)*PI/180))),(OCX+(pit[RDRadiusB].current*cos((i*6+pit[RDRuleDelaut].current)*PI/180))),(OCY+(pit[RDRadiusB].current*sin((i*6+pit[RDRuleDelaut].current)*PI/180))),color_half);
		//		else
		//			oled.Draw_Line((OCX+(pit[RDRadius].current*cos((i*6+pit[RDRuleDelaut].current)*PI/180))),(OCY+(pit[RDRadius].current*sin((i*6+pit[RDRuleDelaut].current)*PI/180))),(OCX+(pit[RDRadiusC].current*cos((i*6+pit[RDRuleDelaut].current)*PI/180))),(OCY+(pit[RDRadiusC].current*sin((i*6+pit[RDRuleDelaut].current)*PI/180))),color_min);
		//	}
		//	oled.Draw_Circle(OCX,OCY,pit[RDRadius].current+2,color_half);
		//	oled.Draw_Circle(OCX,OCY,pit[RDRadius].current);
		//
		//	oled.OLED_SNF6x8(pit[PNTTIME].current,60,ds3231.Timens);
		//	
		//	oled.Draw_Line((OCX+(pit[RDHourRadius].current*cos(pit[PNTHOUR].current*PI/180))),(OCY+(pit[RDHourRadius].current*sin(pit[PNTHOUR].current*PI/180))),OCX,OCY,2,pit[RDHourColor].target);
		//	oled.Draw_Line((OCX+(pit[RDMinRadius].current*cos(pit[PNTMIN].current*PI/180))),(OCY+(pit[RDMinRadius].current*sin(pit[PNTMIN].current*PI/180))),OCX,OCY,pit[RDMinColor].target);
		//	oled.Draw_Line((OCX+(pit[RDSecRadius].current*cos(pit[PNTSEC].current*PI/180))),(OCY+(pit[RDSecRadius].current*sin(pit[PNTSEC].current*PI/180))),OCX,OCY,pit[RDSecColor].target);
		////	oled.Draw_Line((OCX+(pit[RDSecRadius].current/5*cos((pit[PNTSEC].current+180)*PI/180))),(OCY+(pit[RDSecRadius].current/5*sin((pit[PNTSEC].current+180)*PI/180))),OCX,OCY,pit[RDSecColor].target);
		//
		//	if(pit[RDHourRadius].current>5)
		//	{
		//		oled.Fill_Circle(OCX,OCY,3,0);
		//		oled.Draw_Circle(OCX,OCY,1);
		//		oled.Draw_Circle(OCX,OCY,3,color_half);
		//	}
		//	return OLED_IDLE;
	}


	void OLED_UI::T2UI_In() {
		//int i;
		//for(i=10;i<30;i++)
		//	SetCurrent(i,0);
		//pit[RDHourColor].target = oled.WheelPw(rand()%96);
		//pit[RDMinColor].target = oled.WheelPw(rand()%96);
		//pit[RDSecColor].target = oled.WheelP(rand()%96);
		//SetCurrent(RDRadiusA, Radius);
		//SetTarget(RDRadiusA, Radius/2);
		//SetTarget(RDHourRadius, HourRadius);
		//SetTarget(RDMinRadius, MinRadius);
		//SetTarget(RDSecRadius, SecRadius);
		//if(BCD2HEX(DS3231_US_Buf[2])%12<6)
		//{
		//	SetTarget(PNTTIME,22);
		//	SetCurrent(PNTTIME, -60);
		//}
		//else
		//{
		//	SetTarget(PNTTIME,22+76);
		//	if(pit[PNTTIME].target!=22+76)
		//		SetCurrent(PNTTIME,160+50);
		//}
	}
	void OLED_UI::T2UI_Out() {
		//	int i;
		//	for(i=10;i<30;i++)
		//		SetTarget(i,0);
		//	SetTarget(RDRadiusA, Radius);
		////	if(Display_Mode != MODE_DATE)
		//	{
		//		SetTarget(RDHourRadius, 0);
		//		SetTarget(RDMinRadius, 0);
		//		SetTarget(RDSecRadius, 0);
		//		SetTarget(PNTHOUR,-90);
		//		SetTarget(PNTMIN,-90);
		//		SetTarget(PNTSEC,-90);
		//		if(pit[PNTTIME].current<60)
		//		{
		//			SetTarget(PNTTIME,-50);
		//		}
		//		else
		//		{
		//			SetTarget(PNTTIME,160+50);
		//		}
		//	}
	}
	void OLED_UI::T2UIDataPrss() {

		//pit[PNTHOUR].target = (BCD2HEX(DS3231_US_Buf[2])%12-3)*30+BCD2HEX(DS3231_US_Buf[1])/2;
		//pit[PNTMIN].target = (BCD2HEX(DS3231_US_Buf[1])-15)*6+BCD2HEX(DS3231_US_Buf[0])/2/5;
		//pit[PNTSEC].target = (BCD2HEX(DS3231_US_Buf[0])-15)*6;
		//if(pit[PNTHOUR].target == -90)
		//	pit[PNTHOUR].target = 270;
		//else if(pit[PNTHOUR].current == 270)
		//	pit[PNTHOUR].current = -90;
		//if(pit[PNTMIN].target == -90)
		//	pit[PNTMIN].target = 270;
		//else if(pit[PNTMIN].current == 270)
		//	pit[PNTMIN].current = -90;
		//if(pit[PNTSEC].target == -90)
		//	pit[PNTSEC].target = 270;
		//else if(pit[PNTSEC].current == 270)
		//{
		//	pit[RDHourColor].target = oled.WheelPw(rand()%96);
		//	pit[RDMinColor].target = oled.WheelPw(rand()%96);
		//	pit[RDSecColor].target = oled.WheelP(rand()%96);
		//	
		//	pit[PNTSEC].current = -90;
		//}

		//if(BCD2HEX(DS3231_US_Buf[2])%12<6)
		//{
		//	SetTarget(PNTTIME,22);
		//}
		//else
		//{
		//	SetTarget(PNTTIME,22+76);
		//}
	}
	OLED_STATUS OLED_UI::T2UIMainShow() {
		//	oled.Draw_Circle(OCX+RLV+14,OCY+RLV,pit[RDRadiusA].current,1,color_now);
		//	oled.Draw_Circle(OCX+RLV+14,OCY+RLV,pit[RDRadiusA].current+2,1,color_half); //右下
		//	
		//	oled.Draw_Circle(OCX-RLV-14,OCY+RLV,pit[RDRadiusA].current,2,color_now);
		//	oled.Draw_Circle(OCX-RLV-14,OCY+RLV,(pit[RDRadiusA].current+2),2,color_half);	//左下
		//	
		//	oled.Draw_Circle(OCX-RLV-14,OCY-RLV,pit[RDRadiusA].current,4,color_now);
		//	oled.Draw_Circle(OCX-RLV-14,OCY-RLV,(pit[RDRadiusA].current+2),4,color_half); //左上
		//	
		//	oled.Draw_Circle(OCX+RLV+14,OCY-RLV,pit[RDRadiusA].current,3,color_now);
		//	oled.Draw_Circle(OCX+RLV+14,OCY-RLV,(pit[RDRadiusA].current+2),3,color_half); //右上
		//	
		//	oled.Draw_Line(OCX+RLV+14+pit[RDRadiusA].current,OCY+RLV,OCX+RLV+pit[RDRadiusA].current+14,OCY-RLV,color_now);//右侧引导线
		//	oled.Draw_Line(OCX+RLV+14+(pit[RDRadiusA].current+2),OCY+RLV,OCX+RLV+(pit[RDRadiusA].current+2)+14,OCY-RLV,color_half);//右侧引导线
		//	
		//	oled.Draw_Line(OCX-RLV-14-pit[RDRadiusA].current,OCY+RLV,OCX-RLV-pit[RDRadiusA].current-14,OCY-RLV,color_now);//左侧引导线
		//	oled.Draw_Line(OCX-RLV-14-(pit[RDRadiusA].current+2),OCY+RLV,OCX-RLV-(pit[RDRadiusA].current+2)-14,OCY-RLV,color_half);//左侧引导线
		//
		//	oled.OLED_SNF6x8(pit[PNTTIME].current,60,ds3231.Timens);
		//	oled.Draw_Line(pit[PNTTIME].current-1,60+9,pit[PNTTIME].current+30,60+9,color_half);
		//	
		//	oled.Draw_Line((OCX+(pit[RDHourRadius].current*cos(pit[PNTHOUR].current*PI/180))),(OCY+(pit[RDHourRadius].current*sin(pit[PNTHOUR].current*PI/180))),OCX,OCY,2,pit[RDHourColor].target);
		//	oled.Draw_Line((OCX+(pit[RDMinRadius].current*cos(pit[PNTMIN].current*PI/180))),(OCY+(pit[RDMinRadius].current*sin(pit[PNTMIN].current*PI/180))),OCX,OCY,pit[RDMinColor].target);
		//	oled.Draw_Line((OCX+(pit[RDSecRadius].current*cos(pit[PNTSEC].current*PI/180))),(OCY+(pit[RDSecRadius].current*sin(pit[PNTSEC].current*PI/180))),OCX,OCY,pit[RDSecColor].target);
		////	oled.Draw_Line((OCX+(pit[RDSecRadius].current/5*cos((pit[PNTSEC].current+180)*PI/180))),(OCY+(pit[RDSecRadius].current/5*sin((pit[PNTSEC].current+180)*PI/180))),OCX,OCY,pit[RDSecColor].target);
		//
		//	if(pit[RDHourRadius].current>5)
		//	{
		//		oled.Fill_Circle(OCX,OCY,3,0);
		//		oled.Draw_Circle(OCX,OCY,1);
		//		oled.Draw_Circle(OCX,OCY,3,color_half);
		//	}
		//	return OLED_IDLE;
	}



	void ClearFFT(void)
	{
		int i;
		for (i = 0; i < Uart_FFT_Length; i++)
			Device_Msg.fft[i] = 0;

		Device_Msg.leftvol = 0;
		Device_Msg.rightvol = 0;
	}

	extern OLED_FFT fft;
	void OLED_UI::MUI_In() {

		ClearFFT();
	}
	void OLED_UI::MUI_Out() {
		ClearFFT();
	}

	void OLED_UI::MUIDataPrss() {

	}

	OLED_STATUS OLED_UI::MUIMainShow() {
		static uint8_t OTheme = 0;
		int i;
		if (OTheme != Device_Cmd.commandstyle)
		{
			OTheme = Device_Cmd.commandstyle;

			for (i = 0; i < 250; i++)
			{
				ClearFFT();
				fall_pot[i] = 160;
				flow_pot[i] = 160;
			}
		}
		switch (Device_Cmd.commandstyle)
		{
		case 1:fft.Display_Style1(); break;
		case 2:fft.Display_Style2(); break;
		case 3:fft.Display_Style3(); break;
		case 4:fft.Display_Style4(); break;
		case 5:fft.Display_Style5(); break;
		case 6:fft.Display_Style6(); break;
		default:fft.Display_Style1(); break;
		}
		return OLED_IDLE;
	}
	void OLED_UI::HUI_In() {
		int i;
		for (i = 50; i < 60; i++)
			SetCurrent(i, 0);
		SetTarget(50, 160 + 16);
	}
	void OLED_UI::HUI_Out() {
		int i;
		for (i = 50; i < 60; i++)
			SetTarget(i, 0);
	}
	void OLED_UI::HUIDataPrss() {
	}
	OLED_STATUS OLED_UI::HUIMainShow() {

		oled.Display_bmp(0 - 160 + pit[50].current, 0, 128, 128, Logo_amd);

		return OLED_IDLE;
	}


	void OLED_UI::SUI_In() {
		int i;
		for (i = 60; i < 70; i++)
			SetCurrent(i, 0);
		SetTarget(SSLF, 8);
		SetTarget(SSRT, 66);
		SetTarget(SSMLF, 8);
		SetTarget(SSMRT, 98);
		SetTarget(SSLLF, 40);
		SetTarget(SSLRT, 88);
		SetTarget(SSUP, 0);
		SetTarget(SSDN, 112 - 7);
		SetTarget(SSRD, 5);

		SetCurrent(SSLF, 8 - 80);
		SetCurrent(SSRT, 66 + 80);
		SetCurrent(SSMLF, 8 - 120);
		SetCurrent(SSMRT, 98 + 120);
		SetCurrent(SSLLF, 40 - 20);
		SetCurrent(SSLRT, 88 + 20);
		SetCurrent(SSUP, 0 - 20);
		SetCurrent(SSDN, 112 - 7 + 40);
		SetCurrent(SSRD, 5 - 5);
	}
	void OLED_UI::SUI_Out() {
		int i;
		for (i = 60; i < 70; i++)
			SetTarget(i, 0);
		SetTarget(SSLF, 8 - 80);
		SetTarget(SSRT, 66 + 80);
		SetTarget(SSMLF, 8 - 88);
		SetTarget(SSMRT, 98 + 88);
		SetTarget(SSLLF, 40 - 20);
		SetTarget(SSLRT, 88 + 20);
		SetTarget(SSUP, 0 - 20);
		SetTarget(SSDN, 112 - 7 + 40);
		SetTarget(SSRD, 5 - 5);
	}
	void OLED_UI::SUIDataPrss() {

	}

#define DT 16
	extern OLED_Animation motion;
	OLED_STATUS OLED_UI::SUIMainShow() {
		static int i, roun = 0;
		static char tempstr[100];
		roun++;
		oled.Display_bbmp(DT + 21, 46, 86, 43, GeForce_B_Back, color_min);
		oled.Display_bbmp(DT + 6 + 5, 105, 23, 13, shadowleft, color_min);
		oled.Display_bbmp(DT + 99 - 5, 105, 23, 13, shadowright, color_min);

		motion.OLED_CustormMotion(Device_Cmd.commandmotion);
		oled.Display_hbmp(DT + pit[SSLF].current, 22, 54, 9, userleft, color_now);
		oled.Display_hbmp(DT + pit[SSRT].current, 22, 54, 9, userright, color_now);
		oled.Display_hbmp(DT + 10, pit[SSDN].current, 108, 21, userbottom, color_now);


		oled.Display_hbmp(DT + 35, pit[SSDN].current + 3, 58, 3, usermgndbar, 0xFFFF);
		oled.Display_hbmp(DT + pit[SSMLF].current, 47, 21, 37, usermleft, color_half);
		oled.Display_hbmp(DT + pit[SSMRT].current, 47, 21, 37, usermright, color_half);
		for (i = 0; i < 9; i++)
			oled.Draw_Pixel(DT + 9 + 28 + 4 + 8 + i * 5, pit[SSUP].current + 8, color_min);

		oled.Draw_Line(DT + 0, 0, DT + pit[SSRD].current, pit[SSRD].current, color_now);
		oled.Draw_Line(DT + 127, 0, DT + 127 - pit[SSRD].current, pit[SSRD].current, color_now);
		oled.Draw_Line(DT + pit[SSRD].current, 127 - pit[SSRD].current, DT + 0, 127, color_now);
		oled.Draw_Line(DT + 127 - pit[SSRD].current, 127 - pit[SSRD].current, DT + 127, 127, color_now);

		oled.Display_hbmp(DT + 9 - 5 + pit[SSRD].current, pit[SSRD].current, 28, 10, GeForce_LOAD, color_now);
		oled.Display_hbmp(DT + 101 + 5 - pit[SSRD].current, pit[SSRD].current, 21, 10, GeForce_SYS, color_now);
		oled.Display_hbmp(DT + 27 + 1, 33, 74, 10, GeForce_TEMP, color_now);
		oled.Display_hbmp(DT + 48, 88, 33, 13, GeForce_CENT, color_now);
		oled.Draw_Line(DT + 20, 96 - 2, DT + pit[SSLLF].current, 96 - 2, 0xFFFF);
		oled.Draw_Line(DT + pit[SSLRT].current, 96 - 2, DT + 108, 96 - 2, 0xFFFF);
		oled.Draw_Line(DT + 27, 33 + 10, DT + 27 + 73, 33 + 10, color_min);
		sprintf(tempstr, "%02d", Device_Msg.cputemp / 10);
		oled.OLED_SBFAny(DT + 38, 48, tempstr, 25, 0xFFFF);
		sprintf(tempstr, "%03d", Device_Msg.cpuload / 10);
		oled.OLED_SBFAny(DT + 29 - 8 + pit[SSLF].current, 15, tempstr, 10, 0xFFFF);
		sprintf(tempstr, "%03d", Device_Msg.gputemp / 10);
		oled.OLED_SBFAny(DT + 69 + 1 + 8 - pit[SSLF].current, 15, tempstr, 10, 0xFFFF);
		return OLED_IDLE;
	}



	void OLED_UI::NUI_In() {
		int i;
		for (i = 75; i < 85; i++)
			SetCurrent(i, 0);
		SetCurrent(POSNBAR, 148);
		SetCurrent(POSNBAT, 170);
		SetCurrent(POSNRCD, 4);
		SetTarget(POSNRCT, 25);
		SetTarget(POSNTOP, 0);
		SetTarget(POSNBAR, 103);
		SetTarget(POSNBAT, 115);
		SetTarget(DAMPTYP, 0);
	}
	void OLED_UI::NUI_Out() {
		int i;
		for (i = 75; i < 85; i++)
			SetTarget(i, 0);
		SetTarget(POSNRCT, -73);
		SetTarget(POSNTOP, 60);
		SetTarget(POSNBAR, 148);
		SetTarget(POSNBAT, 170);
		SetTarget(DAMPTYP, 0);
	}

	uint8_t DataDisType = 0;
	uint8_t UnitDisType = 0;
	uint8_t HWDisType = 0;
	uint8_t Show_Float = False;
	char DataDis[20];
	char DataDisf[3];

	void OLED_UI::NUIDataPrss() {
		switch (DataDisType)
		{
		case 3:
			if (Device_Msg.cpufan > 0)
			{

				SetCurrent(POSNRCD, 0 + 8);
				SetTarget(POSNRCD, 0 + 8);
				SetTarget(CRTVANE, Device_Msg.cpufan);
				HWDisType = CU_CPU;
				Show_Float = False;
				sprintf(DataDis, "%04d", (uint16_t)pit[CRTVANE].target);
				UnitDisType = UT_RPM;
				pit[CRTVADS].target = pit[CRTVANE].target / 50 / 80 * 118;

				if (pit[CRTVADS].target >= 117)
					pit[CRTVADS].target = 117;
			}
			else if (Current_Mode != MODE_GAME)
			{
				DataDisType++; return;
				//				sprintf(DataDis,"----");
				//				UnitDisType=UT_RPM;
				//				pit[CRTVANE].target = 0;
			}
			break;
		case 0:
			if (Device_Msg.cputemp > 0)
			{
				SetTarget(POSNRCD, 11 + 8);
				pit[CRTVANE].target = Device_Msg.cputemp / 10;
				HWDisType = CU_CPU;
				Show_Float = True;
				sprintf(DataDis, "%02d", (uint16_t)pit[CRTVANE].target);
				sprintf(DataDisf, "%01d", Device_Msg.cputemp % 10);
				UnitDisType = UT_DEG;

				pit[CRTVADS].target = pit[CRTVANE].target / 80 * 118;

				if (pit[CRTVADS].target >= 117)
					pit[CRTVADS].target = 117;

			}
			else if (Current_Mode != MODE_GAME)
			{
				DataDisType++; return;
			}
			break;
		case 1:
			if (Device_Msg.cpuclock > 0)
			{
				SetCurrent(POSNRCD, 0 + 8);
				SetTarget(POSNRCD, 0 + 8);
				pit[CRTVANE].target = Device_Msg.cpuclock;
				HWDisType = CU_CPU;
				Show_Float = False;
				sprintf(DataDis, "%04d", (uint16_t)pit[CRTVANE].target);
				UnitDisType = UT_MHZ;
				pit[CRTVADS].target = pit[CRTVANE].target / 50 / 80 * 118;

				if (pit[CRTVADS].target >= 117)
					pit[CRTVADS].target = 117;
			}
			else if (Current_Mode != MODE_GAME)
			{
				DataDisType++; return;
				//				sprintf(DataDis,"----");
				//				UnitDisType=UT_MHZ;
				//				pit[CRTVANE].target = 0;
			}
			break;
		case 2:
			SetTarget(POSNRCD, 11 + 8);
			pit[CRTVANE].target = Device_Msg.cpuload / 10;
			HWDisType = CU_CPU;
			Show_Float = True;
			//			if(Device_Msg.cpuload>0)
			{
				sprintf(DataDis, "%02d", (uint16_t)pit[CRTVANE].target);
				sprintf(DataDisf, "%01d", Device_Msg.cpuload % 10);
				UnitDisType = UT_PREC;
				pit[CRTVADS].target = pit[CRTVANE].target / 80 * 118;

				if (pit[CRTVADS].target >= 117)
					pit[CRTVADS].target = 117;

			}break;
		case 7:
			if (Device_Msg.gpufan > 0)
			{
				SetCurrent(POSNRCD, 0 + 8);
				SetTarget(POSNRCD, 0 + 8);
				pit[CRTVANE].target = Device_Msg.gpufan;
				HWDisType = CU_GPU;
				Show_Float = False;
				sprintf(DataDis, "%04d", (uint16_t)pit[CRTVANE].target);
				UnitDisType = UT_RPM;
				pit[CRTVADS].target = pit[CRTVANE].target / 50 / 80 * 118;
				if (pit[CRTVADS].target >= 117)
					pit[CRTVADS].target = 117;

			}
			else if (Current_Mode != MODE_GAME)
			{
				DataDisType++; return;
				//				sprintf(DataDis,"----");
				//				UnitDisType=UT_RPM;
				//				pit[CRTVANE].target = 0;
			}
			break;
		case 4:
			if (Device_Msg.gputemp > 0)
			{
				SetTarget(POSNRCD, 11 + 8);
				pit[CRTVANE].target = Device_Msg.gputemp / 10;
				HWDisType = CU_GPU;
				Show_Float = True;
				sprintf(DataDis, "%02d", (uint16_t)pit[CRTVANE].target);
				sprintf(DataDisf, "%01d", Device_Msg.gputemp % 10);
				UnitDisType = UT_DEG;
				pit[CRTVADS].target = pit[CRTVANE].target / 80 * 118;

				if (pit[CRTVADS].target >= 117)
					pit[CRTVADS].target = 117;
			}
			else if (Current_Mode != MODE_GAME)
			{
				DataDisType++; return;
			}
			break;
		case 5:
			if (Device_Msg.gpuclock > 0)
			{
				SetCurrent(POSNRCD, 0 + 8);
				SetTarget(POSNRCD, 0 + 8);
				pit[CRTVANE].target = Device_Msg.gpuclock;
				HWDisType = CU_GPU;
				Show_Float = False;
				sprintf(DataDis, "%04d", (uint16_t)pit[CRTVANE].target);
				UnitDisType = UT_MHZ;
				pit[CRTVADS].target = pit[CRTVANE].target / 50 / 80 * 118;

				if (pit[CRTVADS].target >= 117)
					pit[CRTVADS].target = 117;
			}
			else if (Current_Mode != MODE_GAME)
			{
				DataDisType++; return;
				//				sprintf(DataDis,"----");
				//				UnitDisType=UT_MHZ;
				//				pit[CRTVANE].target = 0;
			}
			break;
		case 6:
			SetTarget(POSNRCD, 11 + 8);
			pit[CRTVANE].target = Device_Msg.gpuload / 10;
			HWDisType = CU_GPU;
			Show_Float = True;
			//			if(Device_Msg.gpuload>0)
			{
				sprintf(DataDis, "%02d", (uint16_t)pit[CRTVANE].target);
				sprintf(DataDisf, "%01d", Device_Msg.gpuload % 10);
				UnitDisType = UT_PREC;

				pit[CRTVADS].target = pit[CRTVANE].target / 80 * 118;

				if (pit[CRTVADS].target >= 117)
					pit[CRTVADS].target = 117;

			}break;
		case 8:
			SetTarget(POSNRCD, 11 + 8);
			pit[CRTVANE].target = Device_Msg.ramload / 10;
			HWDisType = CU_RAM;
			Show_Float = True;
			//			if(Device_Msg.gpuload>0)
			{
				sprintf(DataDis, "%02d", (uint16_t)pit[CRTVANE].target);
				sprintf(DataDisf, "%01d", Device_Msg.ramload % 10);
				UnitDisType = UT_PREC;
				pit[CRTVADS].target = pit[CRTVANE].target / 80 * 118;

				if (pit[CRTVADS].target >= 117)
					pit[CRTVADS].target = 117;

			}break;
		}
	}
	OLED_STATUS OLED_UI::NUIMainShow() {
		if (Device_Cmd.commandtoptheme <= 6)
		{
			oled.Display_bmp(pit[POSNTOP].current, pit[POSNRCT].current - 25, 128, 25, Corn_Top[Device_Cmd.commandtoptheme]);
		}
		else
		{
			oled.Display_bmp(pit[POSNTOP].current, pit[POSNRCT].current - 25, 128, 25, Corn_Top[5]);
		}

		oled.Display_bbmp(0, pit[POSNRCT].current, 128, 73, BMP_DataBackGround);
		oled.Display_bbmp(89, pit[POSNRCT].current + 69, 35, 5, Corn_BarUnit[UnitDisType], color_half);
		oled.OLED_SBFAny(pit[POSNRCD].current, 11 + pit[POSNRCT].current, DataDis, 22, color_now);
		if (pit[DAMPTYP].match)
			oled.Display_bbmp(10, pit[POSNRCT].current + 62, 23, 7, Corn_DataType[HWDisType], color_half);
		else
			oled.Display_bbmp(10, pit[POSNRCT].current + 62, 23, 7, Corn_DataType[HWDisType]);
		oled.Display_bbmp(98, 11 + pit[POSNRCT].current, 24, 24, Corn_Unit[UnitDisType], color_half);
		if ((Show_Float) && pit[CRTVANE].target < 100)
		{
			oled.OLED_SBFAny(pit[POSNRCD].current + 52, pit[POSNRCT].current + 27, DataDisf, 13, color_half);
			oled.Fill_Rect(pit[POSNRCD].current + 46, pit[POSNRCT].current + 45, 2, 4, color_half);
		}
		oled.Display_bbmp(0, pit[POSNBAT].current, 128, 5, Corn_Rule);
		oled.Display_bbmp(0, pit[POSNBAT].current + 5, 128, 5, Corn_RuleIndex, color_half);
		oled.Fill_Rect(3 + 2, pit[POSNBAR].current + 2, pit[CRTVADS].current, 6, color_half);
		oled.Draw_Rect(3, pit[POSNBAR].current, 121, 10);
		return OLED_IDLE;
	}


	void begin();
	void OLED_UI::GAMEUI_In() {
		int i;
		begin();
		for (i = 70; i < 75; i++)
			SetCurrent(i, 0);
		SetTarget(70, 30);
		SetTarget(71, -20);
	}
	void OLED_UI::GAMEUI_Out() {
		int i;
		for (i = 70; i < 75; i++)
			SetTarget(i, 0);
	}
	void OLED_UI::GAMEUIDataPrss() {
	}

	//typedef enum 
	//{
	//	ready=0,playing,gameover,loading,pause
	//}GAMESTS;

#define ready 0
#define playing 1
#define gameover 2
#define loading 3
#define pause 4

	typedef struct
	{
		uint8_t is_jump;
		uint8_t is_jumpfinish;
		uint8_t is_fire;
	}PLAYSTS;

	int gamestatus = loading;


	PLAYSTS status = { False,False,True };
	void blue_click() {
		if (status.is_jumpfinish)
		{
			status.is_jump = True;
			status.is_jumpfinish = False;
		}
	}

	typedef struct
	{
		float x; float y;
	}POS;
	POS obj;
	POS player;

	double gametime = 0;
	double distance = 0;
	unsigned int highdistance = 0;

	void begin() {
		gamestatus = loading;
		gametime = 0;
		distance = 0;
		status.is_jump = False;
		status.is_fire = False;
		status.is_jumpfinish = True;

		obj.x = 160;
		obj.y = 44;
		player.y = 43;
	}
	void fire() {

	}
	void red_click() {
		//start game
		if (gamestatus == ready) {
			begin();
			gamestatus = playing;
		}
		//fire
		else if (gamestatus == playing) {
			fire(); gamestatus = pause;
		}
		else if (gamestatus == pause) {
			gamestatus = playing;
		}
		//restart game
		else if (gamestatus == gameover) {
			begin();
			gamestatus = playing;
		}
	}



	void Display_pbmp(int x, int y, int w, int h, const uint8_t* ch) {
		int i, j;
		for (j = 0; j < h; j++) {
			for (i = 0; i < w; i++) {
				if (j * w + i >= 0)
					if (ch[j * w + i])
						oled.Draw_Pixel(i + x, j + y);
			}
		}
	}

	unsigned char imageplayer[] = {
		0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,
		0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1,
		0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,
		0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,
		0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,
		0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,
		0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,
		1,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,
		1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,
		1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,1,0,0,0,0,
		1,1,1,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
		0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,
		0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
		0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,
		0,0,0,0,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0
	};

	unsigned char imageobj[] = {
		0,0,0,0,1,1,1,1,0,0,0,0,
		0,0,0,1,1,1,1,1,1,0,0,0,
		0,0,0,1,1,1,1,1,1,0,0,0,
		0,0,0,1,1,1,1,1,1,0,0,0,
		0,0,0,1,1,1,1,1,1,0,0,0,
		0,0,0,1,1,1,1,1,1,0,0,0,
		1,1,0,1,1,1,1,1,1,0,1,1,
		1,1,0,1,1,1,1,1,1,0,1,1,
		1,1,0,1,1,1,1,1,1,0,1,1,
		1,1,0,1,1,1,1,1,1,0,1,1,
		1,1,0,1,1,1,1,1,1,0,1,1,
		1,1,0,1,1,1,1,1,1,0,1,1,
		0,1,1,1,1,1,1,1,1,1,1,0,
		0,0,1,1,1,1,1,1,1,1,0,0,
		0,0,0,1,1,1,1,1,1,0,0,0,
		0,0,0,1,1,1,1,1,1,0,0,0,
		0,0,0,1,1,1,1,1,1,0,0,0,
		0,0,0,1,1,1,1,1,1,0,0,0,
		0,0,0,1,1,1,1,1,1,0,0,0,
		0,0,0,1,1,1,1,1,1,0,0,0
	};
	const unsigned char gImage_player[][60] = {
		0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFE,0XFF,0XFB,0XFF,0XFF,0XBF,
	0XBF,0XBF,0X3F,0X3E,0X3F,0X7C,0XF8,0XF0,0XF0,0XF8,0XF8,0XFC,0XFE,0XFF,0XFF,0XFF,
	0XFF,0X7F,0X04,0X0C,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X03,0X3F,0X2F,0X07,
	0X03,0X07,0X3F,0X21,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,//stand/* 0X01,0X01,0X14,0X00,0X16,0X00, */

		0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFE,0XFF,0XFB,0XFF,0XFF,0XBF,
	0XBF,0XBF,0X3F,0X3E,0X3F,0X7C,0XF8,0XF0,0XF0,0XF8,0XF8,0XFC,0XFE,0XFF,0XFF,0XFF,
	0XFF,0X7F,0X04,0X0C,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X03,0X3F,0X2F,0X07,
	0X03,0X03,0X07,0X05,0X04,0X00,0X00,0X00,0X00,0X00,0X00,0X00,

	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFE,0XFF,0XFB,0XFF,0XFF,0XBF,
	0XBF,0XBF,0X3F,0X3E,0X3F,0X7C,0XF8,0XF0,0XF0,0XF8,0XF8,0XFC,0XFE,0XFF,0XFF,0XFF,
	0XFF,0X7F,0X04,0X0C,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X03,0X07,0X0F,0X0B,
	0X03,0X07,0X3F,0X21,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,

	};

	void draw_player() {
		static int mstep = 0;
		static int count = 0;
		if (gamestatus != pause)
		{
			if (count++ % 2)
				mstep = 1 - mstep;
			if (status.is_jump) {
				player.y -= (player.y - 15) / 5 + 1;
				if (player.y < 15)
				{
					status.is_jump = False; player.y = 15;
				}
				mstep = -1;
			}
			else {
				player.y += (player.y - 15) / 5 + 1;//15 43   0 1
				if (player.y >= 43)
				{
					player.y = 43;
					status.is_jumpfinish = True;
				}
				else
					mstep = -1;
			}
		}
		if (mstep == 2)
			mstep = 0;
		oled.Fill_Rect(player.x + 4, player.y + 32 + 18, 8, 4, 0x0);
		oled.Display_bbmp(player.x, player.y + 32, 20, 22, gImage_player[mstep + 1]);
		//			Display_pbmp(player.x,player.y+32,20,20,imageplayer);
	}

	float hardspeed = 0;
	int xpos[5], ypos[5], xlength[5];

	float delat = 400;

	void draw_obj(int movedistanse) {
		int i;
		obj.x -= movedistanse;
		delat -= movedistanse;
		if (obj.x + 2 >= 0 && obj.y + 32 + 17 >= 0)
			oled.Fill_Rect(obj.x + 2, obj.y + 32 + 17, 7, 4, 0);
		Display_pbmp(obj.x, obj.y + 31 + 3, 12, 20, imageobj);
		for (i = 0; i < 5; i++)
			if (xpos[i])
				oled.Draw_FastHLine(delat + xpos[i] - 70 - 128, obj.y + 31 + 23 + ypos[i], xlength[i], color_half);
		if (obj.x <= 0) {
			obj.x = 160 + rand() % 60;
		}
		if (delat <= 0)
		{
			for (i = 0; i < 5; i++)
			{
				xpos[i] = rand() % 40 + i * 20;
				ypos[i] = rand() % 3 * 2;
				xlength[i] = rand() % 20 + 5;
			}
			delat = 256 + 128;
		}
	}

	void check() {
		if (obj.x - player.x < 15 && obj.y - player.y < 15) {
			gamestatus = gameover;
		}
	}
	uint8_t short_key1_flag, short_key2_flag;
	char tempchar[50];

	OLED_STATUS OLED_UI::GAMEUIMainShow() {
		static int count = 0;
		if (short_key1_flag)
		{
			short_key1_flag = 0;
			red_click();
		}
		if (gamestatus == loading) {
			gamestatus = ready;
		}
		if (gamestatus == pause) {
			if (short_key2_flag)
			{
				short_key2_flag = 0;
				red_click();
			}
			oled.Draw_Line(0, 95, 160, 95);
			draw_obj(0);
			draw_player();
			sprintf(tempchar, "SCORE:%0.1fM", distance);
			oled.OLED_SBFAny(80 - strlen(tempchar) * 9 / 2, 10 + pit[70].current - 30, tempchar, 9, 0xffff);
			hardspeed = 0;
			oled.OLED_SBFAny(80 - strlen("PAUSE") * 9 / 2, 108 + pit[71].current + 20, "PAUSE", 9, 0xffff);
		}
		if (gamestatus == ready) {
			if (short_key2_flag)
			{
				short_key2_flag = 0;
				red_click();
			}
			sprintf(tempchar, "HIGHEST:%dM", highdistance);
			oled.OLED_SBFAny(80 - strlen(tempchar) * 9 / 2, 10 + pit[70].current - 30, tempchar, 9, 0xffff);
			hardspeed = 0;
			oled.OLED_SBFAny(80 - strlen("CHROME GAME") * 9 / 2, 108 + pit[71].current + 20, "CHROME GAME", 9, 0xffff);
			oled.Draw_Line(0, 95, 160, 95);
			draw_player();
			draw_obj(4 + hardspeed);
			if (obj.x - player.x < 30)
				status.is_jump = True;
		}
		if (gamestatus == playing) {
			if (short_key2_flag)
			{
				short_key2_flag = 0;
				blue_click();
			}
			if (hardspeed < 3)
				hardspeed = distance / 1000;
			distance += 1 + hardspeed / 3;
			gametime += 1;
			oled.Draw_Line(0, 95, 160, 95);
			sprintf(tempchar, "SCORE:%0.1fM", distance);
			oled.OLED_SBFAny(80 - strlen(tempchar) * 9 / 2, 10 + pit[70].current - 30, tempchar, 9, 0xffff);

			sprintf(tempchar, "HIGHEST:%dM", highdistance);
			oled.OLED_SBFAny(80 - strlen(tempchar) * 9 / 2, 108 + pit[71].current + 20, tempchar, 9, 0xffff);
			draw_player();
			draw_obj(4 + hardspeed);
			check();
		}
		if (gamestatus == gameover)
		{
			if (short_key2_flag)
			{
				short_key2_flag = 0;
				red_click();
			}
			if (count++ % 30 > 15)
			{
				if (highdistance < distance)
				{
					highdistance = distance;
					sprintf(tempchar, "HIGHEST:%dM", highdistance);
					oled.OLED_SBFAny(80 - strlen(tempchar) * 9 / 2, 10 + pit[70].current - 30, tempchar, 9, 0xffff);
				}
				else
				{
					sprintf(tempchar, "SCORE:%0.1fM", distance);
					oled.OLED_SBFAny(80 - strlen(tempchar) * 9 / 2, 10 + pit[70].current - 30, tempchar, 9, 0xffff);
				}
			}
			hardspeed = 0;
			oled.OLED_SBFAny(80 - strlen("game over") * 9 / 2, 108 + pit[71].current + 20, "GAME OVER", 9, 0xffff);
			oled.Draw_Line(0, 95, 160, 95);
			draw_player();
			draw_obj(4 + hardspeed);
			if (obj.x - player.x < 30)
				status.is_jump = True;
			//        oled.OLED_SBFAny({0} km.format(distance),2,0);
			//        oled.OLED_SBFAny(game over,25,30);
		}
		return OLED_IDLE;
	}




#ifdef __cplusplus
}
#endif



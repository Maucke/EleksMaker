#include "OLED_FFT.h"

#include "sysmain.h"

#include "math.h"


#ifdef __cplusplus
extern "C" {
#endif

	uint8_t fall_pot[250] = { 0 };	//记录下落点的坐标
	uint8_t flow_pot[250] = { 0 };

	OLED_FFT::OLED_FFT(void) {
	}

	void OLED_FFT::Display_Style1(void)
	{
		uint16_t i = 0;
		int Temp = 0;
		uint16_t Index;
		/*******************显示*******************/
		for (i = 0; i < TrumNum; i++)
		{
			Index = (float)i * Uart_FFT_Length / TrumNum + 1;
			Temp = TrumHeight - (uint16_t)(Device_Msg.fft[Index]);
			if (Temp < 2)
				Temp = 2;
			//		else if(Temp<4) Temp = 4;

			if (flow_pot[i] + 6 < Temp)
				flow_pot[i] += 4;
			else if (flow_pot[i] + 2 < Temp)
				flow_pot[i] += 2;
			else if (flow_pot[i] + 1 < Temp)
				flow_pot[i] += 1;

			if (flow_pot[i] > (Temp + 6))
				flow_pot[i] -= 4;
			else if (flow_pot[i] > (Temp + 2))
				flow_pot[i] -= 2;
			else if (flow_pot[i] > Temp + 1)
				flow_pot[i] -= 1;

			if (fall_pot[i] + 3 > flow_pot[i])
			{
				fall_pot[i] = flow_pot[i] - 3;
			}
			else if (fall_pot[i] + 3 < flow_pot[i])
			{
				fall_pot[i] ++;
			}
			oled.Draw_Line((TrumWidth + TrumInterval) * i, flow_pot[i], (TrumWidth + TrumInterval) * i, TrumHeight - 1);
			oled.Draw_Line((TrumWidth + TrumInterval) * i, fall_pot[i] + 1, (TrumWidth + TrumInterval) * i, fall_pot[i] + 1, color_half);
		}
	}

	void OLED_FFT::Display_Style2(void)
	{
		uint16_t i = 0;
		int Temp = 0;
		uint16_t Index;
		/*******************显示*******************/
		for (i = 0; i < SCR_WIDTH / 3; i++)
		{
			Index = (float)i * Uart_FFT_Length / SCR_WIDTH * 3 + 1;
			Temp = SCR_HEIGHT * 2 / 3 - (float)(Device_Msg.fft[Index] / 2);
			if (Temp < 2)
				Temp = 2;
			//		else if(Temp<4) Temp = 4;

			if (flow_pot[i] + 6 < Temp)
				flow_pot[i] += 4;
			else if (flow_pot[i] + 2 < Temp)
				flow_pot[i] += 2;
			else if (flow_pot[i] + 1 < Temp)
				flow_pot[i] += 1;

			if (flow_pot[i] > (Temp + 6))
				flow_pot[i] -= 4;
			else if (flow_pot[i] > (Temp + 2))
				flow_pot[i] -= 2;
			else if (flow_pot[i] > Temp + 1)
				flow_pot[i] -= 1;

			if (fall_pot[i] + 3 > flow_pot[i])
			{
				fall_pot[i] = flow_pot[i] - 3;
			}
			else if (fall_pot[i] + 3 < flow_pot[i])
			{
				fall_pot[i] ++;
			}
			oled.Draw_Line(3 * i, flow_pot[i] + 1, 3 * i, SCR_HEIGHT * 2 / 3);
			oled.Draw_Line(3 * i + 1, flow_pot[i] + 1, 3 * i + 1, SCR_HEIGHT * 2 / 3);

			oled.Draw_Line(3 * i, fall_pot[i] + 1 + 1, 3 * i, fall_pot[i] + 1 + 1, color_half);
			oled.Draw_Line(3 * i + 1, fall_pot[i] + 1 + 1, 3 * i + 1, fall_pot[i] + 1 + 1, color_half);

			oled.Draw_Line(3 * i, (SCR_HEIGHT * 2 / 3 - flow_pot[i]) / 3 + SCR_HEIGHT * 2 / 3 - 1, 3 * i, SCR_HEIGHT * 2 / 3 - 1, color_half);
			oled.Draw_Line(3 * i + 1, (SCR_HEIGHT * 2 / 3 - flow_pot[i]) / 3 + SCR_HEIGHT * 2 / 3 - 1, 3 * i + 1, SCR_HEIGHT * 2 / 3 - 1, color_half);

		}
		oled.Draw_Line(0, SCR_HEIGHT * 2 / 3 - 1, SCR_WIDTH, SCR_HEIGHT * 2 / 3 - 1, color_min);
	}


	void OLED_FFT::Display_Style3(void)
	{
		uint16_t i = 0;
		uint16_t j = 0;
		int Temp = 0;
		uint16_t Index;
		static uint8_t BackFlag[100] = { 0 };
		/*******************显示*******************/
		for (i = 0; i < SCR_WIDTH / 4; i++)
		{
			Index = (float)i * Uart_FFT_Length / SCR_WIDTH * 4 + 1;
			Temp = TrumHeight - (uint16_t)(Device_Msg.fft[Index] / 2);
			if (Temp < 4)
				Temp = 4;
			if (flow_pot[i] + 6 < Temp)
				flow_pot[i] += 4;
			else if (flow_pot[i] + 2 < Temp)
				flow_pot[i] += 2;
			else if (flow_pot[i] < Temp)
				flow_pot[i] += 1;

			if (flow_pot[i] > (Temp + 6))
				flow_pot[i] -= 4;
			else if (flow_pot[i] > (Temp + 2))
				flow_pot[i] -= 2;
			else if (flow_pot[i] > Temp)
				flow_pot[i] -= 1;

			if (fall_pot[i] + 3 > flow_pot[i])
			{
				fall_pot[i] = flow_pot[i] - 3;
				BackFlag[i] = 0;
			}
			else if (fall_pot[i] + 3 < flow_pot[i])
			{
				if (!BackFlag[i])
				{
					if (fall_pot[i] >= 4)
						fall_pot[i] -= 3;
					else if (fall_pot[i])
						BackFlag[i] = 1;
					else
						fall_pot[i] += 2;
				}
				else
					fall_pot[i] += 2;
			}
			//			HAL_GPIO_TogglePin(GPIOC, SYS_LED_Pin);



			oled.Draw_Line(4 * i + 0, fall_pot[i], 4 * i + 0, fall_pot[i], color_half);
			oled.Draw_Line(4 * i + 1, fall_pot[i], 4 * i + 1, fall_pot[i], color_half);
			oled.Draw_Line(4 * i + 2, fall_pot[i], 4 * i + 2, fall_pot[i], color_half);

			oled.Draw_Line(4 * i + 0, flow_pot[i], 4 * i + 0, TrumHeight - 1);
			oled.Draw_Line(4 * i + 1, flow_pot[i], 4 * i + 1, TrumHeight - 1);
			oled.Draw_Line(4 * i + 2, flow_pot[i], 4 * i + 2, TrumHeight - 1);
			for (j = TrumHeight; j >= flow_pot[i]; j -= 2)
				oled.Draw_Line(4 * i + 0, j, 4 * i + 2, j, 0);
		}
	}

	int16 SampPoint[4][192 * 2];

	void OLED_FFT::Display_Style4(void)
	{

		uint16_t i = 0;
		int Temp = 0;
		uint16_t Index;
		/*******************显示*******************/
		for (i = 0; i < SCR_WIDTH / 3; i++)
		{
			Index = (float)i * Uart_FFT_Length / SCR_WIDTH * 3 + 1;
			Temp = TrumHeight - (uint16_t)(Device_Msg.fft[Index] / 2);
			if (Temp < 2)
				Temp = 2;
			if (flow_pot[i] + 10 < Temp)
				flow_pot[i] += 4;
			else if (flow_pot[i] + 3 < Temp)
				flow_pot[i] += 2;
			else if (flow_pot[i] < Temp)
				flow_pot[i] += 1;
			if (flow_pot[i] > (Temp + 10))
				flow_pot[i] -= 4;
			else if (flow_pot[i] > (Temp + 3))
				flow_pot[i] -= 2;
			else if (flow_pot[i] > Temp)
				flow_pot[i] -= 1;

			SampPoint[0][i * 2] = 3 * i;
			SampPoint[0][i * 2 + 1] = flow_pot[i];
			oled.Draw_Line(3 * i, flow_pot[i], 3 * i, TrumHeight - 1, color_half);
		}
		oled.Draw_LineS(SampPoint[0], SCR_WIDTH / 3);
	}

	void OLED_FFT::Display_Style5(void)
	{

		uint16_t i = 0;
		int Temp = 0;
		uint16_t Index;
		/*******************显示*******************/
		for (i = 0; i < SCR_WIDTH / 3; i++)
		{
			Index = (float)i * Uart_FFT_Length / SCR_WIDTH * 3 + 1;
			Temp = SCR_HEIGHT / 2 - (uint16_t)(Device_Msg.fft[Index] / 3);
			if (Temp < 2)
				Temp = 2;
			if (flow_pot[i] + 10 < Temp)
				flow_pot[i] += 4;
			else if (flow_pot[i] + 3 < Temp)
				flow_pot[i] += 2;
			else if (flow_pot[i] < Temp)
				flow_pot[i] += 1;
			if (flow_pot[i] > (Temp + 10))
				flow_pot[i] -= 4;
			else if (flow_pot[i] > (Temp + 3))
				flow_pot[i] -= 2;
			else if (flow_pot[i] > Temp)
				flow_pot[i] -= 1;

			SampPoint[0][i * 2] = 3 * i;
			SampPoint[0][i * 2 + 1] = flow_pot[i];
			SampPoint[1][i * 2] = 3 * i;
			SampPoint[1][i * 2 + 1] = -flow_pot[i] + SCR_HEIGHT + 1;

			oled.Draw_Line(3 * i, SampPoint[0][i * 2 + 1], 3 * i, SampPoint[1][i * 2 + 1] - 1, color_half);

		}
		oled.Draw_LineS(SampPoint[0], SCR_WIDTH / 3);
		oled.Draw_LineS(SampPoint[1], SCR_WIDTH / 3);
	}

	int abs2(int num)
	{
		if (num >= 0)
			return num;
		else
			return -num;
	}

	void OLED_FFT::Display_Style6(void)
	{
		//	uint16_t i = 0; 
		uint16_t i = 0;
		int Temp = 0;
		uint16_t Index;
		uint8_t MaxType = 0xff;
		static int runCount = 0;
		static float Rr, Rn, step;
		static int runCount1 = 0;
		static int runCount2 = 0;
		/*******************显示*******************/
	//	if(Device_Msg.leftvol)
		Rn = 100 + Device_Msg.leftvol / (20 * 256);
		//	else
		//		Rn = 5;

		step = abs2(Rn - Rr) / 10 + 1;

		if (Rn > Rr + step)
		{
			Rr += step;
		}
		else if (Rn < Rr - step)
		{
			Rr -= step;
		}
		else if (abs2(Rn - Rr) <= step)
		{
			Rr = Rn;
		}

		runCount2++;
		for (i = 0; i < 60; i++)
		{
			Index = (runCount2 + i * 180 / 60) % 60 * 3;

			if (Device_Msg.fft[Index] < 100)
				Temp = Rr / 2 - (uint16_t)(Device_Msg.fft[Index] / 32);
			else if (Device_Msg.fft[Index] > 200)
				Temp = Rr / 2 - (uint16_t)(Device_Msg.fft[Index] / 24);
			else
				Temp = Rr / 2 - (uint16_t)(Device_Msg.fft[Index] / 8);
			if (Temp < 2)
				Temp = 0;

			if (flow_pot[i] + 10 < Temp)
				flow_pot[i] += 4;
			else if (flow_pot[i] + 3 < Temp)
				flow_pot[i] += 2;
			else if (flow_pot[i] < Temp)
				flow_pot[i] += 1;
			if (flow_pot[i] > (Temp + 10))
				flow_pot[i] -= 4;
			else if (flow_pot[i] > (Temp + 3))
				flow_pot[i] -= 2;
			else if (flow_pot[i] > Temp)
				flow_pot[i] -= 1;
			if (flow_pot[i] < MaxType)
				MaxType = flow_pot[i];
			if (flow_pot[i] < Rr)
			{
				SampPoint[0][i * 2] = OCX + ((Rr + flow_pot[i] - Rr / 2) * cos(i * 6 * PI / 180));
				SampPoint[0][i * 2 + 1] = OCY + ((Rr + flow_pot[i] - Rr / 2) * sin(i * 6 * PI / 180));
			}
			else
			{
				SampPoint[0][i * 2] = OCX + ((Rr + Rr - flow_pot[i] + Rr - Rr / 2) * cos(i * 6 * PI / 180));
				SampPoint[0][i * 2 + 1] = OCY + ((Rr + Rr - flow_pot[i] + Rr - Rr / 2) * sin(i * 6 * PI / 180));
				//			SampPoint[0][i*2] = OCX;
				//			SampPoint[0][i*2+1] = OCY;
			}
			SampPoint[1][i * 2] = OCX + ((Rr - flow_pot[i] + Rr / 2) * cos(i * 6 * PI / 180));
			SampPoint[1][i * 2 + 1] = OCY + ((Rr - flow_pot[i] + Rr / 2) * sin(i * 6 * PI / 180));

			oled.Draw_Line(SampPoint[0][i * 2], SampPoint[0][i * 2 + 1], SampPoint[1][i * 2], SampPoint[1][i * 2 + 1], 0xffff);

		}
		for (i = 0; i < 60; i++)
		{
			SampPoint[1][i * 2] = OCX + ((Rr + 3 - flow_pot[i] + Rr / 2) * cos(i * 6 * PI / 180));
			SampPoint[1][i * 2 + 1] = OCY + ((Rr + 3 - flow_pot[i] + Rr / 2) * sin(i * 6 * PI / 180));
		}
		oled.Draw_Line(SampPoint[1][0 * 2], SampPoint[1][0 * 2 + 1], SampPoint[1][59 * 2], SampPoint[1][59 * 2 + 1]);
		oled.Draw_LineS(SampPoint[1], 60);

		for (i = 0; i < 60; i++)
		{
			SampPoint[1][i * 2] = OCX + ((Rr + 5 - flow_pot[i] + Rr / 2) * cos(i * 6 * PI / 180));
			SampPoint[1][i * 2 + 1] = OCY + ((Rr + 5 - flow_pot[i] + Rr / 2) * sin(i * 6 * PI / 180));
		}
		oled.Draw_Line(SampPoint[1][0 * 2], SampPoint[1][0 * 2 + 1], SampPoint[1][59 * 2], SampPoint[1][59 * 2 + 1], color_half);
		oled.Draw_LineS(SampPoint[1], 60, color_half);

		runCount++;
		if (runCount >= 20)
			runCount = 0;
		runCount1 -= 2;
		if (runCount1 <= 0)
			runCount1 = 20;

		//	HAL_Delay(2000);
		//	oled.Draw_Circle(OCX,OCY,40-MaxType+20+2,color_half);
		//	oled.Draw_Circle(OCX,OCY,40-MaxType+20+3,color_min);
		Temp = 70 - MaxType + 20 + 3;

		oled.Draw_Line(OCX + (Temp * cos((runCount1 + 0) * 6 * PI / 180)), OCY + (Temp * sin((runCount1 + 0) * 6 * PI / 180)), OCX + (Temp * cos((runCount1 + 5) * 6 * PI / 180)), OCY + (Temp * sin((runCount1 + 5) * 6 * PI / 180)), color_half);
		oled.Draw_Line(OCX + (Temp * cos((runCount1 + 20) * 6 * PI / 180)), OCY + (Temp * sin((runCount1 + 20) * 6 * PI / 180)), OCX + (Temp * cos((runCount1 + 25) * 6 * PI / 180)), OCY + (Temp * sin((runCount1 + 25) * 6 * PI / 180)), color_half);
		oled.Draw_Line(OCX + (Temp * cos((runCount1 + 40) * 6 * PI / 180)), OCY + (Temp * sin((runCount1 + 40) * 6 * PI / 180)), OCX + (Temp * cos((runCount1 + 45) * 6 * PI / 180)), OCY + (Temp * sin((runCount1 + 45) * 6 * PI / 180)), color_half);
		Temp = 40 + MaxType - 20 - 2;
		//	oled.Fill_Circle(OCX,OCY,40+MaxType-20-4);
		oled.Draw_Triangle(OCX + (Temp * cos(runCount * 6 * PI / 180)), OCY + (Temp * sin(runCount * 6 * PI / 180)), OCX + (Temp * cos((runCount + 20) * 6 * PI / 180)), OCY + (Temp * sin((runCount + 20) * 6 * PI / 180)), OCX + (Temp * cos((runCount + 40) * 6 * PI / 180)), OCY + (Temp * sin((runCount + 40) * 6 * PI / 180)), color_half);
		Temp -= 4;
		oled.Draw_Triangle(OCX + (Temp * cos(runCount * 6 * PI / 180)), OCY + (Temp * sin(runCount * 6 * PI / 180)), OCX + (Temp * cos((runCount + 20) * 6 * PI / 180)), OCY + (Temp * sin((runCount + 20) * 6 * PI / 180)), OCX + (Temp * cos((runCount + 40) * 6 * PI / 180)), OCY + (Temp * sin((runCount + 40) * 6 * PI / 180)), color_min);
		//HAL_Delay(100);
	}




#ifdef __cplusplus
}
#endif



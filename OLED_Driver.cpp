#include "OLED_Driver.h"
#include "ASCII_Font.h"
#include <arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include "stdlib.h"


uint16_t color_byte,color_Damp_byte;

uint16_t wheel;
uint16_t OLED_GRAM[SCR_WIDTH*SCR_HEIGHT];
uint16_t color_now,color_half,color_min;

#define TFT_MOSI            19
#define TFT_SCLK            18
#define TFT_CS              5
#define TFT_DC              16
#define TFT_RST             23

#define TFT_BL              4   // Display backlight control pin

TFT_eSPI tft = TFT_eSPI(135, 240); // Invoke custom library
#ifdef __cplusplus
extern "C"  {
#endif


OLED_Driver::OLED_Driver(void) {
}
  
uint16_t OLED_Driver::ConvertColor(uint8_t red,uint8_t green,uint8_t blue)
{
	return red<<11|green<<6|blue;
}
uint16_t OLED_Driver::WheelP(uint16_t WheelPos)
{
	
	uint8_t red,green,blue;
	if(WheelPos < 32) 
	{
		red = 0;
		green = WheelPos;
		blue = (31 - WheelPos);
	}
	else if(WheelPos < (32*2)) 
	{          
		red = WheelPos-32;
		green = 32*2-1 - WheelPos;
		blue = 0;
	}
	else
	{
		red = (32*3)-1 - WheelPos;
		green = 0;
		blue = WheelPos-(32*2);
	}
	return (red<<11|green<<5|blue);
}	
uint16_t OLED_Driver::WheelPw(uint16_t WheelPos)
{
	
	uint8_t red,green,blue;
	if(WheelPos < 32) 
	{
		red = 31;
		green = WheelPos;
		blue = (31 - WheelPos);
	}
	else if(WheelPos < (32*2)) 
	{          
		red = WheelPos-32;
		green = 32*2-1 - WheelPos;
		blue = 31;
	}
	else
	{
		red = (32*3)-1 - WheelPos;
		green = 31;
		blue = WheelPos-(32*2);
	}
	return (red<<11|green<<5|blue);
}	


void OLED_Driver::Set_Wheel(uint16_t WheelPos)	{
	
	uint8_t red,green,blue;
	wheel = WheelPos;
	if(WheelPos < 32) 
	{
		red = 0;
		green = WheelPos;
		blue = (31 - WheelPos);
	}
	else if(WheelPos < (32*2)) 
	{          
		red = WheelPos-32;
		green = 32*2-1 - WheelPos;
		blue = 0;
	}
	else
	{
		red = (32*3)-1 - WheelPos;
		green = 0;
		blue = WheelPos-(32*2);
	}
	color_Damp_byte = (red << 11 | green << 5 | blue);
}
void OLED_Driver::Calc_Color(void){
				
	uint8_t red,green,blue;
	uint8_t red1,green1,blue1;
	red = color_byte >> 11;
	green = (color_byte & 0x7E0) >> 5;
	blue = color_byte & 0x1F;

	red1 = color_Damp_byte >> 11;
	green1 = (color_Damp_byte & 0x7E0) >> 5;
	blue1 = color_Damp_byte & 0x1F;
	
	if(red>red1)
	{
		red--;
	}
	else if(red<red1)
	{
		red++;
	}
	if(green>green1+1)
	{
		green-=2;
	}
	else if(green+1<green1)
	{
		green+=2;
	}
	if(blue>blue1)
	{
		blue--;
	}
	else if(blue<blue1)
	{
		blue++;
	}
	color_now = red<<11|green<<5|blue;
	color_byte = color_now;
	red >>=1;
	green >>=1;
	blue >>=1;
	color_half = red<<11|green<<5|blue;
	red >>=1;
	green >>=1;
	blue >>=1;
	color_min = red<<11|green<<5|blue;
	
}


uint16_t OLED_Driver::RandomColor(void){
	
	uint8_t red,green,blue;
	red = rand();
	green = rand();
	blue = rand();
	return (red<<11|green<<5|blue);
}

void OLED_Driver::Set_DampColor(uint16_t color)  {
  
  color_Damp_byte=color ;
}




void OLED_Driver::Set_Color(uint16_t color)  {
  
  color_byte = color;
}


//void OLED_Driver::Set_FillColor(uint16_t color)  {
//  
//  color_fill_byte[0] = (uint8_t)(color >> 8);
//  color_fill_byte[1] = (uint8_t)(color & 0x00ff);
//}
//  

void OLED_Driver::Refrash_Screen(void)  {

	tft.pushImage(0, 0,  240, 135, OLED_GRAM);
}
  

void OLED_Driver::Clear_Screen(void)  {
  
  //int i,j;
  //for(i=0;i<SCR_HEIGHT;i++)  {
  //  for(j=0;j<SCR_WIDTH;j++)  {
  //    OLED_GRAM[j+i*SCR_WIDTH] = 0;
  //  }
  //}
  memset(OLED_GRAM,0,sizeof(OLED_GRAM));
}
  
void OLED_Driver::Draw_Pixel(long x, long y)
{
  // Bounds check.
  if ((x >= SCR_WIDTH) || (y >= SCR_HEIGHT)) return;
  if ((x < 0) || (y < 0)) return;

	OLED_GRAM[x+y*SCR_WIDTH] = color_byte;
  
}

void OLED_Driver::Draw_Pixel(long x, long y,uint16_t color)
{
  // Bounds check.
  if ((x >= SCR_WIDTH) || (y >= SCR_HEIGHT)) return;
  if ((x < 0) || (y < 0)) return;

	OLED_GRAM[x+y*SCR_WIDTH] = color;
  
}
  
  
void OLED_Driver::Device_Init(void) {

	tft.init();
	tft.setRotation(1);
	tft.setSwapBytes(true);
}


// Draw a horizontal line ignoring any screen rotation.
void OLED_Driver::Draw_FastHLine(int16_t x, int16_t y, int16_t length) {
  // Bounds check
		int16_t x0=x;
    do
    {
        Draw_Pixel(x, y);   // 逐点显示，描出垂直线
        x++;
    }
    while(x0+length>=x);
}
// Draw a horizontal line ignoring any screen rotation.
void OLED_Driver::Draw_FastHLine(int16_t x, int16_t y, int16_t length,uint16_t color) {
  // Bounds check
		int16_t x0=x;
    do
    {
        Draw_Pixel(x, y,color);   // 逐点显示，描出垂直线
        x++;
    }
    while(x0+length>=x);
}
  
  // Draw a vertical line ignoring any screen rotation.
void OLED_Driver::Draw_FastVLine(int16_t x, int16_t y, int16_t length)  {
  // Bounds check
		int16_t y0=y;
    do
    {
        Draw_Pixel(x, y);   // 逐点显示，描出垂直线
        y++;
    }
    while(y0+length>=y);
}
  // Draw a vertical line ignoring any screen rotation.
void OLED_Driver::Draw_FastVLine(int16_t x, int16_t y, int16_t length,uint16_t color)  {
  // Bounds check
		int16_t y0=y;
    do
    {
        Draw_Pixel(x, y,color);   // 逐点显示，描出垂直线
        y++;
    }
    while(y0+length>=y);
}
void OLED_Driver::Display_bbmp(int x,int y,int w,int h,const uint8_t *ch) {
  
	uint8_t i,j,k;
	for(k=0;k<(h/8+1);k++)
		for(i=0;i<8;i++)
		{
			if(k*8+i>=h)
				return;
			for(j=0;j<w;j++)
					if(ch[k*w+j]&(1<<i))
						Draw_Pixel(x+j,y+k*8+i);
		}
}

void OLED_Driver::Display_bbmp(int x,int y,int w,int h,const uint8_t *ch,uint16_t color) {
  
	uint8_t i,j,k;
	for(k=0;k<(h/8+1);k++)
		for(i=0;i<8;i++)
		{
			if(k*8+i>=h)
				return;
			for(j=0;j<w;j++)
					if(ch[k*w+j]&(1<<i))
						Draw_Pixel(x+j,y+k*8+i,color);
		}
}
  
void OLED_Driver::Display_bmp(int x,int y,int w,int h,const uint8_t *ch) {
  int Temp;
  int i,j;
  for(i=y;i<y+h;i++)  {
    for(j=x;j<x+w;j++)  {
			Temp = (i-y)*w*2+2*(j-x);
			if((ch[Temp+1]<<8)|ch[Temp])
				Draw_Pixel(j,i,(ch[Temp+1]<<8)|ch[Temp]); 
    }
  }
} 

void OLED_Driver::Display_hbmp(int x,int y,int w,int h,const uint8_t *ch,uint16_t color)
{
	uint16_t i,j;
	uint16_t red,green,blue;
	uint16_t red1,green1,blue1;
	uint16_t Factor;
//	color = 0xFFFF;
	red = color>>11;
	green = (color&0x7E0)>>5;
	blue = color&0x1F;
	for(j=0;j<h;j++)
		for(i=0;i<(w+1)/2;i++)
		{
			Factor = (ch[j*((w+1)/2)+i]&0xF0)>>4;
			red1 = red*(Factor+16)/32;
			green1 = green*(Factor+16)/32;
			blue1=blue*(Factor+16)/32;
			
			if(Factor)
				Draw_Pixel(x+i*2+0,y+j,red1<<11|(green1<<5)|(blue1));
			
			Factor = (ch[j*((w+1)/2)+i]&0xF);
			red1 = red*(Factor+16)/32;
			green1 = green*(Factor+16)/32;
			blue1=blue*(Factor+16)/32;
			
			if(Factor)
				Draw_Pixel(x+i*2+1,y+j,red1<<11|(green1<<5)|(blue1));
		}
}	
  
void OLED_Driver::Display_hbmp(int x,int y,int w,int h,const uint8_t *ch,uint16_t color,uint8_t bk)
{
	uint16_t i,j;
	uint16_t red,green,blue;
	uint16_t red1,green1,blue1;
	uint16_t Factor;
//	color = 0xFFFF;
	red = color>>11;
	green = (color&0x7E0)>>5;
	blue = color&0x1F;
	for(j=0;j<h;j++)
		for(i=0;i<(w+1)/2;i++)
		{
			Factor = (ch[j*((w+1)/2)+i]&0xF0)>>4;
			red1 = red*(Factor+16)/32;
			green1 = green*(Factor+16)/32;
			blue1=blue*(Factor+16)/32;
			
			if(Factor)
				Draw_Pixel(x+i*2+0,y+j,red1<<11|(green1<<5)|(blue1));
			else
				Draw_Pixel(x+i*2+0,y+j,bk);
			
			Factor = (ch[j*((w+1)/2)+i]&0xF);
			red1 = red*(Factor+16)/32;
			green1 = green*(Factor+16)/32;
			blue1=blue*(Factor+16)/32;
			
			if(Factor)
				Draw_Pixel(x+i*2+1,y+j,red1<<11|(green1<<5)|(blue1));
			else
				Draw_Pixel(x+i*2+1,y+j,bk);
		}
}	

void OLED_Driver::OLED_HFAny(int x,int y,int w,int h,uint8_t Num,const unsigned char *ch,uint16_t color)
{
	uint16_t i,j;
	uint16_t red,green,blue;
	uint16_t red1,green1,blue1;
	uint16_t Factor;
//	color = 0xFFFF;
	red = color>>11;
	green = (color&0x7E0)>>5;
	blue = color&0x1F;
	for(j=0;j<h;j++)
		for(i=0;i<(w+1)/2;i++)
		{
			Factor = (ch[Num*h*((w+1)/2)+j*((w+1)/2)+i]&0xF0)>>4;
			red1 = red*(Factor+16)/32;
			green1 = green*(Factor+16)/32;
			blue1=blue*(Factor+16)/32;
			
			if(Factor)
				Draw_Pixel(x+i*2+0,y+j,red1<<11|(green1<<5)|(blue1));
			
			Factor = (ch[Num*h*((w+1)/2)+j*((w+1)/2)+i]&0xF);
			red1 = red*(Factor+16)/32;
			green1 = green*(Factor+16)/32;
			blue1=blue*(Factor+16)/32;
			
			if(Factor)
				Draw_Pixel(x+i*2+1,y+j,red1<<11|(green1<<5)|(blue1));
		}
}	

//extern const unsigned char Defu_XF4x5[];
//extern const unsigned char GeForce_10x13[];
//extern const unsigned char GeForce_13x16[];
//extern const unsigned char GeForce_19x23[];
//extern const unsigned char GeForce_25x37[];
void OLED_Driver::OLED_SHFAny(int x,int y,char *ch,int w,uint16_t color)
{
	uint8_t c=0,j=0;
	while(ch[j]!='\0')
	{
		if(ch[j]=='-')
			c=10;
		else
			c=ch[j]-'0';
		
		switch(w)
		{
			case 4:OLED_HFAny(x,y,4,5,c,Defu_XF4x5,color);break;
			case 10:OLED_HFAny(x,y,10,13,c,GeForce_10x13,color);break;
			case 13:OLED_HFAny(x,y,13,16,c,GeForce_13x16,color);break;
			case 19:OLED_HFAny(x,y,19,23,c,GeForce_19x23,color);break;
			case 25:OLED_HFAny(x,y,25,37,c,GeForce_25x37,color);break;
			default:OLED_HFAny(x,y,10,13,c,GeForce_10x13,color);break;
		}
		x+=w; 
		j++;
	}
}

void OLED_Driver::OLED_BFAny(int x,int y,int w,int h,uint8_t Num,const unsigned char *ch,uint16_t color)
{
	uint16_t i,j,k;
	uint16_t bnum = ((h+7)/8)*w;
	
	for(k=0;k<(h+7)/8;k++)//8*k层
		for(j=0;j<w;j++)//w
			for(i=0;i<8;i++)
				if((ch[Num*bnum+w*k+j]>>i)&1)
					Draw_Pixel(x+j,y+i+k*8,color);
}

void OLED_Driver::OLED_BFAny(int x,int y,int w,int h,uint8_t Num,const unsigned char *ch,uint16_t color,uint16_t hui)
{
	uint16_t i,j,k;
	uint16_t red,green,blue;
	uint16_t red1,green1,blue1;
	
	red = color>>11;
	green = (color&0x7E0)>>5;
	blue = color&0x1F;
	uint16_t bnum = ((h+7)/8)*w;
	
	for(k=0;k<(h+7)/8;k++)//8*k层
		for(j=0;j<w;j++)//w
			for(i=0;i<8;i++)
				if((ch[Num*bnum+w*k+j]>>i)&1)
				{
					red1 = red*(hui-abs(j-w/2))/hui;
					green1 = green*(8-abs(j-w/2))/hui;
					blue1=blue*(hui-abs(j-w/2))/hui;
					
					Draw_Pixel(x+j,y+i+k*8,red1<<11|(green1<<5)|(blue1));
				}
}
	
	
//extern const unsigned char OCRB_F8x16[];
//extern const unsigned char Self_F9x16[];
//extern const unsigned char OCR_F10x16[];
//extern const unsigned char OCR_F12x16[];
//extern const unsigned char OCRB_F12x16[];
//extern const unsigned char Agency_F12x24[];
//extern const unsigned char OCR_F16x24[];
//extern const unsigned char OCRB_F16x24[];
//extern const unsigned char Agency_F22x40[];
//extern const unsigned char Robot_F32x46[];
//extern const unsigned char RobotT_F32x46[];
//extern const unsigned char RobotB_F32x46[];	
	
void OLED_Driver::OLED_SBFAny(int x,int y,char *ch,int w,uint16_t color)
{
	uint8_t c=0,j=0;
	while(ch[j]!='\0')
	{
		c=ch[j]-' ';
		
		switch(w)
		{
			case 8:OLED_BFAny(x,y,8,16,c,OCRB_F8x16,color,8);break;
			case 9:if(c==0)c=1;else c+=' '-'.';OLED_BFAny(x,y,9,16,c,Self_F9x16,color);break;
			case 10:OLED_BFAny(x,y,10,16,c,OCR_F10x16,color);break;
			case 12:OLED_BFAny(x,y,12,16,c,OCR_F12x16,color);break;
			case 13:OLED_BFAny(x,y,12,24,c,Agency_F12x24,color);break;
//			case 12:OLED_BFAny(x,y,12,16,c,OCRB_F12x16,color);break;
			case 16:OLED_BFAny(x,y,16,24,c,OCR_F16x24,color);break;
			case 22:OLED_BFAny(x,y,22,40,c,Agency_F22x40,color);break;
//			case 16:OLED_BFAny(x,y,16,24,c,OCRB_F16x24,color);break;
			default:OLED_BFAny(x,y,8,16,c,OCRB_F8x16,color);break;
		}
		x+=w; 
		j++;
	}
}
const unsigned char Font_Default6x8[] =
{
	0x7E,0x7E,0x42,0x42,0x7E,0x00,
	0x00,0x00,0x7E,0x7E,0x00,0x00,
	0x7A,0x7A,0x4A,0x4A,0x4E,0x00,
	0x42,0x4A,0x4A,0x7E,0x7E,0x00,
	0x0E,0x0E,0x08,0x08,0x7E,0x00,
	0x4E,0x4E,0x4A,0x4A,0x7A,0x00,
	0x7E,0x7E,0x4A,0x4A,0x7A,0x00,
	0x02,0x02,0x02,0x7E,0x7E,0x00,
	0x7E,0x7E,0x4A,0x4A,0x7E,0x00,
	0x4E,0x4A,0x4A,0x7E,0x7E,0x00,
	0x00,0x0C,0x0C,0x00,0x00,0x00,// .
	0x02,0x00,0x0E,0x0A,0x0A,0x02,
	0x08,0x08,0x08,0x08,0x08,0x00,
	0x00,0x6C,0x6C,0x00,0x00,0x00,// :
};

void OLED_Driver::OLED_NF6x8(int x,int y,uint8_t Num,uint8_t Offset)
{
	uint8_t i,j;
	
	for(i=0;i<8;i++)
	{
		for(j=0;j<3;j++)
		{
			if(!(((Font_Default6x8[(Num+Offset)*6+j*2]>>i)&1)<<1))
				Draw_Pixel(x+j*2,y+i);
			if(!((Font_Default6x8[(Num+Offset)*6+j*2+1]>>i)&1))
				Draw_Pixel(x+j*2+1,y+i);
		}
	}
}	


void OLED_Driver::OLED_SNF6x8(int x,int y,char *ch)
{
	uint8_t c=0,j=0;
	for(j=0;j<8;j++)
		Draw_Pixel(x-1,y+j);
	j = 0;
	while(ch[j]!='\0')
	{
		c=ch[j];
		if(x<253)
		{
			if(c=='$')
				OLED_NF6x8(x,y,11,0);
			else if(c=='.')
				OLED_NF6x8(x,y,10,0);
			else if(c==':')
				OLED_NF6x8(x,y,13,0);
			else if(c=='-')
				OLED_NF6x8(x,y,12,0);
			else
			{
				c=ch[j]-'0';
				OLED_NF6x8(x,y,c,0);
			}
		}
		x+=6;
		j++;
	}
	for(j=0;j<8;j++)
		Draw_Pixel(x,y+j);
}
#ifdef __cplusplus
}
#endif



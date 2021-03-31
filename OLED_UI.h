#ifndef __OLED_UI_H
#define __OLED_UI_H

#include <arduino.h>
#include "OLED_GFX.h"
#include "OLED_Driver.h"
#include "OLED_Animation.h"
#include "motion.h"
#ifdef __cplusplus
extern "C" {
#endif
extern uint8_t DataDisType;

  class OLED_UI : public virtual OLED_GFX {
    
    public: 
      			OLED_UI(void);
	  
			void SUI_In();
			void SUI_Out();
			void SUIDataPrss();
			OLED_STATUS SUIMainShow();
	  
			void NUI_In();
			void NUI_Out();
			void NUIDataPrss();
			OLED_STATUS NUIMainShow();

			void TUI_In();
			void TUI_Out();
			void TUIDataPrss();
			OLED_STATUS TUIMainShow();

			void T1UI_In();
			void T1UI_Out();
			void T1UIDataPrss();
			OLED_STATUS T1UIMainShow();

			void T2UI_In();
			void T2UI_Out();
			void T2UIDataPrss();
			OLED_STATUS T2UIMainShow();
		
			void MUI_In();
			void MUI_Out();
			void MUIDataPrss();
			OLED_STATUS MUIMainShow();

			void HUI_In();
			void HUI_Out();
			void HUIDataPrss();
			OLED_STATUS HUIMainShow();

			void GAMEUI_In();
			void GAMEUI_Out();
			void GAMEUIDataPrss();
			OLED_STATUS GAMEUIMainShow();
		
    private:  
			OLED_STATUS MtRect(int x,int y,int w,int h,int step,uint16_t color);
			OLED_STATUS SUITitleShow(int step,uint16_t color);
			OLED_STATUS SUICornShow(void);
			OLED_STATUS NUICornShow(void);
			OLED_STATUS TUICornShow(void);
			void CoordinateDataPrss(int cycle,int height,int width);
			void DrawCoordinate(int x,int y,int height,int width,uint16_t color);
			void OLED_LFPixel(int x,int y,int w,int h,int psize,int pinterval,uint8_t Num,const unsigned char *ch,uint16_t color);
			void OLED_SLFAny(int x,int y,int psize,int pinterval,char *ch,int w,uint16_t color);
  };



#ifdef __cplusplus
}
#endif
  
#endif


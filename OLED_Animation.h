#ifndef __OLED_ANIMATION_H
#define __OLED_ANIMATION_H

#include <arduino.h>
#include "OLED_GFX.h"
#include "sysmain.h"
#include "ASCII_Font.h"
#include "stdlib.h"

#define MINDMAX 14
#define CIRCLEMAX 8
#define STARMAX 20
#define METEORMAX 20
#define DEFLINEMAX 30
#define PLANETMAX 5
#define TRIANGLEMAX 8
#define FULLTRIANGLEMAX 8

typedef enum
{
  OLED_OK       = 0x00U,
  OLED_ERROR    = 0x01U,
  OLED_BUSY     = 0x02U,
  OLED_IDLE     = 0x03U,
} OLED_STATUS;

extern OLED_GFX oled;
#ifdef __cplusplus
extern "C" {
#endif

  class OLED_Animation {
    
    public: 
			OLED_Animation(void);
			void Motion_MindInit(void);
			void Motion_Mind(void);
			void Motion_CircleInit(void);
			void Motion_Circle(void);
			void Motion_SnowflakeInit(void);
			void Motion_Snowflake(void);
			void Motion_MovmeteorInit(void);
			void Motion_Movmeteor(void);
			void Motion_PlanetInit(void);
			void Motion_Planet(void);
			void Motion_TriangleInit(void);
			void Motion_Triangle(void);
			void Motion_TriangleF(void);
			void OLED_AllMotion_Init(void);
			void OLED_CustormMotion(uint8_t Channel);
			void OLED_AllMotion(uint8_t Type,uint16_t Speed);
    private:  
      OLED_STATUS OLED_MovMind(uint8_t Index);
			OLED_STATUS OLED_FucCircle(uint8_t Index);
			OLED_STATUS OLED_MovSnowflake(uint8_t Index);
			OLED_STATUS OLED_Movmeteor(uint8_t Index);
			OLED_STATUS OLED_Planet(uint8_t Index);
			OLED_STATUS OLED_Triangle(uint8_t Index);

  };





#ifdef __cplusplus
}
#endif
  
#endif

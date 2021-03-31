#ifndef __MOTIOH_H__ 	
#define __MOTIOH_H__ 

#include <arduino.h>

#ifdef __cplusplus
extern "C" {
#endif
#define PITITEM 90
typedef struct
{
	float target;
	float current;
	uint8_t match;
	uint8_t channel;
}PIT;

extern PIT pit[PITITEM];

void DampAutoPos(uint8_t channel);
void DampManualPos(float step,uint8_t channel);
void DampCustormPos(uint16_t index,float step);

void SetCurrent(uint8_t index,float value);
void SetTarget(uint8_t index,float value);
void SetChannel(uint8_t index,uint8_t able);

//#define POSNRCT 0
//#define POSNRCD 1
//#define POSNTOP 2
//#define POSNBAR 3
//#define POSNBAT 4
//#define POSNBRO 5
//#define CRTVANE 6
//#define CRTVADS 7
//#define DAMPTYP 8

#define PNTHOUR 10
#define PNTMIN 11
#define PNTSEC 12

#define RDRadius 13
#define RDRadiusC 14
#define RDRadiusB 15
#define RDHourRadius 16
#define RDMinRadius 17
#define RDSecRadius 18
#define RDRuleDelaut 19

#define RDHourColor 20
#define RDMinColor 21
#define RDSecColor 22

#define RDRadiusA 23
#define PNTTIME 24
#define PNTTIMEY 25

//#define PBLOGO	26
//#define PBNUM 	27
//#define PBLINEL 	28
//#define PBLINER 	29
//#define PBPT22 	30
//#define PBPT33 	31
//#define PBPTbk 	32

//#define PWPTUP 	33
//#define PWPTDN 	34
//#define PWPTRT 	35
//#define PWPTLF 	36
//#define PWPTRTICON 	37
//#define PWPTLINE 	38

//#define DIM 65
//#define UNUSE 66
#define SSLF  60
#define SSRT  61
#define SSMLF 62
#define SSMRT 63
#define SSLLF 64
#define SSLRT 65

#define SSUP  66
#define SSDN  67
#define SSRD  68

#define STSOK  69

#define POSNRCT 75
#define POSNRCD 76
#define POSNTOP 77
#define POSNBAR 78
#define POSNBAT 79
#define POSNBRO 80

#define CRTVANE 81
#define CRTVADS 82
#define DAMPTYP 83


#ifdef __cplusplus
}
#endif

#endif

#include "motion.h"
#include <arduino.h>
#include <stdio.h>
#include <stdlib.h>


#ifdef __cplusplus
extern "C" {
#endif
	
PIT pit[PITITEM];
int absl(int num)
{
	if(num>=0)
		return num;
	else
		return -num;
}

void DampAutoPos(uint8_t channel)
{
	int i;
	float step;
	for(i=0;i<PITITEM;i++)
	{
		if(pit[i].channel == channel)
		{
			step = absl(pit[i].target-pit[i].current)/20+1;
			
			if(pit[i].target > pit[i].current+step)
			{
				pit[i].current += step;
				pit[i].match = 0;
			}
			else if(pit[i].target < pit[i].current-step)
			{
				pit[i].current -= step;
				pit[i].match = 0;
			}
			else if(absl(pit[i].target-pit[i].current)<=step)
			{
				pit[i].current = pit[i].target;
				pit[i].match = 1;
			}
		}
	}
}

void DampManualPos(float step,uint8_t channel)
{
	int i;
	for(i=0;i<PITITEM;i++)
	{
		if(pit[i].channel == channel)
		{
			if(pit[i].target > pit[i].current+step)
			{
				pit[i].current += step;
				pit[i].match = 0;
			}
			else if(pit[i].target < pit[i].current-step)
			{
				pit[i].current -= step;
				pit[i].match = 0;
			}
			else if(absl(pit[i].target-pit[i].current)<=step)
			{
				pit[i].current = pit[i].target;
				pit[i].match = 1;
			}
		}
	}
}

void DampCustormPos(uint16_t index,float step)
{
	if(pit[index].target > pit[index].current+step)
	{
		pit[index].current += step;
		pit[index].match = 0;
	}
	else if(pit[index].target < pit[index].current-step)
	{
		pit[index].current -= step;
		pit[index].match = 0;
	}
	else if(absl(pit[index].target-pit[index].current)<=step)
	{
		pit[index].current = pit[index].target;
		pit[index].match = 1;
	}
}

void SetCurrent(uint8_t index,float value)
{
	pit[index].current = value;
}

void SetTarget(uint8_t index,float value)
{
	pit[index].target = value;
}

void SetChannel(uint8_t index,uint8_t channel)
{
	pit[index].channel = channel;
}


#ifdef __cplusplus
}
#endif

#ifndef __TIMER_H__
#define __TIMER_H__

#include "Globals.h"

class Timer
{
public:

	// Constructor
	Timer();

	void Start();
	uint Read() const;
	float ReadSec() const;

private:
	uint startTime;
};
#endif //__TIMER_H__
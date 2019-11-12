#pragma once
#include "SDL.h"

class TimerMilliS
{
public:
	TimerMilliS();
	~TimerMilliS();

	void Start();
	Uint32 Read();
	Uint32 Stop();

private:
	Uint32 startMillis;
	Uint32 stopMillis;
};


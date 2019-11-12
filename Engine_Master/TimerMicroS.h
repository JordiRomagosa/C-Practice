#pragma once
#include "SDL.h"

class TimerMicroS
{
public:
	TimerMicroS();
	~TimerMicroS();

	void Start();
	Uint64 Read();
	Uint64 Stop();

private:
	Uint64 startMicros;
	Uint64 stopMicros;
	double frequency;
};


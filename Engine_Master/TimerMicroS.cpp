#include "TimerMicroS.h"

TimerMicroS::TimerMicroS()
{
	frequency = SDL_GetPerformanceFrequency();
}

TimerMicroS::~TimerMicroS()
{
}

void TimerMicroS::Start()
{
	startMicros = SDL_GetPerformanceCounter();
	stopMicros = 0;
}

Uint64 TimerMicroS::Read()
{
	frequency = SDL_GetPerformanceFrequency();
	if (stopMicros != 0)
		return stopMicros;

	return (SDL_GetPerformanceCounter() - startMicros) * 1000000 / frequency;
}

Uint64 TimerMicroS::Stop()
{
	frequency = SDL_GetPerformanceFrequency();
	stopMicros = (SDL_GetPerformanceCounter() - startMicros) * 1000000 / frequency;
	return stopMicros;
}

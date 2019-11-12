#include "TimerMilliS.h"


TimerMilliS::TimerMilliS()
{
}

TimerMilliS::~TimerMilliS()
{
}

void TimerMilliS::Start()
{
	startMillis = SDL_GetTicks();
	stopMillis = 0;
}

Uint32 TimerMilliS::Read()
{
	if (stopMillis != 0)
		return stopMillis;
	
	return SDL_GetTicks() - startMillis;
}

Uint32 TimerMilliS::Stop()
{
	stopMillis = SDL_GetTicks() - startMillis;
	return stopMillis;
}

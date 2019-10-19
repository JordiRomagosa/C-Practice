#ifndef __MODULESCENEHONDA_H__
#define __MODULESCENEHONDA_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneHonda : public Module
{
public:
	ModuleSceneHonda(bool start_enabled = true);
	~ModuleSceneHonda();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* graphics = nullptr;
	SDL_Rect ground;
	SDL_Rect ceiling;
	SDL_Rect background1;
	SDL_Rect background2;
	SDL_Rect bathtub;
	Animation water;
	Animation mountain;
	Animation posterman;

private:
	int posterAnimationCount;
	bool posterAnimated;
};

#endif // __MODULESCENEHONDA_H__
#ifndef __MODULESCENEKEN_H__
#define __MODULESCENEKEN_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneKen : public Module
{
public:
	ModuleSceneKen( bool start_enabled = true);
	~ModuleSceneKen();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	SDL_Texture* graphics = nullptr;
	SDL_Rect ground;
	SDL_Rect ship;
	SDL_Rect background;
	Animation flag;
	Animation girl;
	Animation twoMen;
	Animation greenMan;
	Animation blueMan;
	Animation brownMan;
	Animation purpleMan;

private:
	double timeElapsed;
	int shipFloatLine;
};

#endif // __MODULESCENEKEN_H__
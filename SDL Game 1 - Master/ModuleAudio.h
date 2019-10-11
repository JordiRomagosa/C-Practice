#pragma once

#include "Globals.h"
#include "Module.h"

struct _Mix_Music;
typedef struct _Mix_Music Mix_Music;

class ModuleAudio : public Module
{

public:
	ModuleAudio();
	~ModuleAudio();

	bool Init();
	bool CleanUp();

	bool PlayMusic(const char* path);

private:

	Mix_Music* music = nullptr;
};


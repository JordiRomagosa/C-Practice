#include "Globals.h"
#include "ModuleAudio.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

using namespace std;

ModuleAudio::ModuleAudio()
{}

ModuleAudio::~ModuleAudio()
{}

bool ModuleAudio::Init()
{
	LOG("Loading Audio Mixer");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
	{
		LOG("SDL_INIT_AUDIO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 256000) < 0)
	{
		LOG("SDL_INIT_AUDIO could not initialize!SDL_Error: % s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleAudio::CleanUp()
{
	Mix_FreeMusic(music);
	music = nullptr;

	return true;
}

bool ModuleAudio::PlayMusic(const char* path)
{
	bool ret = true;
	music = Mix_LoadMUS(path);

	if (music == nullptr)
	{
		LOG("Cannot load music %s. Mix_GetError(): %s\n", path, Mix_GetError());
		ret = false;
	}

	if (Mix_PlayingMusic() == 0)
		Mix_PlayMusic(music, -1);

	else
	{
		Mix_HaltMusic();
		Mix_PlayMusic(music, -1);
	}
		
	return ret;
}

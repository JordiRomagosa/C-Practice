#include "Globals.h"
#include "Application.h"
#include "ModuleSceneHonda.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"

ModuleSceneHonda::ModuleSceneHonda(bool start_enabled) : Module(start_enabled)
{
	ground.x = 45;
	ground.y = 376;
	ground.w = 810;
	ground.h = 64;

	background1.x = 127;
	background1.y = 128;
	background1.w = 88;
	background1.h = 199;

	background2.x = 215;
	background2.y = 176;
	background2.w = 575;
	background2.h = 130;

	ceiling.x = 91;
	ceiling.y = 8;
	ceiling.w = 765;
	ceiling.h = 48;

	bathtub.x = 312;
	bathtub.y = 316;
	bathtub.w = 336;
	bathtub.h = 52;

	water.frames.push_back({ 8, 448, 284, 8 });
	water.frames.push_back({ 296, 448, 284, 12 });
	water.frames.push_back({ 588, 448, 284, 18 });
	water.frames.push_back({ 296, 448, 284, 12 });
	water.speed = 0.03f;

	posterAnimationCount = 0;
	posterAnimated = false;

	mountain.frames.push_back({ 224, 64, 224, 104 });
	mountain.frames.push_back({ 456, 64, 224, 104 });
	mountain.speed = 0.15f;

	posterman.frames.push_back({ 688, 64, 96, 104 });
	posterman.frames.push_back({ 792, 64, 64, 104 });
	posterman.speed = 0.05f;
}

ModuleSceneHonda::~ModuleSceneHonda()
{}

bool ModuleSceneHonda::Start()
{
	LOG("Loading honda scene");

	graphics = App->textures->Load("honda_stage.png");
	App->player->Enable();
	App->audio->PlayMusic("honda.ogg", 0);

	return true;
}

bool ModuleSceneHonda::CleanUp()
{
	LOG("Unloading honda scene");

	App->textures->Unload(graphics);
	App->player->Disable();

	return true;
}

update_status ModuleSceneHonda::Update()
{
	App->renderer->Blit(graphics, -45, 160, &ground);
	App->renderer->Blit(graphics, 0, -15, &background1, 0.8f);
	App->renderer->Blit(graphics, 88, 33, &background2, 0.8f);
	App->renderer->Blit(graphics, -57, -15, &ceiling, 0.8f);

	if (posterAnimated)
	{
		App->renderer->Blit(graphics, 185, 41, &(mountain.GetCurrentFrame()), 0.8f);
		SDL_Rect postmanFrame = posterman.GetCurrentFrame();
		App->renderer->Blit(graphics, 504 - postmanFrame.w, 41, &(postmanFrame), 0.8f);
		posterAnimationCount++;
		if (posterAnimationCount >= 200)
		{
			posterAnimated = false;
			posterAnimationCount = 0;
		}
	}
	else
	{
		posterAnimationCount++;
		if (posterAnimationCount >= 500)
		{
			posterAnimated = true;
			posterAnimationCount = 0;
		}	
	}

	App->renderer->Blit(graphics, 200, 125, &bathtub, 0.9f);
	App->renderer->Blit(graphics, 223, 137, &(water.GetCurrentFrame()), 0.9f);

	if (App->input->GetKey(SDL_SCANCODE_SPACE)) {
		App->fade->FadeToBlack((Module*)App->scene_ken, this, 3.0f);
	}

	return UPDATE_CONTINUE;
}



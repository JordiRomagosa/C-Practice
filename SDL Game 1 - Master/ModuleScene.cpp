#include "Globals.h"
#include "ModuleScene.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"


ModuleScene::ModuleScene()
{
	background.x = 0;
	background.y = 0;
	background.w = 475;
	background.h = 475;
}

ModuleScene::~ModuleScene()
{
}

bool ModuleScene::Start()
{
	bool ret = true;
	LOG("Loading scene");

	graphics = App->textures->Load("ditto.png");

	if (!App->audio->PlayMusic("base.wav"))
		ret = false;

	return ret;
}

update_status ModuleScene::Update()
{
	App->renderer->Blit(graphics, 70, 20, &background);
	return UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{
	LOG("Unloading scene");
	return true;
}

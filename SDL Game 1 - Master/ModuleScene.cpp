#include "ModuleScene.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "SDL/include/SDL.h"

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
	//load image into textures
	graphics = App->textures->Load("ditto.png");
	return true;
}

update_status ModuleScene::Update()
{
	App->renderer->Blit(graphics, 60, 20, &background);
	return UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{
	return true;
}

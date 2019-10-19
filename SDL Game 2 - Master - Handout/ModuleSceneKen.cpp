#include "Globals.h"
#include "Application.h"
#include "ModuleSceneKen.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"

#include <cmath>

using namespace std;

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneKen::ModuleSceneKen(bool start_enabled) : Module(start_enabled)
{
	// ground
	ground.x = 8;
	ground.y = 391;
	ground.w = 896;
	ground.h = 72;

	// TODO 2 : setup the foreground (red ship) with
	ship.x = 8 ;
	ship.y = 24;
	ship.w = 524;
	ship.h = 180;
	// coordinates x,y,w,h from ken_stage.png

	// Background / sky
	background.x = 72;
	background.y = 208;
	background.w = 768;
	background.h = 176;

	// flag animation
	flag.frames.push_back({848, 208, 40, 40});
	flag.frames.push_back({848, 256, 40, 40});
	flag.frames.push_back({848, 304, 40, 40});
	flag.speed = 0.08f;

	// TODO 4: Setup Girl Animation from coordinates from ken_stage.png
	timeElapsed = 0;

	girl.frames.push_back({ 624, 16, 32, 56 });
	girl.frames.push_back({ 624, 80, 32, 56 });
	girl.frames.push_back({ 624, 144, 32, 56 });
	girl.frames.push_back({ 624, 80, 32, 56 });
	girl.speed = 0.06f;

	twoMen.frames.push_back({ 552, 8, 64, 64 });
	twoMen.frames.push_back({ 552, 80, 64, 56 });
	twoMen.frames.push_back({ 552, 144, 64, 56 });
	twoMen.frames.push_back({ 552, 144, 64, 56 });
	twoMen.frames.push_back({ 552, 80, 64, 56 });
	twoMen.speed = 0.08f;

	greenMan.frames.push_back({ 664, 16, 32, 56 });
	greenMan.frames.push_back({ 664, 80, 32, 56 });
	greenMan.speed = 0.02f;

	blueMan.frames.push_back({ 704 , 16, 48, 56 });
	blueMan.frames.push_back({ 704 , 80, 48, 56 });
	blueMan.frames.push_back({ 704 , 144, 48, 56 });
	blueMan.frames.push_back({ 704 , 144, 48, 56 });
	blueMan.frames.push_back({ 704 , 80, 48, 56 });
	blueMan.frames.push_back({ 704 , 16, 48, 56 });
	blueMan.speed = 0.15f;

	brownMan.frames.push_back({ 760, 16, 40, 40 });
	brownMan.frames.push_back({ 760, 64, 40, 40 });
	brownMan.frames.push_back({ 760, 112, 40, 40 });
	brownMan.frames.push_back({ 760, 64, 40, 40 });
	brownMan.speed = 0.1f;

	purpleMan.frames.push_back({ 808, 24, 48, 32 });
	purpleMan.frames.push_back({ 808, 72, 48, 32 });
	purpleMan.frames.push_back({ 808, 120, 48, 32 });
	purpleMan.frames.push_back({ 808, 72, 48, 32 });
	purpleMan.speed = 0.08f;
}

ModuleSceneKen::~ModuleSceneKen()
{}

// Load assets
bool ModuleSceneKen::Start()
{
	LOG("Loading ken scene");
	
	graphics = App->textures->Load("ken_stage.png");

	// TODO 7: Enable the player module
	App->player->Enable();

	// TODO 0: trigger background music
	App->audio->PlayMusic("ken.ogg", 0);

	return true;
}

// UnLoad assets
bool ModuleSceneKen::CleanUp()
{
	LOG("Unloading ken scene");

	App->textures->Unload(graphics);
	App->player->Disable();
	
	return true;
}

// Update: draw background
update_status ModuleSceneKen::Update()
{
	// TODO 5: make sure the ship goes up and down
	timeElapsed++;
	shipFloatLine = -2 + (2 * sin(timeElapsed / 30));

	// Draw everything --------------------------------------
	// TODO 1: Tweak the movement speed of the sea&sky + flag to your taste
	App->renderer->Blit(graphics, 0, 0, &background, 0.75f); // sea and sky
	App->renderer->Blit(graphics, 560, 8, &(flag.GetCurrentFrame()), 0.75f); // flag animation

	// TODO 3: Draw the ship. Be sure to tweak the speed.
	App->renderer->Blit(graphics, 0, shipFloatLine, &ship, 0.85f); // red ship

	// TODO 6: Draw the girl. Make sure it follows the ship movement!
	App->renderer->Blit(graphics, 192, 104 + shipFloatLine, &(girl.GetCurrentFrame()), 0.85f); // girl animation

	SDL_Rect twoMenFrame = twoMen.GetCurrentFrame(); // two men animation
	if (twoMenFrame.y == 8)
		App->renderer->Blit(graphics, 128, 104 + shipFloatLine - 8, &twoMenFrame, 0.85f);
	else
		App->renderer->Blit(graphics, 128, 104 + shipFloatLine, &twoMenFrame, 0.85f);
	
	App->renderer->Blit(graphics, 224, 104 + shipFloatLine, &(greenMan.GetCurrentFrame()), 0.85f); // green man animation
	App->renderer->Blit(graphics, 288, 96 + shipFloatLine, &(blueMan.GetCurrentFrame()), 0.85f); // blue man animation
	App->renderer->Blit(graphics, 88, 24 + shipFloatLine, &(brownMan.GetCurrentFrame()), 0.85f); // brown man animation
	App->renderer->Blit(graphics, 128, 24 + shipFloatLine, &(purpleMan.GetCurrentFrame()), 0.85f); // purple man animation
	
	App->renderer->Blit(graphics, 0, 170, &ground);

	// TODO 10: Build an entire new scene "honda", you can find its
	// and music in the Game/ folder

	// TODO 11: Make that pressing space triggers a switch to honda logic module
	// using FadeToBlack module
	if (App->input->GetKey(SDL_SCANCODE_SPACE)) {
		App->fade->FadeToBlack((Module*)App->scene_honda, this, 3.0f);
	}

	return UPDATE_CONTINUE;
}
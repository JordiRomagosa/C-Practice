#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleCamera.h"
#include "ModuleRender.h"
#include "SDL/include/SDL.h"

ModuleInput::ModuleInput()
{}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::Update()
{
	SDL_PumpEvents();

	keyboard = SDL_GetKeyboardState(NULL);

	if (keyboard[SDL_SCANCODE_ESCAPE])
		return UPDATE_STOP;

	bool shift = keyboard[SDL_SCANCODE_LSHIFT] || keyboard[SDL_SCANCODE_RSHIFT];

	if (keyboard[SDL_SCANCODE_A] && !keyboard[SDL_SCANCODE_D])
		App->camera->Translate(1, 0, 0, shift);
	if (keyboard[SDL_SCANCODE_D] && !keyboard[SDL_SCANCODE_A])
		App->camera->Translate(-1, 0, 0, shift);
	if (keyboard[SDL_SCANCODE_W] && !keyboard[SDL_SCANCODE_S])
		App->camera->Translate(0, 0, 1, shift);
	if (keyboard[SDL_SCANCODE_S] && !keyboard[SDL_SCANCODE_W])
		App->camera->Translate(0, 0, -1, shift);
	if (keyboard[SDL_SCANCODE_Q] && !keyboard[SDL_SCANCODE_E])
		App->camera->Translate(0, 1, 0, shift);
	if (keyboard[SDL_SCANCODE_E] && !keyboard[SDL_SCANCODE_Q])
		App->camera->Translate(0, -1, 0, shift);

	if (keyboard[SDL_SCANCODE_LEFT] && !keyboard[SDL_SCANCODE_RIGHT])
		App->camera->Rotate(0, -1);
	if (keyboard[SDL_SCANCODE_RIGHT] && !keyboard[SDL_SCANCODE_LEFT])
		App->camera->Rotate(0, 1);
	if (keyboard[SDL_SCANCODE_UP] && !keyboard[SDL_SCANCODE_DOWN])
		App->camera->Rotate(1, 0);
	if (keyboard[SDL_SCANCODE_DOWN] && !keyboard[SDL_SCANCODE_UP])
		App->camera->Rotate(-1, 0);

	SDL_Event sdlEvent;

	while (SDL_PollEvent(&sdlEvent) != 0)
	{
		switch (sdlEvent.type)
		{
		case SDL_QUIT:
			return UPDATE_STOP;

		case SDL_WINDOWEVENT:
			if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED || sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				App->renderer->WindowResized(sdlEvent.window.data1, sdlEvent.window.data2);
			break;
		}
		CameraMovementWithMouse(sdlEvent);
	}


	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}

void ModuleInput::CameraMovementWithMouse(SDL_Event & event) {

	//if (event.type == SDL_MOUSEBUTTONDOWN)
	//{
	//	lastMousePosition = glm::vec2(event.button.x, event.button.y);
	//	if (event.button.button == SDL_BUTTON_RIGHT) {
	//		rightMouseButtonIsDown = true;
	//	}
	//	if (event.button.button == SDL_BUTTON_MIDDLE) {
	//		middleMouseButtonIsDown = true;
	//	}
	//}
	//if (event.type == SDL_MOUSEBUTTONUP)
	//{
	//	if (event.button.button == SDL_BUTTON_RIGHT) {
	//		rightMouseButtonIsDown = false;
	//	}
	//	if (event.button.button == SDL_BUTTON_MIDDLE) {
	//		middleMouseButtonIsDown = false;
	//	}
	//}
	//if (event.type == SDL_MOUSEWHEEL) {
	//	if (event.wheel.y > 0) // scroll up
	//	{
	//		Engine->moduleCamera->Zoom(true);
	//	}
	//	else if (event.wheel.y < 0) // scroll down
	//	{
	//		Engine->moduleCamera->Zoom(false);
	//	}

	//}
	//if (rightMouseButtonIsDown && event.type == SDL_MOUSEMOTION) {

	//	int mouseXPos = (event.motion.x - lastMousePosition.x) *mouseSensitivity;
	//	int mouseYPos = (lastMousePosition.y - event.motion.y) *mouseSensitivity;

	//	lastMousePosition.x = event.motion.x;
	//	lastMousePosition.y = event.motion.y;
	//	Engine->moduleCamera->MoveCameraWithMousePosition(glm::vec2(mouseXPos, mouseYPos));
	//}

	//if (middleMouseButtonIsDown && event.type == SDL_MOUSEMOTION) {

	//	int mouseXPos = (event.motion.x - lastMousePosition.x) * mouseSensitivity;
	//	int mouseYPos = (event.motion.y - lastMousePosition.y) * mouseSensitivity;

	//	glm::vec2 translationDirection = glm::vec2(0.0f);
	//	lastMousePosition.x = event.motion.x;
	//	lastMousePosition.y = event.motion.y;
	//	translationDirection.x = mouseXPos;
	//	translationDirection.y = mouseYPos;
	//	Engine->moduleCamera->Translate(translationDirection);
	//}
}
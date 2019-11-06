#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleRenderExercise;
class ModuleEditor;
class ModuleProgram;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();
	void RequestBrowser(char * url);

public:
	ModuleRender* renderer = nullptr;
	ModuleRenderExercise* rendererExercise = nullptr;
	ModuleWindow* window = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleInput* input = nullptr;
	ModuleEditor* editor = nullptr;
	ModuleProgram* program = nullptr;

private:

	std::list<Module*> modules;

};

extern Application* App;

#pragma once
#include "Module.h"
#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_sdl.h"
#include "IMGUI/imgui_impl_opengl3.h"
#include <stdio.h>
#include <SDL.h>
#include <GL/glew.h>


class ModuleEditor : public Module
{
public:
	ModuleEditor();
	~ModuleEditor();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

private:
	ImGuiIO io;
	bool show_demo_window;
	bool show_another_window;
	ImVec4 clear_color;
};


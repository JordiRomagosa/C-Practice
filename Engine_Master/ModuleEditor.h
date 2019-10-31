#pragma once
#include "Module.h"
#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_sdl.h"
#include "IMGUI/imgui_impl_opengl3.h"
#include <stdio.h>
#include <SDL.h>
#include <GL/glew.h>
#include <chrono>
#include <vector>

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
	bool showDemo;
	std::chrono::steady_clock::time_point lastSecond;
	short frameCount;
	std::vector<float> ms_log;
	std::vector<float> fps_log;

public:
	ImGuiTextBuffer buffer;
};


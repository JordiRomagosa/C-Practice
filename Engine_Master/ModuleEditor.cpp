#include "ModuleEditor.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"

ModuleEditor::ModuleEditor()
{
}


ModuleEditor::~ModuleEditor()
{
}

bool ModuleEditor::Init()
{
	// Initialize OpenGL loader
	bool err = glewInit() != 0;
	if (err)
	{
		LOG("Failed to initialize OpenGL loader!\n", SDL_GetError());
		return false;
	}

	// Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

	// Setup Platform/Renderer bindings
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->window->glcontext);
	ImGui_ImplOpenGL3_Init("#version 130");

	showDemo = false;

	lastSecond = std::chrono::steady_clock::now();

	return true;
}

update_status ModuleEditor::PreUpdate()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

	return UPDATE_CONTINUE;
}

update_status ModuleEditor::Update()
{
	ImGui::TextUnformatted(buffer.begin());

	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("Help"))
	{
		if (ImGui::MenuItem("Gui Demo"))
			showDemo = !showDemo;

		if (ImGui::MenuItem("Github Link"))
			App->RequestBrowser("https://github.com/JordiRomagosa/C-Practice/tree/master/Engine_Master");
			
		ImGui::EndMenu();
	}
	ImGui::EndMainMenuBar();

	if (showDemo)
		ImGui::ShowDemoWindow();

	
	/*if (firstFrame)
	{
		currentFrame = std::chrono::steady_clock::now();
		firstFrame = false;
	}
	else
	{
		lastFrame = currentFrame;
		currentFrame = std::chrono::steady_clock::now();
		unsigned int millis = std::chrono::duration_cast<std::chrono::milliseconds>(currentFrame - lastFrame).count();
		
		if (ms_log.size() == 30)
			ms_log.erase(ms_log.begin());
		ms_log.push_back(millis);
	}*/

	std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
	unsigned int millis = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastSecond).count();
	frameCount++;

	if (millis > 1000)
	{
		if (fps_log.size() == 30)
			fps_log.erase(fps_log.begin());
		fps_log.push_back(frameCount);

		if (ms_log.size() == 30)
			ms_log.erase(ms_log.begin());
		ms_log.push_back(1.0 * frameCount / millis);

		lastSecond = currentTime;
		frameCount = 0;
	}

	if (fps_log.size() > 0 || ms_log.size() > 0)
	{
		char title[25];
		sprintf_s(title, 25, "Framerate %.1f", fps_log[fps_log.size() - 1]);
		ImGui::PlotHistogram("##framerate", &fps_log[0], fps_log.size(), 0, title, 0.0f, 1500.0f, ImVec2(310, 100));
		sprintf_s(title, 25, "Milliseconds %0.1f", ms_log[ms_log.size() - 1]);
		ImGui::PlotHistogram("##milliseconds", &ms_log[0], ms_log.size(), 0, title, 0.0f, 10.0f, ImVec2(300, 100));
	}

	return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate()
{
	// Rendering
	ImGui::Render();
	glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return UPDATE_CONTINUE;
}

bool ModuleEditor::CleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	return true;
}

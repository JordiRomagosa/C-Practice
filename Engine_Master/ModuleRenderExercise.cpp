#include "ModuleRenderExercise.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "SDL.h"
#include "glew.h"
#include "MathGeoLib/include/MathGeoLib.h"


ModuleRenderExercise::ModuleRenderExercise()
{
}


ModuleRenderExercise::~ModuleRenderExercise()
{
}

bool ModuleRenderExercise::Init()
{
	LOG("Creating Renderer context");
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	GLenum err = glewInit();
	LOG("Using Glew %s", glewGetString(GLEW_VERSION));
	LOG("Vendor: %s", glGetString(GL_VENDOR));
	LOG("Renderer: %s", glGetString(GL_RENDERER));
	LOG("OpenGL version supported %s", glGetString(GL_VERSION));
	LOG("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glClearDepth(1.0f);
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glViewport(0, 0, 1024, 768);

	eye = float3(0, 0, 3);
	up = float3(0, 1, 0);
	target = float3(0, 0, 0);

	math::float3 f(target - eye); f.Normalize();
	math::float3 s(f.Cross(up)); s.Normalize();
	math::float3 u(s.Cross(f));
	matrix[0][0] = s.x; matrix[0][1] = s.y; matrix[0][2] = s.z;
	matrix[1][0] = u.x; matrix[1][1] = u.y; matrix[1][2] = u.z;
	matrix[2][0] = -f.x; matrix[2][1] = -f.y; matrix[2][2] = -f.z;
	matrix[0][3] = -s.Dot(eye); matrix[1][3] = -u.Dot(eye); matrix[2][3] = f.Dot(eye);
	matrix[3][0] = 0.0f; matrix[3][1] = 0.0f; matrix[3][2] = 0.0f; matrix[3][3] = 1.0f;

	return true;
}

update_status ModuleRenderExercise::PreUpdate()
{
	int w, h;
	SDL_GetWindowSize(App->window->window, &w, &h);
	glViewport(0, 0, w, h);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float aspect = w / h;

	Frustum frustum;
	frustum.type = FrustumType::PerspectiveFrustum;
	frustum.pos = float3::zero;
	frustum.front = -float3::unitZ;
	frustum.up = float3::unitY;
	frustum.nearPlaneDistance = 0.1f;
	frustum.farPlaneDistance = 100.0f;
	frustum.verticalFov = math::pi / 4.0f;
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f)) *aspect;
	math::float4x4 proj = frustum.ProjectionMatrix();

	float4x4 model = float4x4::FromTRS(float3(0.0f, 0.0f, -4.0f), float3x3::RotateY(math::pi / 4.0f), float3(1.0f, 1.0f, 1.0f));

	//float4x4 view = float4x4::LookAt(view, math::float3(0.0f, 1.f, 4.0f), math::float3(0.0f, 0.0f, 0.0f), math::float3(0.0f, 1.0f, 0.0f));
	//float4x4 transform = proj * view * float4x4(model);


	return UPDATE_CONTINUE;
}

update_status ModuleRenderExercise::Update()
{
	float buffer_data[] = { -1.0f, -1.0f, 0.0f,
							   1.0f, -1.0f, 0.0f,
							   0.0f, 1.0f, 0.0f };
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_data), buffer_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(0); // attribute 0

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(
		0,			// attribute 0
		3,			// number of componentes (3 floats)
		GL_FLOAT,	// data type
		GL_FALSE,	// should be normalized?
		0,			// stride
		(void*)0	// array buffer offset
	);
	glDrawArrays(GL_TRIANGLES, 0, 3); // start at 0 and 3 tris
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return UPDATE_CONTINUE;
}

update_status ModuleRenderExercise::PostUpdate()
{
	SDL_GL_SwapWindow(App->window->window);

	return UPDATE_CONTINUE;
}

bool ModuleRenderExercise::CleanUp()
{
	return true;
}

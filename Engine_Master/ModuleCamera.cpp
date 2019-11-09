#include "ModuleCamera.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "glew.h"

ModuleCamera::ModuleCamera()
{
}


ModuleCamera::~ModuleCamera()
{
}

bool ModuleCamera::Init()
{
	int w, h;
	SDL_GetWindowSize(App->window->window, &w, &h);
	float aspect = float(w) / float(h);

	frustum.type = FrustumType::PerspectiveFrustum;
	frustum.pos = float3(0, -1, -2);
	frustum.front = -float3::unitZ;
	frustum.up = float3::unitY;
	frustum.nearPlaneDistance = 0.1f;
	frustum.farPlaneDistance = 100.0f;
	frustum.verticalFov = math::pi / 4.0f;
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f) * aspect);

	CalculateMatrixes();
	return true;
}

update_status ModuleCamera::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModuleCamera::Update()
{
	return UPDATE_CONTINUE;
}

update_status ModuleCamera::PostUpdate()
{
	return UPDATE_CONTINUE;
}

bool ModuleCamera::CleanUp()
{
	return true;
}

math::float4x4 ModuleCamera::LookAt(math::float3 eye, math::float3 target, math::float3 up) {
	math::float4x4 matrix;
	math::float3 f(target - eye); f.Normalize();
	math::float3 s(f.Cross(up)); s.Normalize();
	math::float3 u(s.Cross(f));

	matrix[0][0] = s.x; matrix[0][1] = s.y; matrix[0][2] = s.z;
	matrix[1][0] = u.x; matrix[1][1] = u.y; matrix[1][2] = u.z;
	matrix[2][0] = -f.x; matrix[2][1] = -f.y; matrix[2][2] = -f.z;

	matrix[0][3] = -s.Dot(eye); matrix[1][3] = -u.Dot(eye); matrix[2][3] = f.Dot(eye);
	matrix[3][0] = 0.0f; matrix[3][1] = 0.0f; matrix[3][2] = 0.0f; matrix[3][3] = 1.0f;

	return matrix;
}

math::float4x4 ModuleCamera::GetModelMatrix() {
	return model;
}

math::float4x4 ModuleCamera::GetViewMatrix() {
	return view;
}

math::float4x4 ModuleCamera::GetProjectionMatrix() {
	return proj;
}

void ModuleCamera::CalculateMatrixes() {
	model = math::float4x4::FromTRS(frustum.pos, math::float3x3::RotateY(math::pi / 4.0f), math::float3(1.0f, 1.0f, 1.0f));
	//view = LookAt(math::float3(0.0f, 1.f, 4.0f), math::float3(0.0f, 0.0f, 0.0f), math::float3(0.0f, 1.0f, 0.0f));
	view = math::float4x4::LookAt(frustum.pos, frustum.pos + frustum.front, frustum.front, frustum.up, math::float3(0.0f, 1.0f, 0.0f));
	proj = frustum.ProjectionMatrix();
}

void ModuleCamera::SetFOV(float verticalFOV)
{
	float aspect = frustum.AspectRatio();

	frustum.verticalFov = verticalFOV;
	frustum.horizontalFov = frustum.verticalFov *aspect;
	CalculateMatrixes();
}

void ModuleCamera::SetAspectRatio(float height, float width)
{
	float aspect = height / width;
	frustum.horizontalFov = frustum.verticalFov *aspect;
	CalculateMatrixes();
}

void ModuleCamera::Translate(int right, int up, int forward, bool shift)
{
	int speedMult = 1;
	if (shift)
		speedMult = shiftSpeedMultiplier;

	if (right > 0)
		frustum.pos += frustum.WorldRight() * cameraMovementSpeed * speedMult;
	if (right < 0)
		frustum.pos -= frustum.WorldRight() * cameraMovementSpeed * speedMult;

	if (up > 0)
		frustum.pos += float3(0, 1, 0) * cameraMovementSpeed * speedMult;
	if (up < 0)
		frustum.pos -= float3(0, 1, 0) * cameraMovementSpeed * speedMult;

	if (forward > 0)
		frustum.pos += frustum.front * cameraMovementSpeed * speedMult;
	if (forward < 0)
		frustum.pos -= frustum.front * cameraMovementSpeed * speedMult;
	
	CalculateMatrixes();
}

void ModuleCamera::Rotate(int pitch, int yaw)
{
	


	CalculateMatrixes();
}

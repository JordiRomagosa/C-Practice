#pragma once
#include "Module.h"
#include "MathGeoLib/include/MathGeoLib.h"

class ModuleCamera : public Module
{
public:
	ModuleCamera();
	~ModuleCamera();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	math::float4x4 LookAt(math::float3 eye, math::float3 target, math::float3 up);
	math::float4x4 GetModelMatrix();
	math::float4x4 GetViewMatrix();
	math::float4x4 GetProjectionMatrix();
	void CalculateMatrixes();
	void SetFOV(float verticalFOV);
	void SetAspectRatio(float height, float width);
	void Translate(int right, int up, int forward, bool shift);
	void Rotate(int pitch, int yaw);

private:
	Frustum frustum;
	math::float4x4 model;
	math::float4x4 view;
	math::float4x4 proj;

	float cameraMovementSpeed = 0.01f;
	int shiftSpeedMultiplier = 2;
	float cameraRotationSpeed = 0.1f;
};


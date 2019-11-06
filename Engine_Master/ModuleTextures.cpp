#include "ModuleTextures.h"
#include "il.h"
#include "ilu.h"
#include "ilut.h"

ModuleTextures::ModuleTextures()
{
}

ModuleTextures::~ModuleTextures()
{
}

bool ModuleTextures::Init()
{
	ilInit();
	iluInit();
	ilutInit();
	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION)
	{
		LOG("DevIL version is different...exiting!\n");
		return false;
	}

	return true;
}

update_status ModuleTextures::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModuleTextures::Update()
{
	return UPDATE_CONTINUE;
}

update_status ModuleTextures::PostUpdate()
{
	return UPDATE_CONTINUE;
}

bool ModuleTextures::CleanUp()
{
	return true;
}

GLuint ModuleTextures::LoadTexture(char * path)
{
	ILuint ImageName;
	ilGenImages(1, &ImageName);
	ilBindImage(ImageName);

	ilLoadImage(path);

	GLuint Texture;
	Texture = ilutGLBindTexImage();

	return Texture;
}
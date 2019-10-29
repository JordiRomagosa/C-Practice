#include "ModuleProgram.h"
#include "ModuleProgram.h"
#include "SDL.h"
#include "glew.h"
#include "MathGeoLib/include/MathGeoLib.h"
#include <string>

using namespace std;

ModuleProgram::ModuleProgram()
{
}


ModuleProgram::~ModuleProgram()
{
}

bool ModuleProgram::Init()
{
	char * vertexData = LoadShader("default.vs");
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	CompileShader(vertexShader, vertexData);
	
	
	char * fragmentData = LoadShader("default.fs");
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	CompileShader(fragmentShader, fragmentData);

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		LOG("Program linking failed\n");
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return true;
}

update_status ModuleProgram::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModuleProgram::Update()
{
	return UPDATE_CONTINUE;
}

update_status ModuleProgram::PostUpdate()
{
	return UPDATE_CONTINUE;
}

bool ModuleProgram::CleanUp()
{
	return true;
}

char * ModuleProgram::LoadShader(char * filename)
{
	char* data = nullptr;
	FILE* file = nullptr;
	fopen_s(&file, filename, "rb");

	if (file)
	{
		fseek(file, 0, SEEK_END);
		int size = ftell(file);
		rewind(file);
		data = (char*)malloc(size + 1);
		fread(data, 1, size, file);
		data[size] = 0;
		fclose(file);
	}
	else
		LOG("Read file failed");

	return data;
}

void ModuleProgram::CompileShader(unsigned int shader, char * data)
{
	glShaderSource(shader, 1, &data, NULL);
	glCompileShader(shader);
	int  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		LOG("Shader compilation failed");
		LOG(data);
	}
}

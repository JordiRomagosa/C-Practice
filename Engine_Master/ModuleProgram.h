#pragma once
#include "Module.h"

class ModuleProgram : public Module
{
public:
	ModuleProgram();
	~ModuleProgram();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

private:
	char * LoadShader(char * filename);
	void CompileShader(unsigned int shader, char * data);

public:
	unsigned int program;
};


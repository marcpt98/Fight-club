#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "SDL\include\SDL_scancode.h"

#define MAX_KEYS 300

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class ModuleInput : public Module
{
public:

	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

public:
	KEY_STATE keyboard[MAX_KEYS];
	int j = 0;
	int y = 0;
	int t = 0;
	int r = 0;
	int o = 0;
	int p = 0;
	int i = 0;
	int u = 0;
};

#endif // __ModuleInput_H__
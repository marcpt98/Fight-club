#ifndef __MODULESCENELEVEL_1_H__
#define __MODULESCENELEVEL_1_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleScenelevel_1 : public Module
{
public:
	ModuleScenelevel_1();
	~ModuleScenelevel_1();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	SDL_Texture* graphics = nullptr;

	SDL_Rect background1;

	int Scene1_Fight = 0;
	float foreground_pos;
	bool forward;
};

#endif // __MODULESCENELEVEL_1_H__
#ifndef __ModulePlayer2_H__
#define __ModulePlayer2_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModulePlayer2 : public Module
{
public:
	ModulePlayer2();
	~ModulePlayer2();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture * graphics = nullptr;
	iPoint position;
	Animation* current_animation = nullptr;
	Animation idle;
	/*Animation jump;
	Animation forward;
	Animation backward;
	Animation hadouken;
	//Animation ball;
	Animation punch;
	Animation kick;
	int time = 0;*/
};

#endif

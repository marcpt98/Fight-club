#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	Animation idle;
	Animation jump;
	Animation forward;
	Animation backward;
	Animation crouch;
	iPoint position;
	Animation hadouken;
	//Animation ball;
	Animation punch;
	Animation kick;
	int time =0;
	int ryokick = 0;
};

#endif
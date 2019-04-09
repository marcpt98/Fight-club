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
	Animation crouch1;
	Animation crouch2;
	iPoint position;
	Animation hadouken;
	//Animation ball;
	Animation punch;
	Animation kick;
	Collider *ryohitbox;

	int time =0;
	int ryokick = 0;
	int ryopunch = 0;
	int ryojump = 0;
	int ryoKoOuKen = 0;
	int ryoKoOuKensound = 0;
	int god = 0;
};

#endif
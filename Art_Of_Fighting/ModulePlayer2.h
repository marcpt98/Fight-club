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
	Animation* current_animation = nullptr;
	Collider *ryohitbox2;
	iPoint position;
	Animation idle;

	/*Animation jump;
	Animation forward;
	Animation backward;
	Animation crouch1;
	Animation crouch2;
	Animation hadouken;
	//Animation ball;
	Animation punch;
	Animation kick;
	

	int time = 0;
	int ryokick = 0;
	int ryopunch = 0;
	int ryojump = 0;
	int ryoKoOuKen = 0;
	int ryoKoOuKensound = 0;*/
};

#endif

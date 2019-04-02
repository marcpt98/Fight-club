#ifndef __ModuleAnimationHaduken_H__
#define __ModuleAnimationHaduken_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModuleAnimationHaduken : public Module
{
public:
	ModuleAnimationHaduken();
	~ModuleAnimationHaduken(); 
	bool Start();
	update_status Update();

public:

	SDL_Texture* graphics = nullptr;
	iPoint ballposition;
	iPoint position;
	Animation ball;
	Animation idle;

};

#endif
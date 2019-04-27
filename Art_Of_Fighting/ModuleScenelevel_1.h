#ifndef __MODULESCENELEVEL_1_H__
#define __MODULESCENELEVEL_1_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
struct SDL_Texture;

class ModuleScenelevel_1 : public Module
{
private://NEW
	int speed = 3;//NEW
public:
	ModuleScenelevel_1();
	~ModuleScenelevel_1();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphicsLive = nullptr;
	SDL_Texture* graphicsTime = nullptr;

	SDL_Rect lifeFull;
	SDL_Rect liveEmpty;
	SDL_Rect background1;
	SDL_Rect countdown;

	Collider* colliderMap;
	Collider* colliderMap2;
	int Scene1_Fight = 0;
	float foreground_pos;
	bool forward;
	int distance = 0;
	iPoint positionlimitleft;//NEW
	iPoint positionlimitright;//NEW
};

#endif // __MODULESCENELEVEL_1_H__
#ifndef __MODULESCENELEVEL_1_H__
#define __MODULESCENELEVEL_1_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

#define ROUND_TIME 60000

struct SDL_Texture;

class ModuleSceneking : public Module
{
private://NEW
	int speed = 3;//NEW
public:
	ModuleSceneking();
	~ModuleSceneking();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphicsLive = nullptr;
	SDL_Texture* graphicsTime = nullptr;
	SDL_Texture* graphicsUI = nullptr;

	SDL_Rect lifeFull;
	SDL_Rect liveEmpty;
	SDL_Rect background1;
	SDL_Rect countdown;
	SDL_Rect stamina;
	SDL_Rect kingName;
	SDL_Rect picturePlayer;
	SDL_Rect pictureEnemy;

	Collider* colliderMap;
	Collider* colliderMap2;
	int Scene1_Fight = 0;
	float foreground_pos;
	bool forward;
	int distance = 0;
	iPoint positionlimitleft;//NEW
	iPoint positionlimitright;//NEW

	int font_score = -1;
	Uint32 round_timer = 0;

	//////

	char timer_text[10];
	int font_timer = -1;
	uint timer;
	uint endingtimer = 0;
	int starttime;
	int timertime;
	bool matchstart = false;
};

#endif // __MODULESCENELEVEL_1_H__
#ifndef __MODULESCENEWIN_H__
#define __MODULESCENEWIN_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
struct SDL_Texture;

class ModuleScenewin : public Module
{
public:
	ModuleScenewin();
	~ModuleScenewin();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* graphics2 = nullptr;
	SDL_Texture* graphics = nullptr;
	SDL_Rect winimage;
	SDL_Rect winimage2;

	char timer_text[10];
	int font_countdown = -1;
	int timertime;
	uint timer;

	int winLoseMusic = 0;
	
};
#endif // __MODULESCENEWIN_H__

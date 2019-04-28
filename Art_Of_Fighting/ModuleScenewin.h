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
	
};
#endif // __MODULESCENEWIN_H__

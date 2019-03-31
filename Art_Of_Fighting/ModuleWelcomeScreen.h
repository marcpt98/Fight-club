#ifndef __MODULEWELCOMESCREEN_H__
#define __MODULEWELCOMESCREEN_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
struct SDL_Texture;

class ModuleWelcomeScreen: public Module
{
public:
	ModuleWelcomeScreen();
	~ModuleWelcomeScreen();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect Welcomeimage;
	int welcomeScreenMusic = 0;
};
#endif // __MODULEWELCOMESCREEN_H__
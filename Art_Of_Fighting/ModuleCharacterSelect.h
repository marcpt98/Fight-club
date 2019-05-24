#ifndef __MODULECHARACTERSELECT_H__
#define __MODULECHARACTERSELECT_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModuleCharacterSelect : public Module
{
public:
	ModuleCharacterSelect();
	~ModuleCharacterSelect();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics_selection = nullptr;
	SDL_Rect background;

	Animation PlayerSelection;						//to blink the selection
	int welcomeScreenMusic = 0;

private:

	

};

#endif // __MODULECHARACTERSELECT_H__
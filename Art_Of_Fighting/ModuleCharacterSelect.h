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

	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphicsSelection = nullptr;
	SDL_Rect background;
	SDL_Rect SquareP1;
	SDL_Rect SquareP2;
	SDL_Rect SelectPlayer;
	SDL_Rect Todoh;
	SDL_Rect Ryo;
	SDL_Rect Robert;
	SDL_Rect Jack;
	SDL_Rect Lee;
	SDL_Rect King;
	SDL_Rect Micky;
	SDL_Rect John;
	SDL_Rect TodohName;
	SDL_Rect RyoName;
	SDL_Rect RobertName;
	SDL_Rect JackName;
	SDL_Rect LeeName;
	SDL_Rect KingName;
	SDL_Rect MickyName;
	SDL_Rect JohnName;


	iPoint a[4][2];
	iPoint b[4][2];
	iPoint player1;
	iPoint player2;

	
	
	int welcomeScreenMusic = 0;

private:

	

};

#endif // __MODULECHARACTERSELECT_H__
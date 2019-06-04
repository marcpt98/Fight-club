#ifndef __MODULEVERSUS_H__
#define __MODULEVERSUS_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

enum AnimationState
{
	EnterP1,
	EnterP2,
	Donete,
	Terminado
};

struct AnimObject
{
	iPoint position;
	SDL_Rect rect;
};

class ModuleVersus : public Module
{
public:
	ModuleVersus();
	~ModuleVersus();

	bool Start();
	update_status Update();
	bool CleanUp();

	void RenderWords();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphicsKing = nullptr;
	SDL_Rect background;
	int versusFX = 0;
	int versusMusic = 0;
	int kingFX = 0;
	int kingFX2 = 0;
	bool firstFX = false;
	bool secondFX = false;
	bool thirdFX = false;
	int cont = 0;

private:

	AnimObject kingP1;
	AnimObject kingP2;
	AnimObject kingName;
	AnimObject kingNameP2;
	AnimationState animationState;
	int step = 0;
	iPoint finalKingPosition1;
	iPoint finalKingPosition2;

};

#endif // __MODULEWELCOMESCREEN_H__

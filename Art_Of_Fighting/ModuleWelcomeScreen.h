#ifndef __MODULEWELCOMESCREEN_H__
#define __MODULEWELCOMESCREEN_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
struct SDL_Texture;

enum IntroAnimationState
{
	Enter,
	GoBack,
	Fighting,
	Done
};

struct AnimationObject
{
	iPoint position;
	SDL_Rect rect;
	float scale;
};

class ModuleWelcomeScreen: public Module
{
public:
	ModuleWelcomeScreen();
	~ModuleWelcomeScreen();

	bool Start();
	update_status Update();
	bool CleanUp();

	void RenderWords();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* introTexture = nullptr;
	Animation Welcomeimage;
	int welcomeScreenMusic = 0;

private:

	AnimationObject art;
	AnimationObject of;
	AnimationObject fighting;
	IntroAnimationState animationState;
	int step = 0;
	iPoint finalArtPosition1;
	iPoint finalArtPosition2;

};

#endif // __MODULEWELCOMESCREEN_H__
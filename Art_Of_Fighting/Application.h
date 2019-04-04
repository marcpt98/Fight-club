#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 13

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleScenelevel_1;
class ModuleScenelevel_2;
class ModulePlayer;
class ModulePlayer2;
class ModuleFadeToBlack;
class ModuleWelcomeScreen;
class ModuleScenewin;
class ModuleAudio;
class ModuleParticles;
class Module;


class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleScenelevel_1* scene_Todoh;
	ModuleScenelevel_2* scene_Jack;
	ModuleWelcomeScreen* scene_Welcome;
	ModuleScenewin* scene_win;
	ModulePlayer* player;
	ModulePlayer2* player2;
	ModuleFadeToBlack* fade;
	ModuleAudio* audio;
	ModuleParticles* particles;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__
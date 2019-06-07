#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 17

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleSceneking;
class ModulePlayer;
class ModulePlayer2;
class ModuleFadeToBlack;
class ModuleWelcomeScreen;
class ModuleCharacterSelect;
class ModuleVersus;
class ModuleScenewin;
class ModuleAudio;
class ModuleParticles;
class ModuleCollision;
class ModuleAudio;
class ModuleFonts;
class ModuleSlowDownShake;
class Module;


class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleSceneking* scene_King;
	ModuleWelcomeScreen* scene_Welcome;
	ModuleCharacterSelect* scene_selection;
	ModuleVersus* scene_versus;
	ModuleScenewin* scene_win;
	ModulePlayer* player;
	ModulePlayer2* player2;
	ModuleFadeToBlack* fade;
	ModuleAudio* audio;
	ModuleParticles* particles;
	ModuleCollision* collision;
	ModuleFonts* fonts;
	ModuleSlowDownShake* SlowDownShake;

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
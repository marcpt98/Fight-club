#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleSceneking.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleCharacterSelect.h"
#include "ModuleScenewin.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleFonts.h"

Application::Application()
{
	modules[0] = window = new ModuleWindow();
	modules[1] = render = new ModuleRender();
	modules[2] = input = new ModuleInput();
	modules[3] = textures = new ModuleTextures();
	modules[4] = fonts = new ModuleFonts();
	modules[5] = scene_King = new ModuleSceneking();
	modules[6] = scene_Welcome = new ModuleWelcomeScreen();
	modules[7] = scene_selection = new ModuleCharacterSelect();
	modules[8] = scene_win = new ModuleScenewin();
	modules[9] = player = new ModulePlayer();
	modules[10] = player2 = new ModulePlayer2();
	modules[11] = particles = new ModuleParticles();
	modules[12] = collision = new ModuleCollision();
	modules[13] = fade = new ModuleFadeToBlack();
	modules[14] = audio = new ModuleAudio();
	
	
}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	// Player will be enabled on the first update of a new scene
	player->Disable();
	player2->Disable();
	// Disable the map that you do not start with
	scene_King-> Disable();
	scene_win->Disable();
	scene_selection->Disable();
	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneKen.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleScenewin.h"
#include "ModuleWelcomeScreen.h"

ModuleScenewin::ModuleScenewin() {
	winimage = { 0, 0,304,224 };
}

ModuleScenewin::~ModuleScenewin()
{}


bool ModuleScenewin::Start()
{
	LOG("Loading background assets");
	bool ret = true;
 	graphics = App->textures->Load("Victory.png");

	// TODO 1: Enable (and properly disable) the player module
	//App->player->Enable();

	return ret;
}


bool ModuleScenewin::CleanUp()
{
	// TODO 5: Remove all memory leaks
	//SDL_DestroyTexture(graphics);
	LOG("Unloading honda stage");
	App->player->Disable();
	App->textures->Unload(graphics);
	return true;
}

update_status ModuleScenewin::Update()
{
	// Draw everything --------------------------------------	
	App->render->Blit(graphics, 0, 0, &winimage);

	// TODO 2: make so pressing SPACE the KEN stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->scene_win, App->scene_Welcome, 2);
	}

	return UPDATE_CONTINUE;
}
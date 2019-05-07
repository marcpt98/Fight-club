#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneking.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleScenewin.h"
#include "ModuleWelcomeScreen.h"

ModuleScenewin::ModuleScenewin() {
	winimage = { 0, 0,304,224 };
	winimage2= { 0, 0,304,224 };
}

ModuleScenewin::~ModuleScenewin()
{}


bool ModuleScenewin::Start()
{
	LOG("Loading background assets");
	bool ret = true;
 	graphics = App->textures->Load("media/Win/WinCondition.png");
	graphics2 = App->textures->Load("media/Win/WinCondition_P2.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

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
	App->player2->Disable();
	App->textures->Unload(graphics);
	App->textures->Unload(graphics2);
	return true;
}

update_status ModuleScenewin::Update()
{
	// Draw everything --------------------------------------	
	if (App->player->Life > 0 && App->player2->Life > 0) {
		App->render->Blit(graphics, 0, 0, &winimage);
	}

	if (App->player->Life <= App->player2->Life) {
		App->render->Blit(graphics2, 0, 0, &winimage2);
	}
	if (App->player2->Life <= App->player->Life) {
		App->render->Blit(graphics, 0, 0, &winimage);
	}

	// TODO 2: make so pressing SPACE the KEN stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->scene_win, App->scene_Welcome, 2);
	}

	return UPDATE_CONTINUE;
}
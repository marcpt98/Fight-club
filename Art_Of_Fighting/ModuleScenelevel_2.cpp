#include "Globals.h"
#include "Application.h"
#include "ModuleScenelevel_2.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleScenewin.h"
#include "ModuleAudio.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"


// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleScenelevel_2::ModuleScenelevel_2()
{
	// ground
	background2.x = 0;
	background2.y = 0;
	background2.w = 552;
	background2.h = 224;
}

ModuleScenelevel_2::~ModuleScenelevel_2()
{}

// Load assets
bool ModuleScenelevel_2::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("media/level_2.png");
	Scene2_Fight = App->audio->LoadMusic("media/Scene2_Fight.ogg");
	App->audio->PlayMusic(Scene2_Fight);

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	// TODO 1: Enable (and properly disable) the player module
	App->player->Enable();
	App->player2->Enable();
	App->collision->Enable();

	return ret;
}

// Load assets
bool ModuleScenelevel_2::CleanUp()
{
	// TODO 5: Remove all memory leaks
	//SDL_DestroyTexture(graphics);
	LOG("Unloading honda stage");
	App->player->Disable();
	App->player2->Disable();
	App->textures->Unload(graphics);
	App->audio->UnLoadMusic(Scene2_Fight);
	App->collision->Disable();
	return true;
}

// Update: draw background
update_status ModuleScenelevel_2::Update()
{
	// Draw everything --------------------------------------	
	App->render->Blit(graphics, 0, 0, &background2, 0.75f);
	// TODO 2: make so pressing SPACE the KEN stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->scene_Jack, App->scene_Welcome, 2);
	}

	return UPDATE_CONTINUE;
}
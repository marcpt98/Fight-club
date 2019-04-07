#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleScenelevel_1.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleScenelevel_2.h"
#include "ModuleAudio.h"
#include "ModuleSceneWin.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleScenelevel_1::ModuleScenelevel_1()
{
	background1.x = 0;
	background1.y = 0;
	background1.w = 552;
	background1.h = 224;
}

ModuleScenelevel_1::~ModuleScenelevel_1()
{}

// Load assets
bool ModuleScenelevel_1::Start()
{
	LOG("Loading ryo scene");
	
	graphics = App->textures->Load("level_1.png");

	Scene1_Fight = App->audio->LoadMusic("Scene1_Fight.ogg");

	App->audio->PlayMusic(Scene1_Fight);

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	App->player->Enable();
	App->player2->Enable();
	App->collision->Enable();
	return true;
}

// UnLoad assets
bool ModuleScenelevel_1::CleanUp()
{
	LOG("Unloading ryo scene");
	App->player->Disable();
	App->player2->Disable();
	App->textures->Unload(graphics);
	App->collision->Disable();

	App->audio->UnLoadMusic(Scene1_Fight);
	return true;
}

// Update: draw background
update_status ModuleScenelevel_1::Update()
{
	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background1, 0.75f);
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->scene_Todoh, App->scene_win, 2);
	}


	return UPDATE_CONTINUE;
}
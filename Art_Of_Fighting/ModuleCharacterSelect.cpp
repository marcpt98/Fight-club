#include "Globals.h"
#include "Application.h"
#include "ModuleCharacterSelect.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneking.h"
#include "ModuleAudio.h"
#include "ModulePlayer2.h"

ModuleCharacterSelect::ModuleCharacterSelect()
{
	graphics = NULL;
	graphicsUI = NULL;

	background.x = 0;
	background.y = 0;
	background.h = 224;
	background.w = 304;

	SquareP1.x = 155;
	SquareP1.y = 0;
	SquareP1.w = 28;
	SquareP1.h = 31;

	SquareP2.x = 127;
	SquareP2.y = 0;
	SquareP2.w = 28;
	SquareP2.h = 31;

	SelectPlayer.x = 0;
	SelectPlayer.y = 222;
	SelectPlayer.w = 168;
	SelectPlayer.h = 13;
}

ModuleCharacterSelect::~ModuleCharacterSelect()
{}

bool ModuleCharacterSelect::Start()
{
	LOG("Loading background assets");
	bool ret = true;

	graphics = App->textures->Load("media/CharacterSelection/BackgroundSelection.png");
	graphicsUI = App->textures->Load("media/UI/ui.png");

	
	App->audio->PlayMusic(welcomeScreenMusic);

	App->render->camera.x = 0;
	App->render->camera.y = 0;


	return ret;
}

bool ModuleCharacterSelect::CleanUp()
{
	//SDL_DestroyTexture(graphics);
	LOG("Unloading honda stage");
	App->player->Disable();
	App->player2->Disable();
	App->textures->Unload(graphics);
	App->textures->Unload(graphicsUI);
	App->audio->UnLoadMusic(welcomeScreenMusic);



	return true;
}


update_status ModuleCharacterSelect::Update()
{
	

	App->render->Blit(graphics, 0, 0, &background, 0.0);
	App->render->Blit(graphicsUI, 70, 15, &SelectPlayer, 0.0);
	App->render->Blit(graphicsUI, 96, 151, &SquareP1, 0.0);
	App->render->Blit(graphicsUI, 96, 182, &SquareP2, 0.0);


	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->scene_selection, App->scene_King, 2);
	}
	if (SDL_GameControllerGetButton(App->input->gGameController2, SDL_CONTROLLER_BUTTON_START) == 1)
	{
		App->fade->FadeToBlack(App->scene_selection, App->scene_King, 2);
	}
	if (SDL_GameControllerGetButton(App->input->gGameController, SDL_CONTROLLER_BUTTON_START) == 1)
	{
		App->fade->FadeToBlack(App->scene_selection, App->scene_King, 2);
	}

	return UPDATE_CONTINUE;
}


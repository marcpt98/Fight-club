#include "Globals.h"
#include "Application.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleCharacterSelect.h"
#include "ModuleSceneking.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModulePlayer2.h"
#include "ModuleVersus.h"


ModuleVersus::ModuleVersus()
{
	graphics = NULL;
	graphicsKing = NULL;

	background.x = 0;
	background.y = 0;
	background.h = 224;
	background.w = 304;

	kingP1.rect = { 250,143,121,123 };
	kingP2.rect = { 0,342,122,123 };

	kingName.rect = { 288,267,53,15 };
	kingNameP2.rect = { 288,267,53,15 };


}

ModuleVersus::~ModuleVersus()
{}

bool ModuleVersus::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	
	kingP1.position = { -115, 10 };
	kingP2.position = { 398, 10 };
	kingName.position = { -80, 140 };
	kingNameP2.position = { 398, 140 };
	finalKingPosition1 = { 3 , 0 };
	finalKingPosition2 = { -2 , 0 };
	animationState = EnterP1;
	step = 0;

	graphics = App->textures->Load("media/CharacterSelection/BackgroundVS.png");
	graphicsKing = App->textures->Load("media/CharacterSelection/portraits.png");

	
	versusFX = App->audio->LoadFX("media/FX/Versus.wav");
	

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	
	firstFX = true;

	return ret;
}

bool ModuleVersus::CleanUp()
{
	//SDL_DestroyTexture(graphics);
	LOG("Unloading honda stage");
	App->player->Disable();
	App->player2->Disable();
	App->textures->Unload(graphics);
	App->textures->Unload(graphicsKing);
	App->audio->UnLoadFX(versusFX);



	return true;
}

void ModuleVersus::RenderWords()
{
	
	App->render->Blit(graphicsKing, kingP1.position.x, kingP1.position.y, &(kingP1.rect));
	App->render->Blit(graphicsKing, kingP2.position.x, kingP2.position.y, &(kingP2.rect));
	App->render->Blit(graphicsKing, kingName.position.x, kingName.position.y, &(kingName.rect));
	App->render->Blit(graphicsKing, kingNameP2.position.x, kingNameP2.position.y, &(kingNameP2.rect));

}


update_status ModuleVersus::Update()
{
	App->render->Blit(graphics, 0, 0, &background, 0.0);

	if(firstFX == true)
	{
		App->audio->PlayFX(versusFX);
		firstFX = false;
	}

	switch (animationState)
	{
	case EnterP1:
		kingP1.position += finalKingPosition1;
		kingName.position += finalKingPosition1;
		step++;
		if (step >= 40)
		{
			animationState = EnterP2;
			step = 0;
		}
		RenderWords();
		break;
	case EnterP2:
		kingP2.position += {-9, 0};
		kingNameP2.position += {-9, 0};
		step++;
		if (step >= 20)
		{
			step = 0;
			animationState = Donete;
		}
		RenderWords();
		break;
	case Donete:
		kingP2.position += finalKingPosition2;
		step++;
		if (step >= 20)
		{
			animationState = Terminado;
		}
		RenderWords();
		break;
	case Terminado:
		RenderWords();
		break;
	default:
		break;
	}

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->scene_versus, App->scene_King, 2);
	}
	if (SDL_GameControllerGetButton(App->input->gGameController2, SDL_CONTROLLER_BUTTON_START) == 1)
	{
		App->fade->FadeToBlack(App->scene_versus, App->scene_King, 2);
	}
	if (SDL_GameControllerGetButton(App->input->gGameController, SDL_CONTROLLER_BUTTON_START) == 1)
	{
		App->fade->FadeToBlack(App->scene_versus, App->scene_King, 2);
	}


	return UPDATE_CONTINUE;
}
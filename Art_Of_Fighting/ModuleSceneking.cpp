#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneking.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleSceneWin.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleFonts.h"
#include <stdio.h>


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneking::ModuleSceneking()
{
	graphics = NULL;
	graphicsLive = NULL;
	graphicsTime = NULL;
	graphicsUI = NULL;

	background1.x = 0;
	background1.y = 0;
	background1.w = 552;
	background1.h = 224;

	lifeFull.x = 0;
	lifeFull.y = 0;
	lifeFull.w = 129;
	lifeFull.h = 8;

	liveEmpty.x = 0;
	liveEmpty.y = 8;
	liveEmpty.w = 129;
	liveEmpty.h = 8;

	countdown.x = 0;
	countdown.y = 0;
	countdown.w = 32;
	countdown.h = 24;

	stamina.x = 0;
	stamina.y = 0;
	stamina.w = 127;
	stamina.h = 8;

	kingName.x = 0;
	kingName.y = 8;
	kingName.w = 32;
	kingName.h = 8;

	picturePlayer.x = 0;
	picturePlayer.y = 16;
	picturePlayer.w = 24;
	picturePlayer.h = 25;

	pictureEnemy.x = 0;
	pictureEnemy.y = 41;
	pictureEnemy.w = 24;
	pictureEnemy.h = 25;

	beatBy.x = 0;
	beatBy.y = 66;
	beatBy.w = 72;
	beatBy.h = 13;

	Round1.x = 0;
	Round1.y = 94;
	Round1.w = 100;
	Round1.h = 16;

	Round2.x = 0;
	Round2.y = 110;
	Round2.w = 104;
	Round2.h = 16;

	Fight.x = 47;
	Fight.y = 8;
	Fight.w = 80;
	Fight.h = 16;

	Shadow.x = 46;
	Shadow.y = 28;
	Shadow.w = 79;
	Shadow.h = 15;
	
	player1Win.x = 0;
	player1Win.y = 142;
	player1Win.w = 116;
	player1Win.h = 40;

	player2Win.x = 0;
	player2Win.y = 182;
	player2Win.w = 120;
	player2Win.h = 40;

	FinalRound.x = 0;
	FinalRound.y = 126;
	FinalRound.w = 167;
	FinalRound.h = 16;

	ball.x = 30;
	ball.y = 79;
	ball.w = 14;
	ball.h = 15;

}

ModuleSceneking::~ModuleSceneking()
{}

// Load assets
bool ModuleSceneking::Start()
{
	
	LOG("Loading ryo scene");

	graphics = App->textures->Load("media/Stages/stage_king.png");
	graphicsLive = App->textures->Load("media/UI/live.png");
	graphicsTime = App->textures->Load("media/UI/countdown.png");
	graphicsUI = App->textures->Load("media/UI/ui.png");

	//Scene_king = App->audio->LoadMusic("media/Music/king_stage.ogg");
	end = App->audio->LoadFX("media/FX/king_win.wav");

	App->player->Life = 100;
	App->player2->Life = 100;

	App->audio->PlayMusic(Scene_king);

	App->render->camera.x = -315;
	App->render->camera.y = 0;
	App->player->Enable();
	App->player2->Enable();
	App->collision->Enable();
	
	if (RoundsWinP1 == 1 && RoundsWinP2 == 1)
	{
		RoundStart = false;
		Round2Start = false;
		FinalRoundStart = true;
	}
	else if (RoundsWinP1 == 1 && RoundsWinP2 == 0 || RoundsWinP1 == 0 && RoundsWinP2 == 1)
	{
		RoundStart = false;
		Round2Start = true;
		FinalRoundStart = false;
	} 
	else
	{
		RoundStart = true;
		Round2Start = false;
		FinalRoundStart = false;
	}

	

	positionlimitleft.x = 133;//NEW
	positionlimitleft.y = -150;//NEW
	positionlimitright.x = 250;//NEW
	positionlimitright.y = -150;//NEW
	//Scene limits from left and right
	colliderMap = App->collision->AddCollider({ positionlimitleft.x, positionlimitleft.y, 15, 500 }, COLLIDER_WALL, this);//NEW
	colliderMap2 = App->collision->AddCollider({ positionlimitright.x, positionlimitright.y , 15, 500 }, COLLIDER_WALL, this);//NEW

	// TODO 0: Notice how a font is loaded and the meaning of all its arguments 
	font_score = App->fonts->Load("media/UI/numbers.png", "0123456789", 1);
	timer = 60;
	starttime = SDL_GetTicks();
	endingtimer = 0;
	matchforP1 = false;
	playFX = true;


	return true;
}

// UnLoad assets
bool ModuleSceneking::CleanUp()
{
	LOG("Unloading ryo scene");
	App->player->Disable();
	App->player2->Disable();
	App->textures->Unload(graphics);
	App->textures->Unload(graphicsLive);
	App->textures->Unload(graphicsUI);
	App->collision->Disable();

	App->audio->UnLoadMusic(Scene_king);
	App->audio->UnLoadFX(end);

	return true;
}

// Update: draw background
update_status ModuleSceneking::Update()
{
	if (Zoom == false) {
		distance = ((App->player->position.x + App->player2->position.x) / 2);
		App->render->camera.x = (distance*-1 + 125);

		if (App->render->camera.x <= -330) {
			App->render->camera.x = -330;
		}
		if (App->render->camera.x >= 0) {
			App->render->camera.x = 0;
		}
		colliderMap->SetPos((((App->render->camera.x*-1) - 10)), positionlimitleft.y);//NEW
		colliderMap2->SetPos((((App->render->camera.x*-1) + 300)), positionlimitleft.y);//NEW
	}


	if (Zoom == true) {
		camera2= ((App->player->position.x + App->player2->position.x) / 2);
		App->render->camera.x = ((camera2*-1+90)*1.3);

		if (App->render->camera.x <= -530) {
			App->render->camera.x = -530;
		}
		if (App->render->camera.x >= 0) {
			App->render->camera.x = 0;
		}
		colliderMap->SetPos((((App->render->camera.x*-1) - 10)), positionlimitleft.y);//NEW
		colliderMap2->SetPos((((App->render->camera.x*-1) + 300)), positionlimitleft.y);//NEW
	}

	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background1, 0.75f);
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->scene_King, App->scene_win, 2);
	}
	if (SDL_GameControllerGetButton(App->input->gGameController2, SDL_CONTROLLER_BUTTON_START) == 1)
	{
		App->fade->FadeToBlack(App->scene_King, App->scene_win, 2);
	}
	if (SDL_GameControllerGetButton(App->input->gGameController, SDL_CONTROLLER_BUTTON_START) == 1)
	{
		App->fade->FadeToBlack(App->scene_King, App->scene_win, 2);
	}

	if (App->scene_King->Zoom == true) {
		App->scene_King->Zoom = false;   //this works for not making zoom to the UI
		zoomcounter = true;
	}
	//Draw life
	App->render->BlitWithScale(graphicsLive, 138, 15, &liveEmpty, -1, 0.0f, 1.0f, TOP_RIGHT);

	App->render->BlitWithScale(graphicsLive, 138, 15, &lifeFull, -1, 0.0f, App->player->Life / App->player->MaxLife, TOP_RIGHT);

	App->render->BlitWithScale(graphicsLive, 166, 15, &liveEmpty, -1, 0.0f, 1.0f, TOP_LEFT);

	App->render->BlitWithScale(graphicsLive, 166, 15, &lifeFull, 1, 0.0f, App->player2->Life / App->player2->MaxLife, TOP_LEFT);

	//Draw Stamina

	App->render->BlitWithScale(graphicsUI, 138, 23, &stamina, -1, 0.0f, App->player->Stamina / App->player->MaxStamina, TOP_RIGHT);

	App->render->BlitWithScale(graphicsUI, 166, 23, &stamina, 1, 0.0f, App->player2->Stamina / App->player2->MaxStamina, TOP_LEFT);

	//Draw Time
	App->render->BlitWithScale(graphicsTime, 168, 7, &countdown, 1, 0.0f, 1.0f, TOP_RIGHT);

	//Draw KingName
	App->render->BlitWithScale(graphicsUI, 74, 31, &kingName, 1, 0.0f, 1.0f, TOP_RIGHT);
	App->render->BlitWithScale(graphicsUI, 263, 31, &kingName, 1, 0.0f, 1.0f, TOP_RIGHT);

	//Draw Picture of King
	App->render->BlitWithScale(graphicsUI, 42, 32, &picturePlayer, 1, 0.0f, 1.0f, TOP_RIGHT);
	App->render->BlitWithScale(graphicsUI, 286, 32, &pictureEnemy, 1, 0.0f, 1.0f, TOP_RIGHT);

	//Draw beat by 0
	App->render->BlitWithScale(graphicsUI, 97, 2, &beatBy, 1, 0.0f, 1.0f, TOP_RIGHT);
	App->render->BlitWithScale(graphicsUI, 278, 2, &beatBy, 1, 0.0f, 1.0f, TOP_RIGHT);

	if (zoomcounter == true) {
		App->scene_King->Zoom = true; //this ALSO works for not making zoom to the UI
		zoomcounter = false;
	}
	//Draw Fight!
	//App->render->BlitWithScale(graphicsUI, 210, 90, &Fight, 1, 0.0f, 1.0f, TOP_RIGHT);
	

	//Draw Shadows!
	if((SDL_GetTicks() - starttime) % 2 == 0)
	{
		App->render->Blit(graphicsUI, App->player->position.x-10, 203, &Shadow, 1.0);
	}
	else
	{
		App->render->Blit(graphicsUI, App->player2->position.x - 10, 203, &Shadow, 1.0);
	}	


	//Draw Round 1
	if (App->scene_King->Zoom == true) {
		App->scene_King->Zoom = false;   //this works for not making zoom to the UI
		zoomcounter = true;
	}
	if (RoundStart == true)
	{
		App->render->BlitWithScale(graphicsUI, 210, 90, &Round1, 1, 0.0f, 1.0f, TOP_RIGHT);
	}

	//Draw Round 2

	if (Round2Start == true)
	{
		App->render->BlitWithScale(graphicsUI, 210, 90, &Round2, 1, 0.0f, 1.0f, TOP_RIGHT);
	}

	//Draw FinalRound
	if (FinalRoundStart == true)
	{
		App->render->BlitWithScale(graphicsUI, 240, 90, &FinalRound, 1, 0.0f, 1.0f, TOP_RIGHT);
	}
	if (zoomcounter == true) {
		App->scene_King->Zoom = true; //this ALSO works for not making zoom to the UI
		zoomcounter = false;
	}

	//Initialize Countdown
	if (matchstart == false)
	{
		if (SDL_GetTicks() - starttime >= 1500)
		{
			timertime = SDL_GetTicks();
			matchstart = true;
		}
		
	}

	//Makes disappear Round2 Rectangle
	if (SDL_GetTicks() - starttime >= 1500)
	{
		RoundStart = false;

	}

	//Makes disappear Round2 Rectangle
	if (SDL_GetTicks() - starttime >= 1500)
	{
		Round2Start = false;

	}

	//Makes disappear FinalRound Rectangle
	if (SDL_GetTicks() - starttime >= 1500)
	{
		FinalRoundStart = false;
	}


	//Countdown 
	if (SDL_GetTicks() - timertime >= 1000)
	{
		timertime = SDL_GetTicks();
		timer--;
	} 

	sprintf_s(timer_text, 10, "%d", timer);

	if(timer < 10)
	{
		timer_text[2] = timer_text[1];
		timer_text[1] = timer_text[0];
		timer_text[0] = '0';
	}

	App->fonts->BlitText(137, 8, font_score, timer_text);


	//PLAYER 1 /PLAYER 2 WINS
	if (App->player2->Life <= 0)
	{
		App->input->inputs2.Push(IN_DEFEAT2);
		App->input->inputs.Push(IN_WIN);
		
		matchforP1 = true;

		if (playFX)App->audio->PlayFX(end); playFX = false;

		if (endingtimer == 0)endingtimer = SDL_GetTicks();
		if (SDL_GetTicks() - endingtimer >= 3000)App->fade->FadeToBlack(App->scene_King, App->scene_win, 5);
	}

	if (App->player->Life <= 0)
	{
		App->input->inputs2.Push(IN_WIN2);
		App->input->inputs.Push(IN_DEFEAT);
		
		matchforP2 = true;

		if (playFX)App->audio->PlayFX(end); playFX = false;

		if (endingtimer == 0)endingtimer = SDL_GetTicks();
		if (SDL_GetTicks() - endingtimer >= 4000)App->fade->FadeToBlack(App->scene_King, App->scene_win, 5);
	}

	if (App->scene_King->matchforP1 == true)
	{
		App->render->BlitWithScale(graphicsUI, 210, 70, &player1Win, 1, 0.0f, 1.0f, TOP_RIGHT);
	}

	if (App->scene_King->matchforP2 == true)
	{
		App->render->BlitWithScale(graphicsUI, 210, 70, &player2Win, 1, 0.0f, 1.0f, TOP_RIGHT);
	}

	//System of Rounds
	/*
	if(timer <= 0 || App->player->Life == 0 || App->player2->Life == 0)
	{
		
		if(App->player->Life > App->player2->Life || App->player2->Life == 0)
		{
			App->render->BlitWithScale(graphicsUI, 210, 70, &player1Win, 1, 0.0f, 1.0f, TOP_RIGHT);
			RoundsWinP1++;
		}
		if(App->player->Life < App->player2->Life || App->player->Life == 0)
		{
			App->render->BlitWithScale(graphicsUI, 210, 70, &player2Win, 1, 0.0f, 1.0f, TOP_RIGHT);
			RoundsWinP2++;
		}

		if (RoundsWinP1 == 1 && RoundsWinP2 == 0 || RoundsWinP1 == 0 && RoundsWinP2 == 1)
		{
			App->fade->FadeToBlack(App->scene_King, App->scene_King, 2);
		}

		if (RoundsWinP1 == 1 && RoundsWinP2 == 1)
		{
			App->fade->FadeToBlack(App->scene_King, App->scene_King, 2);
			
		}

		if (RoundsWinP1 == 2 || RoundsWinP2 == 2)
		{
			App->fade->FadeToBlack(App->scene_King, App->scene_win, 2);
			RoundsWinP1 = 0;
			RoundsWinP2 = 0;
		}
		
	}
	*/

	if (App->player->position.x >= App->player2->position.x - 120 && App->player->position.x <= App->player2->position.x + 120) {
		Zoom = true;
	}
	else(Zoom = false);


	return UPDATE_CONTINUE;
}
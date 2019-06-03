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
#include "ModuleVersus.h"

ModuleCharacterSelect::ModuleCharacterSelect()
{
	graphics = NULL;
	graphicsSelection = NULL;

	background.x = 0;
	background.y = 0;
	background.h = 224;
	background.w = 304;

	SquareP1.x = 28;
	SquareP1.y = 302;
	SquareP1.w = 28;
	SquareP1.h = 31;

	SquareP2.x = 0;
	SquareP2.y = 302;
	SquareP2.w = 28;
	SquareP2.h = 31;

	SelectPlayer.x = 0;
	SelectPlayer.y = 289;
	SelectPlayer.w = 168;
	SelectPlayer.h = 13;

	Todoh.x = 0;
	Todoh.y = 0;
	Todoh.w = 128;
	Todoh.h = 125;

	Ryo.x = 128;
	Ryo.y = 0;
	Ryo.w = 128;
	Ryo.h = 123;

	Robert.x = 256;
	Robert.y = 0;
	Robert.w = 125;
	Robert.h = 119;

	Jack.x = 381;
	Jack.y = 0;
	Jack.w = 129;
	Jack.h = 122;

	Lee.x = 128;
	Lee.y = 139;
	Lee.w = 122;
	Lee.h = 127;

	King.x = 250;
	King.y = 143;
	King.w = 121;
	King.h = 123;

	Micky.x = 371;
	Micky.y = 142;
	Micky.w = 128;
	Micky.h = 124;

	John.x = 0;
	John.y = 141;
	John.w = 128;
	John.h = 128;

	TodohName.x = 35;
	TodohName.y = 126;
	TodohName.w = 57;
	TodohName.h = 15;

	RyoName.x = 170;
	RyoName.y = 124;
	RyoName.w = 44;
	RyoName.h = 15;

	RobertName.x = 280;
	RobertName.y = 120;
	RobertName.w = 80;
	RobertName.h = 15;

	JackName.x = 417;
	JackName.y = 123;
	JackName.w = 58;
	JackName.h = 15;

	LeeName.x = 172;
	LeeName.y = 267;
	LeeName.w = 42;
	LeeName.h = 15;

	KingName.x = 288;
	KingName.y = 267;
	KingName.w = 53;
	KingName.h = 15;

	MickyName.x = 395;
	MickyName.y = 267;
	MickyName.w = 64;
	MickyName.h = 15;

	JohnName.x = 34;
	JohnName.y = 270;
	JohnName.w = 58;
	JohnName.h = 15;

	a[0][0] = { 96, 151 };
	a[0][1] = { 96, 179 };
	a[1][0] = { 124, 151 };
	a[1][1] = { 124, 179 };
	a[2][0] = { 152, 151 };
	a[2][1] = { 152, 179 };
	a[3][0] = { 180, 151 };
	a[3][1] = { 180, 179 };

	b[0][0] = { 96, 154 };
	b[0][1] = { 96, 182 };
	b[1][0] = { 124, 154 };
	b[1][1] = { 124, 182 };
	b[2][0] = { 152, 154 };
	b[2][1] = { 152, 182 };
	b[3][0] = { 180, 154 };
	b[3][1] = { 180, 182 };

	player1 = { 0, 0 };
	player2 = { 1, 1 };

}

ModuleCharacterSelect::~ModuleCharacterSelect()
{}

bool ModuleCharacterSelect::Start()
{
	LOG("Loading background assets");
	bool ret = true;

	graphics = App->textures->Load("media/CharacterSelection/BackgroundSelection.png");
	graphicsSelection = App->textures->Load("media/CharacterSelection/portraits.png");

	
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
	App->textures->Unload(graphicsSelection);
	App->audio->UnLoadMusic(welcomeScreenMusic);



	return true;
}


update_status ModuleCharacterSelect::Update()
{
	

	App->render->Blit(graphics, 0, 0, &background, 0.0);


	//Ipoint Player 1
	if (App->input->right)
	{
		player1.x += 1;

		if (player1.x > 3)
		{
			player1.x = 3;
		}

		App->input->right = false;
	}

	if (App->input->left)
	{
		player1.x -= 1;

		if (player1.x < 0)
		{
			player1.x = 0;
		}

		App->input->left = false;
	}

	if (App->input->up)
	{
		player1.y -= 1;

		if (player1.y < 0)
		{
			player1.y = 0;
		}

		App->input->up = false;
	}

	if (App->input->down)
	{
		player1.y += 1;

		if (player1.y > 1)
		{
			player1.y = 1;
		}

		App->input->down = false;
	}

	App->render->Blit(graphicsSelection, a[player1.x][player1.y].x, a[player1.x][player1.y].y, &SquareP1, 0.0);

	//Ipoint Player 2

	if (App->input->right2)
	{
		player2.x += 1;

		if (player2.x > 3)
		{
			player2.x = 3;
		}

		App->input->right2 = false;
	}

	if (App->input->left2)
	{
		player2.x -= 1;

		if (player2.x < 0)
		{
			player2.x = 0;
		}

		App->input->left2 = false;
	}

	if (App->input->up2)
	{
		player2.y -= 1;

		if (player2.y < 0)
		{
			player2.y = 0;
		}

		App->input->up2 = false;
	}

	if (App->input->down2)
	{
		player2.y += 1;

		if (player2.y > 1)
		{
			player2.y = 1;
		}

		App->input->down2 = false;
	}

	App->render->Blit(graphicsSelection, b[player2.x][player2.y].x, b[player2.x][player2.y].y, &SquareP2, 0.0);

	//Blit Portraits Player 1

	if(a[player1.x][player1.y] == a[0][0])
	{
		App->render->Blit(graphicsSelection, 20, 8, &Todoh, 0.0);
		App->render->Blit(graphicsSelection, 55, 136, &TodohName, 0.0);
	}
	if (a[player1.x][player1.y] == a[1][0])
	{
		App->render->Blit(graphicsSelection, 20, 10, &Ryo, 0.0);
		App->render->Blit(graphicsSelection, 65, 136, &RyoName, 0.0);
	}
	if (a[player1.x][player1.y] == a[2][0])
	{
		App->render->Blit(graphicsSelection, 20, 14, &Robert, 0.0);
		App->render->Blit(graphicsSelection, 46, 136, &RobertName, 0.0);
	}
	if (a[player1.x][player1.y] == a[3][0])
	{
		App->render->Blit(graphicsSelection, 20, 11, &Jack, 0.0);
		App->render->Blit(graphicsSelection, 55, 136, &JackName, 0.0);
	}
	if (a[player1.x][player1.y] == a[0][1])
	{
		App->render->Blit(graphicsSelection, 20, 6, &Lee, 0.0);
		App->render->Blit(graphicsSelection, 60, 136, &LeeName, 0.0);
	}
	if (a[player1.x][player1.y] == a[1][1])
	{
		App->render->Blit(graphicsSelection, 20, 10, &King, 0.0);
		App->render->Blit(graphicsSelection, 55, 136, &KingName, 0.0);
	}
	if (a[player1.x][player1.y] == a[2][1])
	{
		App->render->Blit(graphicsSelection, 20, 9, &Micky, 0.0);
		App->render->Blit(graphicsSelection, 55, 136, &MickyName, 0.0);
	}
	if (a[player1.x][player1.y] == a[3][1])
	{
		App->render->Blit(graphicsSelection, 20, 5, &John, 0.0);
		App->render->Blit(graphicsSelection, 55, 136, &JohnName, 0.0);
	}
	

	//Blit Portraits Player 2
	if (b[player2.x][player2.y] == b[0][0])
	{
		App->render->BlitWithScale(graphicsSelection, 280, 8, &Todoh, -1, 0.0f, 1.0f, TOP_RIGHT);
		App->render->Blit(graphicsSelection, 185, 136, &TodohName, 0.0);
	}
	if (b[player2.x][player2.y] == b[1][0])
	{
		App->render->BlitWithScale(graphicsSelection, 280, 10, &Ryo, -1, 0.0f, 1.0f, TOP_RIGHT);
		App->render->Blit(graphicsSelection, 195, 136, &RyoName, 0.0);
	}
	if (b[player2.x][player2.y] == b[2][0])
	{
		App->render->BlitWithScale(graphicsSelection, 280, 14, &Robert, -1, 0.0f, 1.0f, TOP_RIGHT);
		App->render->Blit(graphicsSelection, 176, 136, &RobertName, 0.0);
	}
	if (b[player2.x][player2.y] == b[3][0])
	{
		App->render->BlitWithScale(graphicsSelection, 280, 11, &Jack, -1, 0.0f, 1.0f, TOP_RIGHT);
		App->render->Blit(graphicsSelection, 185, 136, &JackName, 0.0);
	}
	if (b[player2.x][player2.y] == b[0][1])
	{
		App->render->BlitWithScale(graphicsSelection, 280, 6, &Lee, -1, 0.0f, 1.0f, TOP_RIGHT);
		App->render->Blit(graphicsSelection, 190, 136, &LeeName, 0.0);
	}
	if (b[player2.x][player2.y] == b[1][1])
	{
		App->render->BlitWithScale(graphicsSelection, 280, 10, &King, -1, 0.0f, 1.0f, TOP_RIGHT);
		App->render->Blit(graphicsSelection, 185, 136, &KingName, 0.0);
	}
	if (b[player2.x][player2.y] == b[2][1])
	{
		App->render->BlitWithScale(graphicsSelection, 280, 9, &Micky, -1, 0.0f, 1.0f, TOP_RIGHT);
		App->render->Blit(graphicsSelection, 185, 136, &MickyName, 0.0);
	}
	if (b[player2.x][player2.y] == b[3][1])
	{
		App->render->BlitWithScale(graphicsSelection, 280, 5, &John, -1, 0.0f, 1.0f, TOP_RIGHT);
		App->render->Blit(graphicsSelection, 185, 136, &JohnName, 0.0);
	}

	App->render->Blit(graphicsSelection, 70, 15, &SelectPlayer, 0.0);


	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->scene_selection, App->scene_versus, 2);
	}
	if (SDL_GameControllerGetButton(App->input->gGameController2, SDL_CONTROLLER_BUTTON_START) == 1)
	{
		App->fade->FadeToBlack(App->scene_selection, App->scene_versus, 2);
	}
	if (SDL_GameControllerGetButton(App->input->gGameController, SDL_CONTROLLER_BUTTON_START) == 1)
	{
		App->fade->FadeToBlack(App->scene_selection, App->scene_versus, 2);
	}

	return UPDATE_CONTINUE;
}


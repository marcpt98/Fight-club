#include "Globals.h"
#include "Application.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleScenelevel_1.h"
#include "ModuleAudio.h"
#include "ModulePlayer2.h"

ModuleWelcomeScreen::ModuleWelcomeScreen()
{
	Welcomeimage.PushBack({ 35, 22, 304, 224 });
	Welcomeimage.PushBack({ 344, 22, 304, 224 });
	Welcomeimage.speed = 0.05f;

	art.rect = { 0, 0, 100, 78 };
	of.rect = { 101, 0, 94, 63 };
	fighting.rect = { 0, 80, 200, 75 };
}

ModuleWelcomeScreen::~ModuleWelcomeScreen()
{}

bool ModuleWelcomeScreen::Start()
{
	LOG("Loading background assets");
	bool ret = true;

	art.position = { -94, 16 };
	of.position = { SCREEN_WIDTH / 3, 24 };
	fighting.position = { 50, 300 };
	of.scale = 0.0f;
	finalArtPosition1 = { 230 / 40 , 0 };
	finalArtPosition2 = { 2 , 0 };
	animationState = Enter;
	step = 0;

	graphics = App->textures->Load("welcomescreen.png");
	introTexture = App->textures->Load("introtitle.png");
	welcomeScreenMusic = App->audio->LoadMusic("welcomescreen.ogg");

	App->audio->PlayMusic(welcomeScreenMusic);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	// TODO 1: Enable (and properly disable) the player module
	//App->player->Enable();
	
	return ret;
}

bool ModuleWelcomeScreen::CleanUp()
{
	// TODO 5: Remove all memory leaks
	//SDL_DestroyTexture(graphics);
	LOG("Unloading honda stage");
	App->player->Disable();
	App->player2->Disable();
	App->textures->Unload(graphics);
	App->audio->UnLoadMusic(welcomeScreenMusic);
	return true;
}

void ModuleWelcomeScreen::RenderWords()
{
	App->render->BlitWithScale(introTexture, of.position.x, of.position.y, &(of.rect), of.scale, 1.0f, MIDDLE);
	App->render->Blit(introTexture, art.position.x, art.position.y, &(art.rect));
	App->render->Blit(introTexture, fighting.position.x, fighting.position.y, &(fighting.rect));
	App->render->DrawQuad({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, 255, 255, 255, 255 * (1 - of.scale), true);
}

update_status ModuleWelcomeScreen::Update()
{
	// Draw everything --------------------------------------
	switch (animationState)
	{
		case Enter:
			art.position += finalArtPosition1;
			of.scale += 0.02f;
			step++;
			if(step >= 40)
			{
				animationState = GoBack;	
				step = 0;
			}
			RenderWords();
			break;
		case GoBack:
			art.position -= finalArtPosition2;
			of.scale += 0.02f;
			fighting.position += {0, -4};

			step++;
			if (step >= 20)
			{
				step = 0;
				animationState = Fighting;
			}
			RenderWords();
			break;
		case Fighting:
			fighting.position += {0, -7};
			step++;
			if (step >= 20)
			{
				animationState = Done;
			}
			RenderWords();
			break;
		case Done:
			//RenderWords();
			App->render->Blit(graphics, 0, 0, &(Welcomeimage.GetCurrentFrame()));
			break;
	default:
		break;
	}
	
	// TODO 2: make so pressing SPACE the KEN stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->scene_Welcome,App->scene_Todoh, 2);
	}

	return UPDATE_CONTINUE;
}


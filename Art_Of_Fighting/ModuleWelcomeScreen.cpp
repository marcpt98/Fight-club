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

	art.position = { -100, 15 };
	of.position = { SCREEN_WIDTH / 3, 35 };
	fighting.position = { 50, 200 };
	of.scale = 0.0f;


}


ModuleWelcomeScreen::~ModuleWelcomeScreen()
{}

bool ModuleWelcomeScreen::Start()
{
	LOG("Loading background assets");
	bool ret = true;
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

update_status ModuleWelcomeScreen::Update()
{
	// Draw everything --------------------------------------	


	if(art.position.x < SCREEN_WIDTH /2 - art.rect.w)
	{
		App->render->BlitWithScale(introTexture, of.position.x, of.position.y, &(of.rect), of.scale);
		App->render->Blit(introTexture, art.position.x, art.position.y, &(art.rect));
		App->render->Blit(introTexture, fighting.position.x, fighting.position.y, &(fighting.rect));

		of.scale += 0.01f;
		art.position.x += 2;
		fighting.position.y -= 2;
		App->render->DrawQuad({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, 255, 255, 255, 255 * (1- of.scale), true);

	}
	else
	{
		App->render->Blit(graphics, 0, 0, &(Welcomeimage.GetCurrentFrame()));
	}


	// TODO 2: make so pressing SPACE the KEN stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->scene_Welcome,App->scene_Todoh, 2);
	}

	return UPDATE_CONTINUE;
}
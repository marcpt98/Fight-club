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
	background.x = 0;
	background.y = 0;
	background.h = 224;
	background.w = 304;


}

ModuleCharacterSelect::~ModuleCharacterSelect()
{}

bool ModuleCharacterSelect::Start()
{
	LOG("Loading background assets");
	bool ret = true;

	graphics_selection = App->textures->Load("media/CharacterSelection/BackgroundSelection.png");
	/*introTexture = App->textures->Load("media/WelcomeScreen/introtitle.png");
	welcomeScreenMusic = App->audio->LoadMusic("media/Music/welcomescreen.ogg");

	
	App->audio->PlayMusic(welcomeScreenMusic);*/

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
	App->textures->Unload(graphics_selection);
	App->audio->UnLoadMusic(welcomeScreenMusic);



	return true;
}

//void ModuleCharacterSelect::RenderWords()
//{
//	/*App->render->BlitWithScale(introTexture, of.position.x, of.position.y, &(of.rect), of.scale, 1.0f, 1.0f, MIDDLE);
//	App->render->Blit(introTexture, art.position.x, art.position.y, &(art.rect));
//	App->render->Blit(introTexture, fighting.position.x, fighting.position.y, &(fighting.rect));*/
//	//App->render->DrawQuad({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, 255, 255, 255, 255 * (1 - of.scale), true);
//}

update_status ModuleCharacterSelect::Update()
{
	// Draw everything --------------------------------------
	//switch (animationState)
	//{
	//case Enter:
	//	art.position += finalArtPosition1;
	//	of.scale += 0.02f;
	//	step++;
	//	if (step >= 40)
	//	{
	//		animationState = GoBack;
	//		step = 0;
	//	}
	//	RenderWords();
	//	break;
	//case GoBack:
	//	art.position -= finalArtPosition2;
	//	of.scale += 0.02f;
	//	fighting.position += {0, -4};

	//	step++;
	//	if (step >= 20)
	//	{
	//		step = 0;
	//		animationState = Fighting;
	//	}
	//	RenderWords();
	//	break;
	//case Fighting:
	//	fighting.position += {0, -7};
	//	step++;
	//	if (step >= 20)
	//	{
	//		animationState = Done;
	//	}
	//	RenderWords();
	//	break;
	//case Done:
	//	//RenderWords();
	//	App->render->Blit(graphics, 0, 0, &(Welcomeimage.GetCurrentFrame()));
	//	break;
	//default:
	//	break;
	//}

	App->render->Blit(graphics_selection, 0, 0, &background);

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


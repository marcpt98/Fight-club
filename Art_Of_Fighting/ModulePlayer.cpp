#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	position.x = 100;
	position.y = 210;

	// idle animation (arcade sprite sheet)
	idle.PushBack({ 0, 10, 66, 106 });
	idle.PushBack({ 66, 10, 67, 106 });
	idle.PushBack({ 133, 9, 69, 107 });
	idle.speed = 0.13f;


	//jump animation(arcade sprite sheet)
	jump.PushBack({ 0,504,60,82 });
	jump.PushBack({ 60,456,65,129 });
	jump.PushBack({ 126,473,61,112 });
	jump.PushBack({ 188,476,57,109 });
	jump.PushBack({ 245,495,53,90 });
	jump.PushBack({ 299,471,56,114 });
	jump.PushBack({ 0,504,60,82 });

	jump.speed = 0.07f;

	// walk forward animation (arcade sprite sheet)
	forward.PushBack({ 691, 348, 58, 108 });
	forward.PushBack({ 756, 350, 69, 106 });
	forward.PushBack({ 831, 348, 58, 108 });
	forward.PushBack({ 897, 350, 67, 106 });
	forward.speed = 0.1f;

	// TODO 4: Make ryu walk backwards with the correct animations
	backward.PushBack({ 577, 479, 60, 108 });
	backward.PushBack({ 636, 477, 54, 108 });
	backward.PushBack({ 690, 479, 61, 108 });
	backward.PushBack({ 636, 477, 54, 108 });
	backward.speed = 0.07f;

	//Hadouken animation

	hadouken.PushBack({ 176, 882, 65, 103 });
	hadouken.PushBack({ 242, 883, 88, 102 });
	hadouken.PushBack({ 330, 889, 85, 96 });
	hadouken.PushBack({ 415, 888, 81, 97 });
	hadouken.PushBack({ 496, 878, 102, 107 });

	hadouken.speed = 0.15f;

	//ball animation

	ball.PushBack({ 682, 869, 25,36 });
	ball.PushBack({ 706, 869, 22,36 });
	ball.PushBack({ 729, 878, 26,27 });
	ball.PushBack({ 682, 913, 54,39 });
	ball.PushBack({ 736, 905, 72,47 });
	ball.PushBack({ 808, 921, 53,31 });
	ball.PushBack({ 861, 931, 36,21 });
	ball.PushBack({ 940, 613, 30,37 });
	ball.PushBack({ 971, 613, 22,36 });
	ball.PushBack({ 940, 665, 21,37 });
	ball.PushBack({ 961, 666, 23,36 });
	ball.PushBack({ 984, 666, 35,36 });

	ball.speed = 0.05f;


	//punch animation(arcade sprite sheet)
	
	punch.PushBack({ 485, 350, 58, 106 });
	punch.PushBack({ 543, 350, 89, 106 });
	punch.speed = 0.1f;

	//kick animation(arcade sprite sheet)
	kick.PushBack({ 669, 238, 60, 110 });
	kick.PushBack({ 729, 235, 61, 113 });
	kick.PushBack({ 790, 235, 103, 113 });
	kick.PushBack({ 893, 235, 61, 113 });
	kick.speed = 0.15f;


}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Ryo_SpriteSheet.png"); // arcade version
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	Animation *current_animation = &idle;
	float speed = 1;
	int inicial = 120;

	if (App->input->keyboard[SDL_SCANCODE_D] == 1)
	{
		current_animation = &forward;
		position.x += speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_A] == 1)
	{
		current_animation = &backward;
		position.x -= speed;
	}

	////////////////////////////////////////////////////////
	if (App->input->keyboard[SDL_SCANCODE_W] == 1)
	{
		App->input->j = 1;
		current_animation = &jump;

	}
	if (App->input->j == 1) {
		position.y--; position.y = position.y - 0.5; current_animation = &jump;
	}
	if (position.y == 120) { App->input->j = 0; }
	if (App->input->j == 0 && position.y != 210) {
		position.y++; position.y++; current_animation = &jump;
	}
	//////////////////////////////////////////////////////////////////////////
	if (App->input->keyboard[SDL_SCANCODE_R] == 1)
	{
		current_animation = &hadouken;
	}                                                           //special atack
	if (App->input->keyboard[SDL_SCANCODE_I] == 1) {
		current_animation = &ball;
		position.x += speed;
	}
	///////////////////////////////////////////////////////////////////////
	if (App->input->keyboard[SDL_SCANCODE_K] == 1)
	{
		current_animation = &punch;

	}                                                      //normal atacks

	if (App->input->keyboard[SDL_SCANCODE_J] == 1)
	{
		current_animation = &kick;

	}
	////////////////////////////////////////////////////////////////
	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);

	return UPDATE_CONTINUE;
}
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleParticles.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	graphics = NULL;
	current_animation = NULL;

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

	//punch animation(arcade sprite sheet)

	punch.PushBack({ 485, 350, 58, 106 });
	punch.PushBack({ 543, 350, 89, 106 });
	punch.speed = 0.1f;

	//kick animation(arcade sprite sheet)
	kick.PushBack({ 669, 238, 60, 110 });
	kick.PushBack({ 729, 235, 61, 113 });
	kick.PushBack({ 790, 235, 103, 113 });
	kick.PushBack({ 893, 235, 61, 113 });
	kick.loop = false;
	kick.speed = 0.15f;

	//Hadouken ryo animation

	hadouken.PushBack({ 176, 882, 65, 103 });
	hadouken.PushBack({ 242, 883, 88, 102 });
	hadouken.PushBack({ 330, 889, 85, 96 });
	hadouken.PushBack({ 415, 888, 81, 97 });
	hadouken.PushBack({ 496, 878, 102, 107 });

	hadouken.speed = 0.015f;
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

bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	Animation *current_animation = &idle;
	float speed = 1;
	float hadspeed = 1;
	int inicial = 120;

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &forward;
		position.x += speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &backward;
		position.x -= speed;
	}

	////////////////////////////////////////////////////////
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
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
	
	if (App->input->keyboard[SDL_SCANCODE_R] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->Hadouken1, position.x+40, position.y-110);
		App->particles->AddParticle(App->particles->Hadouken2, position.x+50, position.y-80);
		App->particles->AddParticle(App->particles->Hadouken3, position.x+50, position.y-80);
		App->particles->AddParticle(App->particles->Hadouken4, position.x+90, position.y-80);
	}    

	if (App->input->keyboard[SDL_SCANCODE_R] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &hadouken;

		if (current_animation != &hadouken)
		{
			hadouken.Reset();
			current_animation = &hadouken;
		}
	}
	
	if (App->input->keyboard[SDL_SCANCODE_K] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &punch;
	}                                                      //normal atacks

	if (App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &kick;
	}

	////////////////////////////////////////////////////////////////

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);

	return UPDATE_CONTINUE;
}
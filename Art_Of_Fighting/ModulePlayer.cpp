#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleParticles.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"


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

	//backawrd animation
	backward.PushBack({ 577, 479, 60, 108 });
	backward.PushBack({ 636, 477, 54, 108 });
	backward.PushBack({ 690, 479, 61, 108 });
	backward.PushBack({ 636, 477, 54, 108 });
	backward.speed = 0.07f;

	//crouch animation

	crouch.PushBack({ 0, 503,60,83 });
	crouch.PushBack({ 576, 42,67,74 });

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

	//Hadouken ryo animation

	hadouken.PushBack({ 176, 882, 65, 103 });
	hadouken.PushBack({ 242, 883, 88, 102 });
	hadouken.PushBack({ 330, 889, 85, 96 });
	hadouken.PushBack({ 415, 888, 81, 97 });
	hadouken.PushBack({ 496, 878, 102, 107 });

	hadouken.speed = 0.15f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Ryo_SpriteSheet.png"); // arcade version

	ryokick = App->audio->LoadFX("ryo_kick.wav");
	ryopunch = App->audio->LoadFX("Ryo_punch.wav");
	ryojump = App->audio->LoadFX("Ryojump.wav");
	ryoKoOuKen= App->audio->LoadFX("Ryo_KoOuKen.wav");
	ryoKoOuKensound= App->audio->LoadFX("ryoKoOuKensound.wav");
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
	float speed = 2;
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

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN && position.y == 210)                             //   JUMP  
	{
		App->audio->PlayFX(ryojump);
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
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (App->input->keyboard[SDL_SCANCODE_R] == KEY_STATE::KEY_DOWN)                                          // HADOUKEN
	{
		App->particles->AddParticle(App->particles->Hadouken1, position.x - 10, position.y - 110);
		App->particles->AddParticle(App->particles->Hadouken2, position.x-8, position.y-85,100);
		App->particles->AddParticle(App->particles->Hadouken3, position.x-10, position.y-80,300);
		App->particles->AddParticle(App->particles->Hadouken4, position.x-60, position.y-80,400);
	}    

	if (App->input->keyboard[SDL_SCANCODE_R] == KEY_STATE::KEY_DOWN && App->input->m == 0)
	{
		App->audio->PlayFX(ryoKoOuKen);
		App->audio->PlayFX(ryoKoOuKensound);
		App->input->m = 1;
		current_animation = &hadouken;
		
	}
	if (App->input->m == 1) {

		current_animation = &hadouken;
		time++;
		if (time == 25) {
			hadouken.Reset();
			App->input->m = 0;
			time = 0;
		}
	}
	
	if (App->input->keyboard[SDL_SCANCODE_K] == KEY_STATE::KEY_DOWN && App->input->l == 0)
	{
		App->audio->PlayFX(ryopunch);
		App->input->l = 1;
		current_animation = &punch;
	}    
	if (App->input->l == 1) {

		current_animation = &punch;
		time++;
		if (time == 25) {
			punch.Reset();
			App->input->l = 0;
			time = 0;
		}
	}
                                                  //normal atacks

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	if (App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_DOWN && App->input->k == 0)                                     //Kick
	{
		App->input->k = 1;
		current_animation = &kick;
		App->audio->PlayFX(ryokick);
	}
	if (App->input->k == 1) {
		
		current_animation = &kick;
		time++;
		if (time==25) {
			kick.Reset();
			App->input->k = 0;
			time = 0;
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);

	return UPDATE_CONTINUE;
}
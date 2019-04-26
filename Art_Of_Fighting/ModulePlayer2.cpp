#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleParticles.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer2.h"
#include "ModuleFonts.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer2::ModulePlayer2()
{
	graphics = NULL;
	current_animation = NULL;


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

	jump.speed = 0.1f;

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

	crouch1.PushBack({ 0, 503,60,83 });
	crouch2.PushBack({ 576, 42,67,74 });

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

	// crouch animation
	crouch1.PushBack({ 0, 503,60,83 });
	crouch2.PushBack({ 576, 42,67,74 });
	crouch1.speed = 0.1f;
	crouch2.speed = 0.1f;



	player2Win.x = 0;
	player2Win.y = 0;
	player2Win.w = 120;
	player2Win.h = 41;

}

ModulePlayer2::~ModulePlayer2()
{}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("media/Ryo_SpriteSheet.png"); // arcade version
	graphicsWin = App->textures->Load("media/WinPlayer.png");

	ryokick = App->audio->LoadFX("media/ryo_kick.wav");
	ryopunch = App->audio->LoadFX("media/Ryo_punch.wav");
	ryojump = App->audio->LoadFX("media/Ryojump.wav");
	ryoKoOuKen = App->audio->LoadFX("media/Ryo_KoOuKen.wav");
	ryoKoOuKensound = App->audio->LoadFX("media/ryoKoOuKensound.wav");

	position.x = 455;
	position.y = 210;

	ryohitbox = App->collision->AddCollider({ position.x,position.y, 50, 97 }, COLLIDER_ENEMY, this);
	kickCollider = App->collision->AddCollider({ position.x,position.y, 60, 30 }, COLLIDER_ENEMY, this);
	kickCollider->Enabled = false;
	punchCollider = App->collision->AddCollider({ position.x,position.y, 40, 15 }, COLLIDER_ENEMY, this);
	punchCollider->Enabled = false;
	return ret;
}

bool ModulePlayer2::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	App->textures->Unload(graphicsWin);


	return true;
}


// Update: draw background
update_status ModulePlayer2::Update()
{
	Animation *current_animation = &idle;

	float hadspeed = 1;
	int inicial = 120;


	///////////////////////////////////////////////////////////////////////////////////

	if (App->input->keyboard[SDL_SCANCODE_K] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &crouch1;
		current_animation = &crouch2;
	}

	if (App->input->keyboard[SDL_SCANCODE_L] == KEY_STATE::KEY_REPEAT)
	{
		if (wall == true && position.x > 552) {}
		else {
			current_animation = &backward;
			position.x += speed;
		}

	}

	if (App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT)
	{
		if (wall == true && (position.x > 0 && position.x < 200)) {}
		else {
			current_animation = &forward;
			position.x -= speed;
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (App->input->keyboard[SDL_SCANCODE_U] == KEY_STATE::KEY_DOWN)                                          // HADOUKEN
	{
		App->particles->AddParticle(App->particles->Hadouken1Player2, position.x - 10, position.y - 110, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->Hadouken2Player2, position.x - 8, position.y - 85, COLLIDER_ENEMY_SHOT, 100);
		App->particles->AddParticle(App->particles->Hadouken3Player2, position.x - 10, position.y - 80, COLLIDER_ENEMY_SHOT, 300);
		App->particles->AddParticle(App->particles->Hadouken4Player2, position.x - 60, position.y - 80, COLLIDER_ENEMY_SHOT, 400);
	}

	if (App->input->keyboard[SDL_SCANCODE_U] == KEY_STATE::KEY_DOWN && App->input->u == 0)
	{
		App->audio->PlayFX(ryoKoOuKen);
		App->audio->PlayFX(ryoKoOuKensound);
		App->input->u = 1;
		current_animation = &hadouken;

	}
	if (App->input->u == 1) {

		current_animation = &hadouken;
		time++;
		if (time == 25) {
			hadouken.Reset();
			App->input->u = 0;
			time = 0;
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////
																																//Punch

	if (App->input->keyboard[SDL_SCANCODE_O] == KEY_STATE::KEY_DOWN && App->input->o == 0)
	{
		App->audio->PlayFX(ryopunch);
		App->input->o = 1;
		current_animation = &punch;
	}
	if (App->input->o == 1) {

		current_animation = &punch;
		time++;
		if (time == 25) {
			punch.Reset();
			App->input->o = 0;
			time = 0;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////

	if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN && App->input->p == 0)                                     //Kick
	{
		App->input->p = 1;
		current_animation = &kick;
		App->audio->PlayFX(ryokick);

	}
	if (App->input->p == 1) {

		current_animation = &kick;
		time++;
		if (time == 25) {
			kick.Reset();
			App->input->p = 0;
			time = 0;
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_DOWN && position.y == 210)                             //   JUMP  
	{
		App->audio->PlayFX(ryojump);
		App->input->i = 1;
		current_animation = &jump;
	}

	if (App->input->i == 1) 
	{
		position.y--; position.y = position.y - 2; current_animation = &jump;
	}
	if (position.y == 120) 
	{ 
		App->input->i = 0; 
	}
	if (App->input->i == 0 && position.y != 210) 
	{
		position.y = position.y + 3; /*position.y++*/; current_animation = &jump;
	}
	speed = 2;
	// Draw everything --------------------------------------
	SDL_Rect* r = &current_animation->GetCurrentFrame();

	App->render->BlitWithScale(graphics, position.x, position.y - r->h, r, -1, 1.0f, 1, TOP_RIGHT);

	ryohitbox->SetPos(position.x-50, position.y - r->h);

	wall = false;

	if (r == &kick.frames[kick.last_frame - 1])
	{
		kickCollider->SetPos(position.x - 100, position.y - r->h);

		kickCollider->Enabled = true;
	}
	else
	{
		kickCollider->Enabled = false;
	}

	if (r == &punch.frames[punch.last_frame - 1])
	{
		punchCollider->SetPos(position.x - 90, position.y + 12 - r->h);

		punchCollider->Enabled = true;
	}
	else
	{
		punchCollider->Enabled = false;
	}

	if (App->player->Life <= 0)
	{
		App->render->BlitWithScale(graphicsWin, 212, 70, &player2Win, 1, 0.0f, 1.0f, TOP_RIGHT);
	}
	return UPDATE_CONTINUE;
}

void ModulePlayer2::OnCollision(Collider* c1, Collider* c2) {

	
	if (ryohitbox == c1 && c2->type == COLLIDER_WALL)
	{
		wall = true;
	}
	if (kickCollider == c1 && c2->type == COLLIDER_PLAYER)
	{
		App->player->Life--;
		App->player->position.x -= 5;
	}

	if (ryohitbox == c1 && c2->type == COLLIDER_PLAYER)
	{
		if (App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) {
			speed = 0;
		}
		else if (App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT) {
			App->player->position.x = position.x - 101;
			speed = 1;
		}
		
	}
	if (punchCollider == c1 && c2->type == COLLIDER_PLAYER)
	{
		App->player->Life--;
		App->player->position.x -= 5;
	}
	
}

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

ModulePlayer::ModulePlayer()
{
	graphics = NULL;
	graphicsbeat = NULL;
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

	//beat animation

	beat.PushBack({ 356,479,88,143 });
	beat.PushBack({ 356,479,88,143 });
	beat.PushBack({ 356,479,88,143 });

	beat.speed = 0.1f;

	player1Win.x = 0;
	player1Win.y = 40;
	player1Win.w = 116;
	player1Win.h = 41;

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("media/Ryo_SpriteSheet.png"); // arcade version
	graphicsWin = App->textures->Load("media/WinPlayer.png");
	graphicsbeat = App->textures->Load("media/Sprites_beat_ryo.png");

	ryokick = App->audio->LoadFX("media/ryo_kick.wav");
	ryopunch = App->audio->LoadFX("media/Ryo_punch.wav");
	ryojump = App->audio->LoadFX("media/Ryojump.wav");
	ryoKoOuKen= App->audio->LoadFX("media/Ryo_KoOuKen.wav");
	ryoKoOuKensound= App->audio->LoadFX("media/ryoKoOuKensound.wav");

	position.x = 50;
	position.y = 210;

	ryohitbox = App->collision->AddCollider({position.x,position.y, 50, 97 }, COLLIDER_PLAYER, this);
	kickCollider = App->collision->AddCollider({ position.x,position.y, 60, 30 }, COLLIDER_PLAYER, this);
	kickCollider->Enabled = false;
	punchCollider = App->collision->AddCollider({ position.x,position.y, 40, 15 }, COLLIDER_PLAYER, this);
	punchCollider->Enabled = false;

	// TODO 0: Notice how a font is loaded and the meaning of all its arguments 
	font_score = App->fonts->Load("fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);

	// TODO 4: Try loading "rtype_font3.png" that has two rows to test if all calculations are correct
	return ret;
}

bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	App->textures->Unload(graphicsWin);
	App->textures->Unload(graphicsbeat);


	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	Animation *current_animation = &idle;
	
	float hadspeed = 1;
	int inicial = 120;
	
	///////////////////////////////////////////////////////////////////////////////////

	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &crouch1;
		current_animation = &crouch2;
	}

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		if (wall == true && position.x > 552) {}
		else {
		current_animation = &forward;
		position.x += speed;
	}
		
	}

	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		if (wall == true && (position.x > 0 && position.x < 200)) {}
		else {
			current_animation = &backward;
			position.x -= speed;
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN && position.y == 210)                             //   JUMP  
	{
		App->audio->PlayFX(ryojump);
		App->input->j = 1;
		current_animation = &jump;
	}

	if (App->input->j == 1) {
		position.y--; position.y = position.y - 2; current_animation = &jump;               
	}
	if (position.y == 120) { App->input->j = 0; }
	if (App->input->j == 0 && position.y != 210) {
		position.y=position.y+3; /*position.y++*/; current_animation = &jump;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (App->input->keyboard[SDL_SCANCODE_R] == KEY_STATE::KEY_DOWN)                                          // HADOUKEN
	{
		App->particles->AddParticle(App->particles->Hadouken1, position.x-10, position.y-110, COLLIDER_PLAYER_SHOT);
		App->particles->AddParticle(App->particles->Hadouken2, position.x-8, position.y-85, COLLIDER_PLAYER_SHOT,100);
		App->particles->AddParticle(App->particles->Hadouken3, position.x-10, position.y-80, COLLIDER_PLAYER_SHOT,300);
		App->particles->AddParticle(App->particles->Hadouken4, position.x-60, position.y-80, COLLIDER_PLAYER_SHOT,400);
	}    

	if (App->input->keyboard[SDL_SCANCODE_R] == KEY_STATE::KEY_DOWN && App->input->r == 0)
	{
		App->audio->PlayFX(ryoKoOuKen);
		App->audio->PlayFX(ryoKoOuKensound);
		App->input->r = 1;
		current_animation = &hadouken;
		
	}
	if (App->input->r == 1) {

		current_animation = &hadouken;
		time++;
		if (time == 25) {
			hadouken.Reset();
			App->input->r = 0;
			time = 0;
		}
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////
																															//Punch

	if (App->input->keyboard[SDL_SCANCODE_T] == KEY_STATE::KEY_DOWN && App->input->t == 0)
	{
		App->audio->PlayFX(ryopunch);
		App->input->t = 1;
		current_animation = &punch;
	}    
	if (App->input->t == 1) {

		current_animation = &punch;
		time++;
		if (time == 25) {
			punch.Reset();
			App->input->t = 0;
			time = 0;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////

	if (App->input->keyboard[SDL_SCANCODE_Y] == KEY_STATE::KEY_DOWN && App->input->y == 0)                                     //Kick
	{
		App->input->y = 1;
		current_animation = &kick;
		App->audio->PlayFX(ryokick);

	}
	if (App->input->y == 1) {
		
		current_animation = &kick;
		time++;
		if (time==25) {
			kick.Reset();
			App->input->y = 0;
			time = 0;
		}
	}
	speed = 2;
	////////////////////////////////////////////////////////////////////////////

	if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN) {															//God mode 
		if (GodMode == false) {
			ryohitbox->to_delete = true;

			GodMode = true;
		}
		else if (GodMode == true) {
			ryohitbox = App->collision->AddCollider({ position.x,position.y,50, 97 }, COLLIDER_PLAYER, this);

			GodMode = false;
		}
	}
	// Draw everything --------------------------------------
	SDL_Rect* r = &current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r->h, r);

	ryohitbox->SetPos(position.x, position.y - r->h);

	wall = false;

	
	if(r == &kick.frames[kick.last_frame - 1])
	{
		kickCollider->SetPos(position.x + 40, position.y - r->h);

		kickCollider->Enabled = true;
	}
	else
	{
		kickCollider->Enabled = false;
	}
	
	if (r == &punch.frames[punch.last_frame - 1])
	{
		punchCollider->SetPos(position.x + 50, position.y+12 - r->h);

		punchCollider->Enabled = true;
	}
	else
	{
		punchCollider->Enabled = false;
	}


	if (App->player2->Life <= 0)
	{
		App->render->BlitWithScale(graphicsWin, 210, 70, &player1Win, 1, 0.0f, 1.0f, TOP_RIGHT);
	}
	return UPDATE_CONTINUE;
}



void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {

	if (ryohitbox == c1 && c2->type == COLLIDER_WALL)
	{
		wall = true;
	}
	
	if (ryohitbox == c1 && c2->type == COLLIDER_ENEMY)
	{
		if (App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) {
			speed = 0;
		}
		else if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) {
			App->player2->position.x = position.x + 101;
			speed = 1;
		}

	}

	if(kickCollider == c1 && c2->type == COLLIDER_ENEMY)
	{
		App->player2->Life--;
		App->player2->position.x += 5;
	}
	if (kickCollider == c1 && c2->type == COLLIDER_ENEMY)
	{
		current_animation = &beat;
	}

	if (punchCollider == c1 && c2->type == COLLIDER_ENEMY)
	{
		App->player2->Life--;
		current_animation2 = &App->player->beat;
		App->player2->position.x += 5;
	}
	
}
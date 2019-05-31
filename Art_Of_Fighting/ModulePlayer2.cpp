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
#include "SDL/include/SDL_timer.h"
#include "SDL/include/SDL.h"
#include "ModuleSceneking.h"

ModulePlayer2::ModulePlayer2()
{
	graphics = NULL;
	current_animation = NULL;
	
	// idle animation (arcade sprite sheet)
	idle.PushBack({ 7, 10, 54, 104 }, 0.1, 0, 0, 0, 0);
	idle.PushBack({ 64, 10, 54, 104 }, 0.1, 0, 0, 0, 0);
	idle.PushBack({ 118, 10, 54, 104 }, 0.1, 0, 0, 0, 0);

	//jump animation(arcade sprite sheet)
	jumping.PushBack({ 68,140,48,85 }, 0.1, 0, 0, 0, 0);
	jumping.PushBack({ 148,256,68,101 }, 0.1, 0, 0, 0, 0);
	jumping.PushBack({ 68,140,49,85 }, 0.1, 0, 0, 0, 0);

	// walk forward animation (arcade sprite sheet)
	forward.PushBack({ 419, 11, 49, 103 }, 0.1, 0, 0, 0, 0);
	forward.PushBack({ 528, 10, 47, 104 }, 0.1, 0, 0, 0, 0);
	forward.PushBack({ 474, 10, 48, 104 }, 0.1, 0, 0, 0, 0);
	forward.PushBack({ 7, 10, 54, 104 }, 0.1, 0, 0, 0, 0);

	//backawrd animation
	backward.PushBack({ 419, 11, 49, 103 }, 0.1, 0, 0, 0, 0);
	backward.PushBack({ 474, 10, 48, 104 }, 0.1, 0, 0, 0, 0);
	backward.PushBack({ 528, 10, 47, 104 }, 0.1, 0, 0, 0, 0);

	//punch animation(arcade sprite sheet)
	punch.PushBack({ 15, 476, 48, 102 }, 0.23, 6, 0, 0, 0);
	punch.PushBack({ 527, 483, 94, 100 }, 0.2, 2, 0, 0, 0);
	punch.PushBack({ 15, 476, 48, 102 }, 0.2, 0, 0, 0, 0);

	punchJump.PushBack({ 714,141,66,94 }, 0.1, 0, 0, 0, 0);
	punchJump.PushBack({ 780,157,86,78 }, 0.1, 0, 0, 0, 0);
	punchJump.PushBack({ 714,141,66,94 }, 0.1, 0, 0, 0, 0);														//CHANGE

	punchCrouch.PushBack({ 335,152,70,73 }, 0.1, 0, 0, 0, 0);
	punchCrouch.PushBack({ 405,157,103,68 }, 0.1, 0, 0, 0, 0);
	punchCrouch.PushBack({ 335,152,70,73 }, 0.1, 0, 0, 0, 0);

	//kick animation(arcade sprite sheet)
	kick.PushBack({ 4,593,72,113 }, 0.16363, 0, 0, 0, 0);
	kick.PushBack({ 96,593,51,112 }, 0.16363, 0, 0, 36, -3);
	kick.PushBack({ 172,593,82,112 }, 0.072727, 0, 0, 37, -3);
	kick.PushBack({ 264,599,49,102 }, 0.065, 0, 0, 14, -3);
	kick.PushBack({ 338,607,63,92 }, 0.072727, 0, 0, -15, 0);

	lowkick.PushBack({ 84, 478, 56, 101 }, 0.1, 0, 0, 0, 0);
	lowkick.PushBack({ 151, 478, 49, 101 }, 0.1, 0, 0, 0, 0);
	lowkick.PushBack({ 211, 478, 86, 101 }, 0.1, 0, 0, 0, 0);
	lowkick.PushBack({ 151, 478, 49, 101 }, 0.1, 0, 0, 0, 0);
	lowkick.PushBack({ 84, 478, 56, 101 }, 0.1, 0, 0, 0, 0);

	kickJump.PushBack({ 561,146,57,89 }, 0.1, 0, 0, 0, 0);												//CHANGE
	kickJump.PushBack({ 618,149,96,86 }, 0.1, 0, 0, 0, 0);
	kickJump.PushBack({ 561,146,57,89 }, 0.1, 0, 0, 0, 0);

	kickCrouch.PushBack({ 335,152,70,73 }, 0.1, 0, 0, 0, 0);
	kickCrouch.PushBack({ 405,157,103,68 }, 0.1, 0, 0, 0, 0);
	kickCrouch.PushBack({ 335,152,70,73 }, 0.1, 0, 0, 0, 0);

	// Hadouken ryo animation
	hadouken.PushBack({ 431, 245, 56, 108 }, 0.1, 0, 0, 0, 0);                                        //CHANGE
	hadouken.PushBack({ 498, 245, 49, 100 }, 0.1, 0, 0, 0, 0);
	hadouken.PushBack({ 552, 245, 81, 77 }, 0.1, 0, 0, 0, 0);
	hadouken.PushBack({ 642, 241, 48, 86 }, 0.1, 0, 0, 0, 0);
	hadouken.PushBack({ 724, 241, 53, 99 }, 0.1, 0, 0, 0, 0);

	// Moushuu Kyaku animation
	Moushuu_Kyaku.PushBack({ 15, 366, 58, 102 }, 0.1, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 83, 366, 103, 101 }, 0.1, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 195, 367, 69, 101 }, 0.1, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 273, 351, 95, 117 }, 0.1, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 195, 367, 69, 101 }, 0.1, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 83, 366, 103, 101 }, 0.1, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 195, 367, 69, 101 }, 0.1, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 273, 351, 95, 117 }, 0.1, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 195, 367, 69, 101 }, 0.1, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 83, 366, 103, 101 }, 0.1, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 195, 367, 69, 101 }, 0.1, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 273, 351, 95, 117 }, 0.1, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 195, 367, 69, 101 }, 0.1, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 83, 366, 103, 101 }, 0.1, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 195, 367, 69, 101 }, 0.1, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 273, 351, 95, 117 }, 0.1, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 195, 367, 69, 101 }, 0.1, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 15, 366, 58, 102 }, 0.1, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 7, 10, 54, 104 }, 0.1, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 4,593,72,113 }, 0.1, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 96,593,51,112 }, 0.1, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 172,593,82,112 }, 0.1, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 264,599,49,102 }, 0.1, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 338,607,63,92 }, 0.1, 0, 0, 0, 0);

	// Tornado Kick animation
	Tornado_Kick.PushBack({ 456, 350, 72, 130 }, 0.1, 0, 0, 0, 0);
	Tornado_Kick.PushBack({ 96,593,51,112 }, 0.1, 0, 0, 0, 0); //KICK 2ND FRAME
	Tornado_Kick.PushBack({ 544, 388, 52, 78 }, 0.1, 0, 0, 0, 0);
	Tornado_Kick.PushBack({ 599, 356, 62, 110 }, 0.1, 0, 0, 0, 0);
	Tornado_Kick.PushBack({ 78, 254, 59, 101 }, 0.1, 0, 0, 0, 0); //JUMP 2ND FRAME (PAINT)
	Tornado_Kick.PushBack({ 677, 364, 63, 101 }, 0.1, 0, 0, 0, 0); //JUMP 2ND FRAME WITH  
	// ANIMATION LOOP 21 FRAMES
	/*Tornado_Kick.PushBack({ 78, 254, 59, 101 }, 0.1, 0, 0, 0, 0);
	Tornado_Kick.PushBack({ 677, 364, 63, 101 }, 0.1, 0, 0, 0, 0);
	Tornado_Kick.PushBack({ 78, 254, 59, 101 }, 0.1, 0, 0, 0, 0);
	Tornado_Kick.PushBack({ 677, 364, 63, 101 }, 0.1, 0, 0, 0, 0);
	Tornado_Kick.PushBack({ 78, 254, 59, 101 }, 0.1, 0, 0, 0, 0);
	Tornado_Kick.PushBack({ 677, 364, 63, 101 }, 0.1, 0, 0, 0, 0);
	Tornado_Kick.PushBack({ 78, 254, 59, 101 }, 0.1, 0, 0, 0, 0);
	Tornado_Kick.PushBack({ 677, 364, 63, 101 }, 0.1, 0, 0, 0, 0);
	Tornado_Kick.PushBack({ 78, 254, 59, 101 }, 0.1, 0, 0, 0, 0);
	Tornado_Kick.PushBack({ 677, 364, 63, 101 }, 0.1, 0, 0, 0, 0);
	Tornado_Kick.PushBack({ 78, 254, 59, 101 }, 0.1, 0, 0, 0, 0);
	Tornado_Kick.PushBack({ 677, 364, 63, 101 }, 0.1, 0, 0, 0, 0);
	Tornado_Kick.PushBack({ 78, 254, 59, 101 }, 0.1, 0, 0, 0, 0);
	Tornado_Kick.PushBack({ 677, 364, 63, 101 }, 0.1, 0, 0, 0, 0);
	Tornado_Kick.PushBack({ 78, 254, 59, 101 }, 0.1, 0, 0, 0, 0);
	Tornado_Kick.PushBack({ 677, 364, 63, 101 }, 0.1, 0, 0, 0, 0);
	Tornado_Kick.PushBack({ 78, 254, 59, 101 }, 0.1, 0, 0, 0, 0);
	Tornado_Kick.PushBack({ 677, 364, 63, 101 }, 0.1, 0, 0, 0, 0);
	Tornado_Kick.PushBack({ 78, 254, 59, 101 }, 0.1, 0, 0, 0, 0);
	Tornado_Kick.PushBack({ 677, 364, 63, 101 }, 0.1, 0, 0, 0, 0);
	Tornado_Kick.PushBack({ 78, 254, 59, 101 }, 0.1, 0, 0, 0, 0);*/
	////////////////////////////////////////////////////////////////
	Tornado_Kick.PushBack({ 752, 366, 55, 95 }, 0.1, 0, 0, 0, 0);
	//IF KING HIT THE ENEMY///////////////////////////////////
	Tornado_Kick.PushBack({ 824, 376, 95, 81 }, 0.1, 0, 0, 0, 0);
	Tornado_Kick.PushBack({ 929, 374, 78, 89 }, 0.1, 0, 0, 0, 0);
	//////////////////////////////////////////////////////////
	Tornado_Kick.PushBack({ 148,256,68,101 }, 0.1, 0, 0, 0, 0); //JUMP 3RD FRAME
	Tornado_Kick.PushBack({ 68,140,49,85 }, 0.1, 0, 0, 0, 0); //JUMP 1ST FRAME

	// crouch animation
	crouch.PushBack({ 117,133,51,92 }, 0.1, 0, 0, 0, 0);
	crouch.PushBack({ 15,151,49,74 }, 0.1, 0, 0, 0, 0);
	crouch.loop = false;

	//beat animation
	/*beat.PushBack({ 866, 750,64,106 });
	beat.PushBack({ 934, 747,78,108 });
	beat.PushBack({ 866, 750,64,106 });
	beat.speed = 0.15f;*/

	player2Win.x = 0;
	player2Win.y = 0;
	player2Win.w = 120;
	player2Win.h = 39;
}

ModulePlayer2::~ModulePlayer2()
{}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("media/Spritesheets/king_old_spritesheet.png"); // arcade version
	graphicsWin = App->textures->Load("media/Win/WinPlayer.png");

	kingkick = App->audio->LoadFX("media/FX/king_high_kick.wav");
	kingpunch = App->audio->LoadFX("media/FX/king_punch.wav");
	kingjump = App->audio->LoadFX("media/FX/Ryojump.wav");
	king_punch_crouch = App->audio->LoadFX("media/FX/king_punch_crouch.wav");
	slize_sound = App->audio->LoadFX("media/FX/slize_sound.wav");
	kingKoOuKen = App->audio->LoadFX("media/FX/king_haduken.wav");
	ryoKoOuKensound = App->audio->LoadFX("media/FX/ryoKoOuKensound.wav");

	position.x = 420;
	position.y = 210;
	initialPos = position.y;

	//Colliders
	ryohitbox = App->collision->AddCollider({ position.x,position.y, 35, 80 }, COLLIDER_ENEMY, this);

	punchCollider = App->collision->AddCollider({ position.x,position.y, 60, 15 }, COLLIDER_ENEMY, this);
	punchCollider->Enabled = false;

	kickCollider = App->collision->AddCollider({ position.x,position.y, 45, 30 }, COLLIDER_ENEMY, this);
	kickCollider->Enabled = false;

	punchCrouchCollider = App->collision->AddCollider({ position.x, position.y - 70 , 40, 15 }, COLLIDER_ENEMY, this);
	punchCrouchCollider->Enabled = false;

	kickCrouchCollider = App->collision->AddCollider({ position.x, position.y - 70 , 65, 15 }, COLLIDER_ENEMY, this);
	kickCrouchCollider->Enabled = false;

	//Initialize Stamina
	Stamina = 100;

	return ret;
}

bool ModulePlayer2::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	App->textures->Unload(graphicsWin);
	App->audio->UnLoadFX(kingkick);
	App->audio->UnLoadFX(kingpunch);
	App->audio->UnLoadFX(kingjump);
	App->audio->UnLoadFX(king_punch_crouch);
	App->audio->UnLoadFX(slize_sound);
	App->audio->UnLoadFX(kingKoOuKen);

	return true;
}

// Update: draw background
update_status ModulePlayer2::Update()
{

	Animation* current_animation = &idle;

	king_states current_state = ST_UNKNOWN;
	king_states state = process_fsm(App->input->inputs2);

	int speed = 2;

	if (state != current_state)
	{
		switch (state)
		{
		case ST_IDLE:
			current_animation = &idle;
			forward.Reset();
			backward.Reset();
			crouch.Reset();
			kick.Reset();
			lowkick.Reset();
			punch.Reset();
			hadouken.Reset();
			Tornado_Kick.Reset();
			Moushuu_Kyaku.Reset();
			jumping.Reset();
			punchJump.Reset();
			punchCrouch.Reset();
			kickJump.Reset();
			kickCrouch.Reset();
			break;

		case ST_WALK_FORWARD:
			current_animation = &forward;
			position.x += speed;
			backward.Reset();
			crouch.Reset();
			kick.Reset();
			lowkick.Reset();
			punch.Reset();
			hadouken.Reset();
			Tornado_Kick.Reset();
			Moushuu_Kyaku.Reset();
			jumping.Reset();
			punchJump.Reset();
			punchCrouch.Reset();
			kickJump.Reset();
			kickCrouch.Reset();
			LOG("FORWARD");
			break;

		case ST_WALK_BACKWARD:
			current_animation = &backward;
			position.x -= speed;
			forward.Reset();
			crouch.Reset();
			kick.Reset();
			lowkick.Reset();
			punch.Reset();
			hadouken.Reset();
			Tornado_Kick.Reset();
			Moushuu_Kyaku.Reset();
			jumping.Reset();
			punchJump.Reset();
			punchCrouch.Reset();
			kickJump.Reset();
			kickCrouch.Reset();
			break;

		case ST_JUMP_NEUTRAL:
			if (animstart == 0)
			{
				position.y -= jumpSpeed;
				current_animation = &jumping;

				if (SFXsound == true)
				{
					App->audio->PlayFX(kingjump);
					SFXsound = false;
				}

				if (position.y < 140) {
					jumpSpeed -= 0.5;
					if (jumpSpeed < 0) jumpSpeed = -6;
				}
				if (position.y >= initialPos && jumpSpeed < 0) {
					animstart = 1;
					position.y = initialPos;
					jumpSpeed = 6;
				}
				LOG("JUMPING ^^\n")
			}break;

		case ST_JUMP_FORWARD:
			if (animstart == 0)
			{
				current_animation = &jumping;
				position.y -= jumpSpeed;
				position.x += 3;

				if (SFXsound == true)
				{
					App->audio->PlayFX(kingjump);
					SFXsound = false;
				}

				if (position.y < 120) {
					jumpSpeed -= 0.5;
					if (jumpSpeed < 0) jumpSpeed = -6;
				}
				if (position.y >= initialPos && jumpSpeed < 0) {
					animstart = 1;
					position.y = initialPos;
					jumpSpeed = 6;
				}
			}
			LOG("JUMPING FORWARD ^^>>\n");
			break;
		case ST_JUMP_BACKWARD:
			if (animstart == 0)
			{
				current_animation = &jumping;
				position.y -= jumpSpeed;

				if (SFXsound == true)
				{
					App->audio->PlayFX(kingjump);
					SFXsound = false;
				}

				if (wall) {}
				else {
					if (position.x) position.x -= 3;
				}
				if (position.y < 120) {
					jumpSpeed -= 0.5;
					if (jumpSpeed < 0) jumpSpeed = -6;
				}
				if (position.y >= initialPos && jumpSpeed < 0) {
					animstart = 1;
					position.y = initialPos;
					jumpSpeed = 6;
				}
			}
			LOG("JUMPING BACKWARD ^^<<\n");
			break;
		case ST_CROUCH:
			current_animation = &crouch;
			punchCrouch.Reset();
			kickCrouch.Reset();

			LOG("CROUCHING ****\n");
			break;
		case ST_PUNCH_CROUCH:
			if (SFXsound == true)
			{
				App->audio->PlayFX(king_punch_crouch);
				SFXsound = false;
			}
			if (animstart == 0)
			{
				current_animation = &punchCrouch;
			}

			LOG("PUNCH CROUCHING **++\n");
			break;
		case ST_PUNCH_STANDING:
			if (SFXsound == true)
			{
				App->audio->PlayFX(kingpunch);
				SFXsound = false;
			}
			if (animstart == 0)
			{
				current_animation = &punch;
			}
			LOG("PUNCH STANDING ++++\n");
			break;
		case ST_PUNCH_NEUTRAL_JUMP:
			if (SFXsound == true)
			{
				SFXsound = false;
			}
			if (animstart == 0)
			{
				current_animation = &punchJump;
			}
			LOG("PUNCH NEUTRAL JUMP ++++\n");
			break;
		case ST_PUNCH_FORWARD_JUMP:
			LOG("PUNCH JUMP FORWARD ^>>+\n");
			break;
		case ST_PUNCH_BACKWARD_JUMP:
			LOG("PUNCH JUMP BACKWARD ^<<+\n");
			break;
		case ST_KICK_CROUCH:
			position.x -= 0.5*speed;
			if (SFXsound == true)
			{
				App->audio->PlayFX(king_punch_crouch);
				App->audio->PlayFX(slize_sound);

				SFXsound = false;
			}
			if (animstart == 0)
			{
				current_animation = &kickCrouch;
			}
			LOG("KICK CROUCHING **--\n");
			break;
		case ST_KICK_STANDING:
			if (SFXsound == true)
			{
				App->audio->PlayFX(kingkick);
				SFXsound = false;
			}
			if (animstart == 0)
			{
				current_animation = &kick;
			}
			LOG("KICK --\n")
				break;
		case ST_KICK_NEUTRAL_JUMP:
			if (SFXsound == true)
			{
				//App->audio->PlayFX(ryokick);
				SFXsound = false;
			}
			if (animstart == 0)
			{
				current_animation = &kickJump;
			}
			LOG("KICK JUMP NEUTRAL ^^--\n");
			break;
		case ST_KICK_FORWARD_JUMP:
			LOG("KICK JUMP FORWARD ^>>-\n");
			break;
		case ST_KICK_BACKWARD_JUMP:
			LOG("KICK JUMP BACKWARD ^<<-\n");
			break;
			/*case ST_HIT:
			damage = true;
			current_animation = &App->player2->beat;
			break;*/
		case ST_HADOUKEN:
			if (Activehadouken == true)
			{
				if (Stamina > 0) {
					if (Stamina >= 20) { shoot = true; }
					Stamina = (Stamina - 20);
					if (Stamina < 0) {
						Stamina = 0;
					}

				}

				if (shoot == true)
				{
					App->audio->PlayFX(kingKoOuKen);
					App->audio->PlayFX(ryoKoOuKensound);

					if ((position.x + 25) >= (App->player->position.x - 25))
					{
						App->particles->HadoukenFlip2.speed.x = -3;
						App->particles->AddParticle(App->particles->HadoukenFlip, position.x - 10, position.y - 60, COLLIDER_ENEMY_SHOT);
						App->particles->AddParticle(App->particles->HadoukenFlip2, position.x - 10, position.y - 60, COLLIDER_ENEMY_SHOT);
					}
					else
					{
						App->particles->Hadouken2.speed.x = +3;
						App->particles->AddParticle(App->particles->Hadouken, position.x + 10, position.y - 60, COLLIDER_ENEMY_SHOT);
						App->particles->AddParticle(App->particles->Hadouken2, position.x + 10, position.y - 60, COLLIDER_ENEMY_SHOT);
					}
					shoot = false;
				}

			}
			Activehadouken = false;
			if (animstart == 0)
			{
				current_animation = &hadouken;
			}
			break;
		case ST_TORNADOKICK:
			if (SFXsound == true)
			{
				//App->audio->PlayFX(kingpunch);
				SFXsound = false;
			}
			if (animstart == 0)
			{
				current_animation = &Tornado_Kick;
			}
			LOG("TORNADOKICK ++++\n");
			break;
		case ST_MOUSHUUKYAKU:
			if (SFXsound == true)
			{
				//App->audio->PlayFX(kingpunch);
				SFXsound = false;
			}
			if (animstart == 0)
			{
				current_animation = &Moushuu_Kyaku;
			}
			LOG("MOUSHUUKYAKU ++++\n");
			break;
		}
	}
	current_state = state;

	// Draw everything --------------------------------------
	SDL_Rect* r = &current_animation->GetCurrentFrame();

	if ((position.x + 25) >= (App->player->position.x + 25))
	{
		App->render->BlitWithScale(graphics, position.x + 50 + (-current_animation->pivotx2[current_animation->returnCurrentFrame()]), position.y - r->h + current_animation->pivoty2[current_animation->returnCurrentFrame()], r, -1, 1.0f, 1, TOP_RIGHT);
		ryohitbox->SetPos(position.x + 15, position.y - r->h);

		if (r == &kick.frames[kick.last_frame - 5])
		{
			kickCollider->SetPos(position.x - 65, position.y - r->h);

			kickCollider->Enabled = true;
		}
		else
		{
			kickCollider->Enabled = false;
		}

		if (r == &punch.frames[punch.last_frame - 1])
		{
			punchCollider->SetPos(position.x - 40, position.y + 12 - r->h);

			punchCollider->Enabled = true;
		}
		else
		{
			punchCollider->Enabled = false;
		}

		

	}
	else 
	{
		App->render->Blit(graphics, position.x + (current_animation->pivotx2[current_animation->returnCurrentFrame()]), position.y - r->h + current_animation->pivoty2[current_animation->returnCurrentFrame()], r);
		ryohitbox->SetPos(position.x, position.y - r->h);


		if (r == &kick.frames[kick.last_frame - 5])
		{
			kickCollider->SetPos(position.x + 70, position.y - r->h);

			kickCollider->Enabled = true;
		}
		else
		{
			kickCollider->Enabled = false;
		}

		if (r == &punch.frames[punch.last_frame - 1])
		{
			punchCollider->SetPos(position.x + 32, position.y + 12 - r->h);

			punchCollider->Enabled = true;
		}
		else
		{
			punchCollider->Enabled = false;
		}
	}
	
	
	
	wall = false;



	//Graphis PLAYER 2 WIN!
	if (App->player->Life <= 0)
	{
		App->render->BlitWithScale(graphicsWin, 210, 70, &player2Win, 1, 0.0f, 1.0f, TOP_RIGHT);
	}

	//Stamina increase
	if (App->player2->Stamina < 100)
	{
		App->player2->Stamina = (App->player2->Stamina + 0.05);
	}

	return UPDATE_CONTINUE;
}

king_states ModulePlayer2::process_fsm(p2Qeue<king_inputs>& inputs)
{
	static king_states state = ST_IDLE;
	king_inputs last_input;

	while (inputs.Pop(last_input))
	{
		switch (state)
		{
		case ST_IDLE:
		{
			switch (last_input)
			{
			case IN_RIGHT_DOWN2: state = ST_WALK_FORWARD; break;
			case IN_LEFT_DOWN2: state = ST_WALK_BACKWARD; break;
			case IN_JUMP2: state = ST_JUMP_NEUTRAL; App->input->jump_timer2 = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN2: state = ST_CROUCH; break;
			case IN_Y: state = ST_PUNCH_STANDING, App->input->punch_timer2 = SDL_GetTicks(); break;
			case IN_U: state = ST_KICK_STANDING, App->input->kick_timer2 = SDL_GetTicks(); break;
			case IN_H: state = ST_HADOUKEN, App->input->hadouken_timer2 = SDL_GetTicks(); break;
			case IN_N: state = ST_MOUSHUUKYAKU, App->input->moshuukyaku_timer2 = SDL_GetTicks(); break;
			case IN_M: state = ST_TORNADOKICK, App->input->tornadokick_timer2 = SDL_GetTicks(); break;
				//case IN_DAMAGE_RECEIVED: state = ST_HIT, beat_timer = SDL_GetTicks(); break;

			}
		}
		break;

		case ST_WALK_FORWARD:
		{
			switch (last_input)
			{
			case IN_RIGHT_UP2: state = ST_IDLE; break;
			case IN_LEFT_AND_RIGHT2: state = ST_IDLE; break;
			case IN_JUMP2: state = ST_JUMP_FORWARD;  App->input->jump_timer2 = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN2: state = ST_CROUCH; break;
			case IN_Y: state = ST_PUNCH_STANDING, App->input->punch_timer2 = SDL_GetTicks(); break;
			case IN_U: state = ST_KICK_STANDING, App->input->kick_timer2 = SDL_GetTicks(); break;
			case IN_H: state = ST_HADOUKEN, App->input->hadouken_timer2 = SDL_GetTicks(); break;
			case IN_N: state = ST_MOUSHUUKYAKU, App->input->moshuukyaku_timer2 = SDL_GetTicks(); break;
			case IN_M: state = ST_TORNADOKICK, App->input->tornadokick_timer2 = SDL_GetTicks(); break;
				//case IN_DAMAGE_RECEIVED: state = ST_HIT, beat_timer = SDL_GetTicks(); break;

			}
		}
		break;

		case ST_WALK_BACKWARD:
		{
			switch (last_input)
			{
			case IN_LEFT_UP2: state = ST_IDLE; break;
			case IN_LEFT_AND_RIGHT2: state = ST_IDLE; break;
			case IN_JUMP2: state = ST_JUMP_BACKWARD;  App->input->jump_timer2 = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN2: state = ST_CROUCH; break;
			case IN_Y: state = ST_PUNCH_STANDING, App->input->punch_timer2 = SDL_GetTicks(); break;
			case IN_U: state = ST_KICK_STANDING, App->input->kick_timer2 = SDL_GetTicks(); break;
			case IN_H: state = ST_HADOUKEN, App->input->hadouken_timer2 = SDL_GetTicks(); break;
			case IN_N: state = ST_MOUSHUUKYAKU, App->input->moshuukyaku_timer2 = SDL_GetTicks(); break;
			case IN_M: state = ST_TORNADOKICK, App->input->tornadokick_timer2 = SDL_GetTicks(); break;
				//case IN_DAMAGE_RECEIVED: state = ST_HIT, beat_timer = SDL_GetTicks(); break;

			}
		}
		break;

		case ST_JUMP_NEUTRAL:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH2: state = ST_IDLE; animstart = 0; SFXsound = true; break;
				//case IN_T: state = ST_PUNCH_NEUTRAL_JUMP;  punch_timer = SDL_GetTicks(); animstart = 0; attack = true; break;
				//case IN_R: state = ST_KICK_NEUTRAL_JUMP; kick_timer = SDL_GetTicks(); animstart = 0; attack = true; break;
				//case IN_DAMAGE_RECEIVED: state = ST_HIT, beat_timer = SDL_GetTicks(); break;
			}
		}
		break;

		case ST_JUMP_FORWARD:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH2: state = ST_IDLE; animstart = 0; SFXsound = true; break;
				//case IN_T: state = ST_PUNCH_FORWARD_JUMP;  punch_timer = SDL_GetTicks(); break;
				//case IN_DAMAGE_RECEIVED: state = ST_HIT, beat_timer = SDL_GetTicks(); break;

			}
		}
		break;

		case ST_JUMP_BACKWARD:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH2: state = ST_IDLE; animstart = 0; SFXsound = true; break;
				//case IN_T: state = ST_PUNCH_BACKWARD_JUMP;  punch_timer = SDL_GetTicks(); break;
				//case IN_DAMAGE_RECEIVED: state = ST_HIT, beat_timer = SDL_GetTicks(); break;

			}
		}
		break;

		case ST_PUNCH_NEUTRAL_JUMP:
		{
			switch (last_input)
			{
				//case IN_PUNCH_FINISH: state = ST_JUMP_NEUTRAL; animstart = 0; attack = true; break;
			case IN_JUMP_FINISH2: state = ST_IDLE; break;
				//case IN_DAMAGE_RECEIVED: state = ST_HIT, beat_timer = SDL_GetTicks(); break;

			}
		}
		break;

		case ST_PUNCH_FORWARD_JUMP:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH2: state = ST_JUMP_FORWARD; break;
			case IN_JUMP_FINISH2: state = ST_IDLE; break;
				//case IN_DAMAGE_RECEIVED: state = ST_HIT, beat_timer = SDL_GetTicks(); break;

			}
		}
		break;

		case ST_PUNCH_BACKWARD_JUMP:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH2: state = ST_JUMP_BACKWARD; break;
			case IN_JUMP_FINISH2: state = ST_IDLE; break;
				//case IN_DAMAGE_RECEIVED: state = ST_HIT, beat_timer = SDL_GetTicks(); break;

			}
		}
		break;

		case ST_PUNCH_STANDING:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH2: state = ST_IDLE; animstart = 0; SFXsound = true; break;
				//case IN_DAMAGE_RECEIVED: state = ST_HIT, beat_timer = SDL_GetTicks(); break;


			}
		}
		break;

		case ST_CROUCH:
		{
			switch (last_input)
			{
			case IN_CROUCH_UP2: state = ST_IDLE; break;
			case IN_JUMP_AND_CROUCH2: state = ST_IDLE; break;
			case IN_Y: state = ST_PUNCH_CROUCH; App->input->punch_crouch_timer2 = SDL_GetTicks(); break;
			case IN_U: state = ST_KICK_CROUCH; App->input->kick_crouch_timer2 = SDL_GetTicks(); break;
			}
		}
		break;
		case ST_PUNCH_CROUCH:
		{
			switch (last_input)
			{
			case IN_PUNCH_CROUCH_FINISH2:
				if (IN_CROUCH_DOWN2 == true)
				{
					state = ST_CROUCH; animstart = 0; SFXsound = true;

				}
				else
				{
					state = ST_IDLE; animstart = 0; SFXsound = true;
				}

			}
		}
		break;
		case ST_KICK_STANDING:
		{
			switch (last_input)
			{
			case IN_KICK_FINISH2: state = ST_IDLE; animstart = 0; SFXsound = true; break;

			}

		}break;

		case ST_KICK_NEUTRAL_JUMP:
		{
			switch (last_input)
			{
			case IN_KICK_FINISH2: state = ST_JUMP_NEUTRAL; animstart = 0; SFXsound = true; break;
			case IN_JUMP_FINISH2: state = ST_IDLE; break;
				//case IN_DAMAGE_RECEIVED: state = ST_HIT, beat_timer = SDL_GetTicks(); break;

			}
		}

		case ST_KICK_CROUCH:
		{
			switch (last_input)
			{
			case IN_KICK_CROUCH_FINISH2:
				if (IN_CROUCH_DOWN2 == true)
				{
					state = ST_CROUCH; animstart = 0; SFXsound = true;

				}
				else
				{
					state = ST_IDLE; animstart = 0; SFXsound = true;
				}

			}
		}

		/*case ST_HIT:
		{
		switch (last_input)
		{
		beatanim = false;
		case IN_DAMAGE_RECEIVED_FINISH: state = ST_IDLE; break;
		}
		} break;*/

		case ST_HADOUKEN:
		{
			switch (last_input)
			{
			case IN_HADOUKEN_FINISH2: state = ST_IDLE; animstart = 0; Activehadouken = true; SFXsound = true; break;
			}
			break;

		}

		case ST_MOUSHUUKYAKU:
		{
			switch (last_input)
			{
			case IN_MOUSHUUKYAKU_FINISH2: state = ST_IDLE; animstart = 0; SFXsound = true; break;
			}
			break;

		}

		case ST_TORNADOKICK:
		{
			switch (last_input)
			{
			case IN_TORNADOKICK_FINISH2: state = ST_IDLE; animstart = 0; SFXsound = true; break;
			}
			break;

		}

		}



	}

	return state;
}

void ModulePlayer2::OnCollision(Collider* c1, Collider* c2) {


	if (ryohitbox == c1 && c2->type == COLLIDER_WALL)
	{
		wall = true;
	}

	if (ryohitbox == c1 && c2->type == COLLIDER_PLAYER)
	{/*
		if (App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) {
			speed = 0;

		}
		else if (App->input->keyboard[SDL_SCANCODE_L] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) { //NEWW 
			speed = 0;

		}
		else if (App->input->keyboard[SDL_SCANCODE_J] != NULL && App->input->keyboard[SDL_SCANCODE_D] == NULL) { //when player 2 run and player 1 no(player 2 in the left side)
			speed = 1;
		}
		else if (App->input->keyboard[SDL_SCANCODE_D] != NULL && App->input->keyboard[SDL_SCANCODE_J] == NULL) { //when player 1 run and player 2 no(player 2 in the left side)
			position.x += 2;
		}
		else if (App->input->keyboard[SDL_SCANCODE_L] != NULL && App->input->keyboard[SDL_SCANCODE_A] == NULL) { //when player 2 run and player 1 no (player 2 in the left side)
			speed = 1;
		}
		else if (App->input->keyboard[SDL_SCANCODE_A] != NULL && App->input->keyboard[SDL_SCANCODE_L] == NULL) { //when player 2 run and player 1 no (player 2 in the left side)
			position.x -= 2;
		}

		*/
	}
	if (ryohitbox == c1 && App->scene_King->colliderMap2 == c2)   //Colisions with second wall
	{
		if (App->input->keyboard[SDL_SCANCODE_L] == NULL) {
			position.x -= 2;
		}
		if (App->input->keyboard[SDL_SCANCODE_L] != NULL) {
			speed = 0;
		}
	}
	if (ryohitbox == c1 && App->scene_King->colliderMap == c2)   //Colisions with first wall
	{
		if (App->input->keyboard[SDL_SCANCODE_J] == NULL) {
			position.x += 2;
		}
		if (App->input->keyboard[SDL_SCANCODE_J] != NULL) {
			speed = 0;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////// KICK HITBOX

	if (kickCollider == c1 && c2->type == COLLIDER_PLAYER)
	{
		App->player2->Life--;

	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////// PUNCH HITBOX
	if (punchCollider == c1 && c2->type == COLLIDER_PLAYER)
	{
		App->player2->Life--;
		collision = true;

	}

}
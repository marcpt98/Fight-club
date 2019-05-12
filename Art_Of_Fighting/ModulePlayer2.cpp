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
	idle.PushBack({ 7, 10, 54, 104 });
	idle.PushBack({ 64, 10, 54, 104 });
	idle.PushBack({ 118, 10, 54, 104 });
	idle.speed = 0.14f;

	//jump animation(arcade sprite sheet)
	jumping.PushBack({ 68,140,48,85 });
	jumping.PushBack({ 148,256,68,101 });
	jumping.PushBack({ 68,140,49,85 });
	jumping.speed = 0.05f;

	// walk forward animation (arcade sprite sheet)
	forward.PushBack({ 419, 11, 49, 103 });
	forward.PushBack({ 528, 10, 47, 104 });
	forward.PushBack({ 474, 10, 48, 104 });
	forward.PushBack({ 7, 10, 54, 104 });
	forward.speed = 0.1f;

	//backawrd animation
	backward.PushBack({ 419, 11, 49, 103 });
	backward.PushBack({ 474, 10, 48, 104 });
	backward.PushBack({ 528, 10, 47, 104 });
	backward.speed = 0.1f;

	//punch animation(arcade sprite sheet)

	punch.PushBack({ 15, 476, 48, 102 });
	punch.PushBack({ 314, 10, 94, 100 });
	punch.PushBack({ 15, 476, 48, 102 });
	punch.speed = 0.16f;

	punchJump.PushBack({ 714,141,66,94 });
	punchJump.PushBack({ 780,157,86,78 });
	punchJump.PushBack({ 714,141,66,94 });
	punchJump.speed = 0.15f;															//CHANGE

	punchCrouch.PushBack({ 335,152,70,73 });
	punchCrouch.PushBack({ 405,157,103,68 });
	punchCrouch.PushBack({ 335,152,70,73 });
	punchCrouch.speed = 0.15f;

	//kick animation(arcade sprite sheet)
	kick.PushBack({ 4,593,72,113 });
	kick.PushBack({ 96,593,51,112 });
	kick.PushBack({ 172,593,82,112 });
	kick.PushBack({ 264,599,49,102 });
	kick.PushBack({ 338,607,63,92 });
	kick.speed = 0.15f;

	lowkick.PushBack({ 84, 478, 56, 101 });
	lowkick.PushBack({ 151, 478, 49, 101 });
	lowkick.PushBack({ 211, 478, 86, 101 });
	lowkick.PushBack({ 151, 478, 49, 101 });
	lowkick.PushBack({ 84, 478, 56, 101 });
	lowkick.speed = 0.15f;

	kickJump.PushBack({ 561,146,57,89 });												//CHANGE
	kickJump.PushBack({ 618,149,96,86 });
	kickJump.PushBack({ 561,146,57,89 });
	kickJump.speed = 0.15f;

	kickCrouch.PushBack({ 335,152,70,73 });
	kickCrouch.PushBack({ 405,157,103,68 });
	kickCrouch.PushBack({ 335,152,70,73 });
	kickCrouch.speed = 0.1f;

	// Hadouken ryo animation
	hadouken.PushBack({ 431, 245, 56, 108 });                                        //CHANGE
	hadouken.PushBack({ 498, 245, 49, 100 });
	hadouken.PushBack({ 552, 245, 81, 77 });
	hadouken.PushBack({ 642, 241, 48, 86 });
	hadouken.PushBack({ 724, 241, 53, 99 });

	hadouken.speed = 0.15f;

	// crouch animation
	crouch.PushBack({ 117,133,51,92 });
	crouch.PushBack({ 15,151,49,74 });
	crouch.speed = 0.3f;
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
	graphics = App->textures->Load("media/Spritesheets/king_SpriteSheet.png"); // arcade version
	graphicsWin = App->textures->Load("media/Win/WinPlayer.png");

	kingkick = App->audio->LoadFX("media/FX/king_high_kick.wav");
	kingpunch = App->audio->LoadFX("media/FX/king_punch.wav");
	kingjump = App->audio->LoadFX("media/FX/Ryojump.wav");
	king_punch_crouch = App->audio->LoadFX("media/FX/king_punch_crouch.wav");
	slize_sound = App->audio->LoadFX("media/FX/slize_sound.wav");
	kingKoOuKen = App->audio->LoadFX("media/FX/king_haduken.wav");
	ryoKoOuKensound = App->audio->LoadFX("media/FX/ryoKoOuKensound.wav");

	position.x = 520;
	position.y = 210;
	initialPos = position.y;

	ryohitbox = App->collision->AddCollider({ position.x,position.y, 50, 97 }, COLLIDER_ENEMY, this);
	punchCollider = App->collision->AddCollider({ position.x,position.y, 40, 15 }, COLLIDER_ENEMY, this);
	punchCollider->Enabled = false;
	kickCollider = App->collision->AddCollider({ position.x,position.y, 60, 30 }, COLLIDER_ENEMY, this);
	kickCollider->Enabled = false;
	punchCrouchCollider = App->collision->AddCollider({ position.x, position.y - 70 , 40, 15 }, COLLIDER_ENEMY, this);
	punchCrouchCollider->Enabled = false;
	kickCrouchCollider = App->collision->AddCollider({ position.x, position.y - 70 , 65, 15 }, COLLIDER_ENEMY, this);
	kickCrouchCollider->Enabled = false;

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

				if (attack == true)
				{
					App->audio->PlayFX(kingjump);
					attack = false;
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
				position.x -= 3;

				if (attack == true)
				{
					App->audio->PlayFX(kingjump);
					attack = false;
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
				position.y += jumpSpeed;

				if (attack == true)
				{
					App->audio->PlayFX(kingjump);
					attack = false;
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
			if (attack == true)
			{
				App->audio->PlayFX(king_punch_crouch);
				attack = false;
			}
			if (animstart == 0)
			{
				current_animation = &punchCrouch;
			}

			LOG("PUNCH CROUCHING **++\n");
			break;
		case ST_PUNCH_STANDING:
			if (attack == true)
			{
				App->audio->PlayFX(kingpunch);
				attack = false;
			}
			if (animstart == 0)
			{
				current_animation = &punch;
			}
			LOG("PUNCH STANDING ++++\n");
			break;
		case ST_PUNCH_NEUTRAL_JUMP:
			if (attack == true)
			{
				//App->audio->PlayFX(ryopunch);
				attack = false;
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
			if (attack == true)
			{
				App->audio->PlayFX(king_punch_crouch);
				App->audio->PlayFX(slize_sound);

				attack = false;
			}
			if (animstart == 0)
			{
				current_animation = &kickCrouch;
			}
			LOG("KICK CROUCHING **--\n");
			break;
		case ST_KICK_STANDING:
			if (attack == true)
			{
				App->audio->PlayFX(kingkick);
				attack = false;
			}
			if (animstart == 0)
			{
				current_animation = &kick;
			}
			LOG("KICK --\n")
				break;
		case ST_KICK_NEUTRAL_JUMP:
			if (attack == true)
			{
				//App->audio->PlayFX(ryokick);
				attack = false;
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
					if ((position.x - 25) >= (App->player->position.x + 25))
					{
						App->particles->AddParticle(App->particles->Hadouken1, position.x + 30, position.y - 110, COLLIDER_ENEMY_SHOT);
						App->particles->AddParticle(App->particles->Hadouken2, position.x + 28, position.y - 85, COLLIDER_ENEMY_SHOT, 100);
						App->particles->AddParticle(App->particles->Hadouken3, position.x + 30, position.y - 80, COLLIDER_ENEMY_SHOT, 300);
					}
					else {
						App->particles->AddParticle(App->particles->Hadouken1, position.x - 10, position.y - 110, COLLIDER_ENEMY_SHOT);
						App->particles->AddParticle(App->particles->Hadouken2, position.x - 8, position.y - 85, COLLIDER_ENEMY_SHOT, 100);
						App->particles->AddParticle(App->particles->Hadouken3, position.x - 10, position.y - 80, COLLIDER_ENEMY_SHOT, 300);
					}
					shoot = false;
				}

			}
			Activehadouken = false;
			if (animstart == 0)
			{
				current_animation = &hadouken;
			}
		}
	}
	current_state = state;

	// Draw everything --------------------------------------
	SDL_Rect* r = &current_animation->GetCurrentFrame();



	if ((position.x + 25) >= (App->player->position.x + 25)) {
		App->render->BlitWithScale(graphics, position.x - 50, position.y - r->h, r, -1, 1.0f, 1, TOP_RIGHT);
		if (r == &lowkick.frames[lowkick.last_frame - 1])
		{
			kickCollider->SetPos(position.x - 40, position.y - r->h);

			kickCollider->Enabled = true;
		}
		else
		{
			kickCollider->Enabled = false;
		}

		if (r == &punchCrouch.frames[punchCrouch.last_frame - 1])
		{
			punchCrouchCollider->SetPos(position.x - 50, position.y + 30 - r->h);

			punchCrouchCollider->Enabled = true;
		}
		else
		{
			punchCrouchCollider->Enabled = false;
		}

		if (r == &kickCrouch.frames[kickCrouch.last_frame - 1])
		{
			kickCrouchCollider->SetPos(position.x - 50, position.y + 30 - r->h);

			kickCrouchCollider->Enabled = true;
		}
		else
		{
			kickCrouchCollider->Enabled = false;
		}

	}
	else {
		App->render->Blit(graphics, position.x, position.y - r->h, r);

		if (r == &lowkick.frames[lowkick.last_frame - 1])
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
			punchCollider->SetPos(position.x + 50, position.y + 12 - r->h);

			punchCollider->Enabled = true;
		}
		else
		{
			punchCollider->Enabled = false;
		}

		if (r == &punchCrouch.frames[punchCrouch.last_frame - 1])
		{
			punchCrouchCollider->SetPos(position.x + 50, position.y + 30 - r->h);

			punchCrouchCollider->Enabled = true;
		}
		else
		{
			punchCrouchCollider->Enabled = false;
		}

		if (r == &kickCrouch.frames[kickCrouch.last_frame - 1])
		{
			kickCrouchCollider->SetPos(position.x + 50, position.y + 30 - r->h);

			kickCrouchCollider->Enabled = true;
		}
		else
		{
			kickCrouchCollider->Enabled = false;
		}
	}

	ryohitbox->SetPos(position.x-100, position.y - r->h);
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
				//case IN_DAMAGE_RECEIVED: state = ST_HIT, beat_timer = SDL_GetTicks(); break;

			}
		}
		break;

		case ST_JUMP_NEUTRAL:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH2: state = ST_IDLE; animstart = 0; attack = true; break;
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
			case IN_JUMP_FINISH2: state = ST_IDLE; animstart = 0; attack = true; break;
				//case IN_T: state = ST_PUNCH_FORWARD_JUMP;  punch_timer = SDL_GetTicks(); break;
				//case IN_DAMAGE_RECEIVED: state = ST_HIT, beat_timer = SDL_GetTicks(); break;

			}
		}
		break;

		case ST_JUMP_BACKWARD:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH2: state = ST_IDLE; animstart = 0; attack = true; break;
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
			case IN_PUNCH_FINISH2: state = ST_IDLE; animstart = 0; attack = true; break;
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
					state = ST_CROUCH; animstart = 0; attack = true;

				}
				else
				{
					state = ST_IDLE; animstart = 0; attack = true;
				}

			}
		}
		break;
		case ST_KICK_STANDING:
		{
			switch (last_input)
			{
			case IN_KICK_FINISH2: state = ST_IDLE; animstart = 0; attack = true; break;

			}

		}break;

		case ST_KICK_NEUTRAL_JUMP:
		{
			switch (last_input)
			{
			case IN_KICK_FINISH2: state = ST_JUMP_NEUTRAL; animstart = 0; attack = true; break;
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
					state = ST_CROUCH; animstart = 0; attack = true;

				}
				else
				{
					state = ST_IDLE; animstart = 0; attack = true;
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
			case IN_HADOUKEN_FINISH2: state = ST_IDLE; animstart = 0; Activehadouken = true; break;
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
	if (kickCollider == c1 && c2->type == COLLIDER_PLAYER)
	{
		App->player->Life--;
		if (position.x < App->player->position.x) {
			App->player->position.x += 5;
		}
		else {
			App->player->position.x -= 5;
		}
	}

	if (ryohitbox == c1 && c2->type == COLLIDER_PLAYER)
	{
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
	if (punchCollider == c1 && c2->type == COLLIDER_PLAYER)
	{
		App->player->Life--;
		if (position.x < App->player->position.x) {
			App->player->position.x += 5;
		}
		else {
			App->player->position.x -= 5;
		}
	}

}
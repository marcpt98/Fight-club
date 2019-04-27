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
#include "p2Qeue.h"
#include "SDL/include/SDL.h"
#include "ModuleScenelevel_1.h"

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
	jumping.PushBack({ 0,504,60,82 });
	jumping.PushBack({ 60,456,65,129 });
	jumping.PushBack({ 126,473,61,112 });
	jumping.PushBack({ 245,495,54,91 });
	jumping.speed = 0.15f;

	jumpFalling.PushBack({ 299,471,58, 116 });
	jumpFalling.PushBack({ 0,504,60,82 });
	jumpFalling.speed = 0.1f;
	

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

	beat.PushBack({ 863, 748,66,106 });
	beat.PushBack({ 937, 747,78,109 });
	beat.PushBack({ 863, 748,66,106 });

	player1Win.x = 0;
	player1Win.y = 40;
	player1Win.w = 116;
	player1Win.h = 39;

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

	ryokick = App->audio->LoadFX("media/ryo_kick.wav");
	ryopunch = App->audio->LoadFX("media/Ryo_punch.wav");
	ryojump = App->audio->LoadFX("media/Ryojump.wav");
	ryoKoOuKen= App->audio->LoadFX("media/Ryo_KoOuKen.wav");
	ryoKoOuKensound= App->audio->LoadFX("media/ryoKoOuKensound.wav");

	position.x = 168;
	position.y = 210;

	ryohitbox = App->collision->AddCollider({position.x,position.y, 50, 97 }, COLLIDER_PLAYER, this);
	punchCollider = App->collision->AddCollider({ position.x,position.y, 40, 15 }, COLLIDER_PLAYER, this);
	punchCollider->Enabled = false;
	kickCollider = App->collision->AddCollider({ position.x,position.y, 60, 30 }, COLLIDER_PLAYER, this);
	kickCollider->Enabled = false;
	

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


	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{

	Animation* current_animation = &idle;
	p2Qeue<ryo_inputs> inputs;
	ryo_states current_state = ST_UNKNOWN;

	int speed = 2;

	if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN) {															//God mode 
		if (GodMode == false) 
		{
			ryohitbox->to_delete = true;

			GodMode = true;
		}
		else if (GodMode == true) 
		{
			ryohitbox = App->collision->AddCollider({ position.x,position.y,50, 97 }, COLLIDER_PLAYER, this);
			GodMode = false;
		}
	}

	while (external_input(inputs))
	{
		internal_input(inputs);

		ryo_states state = process_fsm(inputs);

		if (state != current_state)
		{
			switch (state)
			{
			case ST_IDLE:
				current_animation = &idle;
				forward.Reset();
				backward.Reset();
				crouch1.Reset();
				crouch2.Reset();
				kick.Reset();
				punch.Reset();
				break;

			case ST_WALK_FORWARD:
				current_animation = &forward;
				position.x += speed;
				backward.Reset();
				crouch1.Reset();
				crouch2.Reset();				
				kick.Reset();
				punch.Reset();
				break;

			case ST_WALK_BACKWARD:
				current_animation = &backward;
				position.x -= speed;
				forward.Reset();
				crouch1.Reset();
				crouch2.Reset();
				kick.Reset();
				punch.Reset();
				break;

			case ST_JUMP_NEUTRAL:

				Jump = 1;
				speed = 3;

				if(Jump == 1)
				{
					if(position.y == 210)
					{
						JumpMax = false;
						JumpMin = true;
					}
					if(position.y == 150)
					{
						JumpMin = false;
						JumpMax = true;
					}

					if(JumpMin == true)
					{
						jumpFalling.Reset();
						position.y -= speed;
						current_animation = &jumping;
					}
					if (JumpMax == true)
					{
						jumping.Reset();
						position.y += speed;
						current_animation = &jumpFalling;
					}
					
				}break;

			case ST_JUMP_FORWARD:
				LOG("JUMPING FORWARD ^^>>\n");
				break;
			case ST_JUMP_BACKWARD:
				LOG("JUMPING BACKWARD ^^<<\n");
				break;
			case ST_CROUCH:
				current_animation = &crouch1;	
				current_animation = &crouch2;

				LOG("CROUCHING ****\n");
				break;
			case ST_PUNCH_CROUCH:
				LOG("PUNCH CROUCHING **++\n");
				break;
			case ST_PUNCH_STANDING:
				current_animation = &punch;
				LOG("PUNCH STANDING ++++\n");
				break;
			case ST_PUNCH_NEUTRAL_JUMP:
				LOG("PUNCH NEUTRAL JUMP ++++\n");
			case ST_PUNCH_FORWARD_JUMP:
				LOG("PUNCH JUMP FORWARD ^>>+\n");
				break;
			case ST_PUNCH_BACKWARD_JUMP:
				LOG("PUNCH JUMP BACKWARD ^<<+\n");
				break;
			case ST_KICK_CROUCH:
				LOG("KICK CROUCHING **--\n");
				break;
			case ST_KICK_STANDING:
				current_animation = &kick;
				break;
			case ST_KICK_NEUTRAL_JUMP:
				LOG("KICK JUMP NEUTRAL ^^--\n");
				break;
			case ST_KICK_FORWARD_JUMP:
				LOG("KICK JUMP FORWARD ^>>-\n");
				break;
			case ST_KICK_BACKWARD_JUMP:
				LOG("KICK JUMP BACKWARD ^<<-\n");
				break;
			case ST_DAMAGE_RECEIVED:
				current_animation = &beat;
				break;
			}
		}
		current_state = state;

		/*
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

		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN)                             //   JUMP
		{
			if (animStart == 0) {
				App->audio->PlayFX(ryojump);
				current_animation = &jump;
				position.y -= jSpeed;


				if (position.y < 120) {
					jSpeed -= 0.5;
					if (jSpeed < 0) jSpeed = -6;
				}
				if (position.y >= InitialPosition && jSpeed < 0) {
					animStart = 1;
					position.y = InitialPosition;
					jSpeed = 6;
				}
			}
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
		speed = 2;*/
		////////////////////////////////////////////////////////////////////////////
		/*
		if (App->input->keyboard[SDL_SCANCODE_ESCAPE] == KEY_STATE::KEY_DOWN) {															//Get out of game

			return UPDATE_STOP;
		}
		*/



		// Draw everything --------------------------------------
		SDL_Rect* r = &current_animation->GetCurrentFrame();

		App->render->Blit(graphics, position.x, position.y - r->h, r);

		ryohitbox->SetPos(position.x, position.y - r->h);

		wall = false;


		if (r == &kick.frames[kick.last_frame - 1])
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


		if (App->player2->Life <= 0)
		{
			App->render->BlitWithScale(graphicsWin, 210, 70, &player1Win, 1, 0.0f, 1.0f, TOP_RIGHT);
		}

		return UPDATE_CONTINUE;
	}
}


void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {

	if (ryohitbox == c1 && c2->type == COLLIDER_WALL)
	{
		wall = true;
	}
	
	if (ryohitbox == c1 && c2->type == COLLIDER_ENEMY)
	{
		if (App->input->keyboard[SDL_SCANCODE_A] == NULL && App->input->keyboard[SDL_SCANCODE_D] == NULL && App->input->keyboard[SDL_SCANCODE_J] == NULL && App->input->keyboard[SDL_SCANCODE_L] == NULL && position.x < App->player2->position.x) {
			position.x--;
		}
		if (App->input->keyboard[SDL_SCANCODE_A] == NULL && App->input->keyboard[SDL_SCANCODE_D] == NULL && App->input->keyboard[SDL_SCANCODE_J] == NULL && App->input->keyboard[SDL_SCANCODE_L] == NULL && position.x > App->player2->position.x) {
			position.x++;
		}
		if (App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) {
			speed = 0;

		}
		else if (App->input->keyboard[SDL_SCANCODE_L] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) { //NEW
			speed = 0;
		}
		else if (App->input->keyboard[SDL_SCANCODE_J] != NULL && App->input->keyboard[SDL_SCANCODE_D] == NULL) { //when player 2 run and player 1 no (player 2 in the left side)
			position.x -= 2;
		}
		else if (App->input->keyboard[SDL_SCANCODE_D] != NULL && App->input->keyboard[SDL_SCANCODE_J] == NULL) { //when player 1 run and player 2 no (player 1 in the left side)
			speed = 1;
		}
		else if (App->input->keyboard[SDL_SCANCODE_L] != NULL && App->input->keyboard[SDL_SCANCODE_A] == NULL) { //when player 2 run and player 1 no (player 2 in the left side)
			position.x += 2;
		}
		else if (App->input->keyboard[SDL_SCANCODE_A] != NULL && App->input->keyboard[SDL_SCANCODE_L] == NULL) { //when player 2 run and player 1 no (player 2 in the left side)
			speed = 1;
		}

	}

	if (ryohitbox == c1 && App->scene_Todoh->colliderMap2 == c2)   //Colisions with second wall
	{
		if (App->input->keyboard[SDL_SCANCODE_A] == NULL) {
			speed = 0;
			position.x -= 2;
		}
		if (App->input->keyboard[SDL_SCANCODE_A] != NULL) {
			speed = 2;
		}
	}
	if (ryohitbox == c1 && App->scene_Todoh->colliderMap == c2)   //Colisions with first wall
	{
		if (App->input->keyboard[SDL_SCANCODE_D] == NULL) {
			speed = 0;
			position.x += 2;
		}
		if (App->input->keyboard[SDL_SCANCODE_D] != NULL) {
			speed = 2;
		}
	}
	if (kickCollider == c1 && c2->type == COLLIDER_ENEMY)
	{
		App->player2->Life--;


		if ((App->player2->position.x) <= (App->scene_Todoh->positionlimitright.x + 300)) {
			App->player2->position.x += 5;
		}

		if ((App->player2->position.x) >= (App->scene_Todoh->positionlimitright.x + 300)) {
			position.x -= 5;
			App->player2->position.x -= 3;
		}

	}

	if (punchCollider == c1 && c2->type == COLLIDER_ENEMY)
	{
		App->player2->Life--;

		if ((App->player2->position.x) <= (App->scene_Todoh->positionlimitright.x + 300)) {
			App->player2->position.x += 5;
		}

		if ((App->player2->position.x) >= (App->scene_Todoh->positionlimitright.x + 300)) {
			position.x -= 5;
			App->player2->position.x -= 3;
		}
	}
	
}

bool ModulePlayer::external_input(p2Qeue<ryo_inputs>& inputs)
{
	static bool left = false;
	static bool right = false;
	static bool down = false;
	static bool up = false;

	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_KEYUP && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				return false;
				break;
			case SDLK_s:
				inputs.Push(IN_CROUCH_UP);
				down = false;
				break;
			case SDLK_w:
				up = false;
				break;
			case SDLK_a:
				inputs.Push(IN_LEFT_UP);
				left = false;
				break;
			case SDLK_d:
				inputs.Push(IN_RIGHT_UP);
				right = false;
				break;
			case SDLK_r:
				return false;
				break;
			case SDLK_t:
				return false;
				break;
			}
		}
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_r:
				inputs.Push(IN_R);
				App->audio->PlayFX(ryokick);
				break;
			case SDLK_t:
				inputs.Push(IN_T);
				App->audio->PlayFX(ryopunch);
				break;
			case SDLK_w:
				up = true;
				App->audio->PlayFX(ryojump);
				break;
			case SDLK_s:
				down = true;
				break;
			case SDLK_a:
				left = true;
				break;
			case SDLK_d:
				right = true;
				break;
			}
		}
	}

	if (left && right)
		inputs.Push(IN_LEFT_AND_RIGHT);
	{
		if (left)
			inputs.Push(IN_LEFT_DOWN);
		if (right)
			inputs.Push(IN_RIGHT_DOWN);
	}

	if (up && down)
		inputs.Push(IN_JUMP_AND_CROUCH);
	else
	{
		if (down)
			inputs.Push(IN_CROUCH_DOWN);
		if (up)
			inputs.Push(IN_JUMP);
	}

	return true;
}

void ModulePlayer::internal_input(p2Qeue<ryo_inputs>& inputs)
{
	if (jump_timer > 0)
	{
		if (SDL_GetTicks() - jump_timer > JUMP_TIME)
		{
			inputs.Push(IN_JUMP_FINISH);
			jump_timer = 0;
		}
	}

	if (punch_timer > 0)
	{
		if (SDL_GetTicks() - punch_timer > PUNCH_TIME)
		{
			inputs.Push(IN_PUNCH_FINISH);
			punch_timer = 0;
		}
	}

	if (kick_timer > 0)
	{
		if (SDL_GetTicks() - kick_timer > KICK_TIME)
		{
			inputs.Push(IN_KICK_FINISH);
			kick_timer = 0;
		}
	}
}
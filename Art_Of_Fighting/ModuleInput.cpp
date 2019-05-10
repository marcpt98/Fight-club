#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "p2Qeue.h"

ModuleInput::ModuleInput() : Module()
{
	for (uint i = 0; i < MAX_KEYS; ++i)
		keyboard[i] = KEY_IDLE;
}

// Destructor
ModuleInput::~ModuleInput()
{
}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleInput::external_input()
{

	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYUP && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				return false;
				break;
				//PLAYER 1
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
				//PLAYER 2
			case SDLK_k:
				inputs2.Push(IN_CROUCH_UP2);
				down2 = false;
				break;
			case SDLK_i:
				up2 = false;
				break;
			case SDLK_j:
				inputs2.Push(IN_LEFT_UP2);
				left2 = false;
				break;
			case SDLK_l:
				inputs2.Push(IN_RIGHT_UP2);
				right2 = false;
				break;
			}
		}
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
				//PLAYER 1
			case SDLK_r:
				inputs.Push(IN_R);
				break;
			case SDLK_t:
				inputs.Push(IN_T);
				break;
			case SDLK_f:
				inputs.Push(IN_F);
				break;
			case SDLK_w:
				up = true;
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
				//PLAYER 2
			case SDLK_u:
				inputs2.Push(IN_U);
				break;
			case SDLK_y:
				inputs2.Push(IN_Y);
				break;
			case SDLK_h:
				inputs2.Push(IN_H);
				break;
			case SDLK_i:
				up2 = true;
				break;
			case SDLK_k:
				down2 = true;
				break;
			case SDLK_j:
				left2 = true;
				break;
			case SDLK_l:
				right2 = true;
				break;
			}
		}
	}

	//PLAYER 1
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

	//PLAYER 2
	if (left2 && right2)
		inputs2.Push(IN_LEFT_AND_RIGHT2);
	{
		if (left2)
			inputs2.Push(IN_LEFT_DOWN2);
		if (right2)
			inputs2.Push(IN_RIGHT_DOWN2);
	}

	if (up2 && down2)
		inputs2.Push(IN_JUMP_AND_CROUCH2);
	else
	{
		if (down2)
			inputs2.Push(IN_CROUCH_DOWN2);
		if (up2)
			inputs2.Push(IN_JUMP2);
	}

	return true;
}

void ModuleInput::internal_input(p2Qeue<king_inputs>& inputs, p2Qeue<king_inputs>& inputs2)
{
	//PLAYER 1
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

	if (punch_crouch_timer > 0)
	{
		if (SDL_GetTicks() - punch_crouch_timer > PUNCH_CROUCH_TIME)
		{
			inputs.Push(IN_PUNCH_CROUCH_FINISH);
			punch_crouch_timer = 0;
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

	if (kick_crouch_timer > 0)
	{
		if (SDL_GetTicks() - kick_crouch_timer > KICK_TIME)
		{
			inputs.Push(IN_KICK_CROUCH_FINISH);
			kick_crouch_timer = 0;
		}
	}

	if (hadouken_timer > 0)
	{
		if (SDL_GetTicks() - hadouken_timer > HADOUKEN_TIME)
		{
			inputs.Push(IN_HADOUKEN_FINISH);
			hadouken_timer = 0;
		}
	}

	/*if (beat_timer > 0)
	{
	if (SDL_GetTicks() - beat_timer > BEAT_TIME)
	{
	inputs.Push(IN_DAMAGE_RECEIVED_FINISH);
	beat_timer = 0;
	collision = false;
	}
	}*/

	//PLAYER 2
	if (jump_timer2 > 0)
	{
		if (SDL_GetTicks() - jump_timer2 > JUMP_TIME)
		{
			inputs2.Push(IN_JUMP_FINISH2);
			jump_timer2 = 0;
		}
	}

	if (punch_timer2 > 0)
	{
		if (SDL_GetTicks() - punch_timer2 > PUNCH_TIME)
		{
			inputs2.Push(IN_PUNCH_FINISH2);
			punch_timer2 = 0;
		}
	}

	if (punch_crouch_timer2 > 0)
	{
		if (SDL_GetTicks() - punch_crouch_timer2 > PUNCH_CROUCH_TIME)
		{
			inputs2.Push(IN_PUNCH_CROUCH_FINISH2);
			punch_crouch_timer2 = 0;
		}
	}

	if (kick_timer2 > 0)
	{
		if (SDL_GetTicks() - kick_timer2 > KICK_TIME)
		{
			inputs2.Push(IN_KICK_FINISH2);
			kick_timer2 = 0;
		}
	}

	if (kick_crouch_timer2 > 0)
	{
		if (SDL_GetTicks() - kick_crouch_timer2 > KICK_TIME)
		{
			inputs2.Push(IN_KICK_CROUCH_FINISH2);
			kick_crouch_timer2 = 0;
		}
	}

	if (hadouken_timer2 > 0)
	{
		if (SDL_GetTicks() - hadouken_timer2 > HADOUKEN_TIME)
		{
			inputs2.Push(IN_HADOUKEN_FINISH2);
			hadouken_timer2 = 0;
		}
	}

	/*if (beat_timer > 0)
	{
	if (SDL_GetTicks() - beat_timer > BEAT_TIME)
	{
	inputs.Push(IN_DAMAGE_RECEIVED_FINISH);
	beat_timer = 0;
	collision = false;
	}
	}*/
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
	SDL_PumpEvents();

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	if (keyboard[SDL_SCANCODE_ESCAPE])
		return update_status::UPDATE_STOP;

	// Para el input que sean estados
	if (external_input() == false) { return update_status::UPDATE_STOP; }
	else {
		internal_input(inputs, inputs2);
	}

	return update_status::UPDATE_CONTINUE;

	SDL_PumpEvents();
}

update_status ModuleInput::PostUpdate() {
	key = -1;
	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}

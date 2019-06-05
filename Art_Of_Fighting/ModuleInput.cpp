#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "p2Qeue.h"
#include "SDL/include/SDL_gamecontroller.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"

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
	
	
	bool ret = true;
	SDL_Init(0);
	SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	if (SDL_NumJoysticks() < 1)
	{
		LOG("Warning: No joysticks connected!\n");
	}
	else
	{
		//Load joystick
		gGameController = SDL_GameControllerOpen(0);
		gGameController2 = SDL_GameControllerOpen(1);

		if (gGameController == NULL)
		{
			LOG("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
		}
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
			case SDLK_v:
				inputs.Push(IN_CHARGE_UP);
				charge = false;
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
			case SDLK_b:
				inputs2.Push(IN_CHARGE_UP2);
				charge2 = false;
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
			case SDLK_c:
				inputs.Push(IN_C);
				break;
			case SDLK_x:
				inputs.Push(IN_X);
				break;
			case SDLK_w:
				up = true;
				break;
			case SDLK_v:
				charge = true;
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
			case SDLK_n:
				inputs2.Push(IN_N);
				break;
			case SDLK_m:
				inputs2.Push(IN_M);
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
			case SDLK_b:
				charge2 = true;
				break;
			}
		}
		if (event.type == SDL_CONTROLLERAXISMOTION) 
		{
			if (event.jaxis.which == 0) 
			{ 
				//PLAYER 1 GAMEPAD
				if (event.jaxis.axis == 0)
				{
					//Left of dead zone
					if (event.jaxis.value < -JOYSTICK_DEAD_ZONE)
					{
						left = true;
						right = false;
					}
					//Right of dead zone
					else if (event.jaxis.value > JOYSTICK_DEAD_ZONE)
					{
						right = true;
						left = false;
					}
					else
					{
						left = false;
						right = false;
					}
				}
				else if (event.jaxis.axis == 1)
				{
					//Below of dead zone
					if (event.jaxis.value < -JOYSTICK_DEAD_ZONE)
					{
						down = false;
						up = true;
					}
					//Above of dead zone
					else if (event.jaxis.value > JOYSTICK_DEAD_ZONE)
					{
						up = false;
						down = true;
					}
					else
					{
						down = false;
						up = false;
					}
				}
			}

			//Player 2 GAMEPAD
			if (event.jaxis.which == 1) //En el gamepad 2
			{ 
				if (event.jaxis.axis == 0)
				{
					//Left of dead zone
					if (event.jaxis.value < -JOYSTICK_DEAD_ZONE)
					{
						left2 = true;
						right2 = false;
					}
					//Right of dead zone
					else if (event.jaxis.value > JOYSTICK_DEAD_ZONE)
					{
						right2 = true;
						left2 = false;
					}
					else
					{
						left2 = false;
						right2 = false;
					}
				}
				else if (event.jaxis.axis == 1)
				{
					//Below of dead zone
					if (event.jaxis.value < -JOYSTICK_DEAD_ZONE)
					{
						down2 = false;
						up2 = true;
					}
					//Above of dead zone
					else if (event.jaxis.value > JOYSTICK_DEAD_ZONE)
					{
						up2 = false;
						down2 = true;
					}
					else
					{
						down2 = false;
						up2 = false;
					}
				}
			}
			

		}

		//EXIT GAME
		//PLAYER 1
		if (SDL_GameControllerGetButton(gGameController2, SDL_CONTROLLER_BUTTON_BACK) == 1)
		{
			return false;
		}
		//PLAYER 2
		if (SDL_GameControllerGetButton(gGameController, SDL_CONTROLLER_BUTTON_BACK) == 1)
		{
			return false;
		}

		//PLAYER 1 GAMEPAD BUTTONS
		if (SDL_GameControllerGetButton(gGameController2, SDL_CONTROLLER_BUTTON_X) == 1)
		{
			inputs.Push(IN_T);
		}
		if (SDL_GameControllerGetButton(gGameController2, SDL_CONTROLLER_BUTTON_Y) == 1)
		{
			inputs.Push(IN_R);
		}
		if (SDL_GameControllerGetButton(gGameController2, SDL_CONTROLLER_BUTTON_B) == 1)
		{
			inputs.Push(IN_D);
		}
		//COMBOS PLAYER 1
		if (SDL_GameControllerGetButton(gGameController2, SDL_CONTROLLER_BUTTON_A) == 1)
		{
			inputs.Push(IN_F);
		}
		if (SDL_GameControllerGetButton(gGameController2, SDL_CONTROLLER_BUTTON_LEFTSHOULDER) == 1)
		{
			inputs.Push(IN_C);
		}
		if (SDL_GameControllerGetButton(gGameController2, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) == 1)
		{
		inputs.Push(IN_X);
		}

		//PLAYER 2 GAMEPAD BUTTONS
		if (SDL_GameControllerGetButton(gGameController, SDL_CONTROLLER_BUTTON_X) == 1)
		{
			inputs2.Push(IN_Y);
		}
		if (SDL_GameControllerGetButton(gGameController, SDL_CONTROLLER_BUTTON_Y) == 1)
		{
			inputs2.Push(IN_U);
		}
		//COMBOS PLAYER 2
		if (SDL_GameControllerGetButton(gGameController, SDL_CONTROLLER_BUTTON_A) == 1)
		{
			inputs2.Push(IN_H);
		}
		if (SDL_GameControllerGetButton(gGameController, SDL_CONTROLLER_BUTTON_LEFTSHOULDER) == 1)
		{
			inputs2.Push(IN_N);
		}
		if (SDL_GameControllerGetButton(gGameController, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) == 1)
		{
			inputs2.Push(IN_M);
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

		if (!left)
			inputs.Push(IN_LEFT_UP);
		if (!right)
			inputs.Push(IN_RIGHT_UP);
		if (!down)
			inputs.Push(IN_CROUCH_UP);
		if (!charge)
			inputs.Push(IN_CHARGE_UP);

		if (up && down)
			inputs.Push(IN_JUMP_AND_CROUCH);
		else
		{
			if (down)
				inputs.Push(IN_CROUCH_DOWN);
			if (up)
				inputs.Push(IN_JUMP);
		}
		if (charge)
			inputs.Push(IN_CHARGE_DOWN);

		//PLAYER 2
		if (left2 && right2)
			inputs2.Push(IN_LEFT_AND_RIGHT2);
		{
			if (left2)
				inputs2.Push(IN_LEFT_DOWN2);
			if (right2)
				inputs2.Push(IN_RIGHT_DOWN2);
		}
		
		if (!left2)
			inputs2.Push(IN_LEFT_UP2);
		if (!right2)
			inputs2.Push(IN_RIGHT_UP2);
		if (!down2)
			inputs2.Push(IN_CROUCH_UP2);
		if (!charge2)
			inputs2.Push(IN_CHARGE_UP2);
		
		if (up2 && down2)
			inputs2.Push(IN_JUMP_AND_CROUCH2);
		else
		{
			if (down2)
				inputs2.Push(IN_CROUCH_DOWN2);
			if (up2)
				inputs2.Push(IN_JUMP2);
		}
		if (charge2)
			inputs2.Push(IN_CHARGE_DOWN2);
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
	if (low_kick_timer > 0)
	{
		if (SDL_GetTicks() - low_kick_timer > LOW_KICK_TIME)
		{
			inputs.Push(IN_LOW_KICK_FINISH);
			low_kick_timer = 0;
		}
	}

	if (kick_crouch_timer > 0)
	{
		if (SDL_GetTicks() - kick_crouch_timer > KICK_CROUCH_TIME)
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

	if (moshuukyaku_timer > 0)
	{
		if (SDL_GetTicks() - moshuukyaku_timer > MOUSHUUKYAKU_TIME)
		{
			inputs.Push(IN_MOUSHUUKYAKU_FINISH);
			moshuukyaku_timer = 0;
		}
	}

	if (tornadokick_timer > 0)
	{
		if (SDL_GetTicks() - tornadokick_timer > TORNADOKICK_TIME)
		{
			inputs.Push(IN_TORNADOKICK_FINISH);
			tornadokick_timer = 0;
		}
	}

	if (damage_timer > 0)
	{
		if (SDL_GetTicks() - damage_timer > DAMAGE_TIME)
		{
			inputs.Push(IN_DAMAGE_FINISH);
			damage_timer = 0;
			App->player->damageP2 = false;
		}
	}

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
		if (SDL_GetTicks() - kick_crouch_timer2 > KICK_CROUCH_TIME)
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

	if (moshuukyaku_timer2 > 0)
	{
		if (SDL_GetTicks() - moshuukyaku_timer2 > MOUSHUUKYAKU_TIME)
		{
			inputs2.Push(IN_MOUSHUUKYAKU_FINISH2);
			moshuukyaku_timer2 = 0;
		}
	}

	if (tornadokick_timer2 > 0)
	{
		if (SDL_GetTicks() - tornadokick_timer2 > TORNADOKICK_TIME)
		{
			inputs2.Push(IN_TORNADOKICK_FINISH2);
			tornadokick_timer2 = 0;
		}
	}

	if (damage_timer2 > 0)
	{
		if (SDL_GetTicks() - damage_timer2 > DAMAGE_TIME)
		{
			inputs2.Push(IN_DAMAGE_FINISH2);
			damage_timer2 = 0;
			App->player2->damageP1 = false;
		}
	}
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
	SDL_GameControllerClose(gGameController);
	SDL_GameControllerClose(gGameController2);
	gGameController = NULL;
	gGameController2 = NULL;
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}

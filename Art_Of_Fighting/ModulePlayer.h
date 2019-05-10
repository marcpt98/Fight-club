#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2Qeue.h"
#include "SDL/include/SDL_timer.h"

#define MAX_KEYS 300
#define JUMP_TIME 820
#define PUNCH_TIME 200
#define KICK_TIME  530
#define PUNCH_CROUCH_TIME 320
#define KICK_CROUCH_TIME 600
#define HADOUKEN_TIME  550
//#define BEAT_TIME  500


struct SDL_Texture;

class ModulePlayer : public Module
{
private:
	bool wall = false;
	int speed = 2;
	int animstart = 0;
	float jumpSpeed = 6;
	int initialPos;
	bool attack = true;
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	bool JumpMax = false;
	bool JumpMin = false;
	bool Activehadouken = true;
	//bool beatanim = false;
	bool damage = false;
	bool collision = false;
	bool shoot = false;
public:

	int font_score = -1;
	SDL_Texture* graphics = nullptr;
	SDL_Texture * graphicsWin = nullptr;
	SDL_Texture * graphicsbeat = nullptr;
	Animation* current_animation = nullptr;
	Animation* current_animation2 = nullptr;
	Animation idle;
	Animation jumping;
	Animation forward;
	Animation backward;
	Animation crouch;
	//Animation beat;
	iPoint position;
	Animation hadouken;
	Animation punch;
	Animation punchJump;
	Animation punchCrouch;
	Animation kick;
	Animation lowkick;
	Animation kickJump;
	Animation kickCrouch;
	Collider *ryohitbox;
	Collider *kickCollider;
	Collider *kickCrouchCollider;
	Collider *punchCollider;
	Collider *punchCrouchCollider;
	SDL_Rect player1Win;

	Uint32 jump_timer = 0;
	Uint32 punch_timer = 0;
	Uint32 punch_crouch_timer = 0;
	Uint32 kick_timer = 0;
	Uint32 kick_crouch_timer = 0;
	Uint32 hadouken_timer = 0;
	Uint32 beat_timer = 0;

	void OnCollision(Collider* c1, Collider* c2);
	int Life = 100;
	float MaxLife = 100;
	float Stamina = 100;
	float MaxStamina = 100;
	int time = 0;
	int ryokick = 0;
	int ryopunch = 0;
	int ryojump = 0;
	int ryoKoOuKen = 0;
	int ryoKoOuKensound = 0;
	int GodMode = false;
	int printMode = false;
	enum ryo_states
	{
		ST_UNKNOWN,

		ST_IDLE,
		ST_WALK_FORWARD,
		ST_WALK_BACKWARD,
		ST_JUMP_NEUTRAL,
		ST_JUMP_FORWARD,
		ST_JUMP_BACKWARD,
		ST_CROUCH,
		ST_PUNCH_STANDING,
		ST_PUNCH_NEUTRAL_JUMP,
		ST_PUNCH_FORWARD_JUMP,
		ST_PUNCH_BACKWARD_JUMP,
		ST_PUNCH_CROUCH,
		ST_KICK_STANDING,
		ST_KICK_NEUTRAL_JUMP,
		ST_KICK_FORWARD_JUMP,
		ST_KICK_BACKWARD_JUMP,
		ST_KICK_CROUCH,
		ST_HIT,
		ST_HADOUKEN
	};

	enum ryo_inputs
	{
		IN_LEFT_DOWN,
		IN_LEFT_UP,
		IN_RIGHT_DOWN,
		IN_RIGHT_UP,
		IN_LEFT_AND_RIGHT,
		IN_JUMP,
		IN_CROUCH_UP,
		IN_CROUCH_DOWN,
		IN_JUMP_AND_CROUCH,
		IN_Y,
		IN_T,
		IN_R,
		IN_F,
		IN_JUMP_FINISH,
		IN_PUNCH_FINISH,
		IN_PUNCH_CROUCH_FINISH,
		IN_KICK_FINISH,
		IN_KICK_CROUCH_FINISH,
		//IN_DAMAGE_RECEIVED,
		//IN_DAMAGE_RECEIVED_FINISH,
		IN_HADOUKEN_FINISH
	};

	bool external_input(p2Qeue<ryo_inputs>&);

	void internal_input(p2Qeue<ryo_inputs>&);

	ryo_states ModulePlayer::process_fsm(p2Qeue<ryo_inputs>& inputs)
	{
		static ryo_states state = ST_IDLE;
		ryo_inputs last_input;

		while (inputs.Pop(last_input))
		{
			switch (state)
			{
			case ST_IDLE:
			{
				switch (last_input)
				{
				case IN_RIGHT_DOWN: state = ST_WALK_FORWARD; break;
				case IN_LEFT_DOWN: state = ST_WALK_BACKWARD; break;
				case IN_JUMP: state = ST_JUMP_NEUTRAL; jump_timer = SDL_GetTicks();  break;
				case IN_CROUCH_DOWN: state = ST_CROUCH; break;
				case IN_T: state = ST_PUNCH_STANDING, punch_timer = SDL_GetTicks(); break;
				case IN_R: state = ST_KICK_STANDING, kick_timer = SDL_GetTicks(); break;
				case IN_F: state = ST_HADOUKEN, hadouken_timer = SDL_GetTicks(); break;
					//case IN_DAMAGE_RECEIVED: state = ST_HIT, beat_timer = SDL_GetTicks(); break;

				}
			}
			break;

			case ST_WALK_FORWARD:
			{
				switch (last_input)
				{
				case IN_RIGHT_UP: state = ST_IDLE; break;
				case IN_LEFT_AND_RIGHT: state = ST_IDLE; break;
				case IN_JUMP: state = ST_JUMP_FORWARD;  jump_timer = SDL_GetTicks();  break;
				case IN_CROUCH_DOWN: state = ST_CROUCH; break;
				case IN_T: state = ST_PUNCH_STANDING, punch_timer = SDL_GetTicks(); break;
				case IN_R: state = ST_KICK_STANDING, kick_timer = SDL_GetTicks(); break;
				case IN_F: state = ST_HADOUKEN, hadouken_timer = SDL_GetTicks(); break;
					//case IN_DAMAGE_RECEIVED: state = ST_HIT, beat_timer = SDL_GetTicks(); break;

				}
			}
			break;

			case ST_WALK_BACKWARD:
			{
				switch (last_input)
				{
				case IN_LEFT_UP: state = ST_IDLE; break;
				case IN_LEFT_AND_RIGHT: state = ST_IDLE; break;
				case IN_JUMP: state = ST_JUMP_BACKWARD;  jump_timer = SDL_GetTicks();  break;
				case IN_CROUCH_DOWN: state = ST_CROUCH; break;
				case IN_T: state = ST_PUNCH_STANDING, punch_timer = SDL_GetTicks(); break;
				case IN_R: state = ST_KICK_STANDING, kick_timer = SDL_GetTicks(); break;
				case IN_F: state = ST_HADOUKEN, hadouken_timer = SDL_GetTicks(); break;
					//case IN_DAMAGE_RECEIVED: state = ST_HIT, beat_timer = SDL_GetTicks(); break;

				}
			}
			break;

			case ST_JUMP_NEUTRAL:
			{
				switch (last_input)
				{
				case IN_JUMP_FINISH: state = ST_IDLE; animstart = 0; attack = true; break;
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
				case IN_JUMP_FINISH: state = ST_IDLE; animstart = 0; attack = true; break;
					//case IN_T: state = ST_PUNCH_FORWARD_JUMP;  punch_timer = SDL_GetTicks(); break;
					//case IN_DAMAGE_RECEIVED: state = ST_HIT, beat_timer = SDL_GetTicks(); break;

				}
			}
			break;

			case ST_JUMP_BACKWARD:
			{
				switch (last_input)
				{
				case IN_JUMP_FINISH: state = ST_IDLE; animstart = 0; attack = true; break;
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
				case IN_JUMP_FINISH: state = ST_IDLE; break;
					//case IN_DAMAGE_RECEIVED: state = ST_HIT, beat_timer = SDL_GetTicks(); break;

				}
			}
			break;

			case ST_PUNCH_FORWARD_JUMP:
			{
				switch (last_input)
				{
				case IN_PUNCH_FINISH: state = ST_JUMP_FORWARD; break;
				case IN_JUMP_FINISH: state = ST_IDLE; break;
					//case IN_DAMAGE_RECEIVED: state = ST_HIT, beat_timer = SDL_GetTicks(); break;

				}
			}
			break;

			case ST_PUNCH_BACKWARD_JUMP:
			{
				switch (last_input)
				{
				case IN_PUNCH_FINISH: state = ST_JUMP_BACKWARD; break;
				case IN_JUMP_FINISH: state = ST_IDLE; break;
					//case IN_DAMAGE_RECEIVED: state = ST_HIT, beat_timer = SDL_GetTicks(); break;

				}
			}
			break;

			case ST_PUNCH_STANDING:
			{
				switch (last_input)
				{
				case IN_PUNCH_FINISH: state = ST_IDLE; animstart = 0; attack = true; break;
					//case IN_DAMAGE_RECEIVED: state = ST_HIT, beat_timer = SDL_GetTicks(); break;


				}
			}
			break;

			case ST_CROUCH:
			{
				switch (last_input)
				{
				case IN_CROUCH_UP: state = ST_IDLE; break;
				case IN_JUMP_AND_CROUCH: state = ST_IDLE; break;
				case IN_T: state = ST_PUNCH_CROUCH; punch_crouch_timer = SDL_GetTicks(); break;
				case IN_R: state = ST_KICK_CROUCH; kick_crouch_timer = SDL_GetTicks(); break;
				}
			}
			break;
			case ST_PUNCH_CROUCH:
			{
				switch (last_input)
				{
				case IN_PUNCH_CROUCH_FINISH:
					if (IN_CROUCH_DOWN == true)
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
				case IN_KICK_FINISH: state = ST_IDLE; animstart = 0; attack = true; break;

				}

			}break;

			case ST_KICK_NEUTRAL_JUMP:
			{
				switch (last_input)
				{
				case IN_KICK_FINISH: state = ST_JUMP_NEUTRAL; animstart = 0; attack = true; break;
				case IN_JUMP_FINISH: state = ST_IDLE; break;
					//case IN_DAMAGE_RECEIVED: state = ST_HIT, beat_timer = SDL_GetTicks(); break;

				}
			}

			case ST_KICK_CROUCH:
			{
				switch (last_input)
				{
				case IN_KICK_CROUCH_FINISH:
					if (IN_CROUCH_DOWN == true)
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
				case IN_HADOUKEN_FINISH: state = ST_IDLE; animstart = 0; Activehadouken = true; break;
				}
				break;

			}
			}



		}

		return state;
	}
};

#endif
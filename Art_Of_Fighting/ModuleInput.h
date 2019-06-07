#ifndef ModuleInput_H
#define ModuleInput_H

#include "Module.h"
#include "Globals.h"
#include "SDL\include\SDL_scancode.h"
#include "SDL/include/SDL_gamecontroller.h"
#include "p2Qeue.h"

#define MAX_KEYS 300
#define JUMP_TIME 820
#define PUNCH_TIME 250
#define KICK_TIME  670
#define PUNCH_CROUCH_TIME 280
#define KICK_CROUCH_TIME 320
#define HADOUKEN_TIME  730
#define TORNADOKICK_TIME 600
#define MOUSHUUKYAKU_TIME 600
#define DAMAGE_TIME 500

enum king_states
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
	ST_HADOUKEN,
	ST_MOUSHUUKYAKU,
	ST_TORNADOKICK,
	ST_CHARGE,
	ST_DAMAGE
};

enum king_inputs
{
	// PLAYER 1
	IN_LEFT_DOWN,
	IN_LEFT_UP,
	IN_RIGHT_DOWN,
	IN_RIGHT_UP,
	IN_LEFT_AND_RIGHT,
	IN_JUMP,
	IN_CROUCH_UP,
	IN_CROUCH_DOWN,
	IN_JUMP_AND_CROUCH,
	IN_CHARGE_UP,
	IN_CHARGE_DOWN,
	IN_T,
	IN_R,
	IN_D,
	IN_F,
	IN_C,
	IN_X,
	IN_JUMP_FINISH,
	IN_PUNCH_FINISH,
	IN_PUNCH_CROUCH_FINISH,
	IN_KICK_FINISH,
	IN_KICK_CROUCH_FINISH,
	IN_DAMAGE,
	IN_DAMAGE_FINISH,
	IN_HADOUKEN_FINISH,
	IN_MOUSHUUKYAKU_FINISH,
	IN_TORNADOKICK_FINISH,

	// PLAYER 2
	IN_LEFT_DOWN2,
	IN_LEFT_UP2,
	IN_RIGHT_DOWN2,
	IN_RIGHT_UP2,
	IN_LEFT_AND_RIGHT2,
	IN_JUMP2,
	IN_CROUCH_UP2,
	IN_CROUCH_DOWN2,
	IN_JUMP_AND_CROUCH2,
	IN_CHARGE_UP2,
	IN_CHARGE_DOWN2,
	IN_Y,
	IN_U,
	IN_H,
	IN_N,
	IN_M,
	IN_JUMP_FINISH2,
	IN_PUNCH_FINISH2,
	IN_PUNCH_CROUCH_FINISH2,
	IN_KICK_FINISH2,
	IN_KICK_CROUCH_FINISH2,
	IN_DAMAGE2,
	IN_DAMAGE_FINISH2,
	IN_HADOUKEN_FINISH2,
	IN_MOUSHUUKYAKU_FINISH2,
	IN_TORNADOKICK_FINISH2
};

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class ModuleInput : public Module
{
public:

	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();
	bool external_input();
	void internal_input(p2Qeue<king_inputs>& inputs, p2Qeue<king_inputs>& inputs2);

public:
	KEY_STATE keyboard[MAX_KEYS];
	int j = 0;
	int y = 0;
	int t = 0;
	int r = 0;
	int o = 0;
	int p = 0;
	int i = 0;
	int u = 0;
	p2Qeue<king_inputs> inputs;
	p2Qeue<king_inputs> inputs2;

	// PLAYER 1
	bool left = false;
	bool right = false;
	bool down = false;
	bool up = false;
	bool charge = false;

	// PLAYER 2
	bool left2 = false;
	bool right2 = false;
	bool down2 = false;
	bool up2 = false;
	bool charge2 = false;

	int key = -1;

	// PLAYER 1
	Uint32 jump_timer = 0;
	Uint32 punch_timer = 0;
	Uint32 punch_crouch_timer = 0;
	Uint32 kick_timer = 0;
	Uint32 kick_crouch_timer = 0;
	Uint32 hadouken_timer = 0;
	Uint32 moshuukyaku_timer = 0;
	Uint32 tornadokick_timer = 0;
	Uint32 damage_timer = 0;

	// PLAYER 2
	Uint32 jump_timer2 = 0;
	Uint32 punch_timer2 = 0;
	Uint32 punch_crouch_timer2 = 0;
	Uint32 kick_timer2 = 0;
	Uint32 kick_crouch_timer2 = 0;
	Uint32 hadouken_timer2 = 0;
	Uint32 moshuukyaku_timer2 = 0;
	Uint32 tornadokick_timer2 = 0;
	Uint32 damage_timer2 = 0;

	// GAMEPAD
	const int JOYSTICK_DEAD_ZONE = 8000;
	SDL_GameController* gGameController = NULL;
	SDL_GameController* gGameController2 = NULL;
};

#endif // ModuleInput_H
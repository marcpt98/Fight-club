#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2Qeue.h"
#include "ModuleInput.h"
#include "SDL/include/SDL_timer.h"


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
	Animation Moushuu_Kyaku;
	Animation Tornado_Kick;
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


	void OnCollision(Collider* c1, Collider* c2);
	king_states process_fsm(p2Qeue<king_inputs>& inputs);

	int Life = 100;
	float MaxLife = 100;
	float Stamina = 100;
	float MaxStamina = 100;
	int time = 0;
	int kingkick = 0;
	int kingpunch = 0;
	int kingjump = 0;
	int king_punch_crouch = 0;
	int slize_sound = 0;
	int kingKoOuKen = 0;
	int ryoKoOuKensound = 0;
	int GodMode = false;
	int printMode = false;
};

#endif
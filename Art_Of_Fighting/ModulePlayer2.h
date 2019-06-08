#ifndef __ModulePlayer2_H__
#define __ModulePlayer2_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2Qeue.h"
#include "ModuleInput.h"
#include "SDL/include/SDL_timer.h"


struct SDL_Texture;

class ModulePlayer2 : public Module
{
private:
	Uint32 speed = 2;
	int animstart = 0;
	int jumpanim = 0;
	float jumpSpeed = 0;
	float jumpSpeedx = 0;
	bool SFXsound2 = true;
	int initialPos;
	bool SFXsound = true;
public:
	ModulePlayer2();
	~ModulePlayer2();

	bool Start();
	update_status Update();
	bool CleanUp();
	bool wall = false;
	bool inair = false;
	bool createnewbighitbox = true;
	bool createnewbighitbox2 = false;
	bool JumpMax = false;
	bool JumpMin = false;
	bool Activehadouken = true;
	bool collision = false;
	bool shoot = false;
	bool shootNo = false;
	bool damageP1 = false;
	bool damageHadokenP1 = false;
public:

	int font_score = -1;
	iPoint position;

	// TEXTURE
	SDL_Texture* graphics = nullptr;
	SDL_Texture * graphicsWin = nullptr;
	SDL_Texture * graphicsbeat = nullptr;

	// ANIMATIONS
	Animation* current_animation = nullptr;
	Animation* current_animation2 = nullptr;
	Animation idle;
	Animation jumping;
	Animation forward;
	Animation backward;
	Animation crouch;
	Animation damage;
	Animation hadouken;
	Animation Moushuu_Kyaku;
	Animation Tornado_Kick;
	Animation punch;
	Animation punch_Near;
	Animation punchJump;
	Animation punchCrouch;
	Animation kick;
	Animation kick_Near;
	Animation kickJump;
	Animation kickCrouch;
	Animation charge;
	Animation taunt;
	Animation winAnimation;
	Animation defeatAnimation;
	Animation damageHadoken;
	Animation protect;
	Animation yellow;
	Animation blue;



	// COLLIDERS
	Collider *ryohitbox;
	Collider *kickCollider;
	Collider *kickCrouchCollider;
	Collider *punchCollider;
	Collider *punchCrouchCollider;
	Collider *punchNearCollider;
	Collider *kicknearCollider;
	Collider *kickjump;
	Collider *punchjump;



	void OnCollision(Collider* c1, Collider* c2);
	king_states process_fsm(p2Qeue<king_inputs>& inputs);

	int Life = 100;
	float MaxLife = 100;
	float Stamina = 100;
	float MaxStamina = 100;
	Uint32 time = 0;
	Uint32 jumptimer = 0;
	int kingkick = 0;

	// FX
	int kingpunch = 0;
	int kingjump = 0;
	int king_punch_crouch = 0;
	int slize_sound = 0;
	int kingKoOuKen = 0;
	int ryoKoOuKensound = 0;
	int kingcharge = 0;
	//int kingdamage = 0;
	//int kingtaunt = 0;
	//int KingMoushuuKyaku = 0;

	int GodMode = false;
	int printMode = false;

	// COMBOS
	Uint32 combo1 = 0;
	Uint32 combo2 = 0;
	Uint32 combo3 = 0;
	Uint32 combotime;
	Uint32 combotimeHadouken;
	Uint32 combotimeMoushuuKyaku;
};

#endif
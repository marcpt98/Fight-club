#ifndef __ModulePlayer2_H__
#define __ModulePlayer2_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModulePlayer2 : public Module
{
private:
	bool wall = false;
	int speed = 2;
public:
	ModulePlayer2();
	~ModulePlayer2();

	bool Start();
	update_status Update();
	bool CleanUp();

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
	Animation beat;
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
	SDL_Rect player2Win;

	void OnCollision(Collider* c1, Collider* c2);
	int Life = 100;
	float MaxLife = 100;
	int Stamina = 100;
	float MaxStamina = 100;
	int time = 0;
	int ryokick = 0;
	int ryopunch = 0;
	int ryojump = 0;
	int ryoKoOuKen = 0;
	int ryoKoOuKensound = 0;
};

#endif

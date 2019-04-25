#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
private:
	bool wall = false;
	int speed = 2;
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	int font_score = -1;
	SDL_Texture* graphics = nullptr;
	SDL_Texture * graphicsWin = nullptr;
	Animation* current_animation = nullptr;
	Animation idle;
	Animation jump;
	Animation forward;
	Animation backward;
	Animation crouch1;
	Animation crouch2;
	iPoint position;
	Animation hadouken;
	//Animation ball;
	Animation punch;
	Animation kick;
	Collider *ryohitbox;
	Collider *kickCollider;
	Collider *punchCollider;
	SDL_Rect player1Win;
	void OnCollision(Collider* c1, Collider* c2);
	int Life = 100;
	float MaxLife = 100;
	int time =0;
	int ryokick = 0;
	int ryopunch = 0;
	int ryojump = 0;
	int ryoKoOuKen = 0;
	int ryoKoOuKensound = 0;
	int GodMode = false;
};

#endif
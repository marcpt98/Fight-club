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
#include "ModuleSlowDownShake.h"

ModulePlayer2::ModulePlayer2()
{
	graphics = NULL;
	current_animation = NULL;
	
	// idle animation (arcade sprite sheet)
	idle.PushBack({ 107, 660, 52, 103 }, 0.13, 0, 0, 0, 0);
	idle.PushBack({ 55, 660, 52, 103 }, 0.13, 0, 0, 0, 0);
	idle.PushBack({ 3, 660, 52, 104 }, 0.13, 0, 0, 0, 0);

	//jump animation(arcade sprite sheet)
	jumping.PushBack({ 1202,660,47,85 }, 0.3, 0, 0, 0, 15);
	jumping.PushBack({ 1249,660,66,101 }, 0.01, 0, 0, 0, 0);

	// walk forward animation (arcade sprite sheet)
	forward.PushBack({ 206, 660, 47, 103 }, 0.16, 0, 0, 0, -4);
	forward.PushBack({ 253, 660, 46, 103 }, 0.16, 0, 0, 0, 1);
	forward.PushBack({ 159, 660, 47, 102 }, 0.16, 0, 0, 0, -1);
	forward.PushBack({ 107, 660, 52, 103 }, 0.16, 0, 0, 0, -3);

	//backawrd animation
	backward.PushBack({ 159, 660, 47, 102 }, 0.16, 0, 0, 0, 1);
	backward.PushBack({ 253, 660, 46, 103 }, 0.16, 0, 0, 0, -4);
	backward.PushBack({ 206, 660, 47, 103 }, 0.16, 0, 0, 0, -3);
	backward.PushBack({ 107, 660, 52, 103 }, 0.16, 0, 0, 0, -1);

	//punch animation(arcade sprite sheet)
	punch.PushBack({ 299, 660, 47, 102 }, 0.2, 0, 0, 2, 0);
	punch.PushBack({ 346, 660, 92, 99 }, 0.2, 0, 0, 4, 0);
	punch.PushBack({ 299, 660, 47, 102 }, 0.2, 0, 0, 2, 0);

	punch_Near.PushBack({ 299, 660, 47, 102 }, 0.2, 2, 0, 0, 0);
	punch_Near.PushBack({ 633, 773, 79, 96 }, 0.1, 2, 0, 0, 0);
	punch_Near.PushBack({ 299, 660, 47, 102 }, 0.2, 2, 0, 0, 0);

	punchCrouch.PushBack({ 1033, 660, 68, 72 }, 0.15, 0, 0, 0, 0);
	punchCrouch.PushBack({ 1101,660,101,68 }, 0.08, 0, 0, -15, 0);
	punchCrouch.PushBack({ 1033, 660, 68, 72 }, 0.15, 0, 0, 0, 0);

	punchJump.PushBack({ 232, 773, 61, 108 }, 0.2, 2, 0, 0, 0);
	punchJump.PushBack({ 299, 773, 57, 100 }, 0.2, 2, 0, 0, 0);
	punchJump.loop = false;

	//kick animation(arcade sprite sheet)
	kick.PushBack({ 438,660,70,113 }, 0.18, 0, 0, 0, 0);
	kick.PushBack({ 509,660,48,111 }, 0.16, 0, 0, 36, -3);
	kick.PushBack({ 559,660,79,111 }, 0.07, 0, 0, 37, -3);
	kick.PushBack({ 639,660,47,101 }, 0.15, 0, 0, 14, -3);
	kick.PushBack({ 686,660,62,92 }, 0.1, 0, 0, -15, 0);

	kick_Near.PushBack({ 793,773,61,98 }, 0.16, 0, 0, 0, 0);
	kick_Near.PushBack({ 858,773,93,97 }, 0.03, 0, 0, 0, 0);
	kick_Near.PushBack({ 957,773,53,101 }, 0.16, 0, 0, 0, 0);

	kickJump.PushBack({ 3,773,55,93 }, 0.15, 0, 0, 0, 0);
	kickJump.PushBack({ 61,773,93,79 }, 0.1, 0, 0, 0, 0);
	kickJump.PushBack({ 159,773,70,81 }, 0.15, 0, 0, 0, 0);
	kickJump.loop = false;

	kickCrouch.PushBack({ 1033, 660, 68, 72 }, 0.19, 0, 0, 0, 0);
	kickCrouch.PushBack({ 777, 1021, 104, 70 }, 0.16, 0, 0, 0, 0);
	kickCrouch.PushBack({ 890, 1024, 111, 69 }, 0.16, 0, 0, 0, 0);
	kickCrouch.PushBack({ 1004, 1020, 95, 78 }, 0.53, 0, 0, 0, 0);
	kickCrouch.PushBack({ 1100, 1023, 93, 75 }, 0.53, 0, 0, 0, 0);
	kickCrouch.PushBack({ 1101,660,101,68 }, 0.08, -18, 0, 0, 0);
	kickCrouch.PushBack({ 1033, 660, 68, 72 }, 0.18, 0, 0, 0, 0);


	// Hadouken king animation
	hadouken.PushBack({ 1202, 660, 47, 85 }, 0.2, 0, 0, 0, 0);
	hadouken.PushBack({ 365, 773, 54, 110 }, 0.15, 0, 0, 0, -10);
	hadouken.PushBack({ 428, 773, 49, 99 }, 0.18, 0, 0, 20, -20);
	hadouken.PushBack({ 486, 773, 81, 76 }, 0.12, 0, 0, 10, -50);
	hadouken.PushBack({ 576, 773, 48, 85 }, 0.13, 0, 0, 0, -20);
	hadouken.PushBack({ 686, 660, 62, 92 }, 0.1, 0, 0, 0, -1); //CHANGE
	
															   //MoushuuKyaku animation
															   // Moushuu Kyaku animation
	Moushuu_Kyaku.PushBack({ 3, 892, 57, 101 }, 0.3, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 68, 892, 102, 100 }, 0.3, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 178, 892, 67, 100 }, 0.3, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 253, 892, 96, 116 }, 0.3, 0, 0, 0, 0);

	Moushuu_Kyaku.PushBack({ 178, 892, 67, 100 }, 0.3, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 68, 892, 102, 100 }, 0.3, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 178, 892, 67, 100 }, 0.3, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 253, 892, 96, 116 }, 0.3, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 178, 892, 67, 100 }, 0.3, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 68, 892, 102, 100 }, 0.3, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 178, 892, 67, 100 }, 0.3, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 253, 892, 96, 116 }, 0.3, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 178, 892, 67, 100 }, 0.3, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 68, 892, 102, 100 }, 0.3, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 178, 892, 67, 100 }, 0.3, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 253, 892, 96, 116 }, 0.3, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 68, 892, 102, 100 }, 0.3, 0, 0, 0, 0);
	//2 TIMES LOOP AND LAST FRAME //2
	Moushuu_Kyaku.PushBack({ 3, 892, 57, 101 }, 0.3, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 107, 660, 52, 103 }, 0.3, 0, 0, 0, 0);
	//NORMAL KICK
	Moushuu_Kyaku.PushBack({ 438,660,70,113 }, 0.18, 0, 0, 0, 0);
	Moushuu_Kyaku.PushBack({ 509,660,48,111 }, 0.16, 36, -3, 0, 0);
	Moushuu_Kyaku.PushBack({ 559,660,79,111 }, 0.07, 37, -3, 0, 0);
	Moushuu_Kyaku.PushBack({ 639,660,47,101 }, 0.15, 14, -3, 0, 0);
	Moushuu_Kyaku.PushBack({ 686,660,62,92 }, 0.1, -15, 0, 0, 0);

	// crouch animation
	crouch.PushBack({ 937, 660,49,91 }, 0.21, 0, 0, 0, 0);
	crouch.PushBack({ 986, 660,47,73 }, 0.5, 0, 0, 0, 0);
	crouch.loop = false;

	//beat animation
	damage.PushBack({ 1033, 773, 54, 100 }, 0.1, 0, 0, -6, 3);
	damage.PushBack({ 1093, 773, 59, 100 }, 0.08, 0, 0, -6, 3);
	damage.PushBack({ 1033, 773, 54, 100 }, 0.1, 0, 0, -6, 3);

	//charge animation
	charge.PushBack({ 358,892,51,100 }, 0.2, 0, 0, 0, 0);
	charge.PushBack({ 414,892,54,102 }, 0.2, 0, 0, 0, 0);
	charge.PushBack({ 473,892,63,103 }, 0.2, 0, 0, 0, 0);
	charge.loop = false;

	//taunt animation
	taunt.PushBack({ 1285,773,49,102 }, 0.1, 0, 0, 0, 0);
	taunt.PushBack({ 1230,773,49,102 }, 0.1, 0, 0, 0, 0);

	//win animation
	winAnimation.PushBack({ 178,1024,42,100 }, 0.1, 0, 0, 0, 0);
	winAnimation.PushBack({ 224,1024,61,96 }, 0.1, 0, 0, 0, 0);
	winAnimation.PushBack({ 291,1024,62,93 }, 0.1, 0, 0, 0, 0);
	winAnimation.loop = false;

	//lose animation
	defeatAnimation.PushBack({ 1156,773,70,97 }, 0.1, 0, 0, -8, 2);
	defeatAnimation.PushBack({ 356,1024,86,78 }, 0.1, 0, 0, -35, 2);
	defeatAnimation.PushBack({ 454,1024,89,55 }, 0.1, 0, 0, -18, 2);
	defeatAnimation.loop = false;

	//damage Hadoken animation
	damageHadoken.PushBack({ 1204,1024,63,87 }, 0.1, 0, 0, -8, 2);
	damageHadoken.PushBack({ 1275,1024,49,78 }, 0.1, 0, 0, -8, 2);
	damageHadoken.PushBack({ 1332,1024,47,60 }, 0.2, 0, 0, -8, 2);
	damageHadoken.PushBack({ 1275,1024,49,78 }, 0.1, 0, 0, -8, 2);
	damageHadoken.PushBack({ 1204,1024,63,87 }, 0.1, 0, 0, -8, 2);

	//protect animation
	protect.PushBack({ 541, 841, 52,102 }, 0.1, 0, 0, 0, 0);
	protect.PushBack({ 599, 890, 51,103 }, 0.1, 0, 0, 0, 0);

	//HITS ANIMATION
	yellow.PushBack({ 1971, 52, 26,31 }, 0.1, 0, 0, 0, 0);
	yellow.PushBack({ 1998, 52, 46,49 }, 0.1, 0, 0, 0, 0);
	blue.PushBack({ 1901,175, 19,22 }, 0.1, 0, 0, 0, 0);
	blue.PushBack({ 1932,169, 31,31 }, 0.1, 0, 0, 0, 0);
}

ModulePlayer2::~ModulePlayer2()
{}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("media/Spritesheets/king_Spritesheet_2.png"); // arcade version

	kingkick = App->audio->LoadFX("media/FX/king_high_kick.wav");
	kingpunch = App->audio->LoadFX("media/FX/king_punch.wav");
	kingjump = App->audio->LoadFX("media/FX/Ryojump.wav");
	king_punch_crouch = App->audio->LoadFX("media/FX/king_punch_crouch.wav");
	slize_sound = App->audio->LoadFX("media/FX/slize_sound.wav");
	kingKoOuKen = App->audio->LoadFX("media/FX/king_haduken.wav");
	ryoKoOuKensound = App->audio->LoadFX("media/FX/ryoKoOuKensound.wav");
	kingcharge = App->audio->LoadFX("media/FX/king_charge.wav");
	kingdamagepunch = App->audio->LoadFX("media/FX/king_hit_by_punch.wav");
	kingdamagekick = App->audio->LoadFX("media/FX/king_hit_by_high_kick.wav");
	kingtaunt = App->audio->LoadFX("media/FX/king_taunt.wav");
	//KingMoushuuKyaku=App->audio->LoadFX("");

	position.x = 420;
	position.y = 210;
	initialPos = position.y;

	//Colliders
	ryohitbox = App->collision->AddCollider({ position.x,position.y, 35, 80 }, COLLIDER_ENEMY, this);

	punchCollider = App->collision->AddCollider({ position.x,position.y, 60, 15 }, COLLIDER_ENEMY, this);
	punchCollider->Enabled = false;

	kickCollider = App->collision->AddCollider({ position.x,position.y, 45, 15 }, COLLIDER_ENEMY, this);
	kickCollider->Enabled = false;

	punchCrouchCollider = App->collision->AddCollider({ position.x, position.y - 70 , 40, 15 }, COLLIDER_ENEMY, this);
	punchCrouchCollider->Enabled = false;

	kickCrouchCollider = App->collision->AddCollider({ position.x, position.y - 70 , 65, 15 }, COLLIDER_ENEMY, this);
	kickCrouchCollider->Enabled = false;

	punchNearCollider = App->collision->AddCollider({ position.x, position.y - 70 , 65, 15 }, COLLIDER_ENEMY, this);
	punchNearCollider->Enabled = false;

	kicknearCollider = App->collision->AddCollider({ position.x, position.y , 45, 15 }, COLLIDER_ENEMY, this);
	kicknearCollider->Enabled = false;

	kickjump = App->collision->AddCollider({ position.x,position.y, 75, 15 }, COLLIDER_ENEMY, this);
	kickjump->Enabled = false;

	punchjump = App->collision->AddCollider({ position.x,position.y, 40, 40 }, COLLIDER_ENEMY, this);
	punchjump->Enabled = false;


	//Initialize Stamina
	Stamina = 100;

	winAnimation.Reset();
	defeatAnimation.Reset();
	return ret;
}

bool ModulePlayer2::CleanUp()
{	
	App->input->inputs2.Push(IN_WIN_FINISH2);
	App->input->inputs2.Push(IN_DEFEAT_FINISH2);
	LOG("Unloading player");

	App->textures->Unload(graphics);
	App->textures->Unload(graphicsWin);
	App->audio->UnLoadFX(kingkick);
	App->audio->UnLoadFX(kingpunch);
	App->audio->UnLoadFX(kingjump);
	App->audio->UnLoadFX(king_punch_crouch);
	App->audio->UnLoadFX(slize_sound);
	App->audio->UnLoadFX(kingKoOuKen);
	App->audio->UnLoadFX(kingcharge);
	App->audio->UnLoadFX(kingdamagepunch);
	App->audio->UnLoadFX(kingdamagekick);
	App->audio->UnLoadFX(kingtaunt);
	//App->audio->UnLoadFX(KingMoushuuKyaku);

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
			position.y = 210;
			inair = false;
			forward.Reset();
			backward.Reset();
			crouch.Reset();
			kick.Reset();
			kick_Near.Reset();
			punch.Reset();
			punch_Near.Reset();
			hadouken.Reset();
			Tornado_Kick.Reset();
			Moushuu_Kyaku.Reset();
			jumping.Reset();
			punchJump.Reset();
			punchCrouch.Reset();
			kickJump.Reset();
			kickCrouch.Reset();
			charge.Reset();
			damage.Reset();
			taunt.Reset();
			winAnimation.Reset();
			defeatAnimation.Reset();
			damageHadoken.Reset();
			break;

		case ST_WALK_FORWARD:
			if ((position.x + 25) >= (App->player->position.x - 25))
			{
				current_animation = &forward;
				backward.Reset();
			}
			else
			{
				current_animation = &backward;
				forward.Reset();
			}
			position.x += speed;
			position.y = 210;
			inair = false;
			crouch.Reset();
			kick.Reset();
			kick_Near.Reset();
			punch.Reset();
			punch_Near.Reset();
			hadouken.Reset();
			Tornado_Kick.Reset();
			Moushuu_Kyaku.Reset();
			jumping.Reset();
			punchJump.Reset();
			punchCrouch.Reset();
			kickJump.Reset();
			kickCrouch.Reset();
			charge.Reset();
			damage.Reset();
			taunt.Reset();
			winAnimation.Reset();
			defeatAnimation.Reset();
			damageHadoken.Reset();
			break;

		case ST_WALK_BACKWARD:
			if ((position.x + 25) >= (App->player->position.x - 25))
			{
				current_animation = &backward;
				forward.Reset();
			}
			else
			{
				current_animation = &forward;
				backward.Reset();
			}
			position.x -= speed;
			position.y = 210;
			inair = false;
			crouch.Reset();
			kick.Reset();
			kick_Near.Reset();
			punch.Reset();
			punch_Near.Reset();
			hadouken.Reset();
			Tornado_Kick.Reset();
			Moushuu_Kyaku.Reset();
			jumping.Reset();
			punchJump.Reset();
			punchCrouch.Reset();
			kickJump.Reset();
			kickCrouch.Reset();
			charge.Reset();
			damage.Reset();
			taunt.Reset();
			winAnimation.Reset();
			defeatAnimation.Reset();
			damageHadoken.Reset();
			break;

		case ST_JUMP_NEUTRAL:
			if (animstart == 0 || 2)
			{
				inair = true;
				switch (jumpanim)
				{
				case 0:
					current_animation = &jumping;
					if (SFXsound == true)
					{
						App->audio->PlayFX(kingjump);
						SFXsound = false;
					}
					break;
				case 1:
					if (animstart == 0)
					{
						current_animation = &punchJump;
						if (SFXsound2 == true)
						{
							App->audio->PlayFX(kingpunch);
							SFXsound2 = false;
						}
						if (SFXsound3 == true)
						{
							if (damagepunch == true && damageHit == true)
							{
								App->audio->PlayFX(kingdamagepunch);
								damagepunch = false;
								SFXsound3 = false;
								damageHit = false;
								LOG("PUNCH HIT");
							}
						}
						time = SDL_GetTicks();
						LOG("JUMP PUNCH \n");
					}
					break;
				case 2:
					if (animstart == 0)
					{
						current_animation = &kickJump;
						if (SFXsound2 == true)
						{
							App->audio->PlayFX(kingkick);
							SFXsound2 = false;
						}
						if (SFXsound3 == true)
						{
							if (damagekick == true && damageHit == true)
							{
								App->audio->PlayFX(kingdamagekick);
								damagekick = false;
								SFXsound3 = false;
								damageHit = false;
								LOG("KICK HIT");
							}
						}
						time = SDL_GetTicks();
						LOG("JUMP KICK \n");
					}
					break;
				}
				position.y -= jumpSpeed;
				if (position.y < 120)
				{
					jumpSpeed -= 1.5;
					if (jumpSpeed < 0) jumpSpeed = -5;
				}
				if (position.y >= initialPos)
				{
					position.y = initialPos;
					if (animstart != 0)animstart = 1;
					punchJump.Reset();
					kickJump.Reset();
				}
				LOG("JUMPING ^^\n");
			}
			break;
		case ST_JUMP_FORWARD:
			if (animstart == 0 || 2)
			{
				inair = true;
				switch (jumpanim)
				{
				case 0:
					current_animation = &jumping;
					if (SFXsound == true)
					{
						App->audio->PlayFX(kingjump);
						SFXsound = false;
					}
					break;
				case 1:
					if (animstart == 0)
					{
						current_animation = &punchJump;
						if (SFXsound2 == true)
						{
							App->audio->PlayFX(kingpunch);
							SFXsound2 = false;
						}
						if (SFXsound3 == true)
						{
							if (damagepunch == true && damageHit == true)
							{
								App->audio->PlayFX(kingdamagepunch);
								damagepunch = false;
								SFXsound3 = false;
								damageHit = false;
								LOG("PUNCH HIT");
							}
						}
						time = SDL_GetTicks();
						LOG("JUMP PUNCH FORWARD\n");
					}
					break;
				case 2:
					if (animstart == 0)
					{
						current_animation = &kickJump;
						if (SFXsound2 == true)
						{
							App->audio->PlayFX(kingkick);
							SFXsound2 = false;
						}
						if (SFXsound3 == true)
						{
							if (damagekick == true && damageHit == true)
							{
								App->audio->PlayFX(kingdamagekick);
								damagekick = false;
								SFXsound3 = false;
								damageHit = false;
								LOG("PUNCH HIT");
							}
						}
						time = SDL_GetTicks();
						LOG("JUMP KICK FORWARD \n");
					}
					break;
				}
				position.y -= jumpSpeed;
				position.x += jumpSpeedx;
				if (position.y < 120)
				{
					jumpSpeed -= 6;
					if (jumpSpeed < 0)
					{
						jumpSpeed = -4;
						jumpSpeedx = 4;
					}
				}
				if (position.y >= initialPos)
				{
					position.y = initialPos;
					if (animstart != 0)animstart = 1;
					punchJump.Reset();
					kickJump.Reset();
				}
				LOG("JUMP FORWARD \n");
			}
			break;
		case ST_JUMP_BACKWARD:
			if (animstart == 0 || 2)
			{
				inair = true;
				switch (jumpanim)
				{
				case 0:
					current_animation = &jumping;
					if (SFXsound == true)
					{
						App->audio->PlayFX(kingjump);
						SFXsound = false;
					}
					break;
				case 1:
					if (animstart == 0)
					{
						current_animation = &punchJump;
						if (SFXsound2 == true)
						{
							App->audio->PlayFX(kingpunch);
							SFXsound2 = false;
						}
						if (SFXsound3 == true)
						{
							if (damagepunch == true && damageHit == true)
							{
								App->audio->PlayFX(kingdamagepunch);
								damagepunch = false;
								SFXsound3 = false;
								damageHit = false;
								LOG("PUNCH HIT");
							}
						}
						time = SDL_GetTicks();
						LOG("JUMP PUNCH BACKWARDS\n");
					}
					break;
				case 2:
					if (animstart == 0)
					{
						current_animation = &kickJump;
						if (SFXsound2 == true)
						{
							App->audio->PlayFX(kingkick);
							SFXsound2 = false;
						}
						if (SFXsound3 == true)
						{
							if (damagekick == true && damageHit == true)
							{
								App->audio->PlayFX(kingdamagekick);
								damagekick = false;
								SFXsound3 = false;
								damageHit = false;
								LOG("PUNCH HIT");
							}
						}
						time = SDL_GetTicks();
						LOG("JUMP KICK BACKWARD \n");
					}
					break;
				}
				position.y -= jumpSpeed;
				position.x -= jumpSpeedx;
				if (position.y < 120)
				{
					jumpSpeed -= 6;
					if (jumpSpeed < 0)
					{
						jumpSpeed = -4;
						jumpSpeedx = 4;
					}
				}
				if (position.y >= initialPos)
				{
					position.y = initialPos;
					if (animstart != 0)animstart = 1;
					punchJump.Reset();
					kickJump.Reset();
				}
				LOG("JUMP BACKWARD \n");
			}
			break;
		case ST_CROUCH:
			current_animation = &crouch;
			punchCrouch.Reset();
			kickCrouch.Reset();

			LOG("CROUCHING ****\n");
			break;
		case ST_PUNCH_CROUCH:
			if (SFXsound == true)
			{
				App->audio->PlayFX(king_punch_crouch);
				SFXsound = false;
			}
			if (SFXsound3 == true)
			{
				if (damagepunch == true && damageHit == true)
				{
					App->audio->PlayFX(kingdamagepunch);
					damagepunch = false;
					SFXsound3 = false;
					damageHit = false;
					LOG("PUNCH HIT");
				}
			}
			if (animstart == 0)
			{
				current_animation = &punchCrouch;
			}

			LOG("PUNCH CROUCHING **++\n");
			break;
		case ST_PUNCH_STANDING:
			if (position.x < App->player->position.x) {
				if ((position.x + 40) <= (App->player->position.x - 25))
				{
					if (animstart == 0)
					{
						current_animation = &punch;
					}
				}
				else
				{
					if (animstart == 0)
					{
						current_animation = &punch_Near;
					}
				}
			}
			else {
				if ((position.x - 40) >= (App->player->position.x + 25))
				{
					if (animstart == 0)
					{
						current_animation = &punch;
					}
				}
				else
				{
					if (animstart == 0)
					{
						current_animation = &punch_Near;
					}
				}
			}
			if (SFXsound == true)
			{
				App->audio->PlayFX(kingpunch);
				SFXsound = false;
			}
			if (SFXsound3 == true)
			{
				if (damagepunch == true && damageHit == true)
				{
					App->audio->PlayFX(kingdamagepunch);
					damagepunch = false;
					SFXsound3 = false;
					damageHit = false;
					LOG("PUNCH HIT");
				}
			}
			LOG("PUNCH --\n")
				break;
		case ST_KICK_CROUCH:
			if (position.x < App->player->position.x) {
				position.x += 0.5*speed;
			}
			else {
				position.x -= 0.5*speed;
			}

			if (SFXsound == true)
			{
				App->audio->PlayFX(king_punch_crouch);
				App->audio->PlayFX(slize_sound);
				SFXsound = false;
			}
			if (SFXsound3 == true)
			{
				if (damagekick == true && damageHit == true)
				{
					App->audio->PlayFX(kingdamagekick);
					damagekick = false;
					SFXsound3 = false;
					damageHit = false;
					LOG("PUNCH HIT");
				}
			}
			if (animstart == 0)
			{
				current_animation = &kickCrouch;
			}
			LOG("KICK CROUCHING **--\n");
			break;
		case ST_KICK_STANDING:
			if (position.x < App->player->position.x) {
				if ((position.x + 40) <= (App->player->position.x - 25))
				{
					if (animstart == 0)
					{
						current_animation = &kick;
					}
				}
				else
				{
					if (animstart == 0)
					{
						current_animation = &kick_Near;
					}
				}
			}
			else {
				if ((position.x - 40) >= (App->player->position.x + 25))
				{
					if (animstart == 0)
					{
						current_animation = &kick;
					}
				}
				else
				{
					if (animstart == 0)
					{
						current_animation = &kick_Near;
					}
				}
			}
			if (SFXsound == true)
			{
				App->audio->PlayFX(kingkick);
				SFXsound = false;
			}
			if (SFXsound3 == true)
			{
				if (damagekick == true && damageHit == true)
				{
					App->audio->PlayFX(kingdamagekick);
					damagekick = false;
					SFXsound3 = false;
					damageHit = false;
					LOG("PUNCH HIT");
				}
			}
			LOG("KICK --\n")
				break;
		case ST_DAMAGE:
			if (SFXsound == true)
			{
				//App->audio->PlayFX(kingdamage);
				SFXsound = false;
			}
			if (App->player->damageP2 == true)
			{
				current_animation = &damage;
			}
			LOG("AAAAAAAAAAAAA ^^--\n");
			break;
		case ST_DAMAGE_HADOKEN:

			if (App->player->damageHadokenP2 == true)
			{
				current_animation = &damageHadoken;
			}
			LOG("DAMAGE HADOKEEEEEEEEEEEN ^^--\n");
			break;
		case ST_CHARGE:
			if (Stamina < 99)
			{
				if (SFXsound == true)
				{
					App->audio->PlayFX(kingcharge);
					SFXsound = false;
				}
				current_animation = &charge;

				Stamina++;
			}
			LOG("CHARGE --\n")
				break;
		case ST_TAUNT:
			if (SFXsound == true)
			{
				App->audio->PlayFX(kingtaunt);
				SFXsound = false;
			}
			if (animstart == 0)
			{
				current_animation = &taunt;
			}
			if (DrainEnergy == true)
			{
				App->player->Stamina = (App->player->Stamina - 20);
				DrainEnergy = false;
			}
			LOG("TAUNT2 --\n")
				break;
		case ST_HADOUKEN:
			if (Activehadouken == true)
			{
				if (Stamina > 0) {
					if (Stamina >= 20)
					{
						shoot = true;
					}
					if (Stamina < 19)
					{
						shootNo = true;
					}
					Stamina = (Stamina - 20);
					if (Stamina < 0) {
						Stamina = 0;
					}

				}

				if (shoot == true)
				{
					App->audio->PlayFX(kingKoOuKen);
					App->audio->PlayFX(ryoKoOuKensound);

					if ((position.x + 25) >= (App->player->position.x - 25))
					{
						App->particles->HadoukenFlip2.speed.x = -8;
						App->particles->AddParticle(App->particles->HadoukenFlip, position.x - 10, position.y - 60, COLLIDER_ENEMY_SHOT);
						App->particles->AddParticle(App->particles->HadoukenFlip2, position.x - 10, position.y - 60, COLLIDER_ENEMY_SHOT);
					}
					else
					{
						App->particles->Hadouken2.speed.x = +8;
						App->particles->AddParticle(App->particles->Hadouken, position.x + 10, position.y - 60, COLLIDER_ENEMY_SHOT);
						App->particles->AddParticle(App->particles->Hadouken2, position.x + 10, position.y - 60, COLLIDER_ENEMY_SHOT);
					}
					shoot = false;
				}

				if (shootNo == true)
				{
					App->audio->PlayFX(kingKoOuKen);
					App->audio->PlayFX(ryoKoOuKensound);
					if ((position.x + 25) >= (App->player->position.x - 25))
					{
						App->particles->HadoukenFlipEnergy2.speed.x = -4;
						App->particles->AddParticle(App->particles->HadoukenFlipEnergy, position.x - 10, position.y - 60, COLLIDER_ENEMY_SHOT);
						App->particles->AddParticle(App->particles->HadoukenFlipEnergy2, position.x - 10, position.y - 60, COLLIDER_ENEMY_SHOT);
					}
					else
					{
						App->particles->HadoukenEnergy2.speed.x = +4;
						App->particles->AddParticle(App->particles->HadoukenEnergy, position.x + 10, position.y - 60, COLLIDER_ENEMY_SHOT);
						App->particles->AddParticle(App->particles->HadoukenEnergy2, position.x + 10, position.y - 60, COLLIDER_ENEMY_SHOT);
					}
					shootNo = false;
				}

			}
			Activehadouken = false;
			if (animstart == 0)
			{
				current_animation = &hadouken;
			}
			break;

		case ST_TORNADOKICK:
			if (SFXsound == true)
			{
				//App->audio->PlayFX(kingpunch);
				SFXsound = false;
			}
			if (animstart == 0)
			{
				current_animation = &Tornado_Kick;
			}
			LOG("TORNADOKICK ++++\n");
			break;
		case ST_MOUSHUUKYAKU:
			if (Activehadouken == true)
			{
				Stamina = (Stamina - 20);
				if (Stamina < 0)
				{
					Stamina = 0;
				}
			}
			Activehadouken = false;
			if (SFXsound == true)
			{
				//App->audio->PlayFX(KingMoushuuKyaku);
				SFXsound = false;
			}
			if (animstart == 0)
			{
				current_animation = &Moushuu_Kyaku;
			}
			LOG("MOUSHUUKYAKU --\n")
				break;
		case ST_WIN:
			current_animation = &winAnimation;
			position.y = 210;
			break;
		case ST_DEFEAT:
			current_animation = &defeatAnimation;
			position.y = 210;
			break;
		
		}
	}
	current_state = state;

	// Draw everything --------------------------------------
	SDL_Rect* r = &current_animation->GetCurrentFrame();

	if ((position.x + 25) >= (App->player->position.x + 25))
	{
		App->render->BlitWithScale(graphics, position.x + 50 + (-current_animation->pivotx2[current_animation->returnCurrentFrame()]), position.y - r->h + current_animation->pivoty2[current_animation->returnCurrentFrame()], r, -1, 1.0f, 1, TOP_RIGHT);
		if (App->scene_King->Zoom == false) { ryohitbox->SetPos(position.x + 15, position.y - r->h); }
		else {
			ryohitbox->SetPos((position.x + (-current_animation->pivotx2[current_animation->returnCurrentFrame()])+7)*1.3, position.y - r->h + current_animation->pivoty2[current_animation->returnCurrentFrame()] + 30);
			//this is the setpos for the zoom
		}

		if (r == &kick.frames[kick.last_frame - 5] && App->scene_King->Zoom == false)
		{
			kickCollider->SetPos(position.x - 65, position.y - r->h);

			kickCollider->Enabled = true;
		}
		else
		{
			kickCollider->Enabled = false;
		}

		if (r == &kick.frames[kick.last_frame - 3] && App->scene_King->Zoom == true)
		{
			kickCollider->SetPos((position.x - 45)*1.3, position.y - r->h + 30);

			kickCollider->Enabled = true;
		}
		else
		{
			kickCollider->Enabled = false;
		}

		if (r == &punch.frames[punch.last_frame - 1] && App->scene_King->Zoom == false)
		{
			punchCollider->SetPos(position.x - 40, position.y + 12 - r->h);

			punchCollider->Enabled = true;
		}
		else
		{
			punchCollider->Enabled = false;
		}

		if (r == &punch.frames[punch.last_frame - 1] && App->scene_King->Zoom == true)
		{
			punchCollider->SetPos((position.x - 40)*1.3, position.y + 12 - r->h + 20);

			punchCollider->Enabled = true;
		}
		else
		{
			punchCollider->Enabled = false;
		}

		if (r == &punch_Near.frames[punch_Near.last_frame - 1] && App->scene_King->Zoom == true)
		{
			punchNearCollider->SetPos((position.x - 40)*1.3, position.y + 12 - r->h + 20);

			punchNearCollider->Enabled = true;
		}
		else
		{
			punchNearCollider->Enabled = false;
		}

		if (r == &kick_Near.frames[kick_Near.last_frame - 1] && App->scene_King->Zoom == true)
		{
			kicknearCollider->SetPos((position.x - 40)*1.3, position.y + 12 - r->h + 40);

			kicknearCollider->Enabled = true;
		}
		else
		{
			kicknearCollider->Enabled = false;
		}

		if (r == &kickCrouch.frames[kickCrouch.last_frame - 6] && App->scene_King->Zoom == true)
		{
			kickCrouchCollider->SetPos((position.x - 30)*1.3, position.y + 30 - r->h + 40);

			kickCrouchCollider->Enabled = true;
		}
		else
		{
			kickCrouchCollider->Enabled = false;
		}
		if (r == &kickJump.frames[kickJump.last_frame - 1] && App->scene_King->Zoom == true) {

			kickjump->SetPos((position.x - 25)*1.3, position.y - r->h + 40);

			kickjump->Enabled = true;
		}
		else
		{
			kickjump->Enabled = false;
		}

		if (r == &punchJump.frames[punchJump.last_frame - 1] && App->scene_King->Zoom == true) {

			punchjump->SetPos((position.x - 25)*1.3, position.y - r->h + 40);

			punchjump->Enabled = true;
		}
		else
		{
			punchjump->Enabled = false;
		}
		if (r == &punchCrouch.frames[punchJump.last_frame - 2] && App->scene_King->Zoom == true) {
			punchCrouchCollider->SetPos((position.x - 30)*1.3, position.y + 30 - r->h + 40);

			punchCrouchCollider->Enabled = true;
		}
		else
		{
			punchCrouchCollider->Enabled = false;
		}
	}
	else 
	{
		App->render->Blit(graphics, position.x + (current_animation->pivotx2[current_animation->returnCurrentFrame()]), position.y - r->h + current_animation->pivoty2[current_animation->returnCurrentFrame()], r);
		if (App->scene_King->Zoom == false) { ryohitbox->SetPos(position.x, position.y - r->h); }
		else {
			ryohitbox->SetPos((position.x + (current_animation->pivotx[current_animation->returnCurrentFrame()]))*1.3, position.y - r->h + current_animation->pivoty[current_animation->returnCurrentFrame()] + 30);

		}


		if (r == &kick.frames[kick.last_frame - 5] && App->scene_King->Zoom == false)
		{
			kickCollider->SetPos(position.x + 70, position.y - r->h);

			kickCollider->Enabled = true;
		}
		else
		{
			kickCollider->Enabled = false;
		}

		if (r == &kick.frames[kick.last_frame -3] && App->scene_King->Zoom == true)
		{
			kickCollider->SetPos((position.x + 60)*1.3, position.y - r->h + 30);

			kickCollider->Enabled = true;
		}
		else
		{
			kickCollider->Enabled = false;
		}

		if (r == &punch.frames[punch.last_frame - 1] && App->scene_King->Zoom == false)
		{
			punchCollider->SetPos(position.x + 32, position.y + 12 - r->h);

			punchCollider->Enabled = true;
		}
		else
		{
			punchCollider->Enabled = false;
		}

		if (r == &punch.frames[punch.last_frame - 1] && App->scene_King->Zoom == true)
		{
			punchCollider->SetPos((position.x + 32)*1.3, position.y + 12 - r->h + 20);

			punchCollider->Enabled = true;
		}
		else
		{
			punchCollider->Enabled = false;
		}

		if (r == &kickCrouch.frames[kickCrouch.last_frame - 5] && App->scene_King->Zoom == false)
		{
			kickCrouchCollider->SetPos(position.x + 50, position.y + 30 - r->h);

			kickCrouchCollider->Enabled = true;
		}
		else
		{
			kickCrouchCollider->Enabled = false;
		}

		if (r == &kickCrouch.frames[kickCrouch.last_frame - 6] && App->scene_King->Zoom == true)
		{
			kickCrouchCollider->SetPos((position.x + 30)*1.3, position.y + 30 - r->h + 40);

			kickCrouchCollider->Enabled = true;
		}
		else
		{
			kickCrouchCollider->Enabled = false;
		}
		if (r == &punch_Near.frames[punch_Near.last_frame - 1] && App->scene_King->Zoom == true)
		{
			punchNearCollider->SetPos((position.x + 32)*1.3, position.y + 12 - r->h + 20);

			punchNearCollider->Enabled = true;
		}
		else
		{
			punchNearCollider->Enabled = false;
		}

		if (r == &kick_Near.frames[kick_Near.last_frame - 1] && App->scene_King->Zoom == true)
		{
			kicknearCollider->SetPos((position.x + 40)*1.3, position.y + 12 - r->h + 40);

			kicknearCollider->Enabled = true;
		}
		else
		{
			kicknearCollider->Enabled = false;
		}
		if (r == &kickJump.frames[kickJump.last_frame - 1] && App->scene_King->Zoom == true) {

			kickjump->SetPos((position.x + 25)*1.3, position.y - r->h + 40);

			kickjump->Enabled = true;
		}
		else
		{
			kickjump->Enabled = false;
		}
		if (r == &punchJump.frames[punchJump.last_frame - 1] && App->scene_King->Zoom == true) {

			punchjump->SetPos((position.x+25)*1.3, position.y - r->h + 40);

			punchjump->Enabled = true;
		}
		else
		{
			punchjump->Enabled = false;
		}
		if (r == &punchCrouch.frames[punchJump.last_frame - 2] && App->scene_King->Zoom == true) {
			punchCrouchCollider->SetPos((position.x + 50)*1.3, position.y + 30 - r->h + 40);

			punchCrouchCollider->Enabled = true;
		}
		else
		{
			punchCrouchCollider->Enabled = false;
		}

	}
	
	
	
	wall = false;


	//Stamina increase
	if (App->player2->Stamina < 100)
	{
		App->player2->Stamina = (App->player2->Stamina + 0.05);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// HITBOXES AND ZOOM
	if (App->scene_King->Zoom == true && createnewbighitbox == true) {
		ryohitbox->to_delete = true;
		createnewbighitbox2 = true;
		ryohitbox = App->collision->AddCollider({ position.x,position.y, 55, 120 }, COLLIDER_ENEMY, this);
		createnewbighitbox = false;

	}
	if (App->scene_King->Zoom == false && createnewbighitbox2 == true) {
		ryohitbox->to_delete = true;
		createnewbighitbox = true;
		ryohitbox = App->collision->AddCollider({ position.x,position.y, 35, 80 }, COLLIDER_ENEMY, this);
		createnewbighitbox2 = false;

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
			case IN_JUMP2: state = ST_JUMP_NEUTRAL; jumpSpeed = 5;  App->input->jump_timer2 = SDL_GetTicks(); animstart = 0; jumptimer = SDL_GetTicks(); break;
			case IN_CROUCH_DOWN2: state = ST_CROUCH; break;
			case IN_Y: state = ST_PUNCH_STANDING, App->input->punch_timer2 = SDL_GetTicks(); break;
			case IN_U:
				if (SDL_GetTicks() - combotime < 120) {
					if (combo1 == 2)combo1 = 3;
				}
				if (combo1 == 3)
				{
					state = ST_HADOUKEN; App->input->hadouken_timer2 = SDL_GetTicks(); combo1 = 0; break;
				}
				if (SDL_GetTicks() - combotime < 120) {
					if (combo2 == 2)combo2 = 3;
				}
				if (combo2 == 3 && Stamina >= 20)
				{
					state = ST_MOUSHUUKYAKU; App->input->moshuukyaku_timer2 = SDL_GetTicks(); combo2 = 0; break;
				}
				else {
					state = ST_KICK_STANDING, App->input->kick_timer2 = SDL_GetTicks(); break;
				}
			case IN_H: state = ST_HADOUKEN, App->input->hadouken_timer2 = SDL_GetTicks(); break;
			case IN_N: state = ST_MOUSHUUKYAKU, App->input->moshuukyaku_timer2 = SDL_GetTicks(); break;
			case IN_M: state = ST_TORNADOKICK, App->input->tornadokick_timer2 = SDL_GetTicks(); break;
			case IN_CHARGE_DOWN2: state = ST_CHARGE; break;
			case IN_DAMAGE2: state = ST_DAMAGE, App->input->damage_timer2 = SDL_GetTicks(); break;
			case IN_TAUNT2: state = ST_TAUNT, App->input->taunt_timer2 = SDL_GetTicks(); break;
			case IN_WIN2: state = ST_WIN; break;
			case IN_DEFEAT2: state = ST_DEFEAT; break;
			case IN_DAMAGE_HADOKEN2: state = ST_DAMAGE_HADOKEN, App->input->damageHadoken_timer2 = SDL_GetTicks(); break;

			}
		}
		break;

		case ST_WALK_FORWARD:
		{
			//MOSTUAMARU RIGHT SIDE
			if (SDL_GetTicks() - combotime < 120) {
				if (combo2 == 1)combo2 = 2;
				combotime = SDL_GetTicks();
			}
			else
			{
				combo2 = 0;
			}
			//HADOUKEN LEFT SIDE
			if ((position.x + 25) <= (App->player->position.x - 25))
			{
				if (SDL_GetTicks() - combotime < 120) {
					if (combo1 == 1)combo1 = 2;
					combotime = SDL_GetTicks();
				}
				else
				{
					combo1 = 0;
				}
			}
			switch (last_input)
			{
			case IN_RIGHT_UP2: state = ST_IDLE; break;
			case IN_LEFT_AND_RIGHT2: state = ST_IDLE; break;
			case IN_JUMP2: state = ST_JUMP_FORWARD; jumpSpeed = 4; jumpSpeedx = 4; jumptimer = SDL_GetTicks();  App->input->jump_timer2 = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN2: state = ST_CROUCH; break;
			case IN_Y: state = ST_PUNCH_STANDING, App->input->punch_timer2 = SDL_GetTicks(); break;
			case IN_U: state = ST_KICK_STANDING, App->input->kick_timer2 = SDL_GetTicks(); break;
			case IN_H: state = ST_HADOUKEN, App->input->hadouken_timer2 = SDL_GetTicks(); break;
			case IN_N: state = ST_MOUSHUUKYAKU, App->input->moshuukyaku_timer2 = SDL_GetTicks(); break;
			case IN_M: state = ST_TORNADOKICK, App->input->tornadokick_timer2 = SDL_GetTicks(); break;
			case IN_DAMAGE2: state = ST_DAMAGE, App->input->damage_timer2 = SDL_GetTicks(); break;
			case IN_TAUNT2: state = ST_TAUNT, App->input->taunt_timer = SDL_GetTicks(); break;
			case IN_WIN2: state = ST_WIN; break;
			case IN_DEFEAT2: state = ST_DEFEAT; break;
			case IN_DAMAGE_HADOKEN2: state = ST_DAMAGE_HADOKEN, App->input->damageHadoken_timer2 = SDL_GetTicks(); break;
			}
		}
		break;

		case ST_WALK_BACKWARD:
		{
			//NOTSUAMARU LEFT SIDE
			if ((position.x + 25) <= (App->player->position.x - 25))
			{
				if (SDL_GetTicks() - combotime < 120) {
					if (combo2 == 1)combo2 = 2;
					combotime = SDL_GetTicks();
				}
				else
				{
					combo2 = 0;
				}
			}
			//HADOUKEN LEFT SIDE
			if ((position.x + 25) >= (App->player->position.x - 25))
			{
				if (SDL_GetTicks() - combotime < 120) {
					if (combo1 == 1)combo1 = 2;
					combotime = SDL_GetTicks();
				}
				else
				{
					combo1 = 0;
				}
			}

			switch (last_input)
			{
			case IN_LEFT_UP2: state = ST_IDLE; break;
			case IN_LEFT_AND_RIGHT2: state = ST_IDLE; break;
			case IN_JUMP2: state = ST_JUMP_BACKWARD; jumpSpeed = 4; jumpSpeedx = 4; jumptimer = SDL_GetTicks(); App->input->jump_timer2 = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN2: state = ST_CROUCH; break;
			case IN_Y: state = ST_PUNCH_STANDING, App->input->punch_timer2 = SDL_GetTicks(); break;
			case IN_U: state = ST_KICK_STANDING, App->input->kick_timer2 = SDL_GetTicks(); break;
			case IN_H: state = ST_HADOUKEN, App->input->hadouken_timer2 = SDL_GetTicks(); break;
			case IN_N: state = ST_MOUSHUUKYAKU, App->input->moshuukyaku_timer2 = SDL_GetTicks(); break;
			case IN_M: state = ST_TORNADOKICK, App->input->tornadokick_timer2 = SDL_GetTicks(); break;
			case IN_TAUNT2: state = ST_TAUNT, App->input->taunt_timer = SDL_GetTicks(); break;
			case IN_DAMAGE_HADOKEN2: state = ST_DAMAGE_HADOKEN, App->input->damageHadoken_timer2 = SDL_GetTicks(); break;
			case IN_WIN2: state = ST_WIN; break;
			case IN_DEFEAT2: state = ST_DEFEAT; break;
			}
		}
		break;

		case ST_JUMP_NEUTRAL:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH2: state = ST_IDLE; animstart = 0; jumpanim = 0; SFXsound = true; SFXsound2 = true; SFXsound3 = true; damageHit = false; jumping.Reset(); break;
			case IN_WIN2: state = ST_WIN; animstart = 0; break;
			case IN_DEFEAT2: state = ST_DEFEAT; animstart = 0; break;
			case IN_Y: if (SDL_GetTicks() - jumptimer > 300) { if (jumpanim == 0)jumpanim = 1; } break;
			case IN_U: if (SDL_GetTicks() - jumptimer > 300) { if (jumpanim == 0)jumpanim = 2; } break;
				//case IN_DAMAGE_RECEIVED: state = ST_HIT, beat_timer = SDL_GetTicks(); break;
			}
		}
		break;

		case ST_JUMP_FORWARD:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH2: state = ST_IDLE; animstart = 0; jumpanim = 0; SFXsound = true; SFXsound2 = true; SFXsound3 = true; damageHit = false; jumping.Reset(); break;
			case IN_WIN2: state = ST_WIN; animstart = 0; break;
			case IN_DEFEAT2: state = ST_DEFEAT; animstart = 0; break;
			case IN_Y: if (SDL_GetTicks() - jumptimer > 300) { if (jumpanim == 0)jumpanim = 1; } break;
			case IN_U: if (SDL_GetTicks() - jumptimer > 300) { if (jumpanim == 0)jumpanim = 2; } break;
				//case IN_DAMAGE_RECEIVED: state = ST_HIT, beat_timer = SDL_GetTicks(); break;

			}
		}
		break;

		case ST_JUMP_BACKWARD:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH2: state = ST_IDLE; animstart = 0; jumpanim = 0; SFXsound = true; SFXsound2 = true; SFXsound3 = true; damageHit = false; jumping.Reset(); break;
			case IN_WIN2: state = ST_WIN; animstart = 0; break;
			case IN_DEFEAT2: state = ST_DEFEAT; animstart = 0; break;
			case IN_Y: if (SDL_GetTicks() - jumptimer > 300) { if (jumpanim == 0)jumpanim = 1; } break;
			case IN_U: if (SDL_GetTicks() - jumptimer > 300) { if (jumpanim == 0)jumpanim = 2; } break;
				//case IN_DAMAGE_RECEIVED: state = ST_HIT, beat_timer = SDL_GetTicks(); break;

			}
		}
		break;

		case ST_PUNCH_STANDING:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH2: state = ST_IDLE; animstart = 0; SFXsound = true; SFXsound3 = true; damageHit = false; break;
			case IN_DAMAGE2: state = ST_DAMAGE, App->input->damage_timer2 = SDL_GetTicks(); break;
			case IN_DAMAGE_HADOKEN2: state = ST_DAMAGE_HADOKEN, App->input->damageHadoken_timer2 = SDL_GetTicks(); break;
			case IN_WIN2: state = ST_WIN; break;
			case IN_DEFEAT2: state = ST_DEFEAT; break;
			}
		}
		break;

		case ST_CROUCH:
		{
			combo1 = 1;
			combo2 = 1;
			combotime = SDL_GetTicks();

			if (SDL_GetTicks() - combotimeHadouken < 120) {
				if (combo1 == 1)combo1 = 2;
				combotimeHadouken = SDL_GetTicks();
			}
			if (SDL_GetTicks() - combotimeMoushuuKyaku < 120) {
				if (combo2 == 1)combo2 = 2;
				combotimeMoushuuKyaku = SDL_GetTicks();
			}

			switch (last_input)
			{
			case IN_CROUCH_UP2: state = ST_IDLE; break;
			case IN_JUMP_AND_CROUCH2: state = ST_IDLE; break;
			case IN_Y: state = ST_PUNCH_CROUCH; App->input->punch_crouch_timer2 = SDL_GetTicks(); break;
			case IN_U: state = ST_KICK_CROUCH; App->input->kick_crouch_timer2 = SDL_GetTicks(); break;
			case IN_DAMAGE2: state = ST_DAMAGE, App->input->damage_timer2 = SDL_GetTicks(); break;
			case IN_TAUNT2: state = ST_TAUNT, App->input->taunt_timer = SDL_GetTicks(); break;
			case IN_DAMAGE_HADOKEN2: state = ST_DAMAGE_HADOKEN, App->input->damageHadoken_timer2 = SDL_GetTicks(); break;
			case IN_WIN2: state = ST_WIN; break;
			case IN_DEFEAT2: state = ST_DEFEAT; break;
			}
		}
		break;

		case ST_PUNCH_CROUCH:
		{
			switch (last_input)
			{
			case IN_DAMAGE_HADOKEN2: state = ST_DAMAGE_HADOKEN, App->input->damageHadoken_timer2 = SDL_GetTicks(); break;
			case IN_DAMAGE2: state = ST_DAMAGE, App->input->damage_timer2 = SDL_GetTicks(); break;
			case IN_PUNCH_CROUCH_FINISH2:
				if (IN_CROUCH_DOWN2 == true)
				{
					state = ST_CROUCH; animstart = 0; SFXsound = true; SFXsound3 = true; damageHit = false;

				}
				else
				{
					state = ST_IDLE; animstart = 0; SFXsound = true; SFXsound3 = true; damageHit = false;
				}
			}
		}
		break;

		case ST_KICK_STANDING:
		{
			switch (last_input)
			{
			case IN_KICK_FINISH2: state = ST_IDLE; animstart = 0; SFXsound = true; SFXsound3 = true; damageHit = false; break;
			case IN_DAMAGE_HADOKEN2: state = ST_DAMAGE_HADOKEN, App->input->damageHadoken_timer2 = SDL_GetTicks(); break;
			case IN_DAMAGE2: state = ST_DAMAGE, App->input->damage_timer2 = SDL_GetTicks(); break;
			case IN_WIN2: state = ST_WIN; break;
			case IN_DEFEAT2: state = ST_DEFEAT; break;
			}

		}
		break;

		case ST_KICK_CROUCH:
		{
			switch (last_input)
			{
			case IN_DAMAGE_HADOKEN2: state = ST_DAMAGE_HADOKEN, App->input->damageHadoken_timer2 = SDL_GetTicks(); break;
			case IN_DAMAGE2: state = ST_DAMAGE, App->input->damage_timer2 = SDL_GetTicks(); break;
			case IN_KICK_CROUCH_FINISH2:
				if (IN_CROUCH_DOWN2 == true)
				{
					state = ST_CROUCH; animstart = 0; SFXsound = true; SFXsound3 = true; damageHit = false; break;
				}
				else
				{
					state = ST_IDLE; animstart = 0; SFXsound = true; SFXsound3 = true; damageHit = false; break;
				}
			
			}
		}
		break;

		case ST_CHARGE:
		{
			switch (last_input)
			{
			case IN_CHARGE_UP2:state = ST_IDLE; SFXsound = true; break;
			case IN_DAMAGE2: state = ST_DAMAGE, App->input->damage_timer2 = SDL_GetTicks(); break;
			case IN_DAMAGE_HADOKEN2: state = ST_DAMAGE_HADOKEN, App->input->damageHadoken_timer2 = SDL_GetTicks(); break;
			case IN_WIN2: state = ST_WIN; break;
			case IN_DEFEAT2: state = ST_DEFEAT; break;
			}
		}

		case ST_DAMAGE:
		{
			switch (last_input)
			{
			case IN_DAMAGE_FINISH2: state = ST_IDLE; animstart = 0;  SFXsound = true; break;
			case IN_WIN2: state = ST_WIN; break;
			case IN_DEFEAT2: state = ST_DEFEAT; break;
			}
			break;
		}

		case ST_TAUNT:
		{
			switch (last_input)
			{
			case IN_TAUNT_FINISH2: state = ST_IDLE; animstart = 0;  SFXsound = true; DrainEnergy = true; break;
			case IN_DAMAGE2: state = ST_DAMAGE, App->input->damage_timer = SDL_GetTicks(); break;
			}
			break;
		}

		case ST_HADOUKEN:
		{
			switch (last_input)
			{
			case IN_HADOUKEN_FINISH2: state = ST_IDLE; animstart = 0; Activehadouken = true; SFXsound = true; break;
			}
			break;

		}

		case ST_MOUSHUUKYAKU:
		{
			switch (last_input)
			{
			case IN_MOUSHUUKYAKU_FINISH2: state = ST_IDLE; animstart = 0; Activehadouken = true; SFXsound = true; break;
			}
			break;

		}

		case ST_TORNADOKICK:
		{
			switch (last_input)
			{
			case IN_TORNADOKICK_FINISH2: state = ST_IDLE; animstart = 0; SFXsound = true; break;
			}
			break;

		}
		case ST_WIN:
			switch (last_input) 
			{
			case IN_WIN_FINISH2: state = ST_IDLE; animstart = 0; break;
			}
			break;

		case ST_DEFEAT:
			switch (last_input) 
			{
			case IN_DEFEAT_FINISH2: state = ST_IDLE; animstart = 0; break;
			}
			break;

		case ST_DAMAGE_HADOKEN:

			switch (last_input)
			{
			case IN_DAMAGE_HADOKEN_FINISH2: state = ST_IDLE; animstart = 0; break;
			}
			break;
		

		}



	}

	return state;
}

void ModulePlayer2::OnCollision(Collider* c1, Collider* c2) {


	if (ryohitbox == c1 && c2->type == COLLIDER_WALL)
	{
		wall = true;
	}

	if (ryohitbox == c1 && c2->type == COLLIDER_PLAYER)
	{
		if (inair == false && App->player->inair == false) {

			if (App->input->left == false && App->input->right == false && App->input->left2 == false && App->input->right2 == false && position.x + 25 <= App->player->position.x + 25) {
				position.x -= 10;
			}
			if (App->input->left == false && App->input->right == false && App->input->left2 == false && App->input->right2 == false && position.x + 25 > App->player->position.x + 25) {
				position.x += 10;
			}

			if (App->input->left2 == true && App->input->right == false) {
				App->player->position.x -= 2;
			}
			if (App->input->right2 == true && App->input->left == false) {
				App->player->position.x += 2;
			}
			if (App->input->right2 == true && App->input->left == false && App->player->wall == true) {
				position.x -= 4;
			}
			if (App->input->left2 == true && App->input->right == false && App->player->wall == true) {
				position.x += 4;
			}
		}
		else {

		}

	}
	
	if (position.x > 250 || App->player->position.x > 250) {
		if (ryohitbox == c1 && App->scene_King->colliderMap2 == c2)   //Colisions with second wall
		{
			if (App->input->keyboard[SDL_SCANCODE_L] == NULL) {
				position.x -= 4;
			}
			if (App->input->left2 == true) {
				speed = 0;
			}
		}
	}

	if (position.x < 100 || App->player->position.x < 100) {
		if (ryohitbox == c1 && App->scene_King->colliderMap == c2)   //Colisions with first wall
		{
			if (App->input->left2 == true) {
				position.x += 4;
			}
			if (App->input->left2 == false) {
				position.x += 4;
			}
			if (App->input->keyboard[SDL_SCANCODE_J] != NULL) {
				speed = 0;
			}
		}
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////// ATTACKS
	//////////////////////////////////////////////////////////////////////////////////////////////////////////// KICK HITBOX

	if (kickCollider == c1 && c2->type == COLLIDER_PLAYER)
	{
		if (damageHit = true) {
			damagekick = true;
		}
		App->render->StartCameraShake(300, 3);
		App->SlowDownShake->StartSlowDownShake(200, 40);
		App->player->Life= App->player->Life-3;
		App->player->hit = true;
		damageP1 = true;
		App->input->inputs.Push(IN_DAMAGE);
		if ((position.x) >= (App->player->position.x + 25)) {

			App->player->position.x -= 15;
		}
		else {
			App->player->position.x += 15;

		}

	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////// PUNCH HITBOX
	if (punchCollider == c1 && c2->type == COLLIDER_PLAYER)
	{
		if (damageHit = true) {
			damagepunch = true;
		}
		App->render->StartCameraShake(150, 2);
		App->SlowDownShake->StartSlowDownShake(500, 40);
		App->player->Life= App->player->Life-2;
		if ((position.x) >= (App->player->position.x + 25))
		{
			App->player->position.x -= 10;
		}
		else
		{
			App->player->position.x += 10;
		}
		
		App->player->hit = true;
		collision = true;
		damageP1 = true;
		App->input->inputs.Push(IN_DAMAGE);

	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////// PUNCH NEAR HITBOX
	if (punchNearCollider == c1 && c2->type == COLLIDER_PLAYER)
	{
		if (damageHit = true) {
			damagepunch = true;
		}
		App->render->StartCameraShake(100, 2);
		App->SlowDownShake->StartSlowDownShake(500, 40);
		if ((position.x) >= (App->player->position.x + 25))
		{
			App->player->position.x -= 10;
		}
		else
		{
			App->player->position.x += 10;
		}
		App->player->Life= App->player->Life-2;
		App->player->hit = true;
		collision = true;
		damageP1 = true;
		App->input->inputs.Push(IN_DAMAGE);

	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////// PUNCH CROUCH HITBOX
	if (punchCrouchCollider == c1 && c2->type == COLLIDER_PLAYER)
	{
		if (damageHit = true) {
			damagekick = true;
		}
		App->SlowDownShake->StartSlowDownShake(500, 40);
		App->player->Life = App->player->Life - 3;
		damageP1 = true;
		App->input->inputs.Push(IN_DAMAGE);
		collision = true;

		if ((App->player->position.x) >= (position.x + 25))
		{
			App->player->position.x += 10;
		}

		else
		{
			App->player->position.x -= 10;
			if ((App->player->position.x) <= (App->scene_King->positionlimitright.x + 300)) {
				App->player->position.x += 5;
			}

			if ((App->player->position.x) >= (App->scene_King->positionlimitright.x + 300)) {
				position.x -= 5;
				App->player->position.x -= 3;
			}
		}

	}





	//////////////////////////////////////////////////////////////////////////////////////////////////////////////// KICK NEAR HITBOX
	if (kicknearCollider == c1 && c2->type == COLLIDER_PLAYER)
	{
		if (damageHit = true) {
			damagekick = true;
		}
		App->SlowDownShake->StartSlowDownShake(500, 40);
		App->player->Life= App->player->Life-3;
		damageP1 = true;
		App->input->inputs.Push(IN_DAMAGE);
		collision = true;

		if ((App->player->position.x) >= (position.x + 25))
		{
			App->player->position.x += 10;
		}

		else
		{
			App->player->position.x -= 10;
			if ((App->player->position.x) <= (App->scene_King->positionlimitright.x + 300)) {
				App->player->position.x += 5;
			}

			if ((App->player->position.x) >= (App->scene_King->positionlimitright.x + 300)) {
				position.x -= 5;
				App->player->position.x -= 3;
			}
		}

	}
	/////////////////////////////////////////////////////////////////////////////////////////////////// KICK CROUCH HITBOX
	if (kickCrouchCollider == c1 && c2->type == COLLIDER_PLAYER)
	{
		if (damageHit = true) {
			damagekick = true;
		}
		App->SlowDownShake->StartSlowDownShake(500, 40);
		App->player->Life = App->player->Life - 4;
		damageP1 = true;
		App->input->inputs.Push(IN_DAMAGE);
		collision = true;

		if ((position.x + 25) >= (App->player->position.x))
		{
			App->player->position.x -= 10;
		}

		else
		{
			App->player->position.x += 10;
			if ((App->player->position.x) <= (App->scene_King->positionlimitright.x + 300)) {
				App->player->position.x += 5;
			}

			if ((App->player->position.x) >= (App->scene_King->positionlimitright.x + 300)) {
				position.x -= 5;
				App->player->position.x -= 3;
			}
		}

	}
	/////////////////////////////////////////////////////////////////////////////////////////////////// KICK JUMP HITBOX
	if (kickjump == c1 && c2->type == COLLIDER_PLAYER)
	{
		if (damageHit = true) {
			damagekick = true;
		}
		App->SlowDownShake->StartSlowDownShake(500, 40);
		App->render->StartCameraShake(150, 20);
		App->player->Life = App->player->Life - 6;
		damageP1 = true;
		App->input->inputs.Push(IN_DAMAGE);
		collision = true;

		if ((position.x + 25) >= (App->player->position.x))
		{
			App->player->position.x -= 15;
		}

		else
		{
			App->player->position.x += 15;
			if ((App->player->position.x) <= (App->scene_King->positionlimitright.x + 300)) {
				App->player->position.x += 5;
			}

			if ((App->player->position.x) >= (App->scene_King->positionlimitright.x + 300)) {
				position.x -= 5;
				App->player->position.x -= 3;
			}
		}

	}

	/////////////////////////////////////////////////////////////////////////////////////////////////// PUNCH JUMP HITBOX
	if (punchjump == c1 && c2->type == COLLIDER_PLAYER)
	{
		if (damageHit = true) {
			damagepunch = true;
		}
		App->SlowDownShake->StartSlowDownShake(500, 40);
		App->render->StartCameraShake(150, 20);
		App->player->Life = App->player->Life - 6;
		damageP1 = true;
		App->input->inputs.Push(IN_DAMAGE);
		collision = true;

		if ((position.x + 25) >= (App->player->position.x))
		{
			App->player->position.x -= 15;
		}

		else
		{
			App->player->position.x += 15;
			if ((App->player->position.x) <= (App->scene_King->positionlimitright.x + 300)) {
				App->player->position.x += 5;
			}

			if ((App->player->position.x) >= (App->scene_King->positionlimitright.x + 300)) {
				position.x -= 5;
				App->player->position.x -= 3;
			}
		}

	}
}
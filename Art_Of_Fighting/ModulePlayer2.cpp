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
#include "ModuleSceneking.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer2::ModulePlayer2()
{
	graphics = NULL;
	current_animation = NULL;


	// idle animation (arcade sprite sheet)
	idle.PushBack({ 7, 10, 54, 104 });
	idle.PushBack({ 64, 10, 54, 104 });
	idle.PushBack({ 118, 10, 54, 104 });
	idle.speed = 0.14f;

	//jump animation(arcade sprite sheet)
	jumping.PushBack({ 68,140,48,85 });
	jumping.PushBack({ 148,256,68,101 });
	jumping.PushBack({ 68,140,49,85 });
	jumping.speed = 0.05f;

	// walk forward animation (arcade sprite sheet)
	forward.PushBack({ 419, 11, 49, 103 });
	forward.PushBack({ 528, 10, 47, 104 });
	forward.PushBack({ 474, 10, 48, 104 });
	forward.PushBack({ 7, 10, 54, 104 });
	forward.speed = 0.1f;

	//backawrd animation
	backward.PushBack({ 419, 11, 49, 103 });
	backward.PushBack({ 474, 10, 48, 104 });
	backward.PushBack({ 528, 10, 47, 104 });
	backward.speed = 0.1f;

	//punch animation(arcade sprite sheet)

	punch.PushBack({ 15, 476, 48, 102 });
	punch.PushBack({ 314, 10, 94, 100 });
	punch.PushBack({ 15, 476, 48, 102 });
	punch.speed = 0.16f;

	punchJump.PushBack({ 714,141,66,94 });
	punchJump.PushBack({ 780,157,86,78 });
	punchJump.PushBack({ 714,141,66,94 });
	punchJump.speed = 0.15f;															//CHANGE

	punchCrouch.PushBack({ 335,152,70,73 });
	punchCrouch.PushBack({ 405,157,103,68 });
	punchCrouch.PushBack({ 335,152,70,73 });
	punchCrouch.speed = 0.15f;

	//kick animation(arcade sprite sheet)
	kick.PushBack({ 4,593,72,113 });
	kick.PushBack({ 96,593,51,112 });
	kick.PushBack({ 172,593,82,112 });
	kick.PushBack({ 264,599,49,102 });
	kick.PushBack({ 338,607,63,92 });
	kick.speed = 0.15f;

	lowkick.PushBack({ 84, 478, 56, 101 });
	lowkick.PushBack({ 151, 478, 49, 101 });
	lowkick.PushBack({ 211, 478, 86, 101 });
	lowkick.PushBack({ 151, 478, 49, 101 });
	lowkick.PushBack({ 84, 478, 56, 101 });
	lowkick.speed = 0.15f;

	kickJump.PushBack({ 561,146,57,89 });												//CHANGE
	kickJump.PushBack({ 618,149,96,86 });
	kickJump.PushBack({ 561,146,57,89 });
	kickJump.speed = 0.15f;

	kickCrouch.PushBack({ 335,152,70,73 });
	kickCrouch.PushBack({ 405,157,103,68 });
	kickCrouch.PushBack({ 335,152,70,73 });
	kickCrouch.speed = 0.1f;

	// Hadouken ryo animation
	hadouken.PushBack({ 431, 245, 56, 108 });                                        //CHANGE
	hadouken.PushBack({ 498, 245, 49, 100 });
	hadouken.PushBack({ 552, 245, 81, 77 });
	hadouken.PushBack({ 642, 241, 48, 86 });
	hadouken.PushBack({ 724, 241, 53, 99 });

	hadouken.speed = 0.15f;

	// crouch animation
	crouch.PushBack({ 117,133,51,92 });
	crouch.PushBack({ 15,151,49,74 });
	crouch.speed = 0.3f;
	crouch.loop = false;
	//beat animation
	beat.PushBack({ 866, 750,64,106 });
	beat.PushBack({ 934, 747,78,108 });
	beat.PushBack({ 866, 750,64,106 });

	beat.speed = 0.15f;

	player2Win.x = 0;
	player2Win.y = 0;
	player2Win.w = 120;
	player2Win.h = 39;

}

ModulePlayer2::~ModulePlayer2()
{}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("media/Spritesheets/king_SpriteSheet.png"); // arcade version
	graphicsWin = App->textures->Load("media/Win/WinPlayer.png");

	ryokick = App->audio->LoadFX("media/FX/ryo_kick.wav");
	ryopunch = App->audio->LoadFX("media/FX/Ryo_punch.wav");
	ryojump = App->audio->LoadFX("media/FX/Ryojump.wav");
	ryoKoOuKen = App->audio->LoadFX("media/FX/Ryo_KoOuKen.wav");
	ryoKoOuKensound = App->audio->LoadFX("media/FX/ryoKoOuKensound.wav");

	position.x = 445;
	position.y = 210;

	ryohitbox = App->collision->AddCollider({ position.x,position.y, 50, 97 }, COLLIDER_ENEMY, this);
	kickCollider = App->collision->AddCollider({ position.x,position.y, 60, 30 }, COLLIDER_ENEMY, this);
	kickCollider->Enabled = false;
	punchCollider = App->collision->AddCollider({ position.x,position.y, 40, 15 }, COLLIDER_ENEMY, this);
	punchCollider->Enabled = false;
	return ret;
}

bool ModulePlayer2::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	App->textures->Unload(graphicsWin);


	return true;
}


// Update: draw background
update_status ModulePlayer2::Update()
{
	Animation *current_animation = &idle;

	float hadspeed = 1;
	int inicial = 120;


	///////////////////////////////////////////////////////////////////////////////////

	if (App->input->keyboard[SDL_SCANCODE_K] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &crouch;
	}

	if (App->input->keyboard[SDL_SCANCODE_L] == KEY_STATE::KEY_REPEAT)
	{
		if (wall == true && position.x > 552) {}
		else {
			current_animation = &backward;
			position.x += speed;
		}

	}

	if (App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT)
	{
		if (wall == true && (position.x > 0 && position.x < 200)) {}
		else {
			current_animation = &forward;
			position.x -= speed;
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (App->input->keyboard[SDL_SCANCODE_U] == KEY_STATE::KEY_DOWN)                                          // HADOUKEN
	{
		App->particles->AddParticle(App->particles->Hadouken1Player2, position.x - 10, position.y - 110, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->Hadouken2Player2, position.x - 8, position.y - 85, COLLIDER_ENEMY_SHOT, 100);
		App->particles->AddParticle(App->particles->Hadouken3Player2, position.x - 10, position.y - 80, COLLIDER_ENEMY_SHOT, 300);
		App->particles->AddParticle(App->particles->Hadouken4Player2, position.x - 60, position.y - 80, COLLIDER_ENEMY_SHOT, 400);
	}

	if (App->input->keyboard[SDL_SCANCODE_U] == KEY_STATE::KEY_DOWN && App->input->u == 0)
	{
		App->audio->PlayFX(ryoKoOuKen);
		App->audio->PlayFX(ryoKoOuKensound);
		App->input->u = 1;
		current_animation = &hadouken;

	}
	if (App->input->u == 1) {

		current_animation = &hadouken;
		time++;
		if (time == 25) {
			hadouken.Reset();
			App->input->u = 0;
			time = 0;
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////
																																//Punch

	if (App->input->keyboard[SDL_SCANCODE_O] == KEY_STATE::KEY_DOWN && App->input->o == 0)
	{
		App->audio->PlayFX(ryopunch);
		App->input->o = 1;
		current_animation = &punch;
	}
	if (App->input->o == 1) {

		current_animation = &punch;
		time++;
		if (time == 25) {
			punch.Reset();
			App->input->o = 0;
			time = 0;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////

	if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN && App->input->p == 0)                                     //Kick
	{
		App->input->p = 1;
		current_animation = &kick;
		App->audio->PlayFX(ryokick);

	}
	if (App->input->p == 1) {

		current_animation = &kick;
		time++;
		if (time == 25) {
			kick.Reset();
			App->input->p = 0;
			time = 0;
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_DOWN && position.y == 210)                             //   JUMP  
	{
		App->audio->PlayFX(ryojump);
		App->input->i = 1;
		current_animation = &jumping;
	}

	if (App->input->i == 1) 
	{
		position.y--; position.y = position.y - 2; current_animation = &jumping;
	}
	if (position.y == 120) 
	{ 
		App->input->i = 0; 
	}
	if (App->input->i == 0 && position.y != 210) 
	{
		position.y = position.y + 3; /*position.y++*/; current_animation = &jumping;
	}
	speed = 2;
	// Draw everything --------------------------------------
	SDL_Rect* r = &current_animation->GetCurrentFrame();

	
	
		if ((position.x-25) >= (App->player->position.x+25)) {
			App->render->BlitWithScale(graphics, position.x, position.y - r->h, r, -1, 1.0f, 1, TOP_RIGHT);
		}
		else {
			App->render->Blit(graphics, position.x-50, position.y - r->h, r);
		}

	

	ryohitbox->SetPos(position.x-50, position.y - r->h);

	wall = false;

	if (r == &kick.frames[kick.last_frame - 1])
	{
		if (position.x > App->player->position.x) {
			kickCollider->SetPos(position.x - 100, position.y - r->h);
		}
		else {
			kickCollider->SetPos(position.x , position.y - r->h);
		}
		kickCollider->Enabled = true;
	}
	else
	{
		kickCollider->Enabled = false;
	}

	if (r == &punch.frames[punch.last_frame - 1])
	{
		if (position.x>App->player->position.x) {
			punchCollider->SetPos(position.x - 90, position.y + 12 - r->h);
		}
		else {
			punchCollider->SetPos(position.x, position.y + 12 - r->h);
		}

		punchCollider->Enabled = true;
	}
	else
	{
		punchCollider->Enabled = false;
	}

	if (App->player->Life <= 0)
	{

		App->render->BlitWithScale(graphicsWin, 212, 70, &player2Win, 1, 0.0f, 1.0f, TOP_RIGHT);
	}
	return UPDATE_CONTINUE;
}

void ModulePlayer2::OnCollision(Collider* c1, Collider* c2) {

	
	if (ryohitbox == c1 && c2->type == COLLIDER_WALL)
	{
		wall = true;
	}
	if (kickCollider == c1 && c2->type == COLLIDER_PLAYER)
	{
		App->player->Life--;
		if (position.x < App->player->position.x) {
			App->player->position.x += 5;
		}
		else {
			App->player->position.x -= 5;
		}
	}

	if (ryohitbox == c1 && c2->type == COLLIDER_PLAYER)
	{
		if (App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) {
			speed = 0;
			
		}
		else if (App->input->keyboard[SDL_SCANCODE_L] == KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) { //NEWW 
			speed = 0;
			
		}
		else if (App->input->keyboard[SDL_SCANCODE_J] != NULL && App->input->keyboard[SDL_SCANCODE_D] == NULL) { //when player 2 run and player 1 no(player 2 in the left side)
			speed = 1;
		}
		else if (App->input->keyboard[SDL_SCANCODE_D] != NULL && App->input->keyboard[SDL_SCANCODE_J] == NULL) { //when player 1 run and player 2 no(player 2 in the left side)
			position.x += 2;
		}
		else if (App->input->keyboard[SDL_SCANCODE_L] != NULL && App->input->keyboard[SDL_SCANCODE_A] == NULL) { //when player 2 run and player 1 no (player 2 in the left side)
			speed = 1;
		}
		else if (App->input->keyboard[SDL_SCANCODE_A] != NULL && App->input->keyboard[SDL_SCANCODE_L] == NULL) { //when player 2 run and player 1 no (player 2 in the left side)
			position.x -= 2;
		}


	}

	if (ryohitbox == c1 && App->scene_King->colliderMap2 == c2)   //Colisions with second wall
	{
		if (App->input->keyboard[SDL_SCANCODE_L] == NULL) {
			position.x -= 2;
		}
		if (App->input->keyboard[SDL_SCANCODE_L] != NULL) {
			speed = 0;
		}
	}
	if (ryohitbox == c1 && App->scene_King->colliderMap == c2)   //Colisions with first wall
	{
		if (App->input->keyboard[SDL_SCANCODE_J] == NULL) {
			position.x += 2;
		}
		if (App->input->keyboard[SDL_SCANCODE_J] != NULL) {
			speed = 0;
		}
	}
	if (punchCollider == c1 && c2->type == COLLIDER_PLAYER)
	{
		App->player->Life--;
		if (position.x < App->player->position.x) {
			App->player->position.x += 5;
		}
		else {
			App->player->position.x -= 5;
		}
	}
	
}

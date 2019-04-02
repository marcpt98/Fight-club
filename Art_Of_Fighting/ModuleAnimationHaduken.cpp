#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleAnimationHaduken.h"

ModuleAnimationHaduken::ModuleAnimationHaduken()
{

	ball.PushBack({ 682, 869, 25,36 });
	ball.PushBack({ 706, 869, 22,36 });
	ball.PushBack({ 729, 878, 26,27 });
	ball.PushBack({ 682, 913, 54,39 });
	ball.PushBack({ 736, 905, 72,47 });
	ball.PushBack({ 808, 921, 53,31 });
	ball.PushBack({ 861, 931, 36,21 });
	ball.PushBack({ 940, 613, 30,37 });
	ball.PushBack({ 971, 613, 22,36 });
	ball.PushBack({ 940, 665, 21,37 });
	ball.PushBack({ 961, 666, 23,36 });
	ball.PushBack({ 984, 666, 35,36 });

	ball.speed = 0.05f;
}

ModuleAnimationHaduken::~ModuleAnimationHaduken()
{}

// Load assets
bool ModuleAnimationHaduken::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Ryo_SpriteSheet.png"); // arcade version
	return ret;
}

// Update: draw background
update_status ModuleAnimationHaduken::Update()
{
	Animation *current_animation = &idle;
	float ballspeed = 1;

	//////////////////////////////////////////////////////////////////////////
	                                                  //special atack
	if (App->input->keyboard[SDL_SCANCODE_I] == 1) {
		current_animation = &ball;
		ballposition.x += ballspeed;
	}
	///////////////////////////////////////////////////////////////////////
	
	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);

	return UPDATE_CONTINUE;
}


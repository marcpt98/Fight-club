#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL_timer.h"
#include <math.h>
#include "ModuleSceneking.h"

ModuleParticles::ModuleParticles()
{

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{}

bool ModuleParticles::Start() 
{
	LOG("Loading particles");
	graphics = App->textures->Load("media/Spritesheets/king_Spritesheet_1.png");
	
	//HADOUKEN
	Hadouken.anim.PushBack({ 1462, 767, 36, 44 }, 0.3, 0, 0, 0, 0);
	Hadouken.anim.PushBack({ 1323, 724, 32, 42 }, 0.2, 0, 0, 0, 0);
	Hadouken2.anim.PushBack({ 1413, 736, 76, 24 }, 0.6, 0, 0, 0, 0);	//Loop animation
	Hadouken2.anim.PushBack({ 1346, 699, 59, 28 }, 0.6, 0, 0, 0, 0);   //Loop animation
	
	//HADOUKEN NO ENERGY
	HadoukenEnergy.anim.PushBack({ 1462, 767, 36, 44 }, 0.3, 0, 0, 0, 0);
	HadoukenEnergy.anim.PushBack({ 1323, 724, 32, 42 }, 0.2, 0, 0, 0, 0);
	HadoukenEnergy2.anim.PushBack({ 1412, 699, 26, 26 }, 0.2, 0, 0, 0, 0);
	HadoukenEnergy2.anim.PushBack({ 1323, 724, 32, 42 }, 0.2, 0, 0, 0, 0);
	HadoukenEnergy2.anim.PushBack({ 1462, 767, 36, 44 }, 0.1, 0, 0, 0, 0);
	HadoukenEnergy2.anim.PushBack({ 1378, 736, 29, 46 }, 0.1, 0, 0, 0, 0);

	Hadouken2.anim.loop = true;
	Hadouken2.life = 3000;
	Hadouken2.speed.x = +3;

	HadoukenEnergy2.anim.loop = false;
	HadoukenEnergy2.life = 450;
	HadoukenEnergy2.speed.x = +3;

	//HADOUKEN FLIP
	HadoukenFlip.anim.PushBack({ 1533, 766, 36, 44 }, 0.3, 0, 0, 0, 0);
	HadoukenFlip.anim.PushBack({ 1648, 719, 30, 39 }, 0.2, 0, 0, 0, 0);
	HadoukenFlip2.anim.PushBack({ 1559, 732, 78, 24 }, 0.6, 0, 0, 0, 0);	 //Loop animation
	HadoukenFlip2.anim.PushBack({ 1630, 775, 61, 30 }, 0.6, 0, 0, 0, 0);   //Loop animation

	//HADOUKEN FLIP NO ENERGY
	HadoukenFlipEnergy.anim.PushBack({ 1533, 766, 36, 44 }, 0.3, 0, 0, 0, 0);
	HadoukenFlipEnergy.anim.PushBack({ 1648, 719, 30, 39 }, 0.2, 0, 0, 0, 0);
	HadoukenFlipEnergy2.anim.PushBack({ 1412, 699, 26, 26 }, 0.2, 0, 0, 0, 0);
	HadoukenFlipEnergy2.anim.PushBack({ 1648, 719, 30, 39 }, 0.2, 0, 0, 0, 0);
	HadoukenFlipEnergy2.anim.PushBack({ 1533, 766, 36, 44 }, 0.3, 0, 0, 0, 0);
	HadoukenFlipEnergy2.anim.PushBack({ 1584, 766, 29, 46 }, 0.1, 0, 0, 0, 0);

	HadoukenFlip2.anim.loop = true;
	HadoukenFlip2.life = 3000;
	HadoukenFlip2.speed.x = -3;

	HadoukenFlipEnergy2.anim.loop = false;
	HadoukenFlipEnergy2.life = 450;

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

update_status  ModuleParticles::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			if (App->scene_King->Zoom==false) { App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame())); }
			else{ App->render->Blit(graphics, p->position.x/1.3, p->position.y/1.3, &(p->anim.GetCurrentFrame())); }
			if (p->fx_played == false)
			{
				p->fx_played = true;
				// Play particle fx here
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y,COLLIDER_TYPE collider_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			if (App->scene_King->Zoom == false) {
				p->position.x = x;
				p->position.y = y;
			}
			else {
				p->position.x = x*1.3;              // this is for the hitbox of the hadouken
				p->position.y = y*1.3;
			}
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;
			break;
		}
	}
	//active[last_particle++] = p;                   we arenot sure why this was here
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			delete active[i];
			active[i] = nullptr;
			if (c1->type == COLLIDER_PLAYER_SHOT && c2->type == COLLIDER_ENEMY)
			{
				
				if (App->player->Stamina >= 20)
				{
					App->player->damageHadokenP2 = true;
					App->input->inputs2.Push(IN_DAMAGE_HADOKEN2);
					App->player2->Life = App->player2->Life - 10;
				}
			}
			if (c1->type == COLLIDER_ENEMY_SHOT && c2->type == COLLIDER_PLAYER)
			{
				
				if (App->player2->Stamina >= 20)
				{
					App->player2->damageHadokenP1 = true;
					App->input->inputs.Push(IN_DAMAGE_HADOKEN);
					App->player->Life = App->player->Life - 10;
				}
			}
			break;
		}
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
{}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Particle::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;
	collider->SetPos(position.x, position.y);

	return ret;
}



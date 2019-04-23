#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL_timer.h"
#include <math.h>
#include "ModuleCollision.h"

ModuleParticles::ModuleParticles()
{

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{}

bool ModuleParticles::Start() {
	LOG("Loading particles");
	graphics = App->textures->Load("media/Ryo_SpriteSheet.png");

	Hadouken1.anim.PushBack({ 682, 869, 25,36 });	//First hadouken frame (hand, orange particles) (Starts on the second frame of Ryo hadouken animation)
	Hadouken2.anim.PushBack({ 706, 869, 22,36 });	//Second hadouken frame (hand, orange ball)
	Hadouken3.anim.PushBack({ 729, 878, 26,27 });	//Third hadouken frame (hand, bigger and whiter orange ball)
													//Still third hadouken frame (hand, bigger and whiter orange ball)
	Hadouken4.anim.PushBack({ 682, 913, 54,39 });	//Fourth hadouken frame (on Ryo, big blue ball) (ball start to move forward)
	Hadouken4.anim.PushBack({ 736, 905, 72,47 });	//Fifht hadouken frame (on Ryo, vey big blue ball)
	Hadouken4.anim.PushBack({ 808, 921, 53,31 });	//Six hadouken frame (almost out Ryo, blue ball moving forward)
	Hadouken4.anim.PushBack({ 861, 931, 36,21 });	//Seventh hadouken frame (out Ryo, little blue ball moving forward)
	/*Hadouken.anim.PushBack({ 940, 613, 30,37 });	//Starts again with a big blue ball (loop to frame 4 to 7)
	Hadouken.anim.PushBack({ 971, 613, 22,36 });	
	Hadouken.anim.PushBack({ 940, 665, 21,37 });	
	Hadouken.anim.PushBack({ 961, 666, 23,36 });	
	Hadouken.anim.PushBack({ 984, 666, 35,36 });*/
	Hadouken4.anim.loop = true;
	Hadouken1.anim.speed = 0.02f;
	Hadouken2.anim.speed = 0.2f;
	Hadouken3.anim.speed = 0.2f;
	Hadouken4.anim.speed = 0.02f;
	Hadouken1.life = 100;
	Hadouken4.speed.x = +3;
	Hadouken4.speed.y = 0;

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
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
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
			p->position.x = x;
			p->position.y = y;
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



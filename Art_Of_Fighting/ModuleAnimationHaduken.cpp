#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleAnimationHaduken.h"
#include "SDL/include/SDL_timer.h"
#include <math.h>

ModuleAnimationHaduken::ModuleAnimationHaduken()
{

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleAnimationHaduken::~ModuleAnimationHaduken()
{}

bool ModuleAnimationHaduken::Start() {
	LOG("Loading particles");
	graphics = App->textures->Load("Ryo_SpriteSheet.png");

	Hadouken.anim.PushBack({ 682, 869, 25,36 });
	Hadouken.anim.PushBack({ 706, 869, 22,36 });
	Hadouken.anim.PushBack({ 729, 878, 26,27 });
	Hadouken.anim.PushBack({ 682, 913, 54,39 });
	Hadouken.anim.PushBack({ 736, 905, 72,47 });
	Hadouken.anim.PushBack({ 808, 921, 53,31 });
	Hadouken.anim.PushBack({ 861, 931, 36,21 });
	Hadouken.anim.PushBack({ 940, 613, 30,37 });
	Hadouken.anim.PushBack({ 971, 613, 22,36 });
	Hadouken.anim.PushBack({ 940, 665, 21,37 });
	Hadouken.anim.PushBack({ 961, 666, 23,36 });
	Hadouken.anim.PushBack({ 984, 666, 35,36 });
	Hadouken.anim.loop = true;
	Hadouken.anim.speed = 0.2f;
	Hadouken.life = 2000;
	Hadouken.speed.x = +4;
	Hadouken.speed.y = 0;
	return true;
}

// Unload assets
bool ModuleAnimationHaduken::CleanUp()
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

update_status  ModuleAnimationHaduken::Update()
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

void ModuleAnimationHaduken::AddParticle(const Particle& particle, int x, int y, Uint32 delay)
{
	Particle* p = new Particle(particle);
	p->born = SDL_GetTicks() + delay;
	p->position.x = x;
	p->position.y = y;

	active[last_particle++] = p;
}

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
{}

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

	return ret;
}



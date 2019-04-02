#ifndef __ModuleAnimationHaduken_H__
#define __ModuleAnimationHaduken_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;
#define MAX_ACTIVE_PARTICLES 1000

struct SDL_Texture;

struct Particle
{
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;

	Particle();
	Particle(const Particle& p);
	bool Update();
};

class ModuleAnimationHaduken : public Module
{
public:
	ModuleAnimationHaduken();
	~ModuleAnimationHaduken();

	bool Start();
	update_status Update();
	bool CleanUp();

	void AddParticle(const Particle& particle, int x, int y, Uint32 delay = 0);

private:

	SDL_Texture* graphics = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];
	uint last_particle = 0;

public:

	Particle Hadouken; //this is the harouken
};

#endif
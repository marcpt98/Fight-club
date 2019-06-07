#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleSlowDownShake.h"
#include "ModuleRender.h"
#include "SDL/include/SDL_render.h"
#include "SDL/include/SDL_timer.h"

ModuleSlowDownShake::ModuleSlowDownShake()
{
}

ModuleSlowDownShake::~ModuleSlowDownShake()
{}

// Load assets
bool ModuleSlowDownShake::Start()
{
	return true;
}

// Update: draw background
update_status ModuleSlowDownShake::PostUpdate()
{
	if (slowing_down)
	{
		UpdateSlowDownShake();
	}

	return UPDATE_CONTINUE;
}
void ModuleSlowDownShake::StartSlowDownShake(int duration, int magnitude)
{
	slowdown_duration = duration;
	slowdown_magnitude = magnitude;
	slowing_down = true;
	slowdown_timer = SDL_GetTicks();
}

void ModuleSlowDownShake::UpdateSlowDownShake()
{

	if (SDL_GetTicks() - slowdown_timer < slowdown_duration) {
		SDL_Delay(slowdown_magnitude);
	}
}

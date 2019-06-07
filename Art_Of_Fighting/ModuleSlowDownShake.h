#ifndef __MODULESLOWDOWNSHAKE_H__
#define __MODULESLOWDOWNSHAKE_H__

#include "Module.h"
#include "SDL\include\SDL_rect.h"

class ModuleSlowDownShake : public Module
{
public:
	ModuleSlowDownShake();
	~ModuleSlowDownShake();

	bool Start();
	update_status PostUpdate();

	void StartSlowDownShake(int duration, int magnitude);
	void UpdateSlowDownShake();

private:
	bool slowing_down = false;

	int slowdown_duration = 0;
	int slowdown_timer = 0;

	int slowdown_magnitude = 0;
};

#endif //__MODULESLOWDOWNSHAKE_H__
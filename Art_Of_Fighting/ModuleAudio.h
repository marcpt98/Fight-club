#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"
#include "Globals.h"
#include "../SDL5_Handout/SDL_mixer/include/SDL_mixer.h"

#define MAX_AUDIO 50

class ModuleAudio : public Module
{
public:
	ModuleAudio();
	~ModuleAudio();

	bool Init();
	bool CleanUp();

	int const LoadMusic(const char* path);
	int const LoadFX(const char* path);

	bool const PlayMusic(int music);
	bool const UnLoadMusic(int music);
	bool const PlayFX(int fx);

private:
	Mix_Music * Musics[MAX_AUDIO];
	Mix_Music * FX[MAX_AUDIO];

	int lastMusic = 0;
	int lastFX = 0;
};

#endif // __ModuleTextures_H__

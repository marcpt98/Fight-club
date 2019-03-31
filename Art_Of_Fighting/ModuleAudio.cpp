#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL.h"


#pragma comment(lib, "SDL_Mixer/libx86/SDL2_mixer.lib")


ModuleAudio::ModuleAudio() : Module()
{
	for (int i = 0; i < MAX_AUDIO; i++)
	{
		Musics[i] = nullptr;
	}
}

// Destructor
ModuleAudio::~ModuleAudio()
{}

// Called before render is available
bool ModuleAudio::Init()
{
	//Init SDL_Mixer
	LOG("Init Audio library");
	bool ret = true;

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		ret = false;
	}

	return ret;
}

// Called before quitting
bool ModuleAudio::CleanUp()
{
	for (int i = 0; i < MAX_AUDIO; i++)
	{
		Mix_FreeMusic(Musics[i]);
	}

	Mix_CloseAudio();
	Mix_Quit();
	return true;
}

// Load new Music from file path
int const ModuleAudio::LoadMusic(const char* path)
{
	if (lastMusic == MAX_AUDIO - 1)
	{
		return -1;
	}
	lastMusic++;

	Musics[lastMusic] = Mix_LoadMUS(path);

	return lastMusic;
}

int const ModuleAudio::LoadFX(const char * path)
{
	return lastFX;
}

bool const ModuleAudio::PlayMusic(int music)
{
	Mix_PlayMusic(Musics[music], -1);
	return nullptr;
}

bool const ModuleAudio::UnLoadMusic(int music)
{
	if (Musics[music] == NULL)
	{
		return false;
	}

	Mix_FreeMusic(Musics[music]);
	return true;
}

bool const ModuleAudio::PlayFX(int fx)
{
	return nullptr;
}
#ifndef __ModuleRenderer_H__
#define __ModuleRenderer_H__

#include "Module.h"

struct SDL_Renderer;
struct SDL_Texture;

enum RENDER_PIVOT
{
	TOP_RIGHT,
	TOP_LEFT,
	MIDDLE
};

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init();
	update_status PostUpdate();
	update_status Update();
	update_status PreUpdate();
	bool CleanUp();
	void StartCameraShake(int duration, float magnitude);
	void UpdateCameraShake();

	bool Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed = 1.0f);
	bool BlitWithScale(SDL_Texture* texture, int x, int y, SDL_Rect* section, float scale, float speed, float fillAmount, RENDER_PIVOT pivot);

	bool DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera = true);

public:
	SDL_Renderer* renderer = nullptr;
	SDL_Rect camera;

private:
	bool shaking = false;

	int shake_duration = 0.0f;
	int shake_timer = 0.0f;
	float shake_magnitude = 0.0f;

	SDL_Point camera_offset;
};

#endif //__ModuleRenderer_H__
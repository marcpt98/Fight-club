#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "SDL/include/SDL.h"
#include "ModuleSceneking.h"
#include <time.h>
#include <stdlib.h>


ModuleRender::ModuleRender() : Module()
{
	camera.x = 0;
	camera.y = 0;
	camera.w = SCREEN_WIDTH;   
	camera.h = SCREEN_HEIGHT;  
	srand(time(NULL));
}

// Destructor
ModuleRender::~ModuleRender()
{}

// Called before render is available
bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if (REN_VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);

	if (renderer == NULL)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleRender::PreUpdate()
{
	SDL_RenderClear(renderer);

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::Update()
{
	/*
	int speed = 3;

	if (camera.x < 0 && App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)
		camera.x += speed;

	if (camera.x > -660 && App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)
		camera.x -= speed;
		*/
	if (shaking)
		UpdateCameraShake();

	if (App->scene_King->Zoom == true) {
		camera.y = -60;

	}
	else {
		camera.y = 0;
	}
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderPresent(renderer);
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);// THIS IS FOR making bigger the screen
	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy window
	if (renderer != NULL)
	{
		SDL_DestroyRenderer(renderer);
	}

	return true;
}

// Blit to screen
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed)
{
	bool ret = true;
	SDL_Rect rect;
	rect.x = (int)(camera.x * speed + camera_offset.x) + x * SCREEN_SIZE;
	rect.y = (int)(camera.y * speed + camera_offset.y) + y * SCREEN_SIZE;

	if (section != NULL)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	rect.w *= SCREEN_SIZE;
	rect.h *= SCREEN_SIZE;

	if (App->scene_King->Zoom == true) {
		rect.x = (int)(camera.x * speed + camera_offset.x) + x * SCREEN_SIZE*1.3;
		rect.y = (int)(camera.y * speed + camera_offset.y) + y * SCREEN_SIZE*1.3;
		rect.w *= SCREEN_SIZE * 1.3;
		rect.h *= SCREEN_SIZE * 1.3;
	}

	if (SDL_RenderCopy(renderer, texture, section, &rect) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleRender::BlitWithScale(SDL_Texture * texture, int x, int y, SDL_Rect * _section, float scale, float speed,float fillAmount, RENDER_PIVOT pivot)
{
	bool ret = true;
	SDL_Rect rect;
	SDL_Rect section = *_section;
	int w = section.w - section.w * fillAmount;

	section.w -= w;


	switch (pivot)
	{
	case TOP_RIGHT:
		rect.x = (int)(camera.x * speed+ camera_offset.x) + (x - section.w)* SCREEN_SIZE;
		rect.y = (int)(camera.y * speed + camera_offset.y) + y * SCREEN_SIZE;
		if (App->scene_King->Zoom == true) {
			rect.x = (int)(camera.x * speed + camera_offset.x) + (x - section.w)* SCREEN_SIZE*1.3;
			rect.y = (int)(camera.y * speed + camera_offset.y) + y * SCREEN_SIZE*1.3;
		}
		break;
	case TOP_LEFT:
		rect.x = (int)(camera.x * speed + camera_offset.x) + (x)* SCREEN_SIZE;
		rect.y = (int)(camera.y * speed + camera_offset.y) + y * SCREEN_SIZE;
		if (App->scene_King->Zoom == true) {
			rect.x = (int)(camera.x * speed + camera_offset.x) + (x)* SCREEN_SIZE*1.3;
			rect.y = (int)(camera.y * speed + camera_offset.y) + y * SCREEN_SIZE*1.3;
		}
		break;
	case MIDDLE:
		rect.x = (int)(camera.x * speed + camera_offset.x) + (x + w + section.x / 2)* SCREEN_SIZE;
		rect.y = (int)(camera.y * speed + camera_offset.y) + (y + section.y / 2)* SCREEN_SIZE;
		if (App->scene_King->Zoom == true) {
			rect.x = (int)(camera.x * speed + camera_offset.x) + (x + w + section.x / 2)* SCREEN_SIZE*1.3;
			rect.y = (int)(camera.y * speed + camera_offset.y) + (y + section.y / 2)* SCREEN_SIZE*1.3;
		}
		break;
	}

	SDL_RendererFlip flip = SDL_FLIP_NONE;

	if(scale < 0)
	{
		scale = fabsf(scale);
		flip = SDL_FLIP_HORIZONTAL;
	}

	if (&section != NULL)
	{
		rect.w = section.w * scale;
		rect.h = section.h * scale;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	if (App->scene_King->Zoom == true) {
		rect.w *= SCREEN_SIZE * 1.3;
		rect.h *= SCREEN_SIZE * 1.3;
	}
	else {
		rect.w *= SCREEN_SIZE;
		rect.h *= SCREEN_SIZE;
	}

	if (SDL_RenderCopyEx(renderer, texture, &section, &rect, 0, NULL, flip) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	if (App->scene_King->Zoom == true) {

	}

	return ret;

}


bool ModuleRender::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera)
{
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect rec(rect);
	if (use_camera)
	{
		rec.x = (int)(camera.x + rect.x * SCREEN_SIZE);
		rec.y = (int)(camera.y + rect.y * SCREEN_SIZE);
		rec.w *= SCREEN_SIZE;
		rec.h *= SCREEN_SIZE;
	}

	if (SDL_RenderFillRect(renderer, &rec) != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

void ModuleRender::StartCameraShake(int duration, float magnitude)
{
	//TODO 1: Store the data and start the shake
	shake_magnitude = magnitude;
	shake_duration = duration;
	shaking = true;
	shake_timer = SDL_GetTicks();
}

void ModuleRender::UpdateCameraShake()
{
	//TODO 2: Update the shake timer, stop shaking if we reach the full duration
	//		  Generate a random value and set the camera offset
	if (SDL_GetTicks() - shake_timer < shake_duration) {

		camera_offset.x = -(int)shake_magnitude + rand() % (int)shake_magnitude;
		camera_offset.y = -(int)shake_magnitude + rand() % (int)shake_magnitude;

	}
	else {
		camera_offset.x = 0;
		camera_offset.y = 0;
		shaking = false;
	}
}


#ifndef __MODULESCENELEVEL_1_H__
#define __MODULESCENELEVEL_1_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

#define ROUND_TIME 60000

struct SDL_Texture;

class ModuleSceneking : public Module
{
private://NEW
	int speed = 3;//NEW
	void OnMatchEnd();
public:
	ModuleSceneking();
	~ModuleSceneking();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphicsLive = nullptr;
	SDL_Texture* graphicsTime = nullptr;
	SDL_Texture* graphicsUI = nullptr;

	SDL_Rect lifeFull;
	SDL_Rect liveEmpty;
	SDL_Rect background1;
	SDL_Rect countdown;
	SDL_Rect stamina;
	SDL_Rect kingName;
	SDL_Rect picturePlayer;
	SDL_Rect pictureEnemy;
	SDL_Rect beatBy;
	SDL_Rect Round1;
	SDL_Rect Round2;
	SDL_Rect FinalRound;
	SDL_Rect Fight;
	SDL_Rect Shadow;
	SDL_Rect player1Win;
	SDL_Rect player2Win;
	SDL_Rect ball;


	Collider* colliderMap=nullptr;
	Collider* colliderMap2=nullptr;
	int Scene_king = 0;
	int end = 0;
	int round1FX = 0;
	int round2FX = 0;
	int finalRoundFX = 0;
	float foreground_pos;
	bool forward;
	float distance = 0;
	iPoint positionlimitleft;//NEW
	iPoint positionlimitright;//NEW
	int font_score = -1;
	Uint32 round_timer = 0;

	//////

	char timer_text[10];
	int font_timer = -1;
	int timer;
	uint endingtimer = 0;
	int starttime;
	int timertime;
	int timershadow;
	float camera2 = 0;
	bool zoomcounter = false;
	bool Zoom = false;
	bool matchstart = false;
	bool RoundStart = false;
	bool Round2Start = false;
	bool FinalRoundStart = false;
	bool matchforP1 = false;
	bool matchforP2 = false;
	bool matchEnded = false;
	bool paintBallforP1 = false;
	bool paintBallforP2 = false;
	bool gameEnd = false;
	int RoundsWinP1 = 0;
	int RoundsWinP2 = 0;

	bool playFX = false;
};

#endif // __MODULESCENELEVEL_1_H__
#ifndef GOLBIN_H_
#define GOLBIN_H_

#include"CommFuction.h"
#include"BaseObject.h"

#define GOLBIN_SPEED 5
#define MAX_GOLBIN_NUM 26
class Golbin :public BaseObject
{
public:

	Golbin();

	//current position
	float px, py;
	long long countdead;
	void setGolbin(SDL_Renderer* screen);
	void setclip();
	void updatePos(SDL_Rect playerrect);
	void Show(SDL_Renderer* screen, SDL_Rect* current_clip, SDL_Texture* golbin);
	bool CheckCollision(const SDL_Rect& UnderTown, const SDL_Rect& Golbin);

	bool front;//front town
	bool faceLeft;
	bool isDead;
	bool attack;
	int bosshealth = 10;
	SDL_Rect GolbinDesRect;
	int numchar;
	int frame_x_;
	int frame_y_;
	int maxframe_x_;
	int maxframe_y_;
	SDL_Rect frame_clip_golbin[5][7];
	SDL_Texture* golbintexture[MAX_GOLBIN_NUM];

private:
	SDL_RendererFlip typeFlip;
};

#endif // !GOLBIN_H_

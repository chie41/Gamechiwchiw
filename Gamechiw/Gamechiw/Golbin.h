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
	void setclip();
	void updatePos(SDL_Rect playerrect);
	void Show(SDL_Renderer* screen, SDL_Rect playerDesRect, SDL_Texture* p_object);

	long long countinteraction;

	bool front;//front town
	bool faceLeft;
	bool isDead;
	bool attack;
	int health ;
	SDL_Rect GolbinDesRect;
	int numchar;
	int frame_x_;
	int frame_y_;
	int frame_x_dead;
	int frame_y_dead;
	int maxframe_x_;
	int maxframe_y_;
	SDL_Rect frame_clip_golbin[5][7];
	SDL_Rect frame_clip_golbin_dead[2][7];
	SDL_Texture* GolbinTexture;
	SDL_Texture* GolbinDead;
	SDL_RendererFlip typeFlip;
private:
	
};

#endif // !GOLBIN_H_

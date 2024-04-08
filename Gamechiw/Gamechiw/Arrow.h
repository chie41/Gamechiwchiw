#ifndef ARROW_H_
#define ARROW_H_

#include"CommFuction.h"
#include "BaseObject.h"

#define ARROW_FRAME_HEIGHT 384/2
#define ARROW_FRAME_WIDTH 1536/8
class Arrow :public BaseObject
{
public:
	Arrow();

	bool attack;

	bool loadImg(std::string path, SDL_Renderer* screen);
	void ArrowUpdatePos(int x, int y);
	void setclips();
	void Show(double angle, SDL_Renderer* des,bool attack);

	double angle;

	SDL_Texture* arrowtext;

	SDL_Rect ArrowdesRect;
	SDL_Point centerarrowpoint;
	SDL_Rect frame_clip_arrow[2][8];
	int frame_x_;
	int frame_y_;
	int maxframe_x_;
	int maxframe_y_;
	SDL_RendererFlip typeFlip;
	
};

#endif // !ARROW_H_

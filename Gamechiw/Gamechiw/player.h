#ifndef PLAYER_H_
#define PLAYER_H_

#include "CommFuction.h"
#include "BaseObject.h"

#define WIDTH_MAIN_OBJECT 64
#define HEIGHT_MAIN_OBJECT 91
#define PLAYER_SPEED 8
#define PLAYER_FRAME_HEIGHT 384/2
#define PLAYER_FRAME_WIDTH 1152/6
class player :public BaseObject
{
public:
	player();
	~player();
	SDL_Rect playerdesRect;
	SDL_Rect playersourceRect;
	int status_;// status of moving
	bool status_attack;
	enum WALKType
	{
		WALK_RIGHT = 0,
		WALK_LEFT = 1,
		WALK_UP = 2,
		WALK_DOWN =3,
		NO_THING =4,
		ATTACK =5,
	};
	bool loadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);

	//XU LY DIEU KHIEN
	void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
	void set_clips();
	void Doplayer();

	//Man hinh di chuyen theo nhan vat
	void CentrerEntityOnMap();

private:
	int x_val;
	int y_val;

	int x_pos_;
	int y_pos_;

	int width_frame_;
	int height_frame_;

	SDL_Rect frame_clip_[2][6];
	Input input_type_;
	int framex_;//count frame
	int framey_;
	SDL_RendererFlip typeFlip;

	// screen;
	int start_x_;
	int start_y_;
	
};

#endif // !PLAYER_H_


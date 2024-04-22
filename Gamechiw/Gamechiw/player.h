#ifndef PLAYER_H_
#define PLAYER_H_

#include "CommFuction.h"
#include "BaseObject.h"

#define PLAYER_SPEED 8

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
		WALK_DOWN = 2,
		WALK_UP = 3,
		STAND = 4,
	};
	bool loadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);

	
	//XU LY DIEU KHIEN
	void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
	void set_clips();
	void Doplayer();

	SDL_RendererFlip typeFlip;

	int health;
private:
	int x_val;
	int y_val;

	int x_pos_;
	int y_pos_;

	int width_frame_;
	int height_frame_;

	SDL_Rect frame_clip_[6][6];
	Input input_type_;
	int framex_;//count frame
	int framey_;

	// screen;
	int start_x_;
	int start_y_;

	Mix_Chunk* p_playermovesound;
	
};

#endif // !PLAYER_H_


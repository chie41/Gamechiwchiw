#include "player.h"

player::player()
{
	framex_ = 0;
	framey_ = 0;
	
	rect_.x = SCREEN_WIDTH/2 - PLAYER_FRAME_WIDTH/2 ;
	rect_.y = SCREEN_HEIGHT/2 - PLAYER_FRAME_HEIGHT/2 - 50 ;

	width_frame_ = 0;
	height_frame_ = 0;

	typeFlip = SDL_FLIP_NONE;

}

player::~player()
{

}

bool player::loadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::loadImg(path, screen);
	if (ret == true)
	{
		width_frame_ = rect_.w / 6;
		height_frame_ = rect_.h / 2;
	}
	return ret;
}
void player::set_clips()
{
	if (width_frame_ > 0 && height_frame_ > 0)
	{
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 6; j++)
			{
				frame_clip_[i][j].x = width_frame_ * j;
				frame_clip_[i][j].y = height_frame_ * i;
				frame_clip_[i][j].w = width_frame_;
				frame_clip_[i][j].h = height_frame_;
			}

	}
	else
	{
		printf(" set clip player faillll");
	}
}

void player::Show(SDL_Renderer* des)
{	
		
	SDL_Delay(70);

	framey_ = 1 - 1;
	framex_++;
	if (framex_ >= 6)
		framex_ = 0;
	
	SDL_Rect* current_clip = &frame_clip_[framey_][framex_];
	playersourceRect = frame_clip_[framey_ / 6][framex_/2];
	SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };
	playerdesRect = renderQuad;
	//SDL_RenderCopy(des, p_object_, &frame_clip_[1][1], &renderQuad);
	//SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
	SDL_RenderCopyEx(des, p_object_, current_clip, &renderQuad, 0, NULL, typeFlip);
}


#include "player.h"

player::player()
{
	framex_ = 0;
	framey_ = 0;
	p_playermovesound = Mix_LoadWAV("sound/running.wav");

	playerdesRect.x = SCREEN_WIDTH/2 ;
	playerdesRect.y = SCREEN_HEIGHT/2;

	rect_.x = SCREEN_WIDTH/2 ;
	rect_.y = SCREEN_HEIGHT /2 ;

	x_pos_ = SCREEN_WIDTH / 2-96;
	y_pos_ = SCREEN_HEIGHT / 2-66;

	x_val = 0;
	y_val = 0;

	typeFlip = SDL_FLIP_NONE;
	status_ = STAND;
	input_type_.standing_ = 1;
	health = 5;
}

player::~player()
{

}

bool player::loadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::loadImg(path, screen);
	if (ret == true)
	{
		width_frame_ = rect_.w / 6 ;
		height_frame_ = rect_.h / 6 ;
	}
	return ret;
}
void player::set_clips()
{
	if (width_frame_ > 0 && height_frame_ > 0)
	{
		for (int i = 0; i < 6; i++)
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
	
	SDL_Delay(30);

	if (input_type_.standing_==1)
	{
		framey_ = 1 - 1;
		framex_++;
		if (framex_ >= 6)
			framex_ = 0;
	}
	else
	{
		Mix_PlayChannel(-1, p_playermovesound, 0);
		framey_ = 2 - 1;
		framex_++;
		if (framex_ >= 6)
			framex_ = 0;
	}
	
	rect_.x = x_pos_;
	rect_.y = y_pos_;
	SDL_Rect* current_clip = &frame_clip_[framey_][framex_];
	playersourceRect = frame_clip_[framey_ / 6][framex_/6];
	SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };
	playerdesRect = renderQuad;
	//SDL_RenderCopy(des, p_object_, &frame_clip_[1][1], &renderQuad);
	//SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
	SDL_RenderCopyEx(des, p_object_, current_clip, &renderQuad, 0, NULL, typeFlip);
}

void player::Doplayer()
{
	x_val = 0;
	y_val = 0;

		if (input_type_.left_ == 1)
		{
			x_val -= PLAYER_SPEED;
			
		}

		if (input_type_.right_ == 1)
		{
			x_val += PLAYER_SPEED;
			
		}

		if (input_type_.up_ == 1)
		{
			y_val -= PLAYER_SPEED;
		}

		if (input_type_.down_ == 1)
		{
			y_val += PLAYER_SPEED;
		}
	x_pos_ += x_val;
	y_pos_ += y_val;

	if (x_pos_ < 0 -66) x_pos_ = 0-66;
	if (y_pos_ < 0 -68) y_pos_ = 0-68;
	if (x_pos_ + 126 > SCREEN_WIDTH ) x_pos_ = SCREEN_WIDTH-126;
	if (y_pos_ + 122 > SCREEN_HEIGHT ) y_pos_ = SCREEN_HEIGHT-122;
	//CentrerEntityOnMap();
}


void player::HandleInputAction(SDL_Event events, SDL_Renderer* des)
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_d:
		{
			status_ = WALK_RIGHT;
			input_type_.right_ = 1;
			input_type_.left_ = 0;
			input_type_.standing_ = 0;
			break;
		}
		case SDLK_a:
		{
			status_ = WALK_LEFT;
			input_type_.right_ = 0;
			input_type_.left_ = 1;
			input_type_.standing_ = 0;
			break;
		}
		case SDLK_w:
		{
			status_ = WALK_UP;
			input_type_.up_ = 1;
			input_type_.down_ = 0;
			input_type_.standing_ = 0;
			break;
		}
		case SDLK_s:
		{
			status_ = WALK_DOWN;
			input_type_.up_ = 0;
			input_type_.down_ = 1;
			input_type_.standing_ = 0;
			break;
		}
		default:
		{
			input_type_.standing_ = 1;
			break;
		}
		}

	}
	else if (events.type == SDL_KEYUP)
	{
		input_type_.standing_ = 1;
		switch (events.key.keysym.sym)
		{
		case SDLK_d:
		{
			status_ = WALK_RIGHT;
			input_type_.right_ = 0;
			input_type_.standing_ = 1;
			break;
		}
		case SDLK_a:
		{
			status_ = WALK_LEFT;
			input_type_.left_ = 0;
			input_type_.right_ = 0;
			input_type_.standing_ = 1;
			break;
		}
		case SDLK_w:
		{
			status_ = WALK_UP;
			input_type_.up_ = 0;
			input_type_.standing_ = 1;
			break;
		}
		case SDLK_s:
		{
			status_ = WALK_DOWN;
			input_type_.down_ = 0;
			input_type_.standing_ = 1;
			break;
		}
		}
	}
}

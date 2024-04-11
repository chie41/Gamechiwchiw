#include "player.h"

player::player()
{
	framex_ = 0;
	framey_ = 0;
	
	rect_.x = SCREEN_WIDTH/2 - PLAYER_FRAME_WIDTH/2 ;
	rect_.y = SCREEN_HEIGHT/2 - PLAYER_FRAME_HEIGHT/2 - 50 ;

	width_frame_ = PLAYER_FRAME_WIDTH;
	height_frame_ = PLAYER_FRAME_HEIGHT;

	typeFlip = SDL_FLIP_NONE;
	status_ = STAND;
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
		height_frame_ = rect_.h / 6;
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

	if (status_ = STAND)
	{
		framey_ = 1 - 1;
		framex_++;
		if (framex_ >= 6)
			framex_ = 0;
	}
	else
	{
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
		}
		break;
		case SDLK_a:
		{
			status_ = WALK_LEFT;
			input_type_.right_ = 0;
			input_type_.left_ = 1;
			input_type_.standing_ = 0;
		}
		break;
		case SDLK_w:
		{
			status_ = WALK_UP;
			input_type_.up_ = 1;
			input_type_.down_ = 0;
			input_type_.standing_ = 0;
		}
		break;
		case SDLK_s:
		{
			status_ = WALK_DOWN;
			input_type_.up_ = 0;
			input_type_.down_ = 1;
			input_type_.standing_ = 0;
		}
		break;
		default:
		{
			input_type_.standing_ = 1;
		}
		break;
		}

	}
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
			input_type_.standing_ = 1;
		case SDLK_d:
		{
			status_ = WALK_RIGHT;
			input_type_.right_ = 0;
			input_type_.standing_ = 1;
		}
		break;
		case SDLK_a:
		{
			status_ = WALK_LEFT;
			input_type_.left_ = 0;
			input_type_.right_ = 0;
			input_type_.standing_ = 1;
		}
		break;
		case SDLK_w:
		{
			status_ = WALK_UP;
			input_type_.up_ = 0;
			input_type_.standing_ = 1;

		}
		break;
		case SDLK_s:
		{
			status_ = WALK_DOWN;
			input_type_.down_ = 0;
			input_type_.standing_ = 1;
		}
		break;
		}
	}
}

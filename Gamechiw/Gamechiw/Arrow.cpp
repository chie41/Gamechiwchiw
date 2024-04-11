#include"Arrow.h"

Arrow::Arrow()
{
	//ArrowdesRect = { SCREEN_WIDTH / 2 - PLAYER_FRAME_WIDTH / 2,SCREEN_HEIGHT / 2 - PLAYER_FRAME_HEIGHT / 2 - 50 ,ARROW_FRAME_WIDTH, ARROW_FRAME_HEIGHT};
	//ArrowdesRect = { SCREEN_WIDTH / 2 - PLAYER_FRAME_WIDTH / 2,SCREEN_HEIGHT / 2 - PLAYER_FRAME_HEIGHT / 2 - 50,50,32 };
	ArrowdesRect = { SCREEN_WIDTH / 2 - PLAYER_FRAME_WIDTH / 2+80,SCREEN_HEIGHT / 2 - PLAYER_FRAME_HEIGHT / 2 +40 ,50+10, 32+10 };
	ArrowsourceRect = { 0,0,50+10,32 +10};
	//centerarrowpoint = { ARROW_FRAME_HEIGHT/2, ARROW_FRAME_WIDTH/2 };
	centerarrowpoint = { 17 ,17 };
	maxframe_x_ = 2;
	maxframe_y_ = 6;

	attack = false;

}

bool Arrow::loadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::loadImg(path, screen);
	if (ret == false)
	{
		printf("fail to load arrow img");
	}
	return ret;
}

void Arrow:: ArrowUpdatePos (int x,int y)
{
	ArrowdesRect.x = x;
	ArrowdesRect.y = y;
}
void Arrow::setclips()
{
	for (int i = 0; i < maxframe_x_; i++)
		for (int j = 0; j < maxframe_y_; j++)
		{
			frame_clip_arrow[i][j].x = ARROW_FRAME_WIDTH * j;
			frame_clip_arrow[i][j].y = ARROW_FRAME_HEIGHT * i;
			frame_clip_arrow[i][j].w = ARROW_FRAME_WIDTH;
			frame_clip_arrow[i][j].h = ARROW_FRAME_HEIGHT;
		}
}
void Arrow::Show(double angle, SDL_Renderer* des,bool attack)
{
	if (attack == true)
	{
		//frame_y_ = 2 - 1;
		frame_y_ = 0;
		frame_x_ = 0;
			SDL_Rect* current_clip = &frame_clip_arrow[frame_y_][frame_x_];
			SDL_Rect renderQuad = { ArrowdesRect.x, ArrowdesRect.y, ARROW_FRAME_WIDTH, ARROW_FRAME_HEIGHT };
			//SDL_RenderCopyEx(des, p_object_, current_clip, &renderQuad, angle, &centerarrowpoint, typeFlip);
			SDL_RenderCopyEx(des, p_object_, &ArrowsourceRect, &ArrowdesRect, angle, &centerarrowpoint, typeFlip);
	}
	else
	{
		frame_y_ = 0;
		frame_x_ = 0;
		angle = 0;
		SDL_Rect* current_clip = &frame_clip_arrow[frame_y_][frame_x_];
		SDL_Rect renderQuad = { ArrowdesRect.x, ArrowdesRect.y, ARROW_FRAME_WIDTH, ARROW_FRAME_HEIGHT };

		//SDL_RenderCopyEx(des, p_object_, current_clip, &renderQuad, angle, &centerarrowpoint, typeFlip);
		SDL_RenderCopyEx(des, p_object_, &ArrowsourceRect, &ArrowdesRect, angle, &centerarrowpoint , typeFlip);
	}
	
}

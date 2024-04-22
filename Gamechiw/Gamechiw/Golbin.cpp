#include"Golbin.h"

Golbin::Golbin()
{
	frame_x_ = 0;
	frame_y_ = 0;
	frame_x_dead = 0;
	frame_y_dead = 0;

	px = 100;
	py = 100;

	isDead = false;
	attack = false;
	numchar = 1;

	health = 5;

	countinteraction = 0;

	GolbinDesRect.x = -SCREEN_WIDTH + (rand() % (SCREEN_WIDTH + 1 - -SCREEN_WIDTH));
	GolbinDesRect.y = -SCREEN_HEIGHT + (rand() % (SCREEN_HEIGHT + 1 - -SCREEN_HEIGHT));
	
	int TownDesRecty = SCREEN_HEIGHT / 2 - 256 / 2;
	int starty = GolbinDesRect.y;
	if (starty >= TownDesRecty)
	{
		front = true;
	}
	else
	{
		front = false;
	}

	GolbinDesRect.w = GOLBIN_FRAME_WIDTH;
	GolbinDesRect.h = GOLBIN_FRAME_HEIGHT;

	countdead = 0;

	maxframe_x_ = 5;
	maxframe_y_ = 7;
}
/*void Golbin::setGolbin(SDL_Renderer* screen)
{
	GolbinTexture = IMG_LoadTexture(screen, "img/Golbin-a.png");
	GolbinDead = IMG_LoadTexture(screen, "img/Golbin-a.png");
}*/

void Golbin::setclip()
{
	for (int i = 0; i < maxframe_x_; i++)
		for (int j = 0; j < maxframe_y_; j++)
		{
			frame_clip_golbin[i][j].x = GOLBIN_FRAME_WIDTH * j;
			frame_clip_golbin[i][j].y = GOLBIN_FRAME_HEIGHT * i;
			frame_clip_golbin[i][j].w = GOLBIN_FRAME_WIDTH;
			frame_clip_golbin[i][j].h = GOLBIN_FRAME_HEIGHT;
		}
	//golbin dead
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 7; j++)
		{
			frame_clip_golbin_dead[i][j].x = GOLBINDEAD_FRAME_WIDTH * j;
			frame_clip_golbin_dead[i][j].y = GOLBINDEAD_FRAME_HEIGHT;
			frame_clip_golbin_dead[i][j].w = GOLBINDEAD_FRAME_WIDTH;
			frame_clip_golbin_dead[i][j].h = GOLBINDEAD_FRAME_HEIGHT;
		}
}

void Golbin::updatePos(SDL_Rect playerDesRect)
{
	if (isDead == false)
	{
		SDL_Rect GolbinDesRect2 = { GolbinDesRect.x + 52,GolbinDesRect.y + 52,66,80 };
		float angle = atan2((playerDesRect.y - GolbinDesRect2.y ), (playerDesRect.x - GolbinDesRect2.x));
		float f1, f2;
		f1 = cos(angle) * GOLBIN_SPEED;
		f2 = sin(angle) * GOLBIN_SPEED;
		//SDL_Rect playerDesRect2 = { playerDesRect.x -10,playerDesRect.y -10,playerDesRect.w-10,playerDesRect.h -10};
		if (SDL_HasIntersection(&GolbinDesRect2, &playerDesRect))
		{
			frame_y_ = 3 - 1;
			frame_x_++;
			countinteraction++;

		}
		else {
			frame_y_ = 2 - 1;
			frame_x_++;
			GolbinDesRect.x += f1;
			GolbinDesRect.y += f2;
			countinteraction = 0;
		}
		if (GolbinDesRect.x < playerDesRect.x - 58/2 )
		{

			typeFlip = SDL_FLIP_NONE;
		}
		else
		{
			typeFlip = SDL_FLIP_HORIZONTAL;
		}
		if (frame_x_ >= maxframe_x_ - 1)
		{
			frame_x_ = 0;
		}
	}
}


void Golbin::Show(SDL_Renderer* screen, SDL_Rect playerDesRect,SDL_Texture* p_object )
{
	if (isDead == false)
	{
		//	SDL_Rect TownDesRect = { SCREEN_WIDTH / 2 - 128 / 2 ,SCREEN_HEIGHT / 2 - 256 / 2 ,128,256 };
			//SDL_Rect UnderTownDesRect = { SCREEN_WIDTH / 2 - 45 ,SCREEN_HEIGHT / 2 + 45,85,55 };
		SDL_Rect GolbinDesRect2 = { GolbinDesRect.x + GOLBIN_FRAME_HEIGHT / 4  ,GolbinDesRect.y + GOLBIN_FRAME_WIDTH / 4  ,74 - 40 , 79 + 40 };
		float angle = atan2((playerDesRect.y - GolbinDesRect.y + 100), (playerDesRect.x - GolbinDesRect.x));
		float f1, f2;
		f1 = cos(angle) * GOLBIN_SPEED;
		f2 = sin(angle) * GOLBIN_SPEED;

		if (GolbinDesRect.x < playerDesRect.x)
		{

			typeFlip = SDL_FLIP_NONE;
		}
		else
		{
			typeFlip = SDL_FLIP_HORIZONTAL;
		}

		frame_y_ = 2 - 1;
		frame_x_++;
		if (frame_x_ >= maxframe_x_ - 1)
		{
			frame_x_ = 0;
		}
		GolbinDesRect.x += f1;
		GolbinDesRect.y += f2;
		printf("%d %d \n", GolbinDesRect.x, GolbinDesRect.y);
		SDL_Rect* current_clip = &frame_clip_golbin[frame_x_][frame_y_];
		SDL_Rect renderQuad = { GolbinDesRect.x, GolbinDesRect.y, GOLBIN_FRAME_WIDTH, GOLBIN_FRAME_HEIGHT };
		if (p_object == NULL)
		{
			printf("GoblinText NULL\n");
		}
		SDL_RenderCopyEx(screen, p_object, current_clip, &renderQuad, NULL, NULL, typeFlip);

	}
	else
	{
		frame_y_dead = 6 - 1;
		frame_x_dead++;
		if (frame_x_dead >= 7-1)
		{
			frame_x_dead = 0;
		}
		SDL_Rect current_clip = frame_clip_golbin_dead[frame_x_][frame_y_];
		SDL_Rect renderQuad = { GolbinDesRect.x, GolbinDesRect.y, GOLBINDEAD_FRAME_WIDTH, GOLBINDEAD_FRAME_HEIGHT };
		SDL_RenderCopyEx(screen, p_object , &current_clip, &renderQuad, NULL, NULL, typeFlip);
	}

}
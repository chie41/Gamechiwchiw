#include"Golbin.h"

Golbin::Golbin()
{

	px = 100;
	py = 100;

	isDead = false;
	attack = false;
	numchar = 1;

	bosshealth = 10;

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
void Golbin::setGolbin(SDL_Renderer* screen)
{
	golbintexture[1] = IMG_LoadTexture(screen, "img/Golbin-a.png");
	if (golbintexture[1] == NULL)
	{
		printf("fail to load golbin 1\n");
	}
	/*string file_img = "";
	for (int i = 1; i <= MAX_GOLBIN_NUM  ; i++)
	{
		file_img = "img/Golbin-";
		printf("%s\n", file_img);
		file_img =  file_img + char(i + 96) ;
		printf("%s\n", file_img);
		file_img = file_img + ".png";
		printf("%c\n", char(i + 96));

		printf("%s\n", file_img);

		golbintexture[i] = IMG_LoadTexture(screen, file_img.c_str());
		if (golbintexture[i] == NULL)
		{
			printf("fail to load golbin %d\n", i);
		}

	}*/
}
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
}

bool Golbin::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
	int left_a = object1.x;
	int right_a = object1.x + object1.w;
	int top_a = object1.y;
	int bottom_a = object1.y + object1.h;

	int left_b = object2.x;
	int right_b = object2.x + object2.w;
	int top_b = object2.y;
	int bottom_b = object2.y + object2.h;

	// Case 1: size object 1 < size object 2
	if (left_a > left_b && left_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			return true;
		}
	}

	if (left_a > left_b && left_a < right_b)
	{
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
			return true;
		}
	}

	if (right_a > left_b && right_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			return true;
		}
	}

	if (right_a > left_b && right_a < right_b)
	{
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
			return true;
		}
	}

	// Case 2: size object 1 < size object 2
	if (left_b > left_a && left_b < right_a)
	{
		if (top_b > top_a && top_b < bottom_a)
		{
			return true;
		}
	}

	if (left_b > left_a && left_b < right_a)
	{
		if (bottom_b > top_a && bottom_b < bottom_a)
		{
			return true;
		}
	}

	if (right_b > left_a && right_b < right_a)
	{
		if (top_b > top_a && top_b < bottom_a)
		{
			return true;
		}
	}

	if (right_b > left_a && right_b < right_a)
	{
		if (bottom_b > top_a && bottom_b < bottom_a)
		{
			return true;
		}
	}

	// Case 3: size object 1 = size object 2
	if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
	{
		return true;
	}

	return false;
}
void Golbin::Show(SDL_Renderer* screen, SDL_Rect* current_clip, SDL_Texture* golbin)
{
	if (isDead == false)
	{
		SDL_Rect TownDesRect = { SCREEN_WIDTH / 2 - 128 / 2 ,SCREEN_HEIGHT / 2 - 256 / 2 ,128,256 };
		SDL_Rect UnderTownDesRect = { SCREEN_WIDTH / 2 - 45 ,SCREEN_HEIGHT / 2 + 45,85,55 };
		SDL_Rect GolbinDesRect2 = { GolbinDesRect.x + GOLBIN_FRAME_HEIGHT / 4  ,GolbinDesRect.y + GOLBIN_FRAME_WIDTH / 4  ,74 - 40 , 79 + 40 };
		float angle = atan2((TownDesRect.y - GolbinDesRect.y + 100), (TownDesRect.x - GolbinDesRect.x));
		float f1, f2;
		f1 = cos(angle) * GOLBIN_SPEED;
		f2 = sin(angle) * GOLBIN_SPEED;

		if (GolbinDesRect.x < TownDesRect.x)
		{

			typeFlip = SDL_FLIP_NONE;
		}
		else
		{
			typeFlip = SDL_FLIP_HORIZONTAL;
		}

		if (CheckCollision(GolbinDesRect2, UnderTownDesRect))
		{
			frame_y_ = 3 - 1;
			frame_x_++;
			if (frame_x_ >= maxframe_x_ - 1)
			{
				frame_x_ = 0;
			}
		}
		else
		{
			frame_y_ = 2 - 1;
			frame_x_++;
			if (frame_x_ >= maxframe_x_ - 1)
			{
				frame_x_ = 0;
			}
			GolbinDesRect.x += f1;
			GolbinDesRect.y += f2;
		}
	}


	//SDL_Rect* current_clip = &frame_clip_golbin[frame_y_][frame_x_];
	//SDL_Delay(30);
	SDL_Rect renderQuad = { GolbinDesRect.x, GolbinDesRect.y, GOLBIN_FRAME_WIDTH, GOLBIN_FRAME_HEIGHT };

	SDL_RenderCopyEx(screen, golbin, current_clip, &renderQuad, NULL, NULL, typeFlip);
}
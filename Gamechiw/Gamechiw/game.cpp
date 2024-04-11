#include "game.h"

bool game::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Game 1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gscreen = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gscreen == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gscreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);


				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}


void game::close()
{

	SDL_DestroyRenderer(gscreen);
	gscreen = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	IMG_Quit();
	SDL_Quit();

}
void game:: loadMainObj()
{
	
	g_Background = IMG_LoadTexture(gscreen, "img/bkground.png");
	Town = IMG_LoadTexture(gscreen, "img/Tower_Blue.png");
	
	//load player
	p_player.loadImg("img/Pawn_Blue.png", gscreen);
	p_player.set_clips();

	//load arrowplayer
	p_arrow.loadImg("img/Mini gun.png", gscreen);
//	p_arrow.setclips();
	//load bullet
	bulletTex = IMG_LoadTexture(gscreen, "img/Bullet3.png");

	//setclip for golbins
	clipgolbin.setclip();
	clipgolbin.setGolbin(gscreen);

}

void game::arrowActive()
{
	SDL_GetMouseState(&mouseposx, &mouseposy);
	if (mouseposx - p_arrow.ArrowdesRect.x <= 0)
	{
		p_player.typeFlip = SDL_FLIP_HORIZONTAL;
		p_arrow.typeFlip = SDL_FLIP_HORIZONTAL;
		p_arrow.ArrowUpdatePos(p_player.playerdesRect.x + 80 - 30, p_player.playerdesRect.y + 85 );
	}
	else
	{
		p_player.typeFlip = SDL_FLIP_NONE;
		p_arrow.typeFlip = SDL_FLIP_NONE;
		p_arrow.ArrowUpdatePos(p_player.playerdesRect.x + 80, p_player.playerdesRect.y + 85);
	}
	//p_arrow.ArrowUpdatePos(p_player.playerdesRect.x + 80, p_player.playerdesRect.y + 85);
	angle = atan2((mouseposy - p_arrow.ArrowdesRect.y), (mouseposx - p_arrow.ArrowdesRect.x)) * 180.0 / 3.14152;
	//add bullet base on mouse state
	if (mousedown)
	{
		bullet __bullet;
		__bullet.bulletDesRect.x = p_arrow.ArrowdesRect.x;
		__bullet.bulletDesRect.y = p_arrow.ArrowdesRect.y;
		SDL_GetMouseState(&mouseposx, &mouseposy);
		__bullet.f1 = __bullet.getWAYf1(mouseposx, mouseposy, p_arrow.ArrowdesRect.x, p_arrow.ArrowdesRect.y);
		__bullet.f2 = __bullet.getWAYf2(mouseposx, mouseposy, p_arrow.ArrowdesRect.x, p_arrow.ArrowdesRect.y);
		_bullet.push_back(__bullet);
	}

	for (int i = 0; i < _bullet.size(); i++)
	{
		//update and check
		_bullet[i].updatebullet();
		for (int j = 0; j < golbin_list.size(); j++)
		{
			if (golbin_list[j].isDead)
			{
				if (SDL_HasIntersection(&golbin_list[j].GolbinDesRect, &_bullet[i].bulletDesRect) && _bullet[i].coll == false)
				{
					golbin_list[j].isDead = true;
					_bullet[i].coll = true;
					score++;//one enemy dead , gain one score
				}
			}

		}
		SDL_Rect nobulletzone = { p_player.playerdesRect.x - 20,p_player.playerdesRect.y - 20,p_player.playerdesRect.w + 20,p_player.playerdesRect.h + 20 };
		//draw the bullet
		if (_bullet[i].disapear() == false && !SDL_HasIntersection(&_bullet[i].bulletDesRect, &p_arrow.ArrowdesRect))
		{
			//SDL_RenderCopy(gscreen, bulletTex, NULL, &_bullet[i].bulletDesRect);
			SDL_RenderCopyEx(gscreen, bulletTex, NULL, &_bullet[i].bulletDesRect, p_arrow.angle, &p_arrow.centerarrowpoint,p_arrow.typeFlip );
		}

		//erase the bullet if out of screen or hit enemy -> save memory
		if (_bullet[i].disapear())
		{
			_bullet.erase(_bullet.begin() + i);
		}

	}


}

void game::golbinActive()
{
	for (int i = 0; i < golbin_list.size(); i++)
	{
		if (golbin_list[i].front == false )
		{
			if (golbin_list[i].isDead) {
				golbin_list[i].countdead++;
				//SDL_RenderCopyEx(maingamerenderer, enemyDead, NULL, &_enemy[i].enemyDesRect, 0, NULL, SDL_FLIP_NONE);
				int framex_golbin = golbin_list[i].frame_x_;
				int	framey_golbin = golbin_list[i].frame_y_;
				SDL_Texture* golbintex = clipgolbin.golbintexture[golbin_list[i].numchar];
				SDL_Rect current_clip = clipgolbin.frame_clip_golbin[framex_golbin][framey_golbin];
				//golbin_list[i].Show(gscreen, &current_clip, golbintex);
				if (golbin_list[i].countdead >= 200)
				{
					golbin_list.erase(golbin_list.begin() + i);
				}
			}
			if (golbin_list[i].isDead == false)//the golbin must alive to be draw on the screen
			{
				int framex_golbin = golbin_list[i].frame_x_;
				int	framey_golbin = golbin_list[i].frame_y_;
				SDL_Texture* golbintex = clipgolbin.golbintexture[golbin_list[i].numchar];

				if (golbintex == NULL)
				{
					printf("no golbintex\n");
				}

				SDL_Rect current_clip = clipgolbin.frame_clip_golbin[framey_golbin][framex_golbin];
				golbin_list[i].Show(gscreen, &current_clip, golbintex);
				//SDL_RenderCopyEx(gscreen, golbintex , NULL, &golbin_list[i].GolbinDesRect, 0, NULL, SDL_FLIP_NONE);

			}
		}
		
	}
}

void game::golbinActivefront()
{
	for (int i = 0; i < golbin_list.size(); i++)
	{
		if (golbin_list[i].front == true)
		{
			if (golbin_list[i].isDead) {
				golbin_list[i].countdead++;
				//SDL_RenderCopyEx(maingamerenderer, enemyDead, NULL, &_enemy[i].enemyDesRect, 0, NULL, SDL_FLIP_NONE);
				int framex_golbin = golbin_list[i].frame_x_;
				int	framey_golbin = golbin_list[i].frame_y_;
				SDL_Texture* golbintex = clipgolbin.golbintexture[golbin_list[i].numchar];
				SDL_Rect current_clip = clipgolbin.frame_clip_golbin[framex_golbin][framey_golbin];
				//golbin_list[i].Show(gscreen, &current_clip, golbintex);
				if (golbin_list[i].countdead >= 200)
				{
					golbin_list.erase(golbin_list.begin() + i);
				}
			}
			if (golbin_list[i].isDead == false)//the golbin must alive to be draw on the screen
			{
				int framex_golbin = golbin_list[i].frame_x_;
				int	framey_golbin = golbin_list[i].frame_y_;
				SDL_Texture* golbintex = clipgolbin.golbintexture[golbin_list[i].numchar];

				if (golbintex == NULL)
				{
					printf("no golbintex\n");
				}

				SDL_Rect current_clip = clipgolbin.frame_clip_golbin[framey_golbin][framex_golbin];
				golbin_list[i].Show(gscreen, &current_clip, golbintex);
				//SDL_RenderCopyEx(gscreen, golbintex , NULL, &golbin_list[i].GolbinDesRect, 0, NULL, SDL_FLIP_NONE);

			}

		}
	}
}

void game::creategolbin()
{
	if (golbin_list.size() < maxgolbin)
	{
		Golbin __golbin;
		//check if the random position is in the screen or not because we need it to be outside
		if (abs(__golbin.GolbinDesRect.x - p_player.playerdesRect.x) > SCREEN_WIDTH / 2 && abs(__golbin.GolbinDesRect.y - p_player.playerdesRect.y) > SCREEN_HEIGHT / 2)
		{
			golbin_list.push_back(__golbin);
		}

	}

}
void game::create()
{
	//SDL_RenderClear(gscreen);
	if (g_Background != NULL)
	{
		SDL_RenderCopy(gscreen, g_Background, NULL, NULL);
	}
	else
	{
		printf("fail load bkgr!!");
	}

	if (Town != NULL)
	{
		//SDL_RenderCopy(gscreen, Town, NULL, &TownDesRect);
	}
	else
	{
		printf("fail load town !!");
	}
	

}

void game::gameloop()
{
	if (!init())
	{
		printf("Failed to initialize!\n");
		return ;
	}

	loadMainObj();

	bool quit = false;

	while (!quit)
	{
		while (SDL_PollEvent(&g_event) != 0)
		{
			//User requests quit
			if (g_event.type == SDL_QUIT)
			{
				quit = true;
			}
			if(g_event.type == SDL_MOUSEBUTTONDOWN)
			{
					mousedown = true;
					p_arrow.attack = true;
					break;
			}
			else
			if (g_event.type == SDL_MOUSEBUTTONUP)
			{
				mousedown = false;
				p_arrow.attack = false;
				break;
			}
			p_player.HandleInputAction(g_event, gscreen);

		}
		SDL_SetRenderDrawColor(gscreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR); 
		SDL_RenderClear(gscreen);

		create();

		creategolbin();
		//golbinActive();
		//SDL_RenderCopy(gscreen, Town, NULL, &TownDesRect);
		//golbinActivefront();

		p_player.Show(gscreen);
		p_player.Doplayer();
		
		arrowActive();
		
		p_arrow.Show(angle, gscreen, p_arrow.attack);
		
	
		SDL_RenderPresent(gscreen);
	}
	close();
}

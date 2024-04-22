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
			if (TTF_Init() == -1)
			{
				printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
				success = false;
			}
			Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
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

void game::loadSound()
{
	gMusic = Mix_LoadMUS("sound/background.wav");
	if (gMusic == NULL)
	{
		printf("Failed to load gMusic! SDL_mixer Error: %s\n", Mix_GetError());
	}
	menusoundclick = Mix_LoadWAV("sound/menusound.wav");
	if (menusoundclick == NULL)
	{
		printf("Failed to load menusound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
	
	golbinattacksound = Mix_LoadWAV("sound/golbinattack.wav");
	golbindeathsound = Mix_LoadWAV("sound/golbindeath.wav");

	p_playermovesound = Mix_LoadWAV("sound/running.wav");
	pickmushroomsound = Mix_LoadWAV("sound/pickmushroom.wav");

	shuttingsound = Mix_LoadWAV("sound/shutting.wav");

}

void game::loadMenuTexture()
{

	MenuText[0] = IMG_LoadTexture(gscreen, "img/Menu.png");
	MenuText[1] = IMG_LoadTexture(gscreen, "img/MenuPressStart.png");
	MenuText[2] = IMG_LoadTexture(gscreen, "img/MenuPressHow.png");
	MenuText[3] = IMG_LoadTexture(gscreen, "img/MenuPressSetting.png");
	MenuText[4] = IMG_LoadTexture(gscreen, "img/MenuPressQuit.png");
	MenuText[5] = IMG_LoadTexture(gscreen, "img/HowToPlay.png");
	MenuText[6] = IMG_LoadTexture(gscreen, "img/SettingMusicOn.png");
	MenuText[7] = IMG_LoadTexture(gscreen, "img/SettingMusicOff.png");

	MenuText[8] = IMG_LoadTexture(gscreen, "img/pause.png");
	MenuText[9] = IMG_LoadTexture(gscreen, "img/presspause.png");

	MenuText[10] = IMG_LoadTexture(gscreen, "img/wall.png");

	MenuText[11] = IMG_LoadTexture(gscreen, "img/Menu_restart.png");

	MenuText[12] = IMG_LoadTexture(gscreen, "img/YouLose.png");
}
void game::drawmenu()
{
	SDL_GetMouseState(&mouseposx, &mouseposy);
	//SDL_RenderClear(gscreen);
	//draw setting
	if (setting && MusicOn) 
	{
		SDL_RenderCopy(gscreen, MenuText[6], NULL, NULL);
	}

	if (setting && !MusicOn)
	{
		SDL_RenderCopy(gscreen, MenuText[7], NULL, NULL);
	}

	if (mainmenu && !howtoplay && !setting)
	{
		SDL_RenderCopy(gscreen, MenuText[0], NULL, NULL);
		
	}
	//draw how to play 
	if (howtoplay)
	{
		SDL_RenderCopy(gscreen, MenuText[5], NULL, NULL);
	}
	//draw menurestart
	if (menurestart)
	{
		SDL_RenderCopy(gscreen, MenuText[11], NULL, NULL);

	}
	//menu LOSE: draw game over and score
	if (menuLose)
	{
		SDL_RenderCopy(gscreen, MenuText[12], NULL, NULL);
		// draw "score"
		Font1 = TTF_OpenFont("img/font.ttf", 100);
		textColor = { 0, 0, 0 };
		scoreText = "Score";
		SDL_FreeSurface(textSurface);
		textSurface = TTF_RenderText_Blended(Font1, scoreText.c_str(), textColor);
		SDL_DestroyTexture(mTexture);
		mTexture = SDL_CreateTextureFromSurface(gscreen, textSurface);
		scoreFinal = { SCREEN_WIDTH / 2 - 130, 10, textSurface->w, textSurface->h };
		SDL_RenderCopy(gscreen, mTexture, NULL, &scoreFinal);


		// draw socre
		Font1 = TTF_OpenFont("img/font.ttf",90);
		textColor = { 0, 0, 0 };
		scoreText = to_string(score);
		SDL_FreeSurface(textSurface);
		textSurface = TTF_RenderText_Blended(Font1, scoreText.c_str(), textColor);
		SDL_DestroyTexture(mTexture);
		mTexture = SDL_CreateTextureFromSurface(gscreen, textSurface);
		scoreFinal = { SCREEN_WIDTH / 2 - 40, 110, textSurface->w, textSurface->h };
		SDL_RenderCopy(gscreen, mTexture, NULL, &scoreFinal);

	}
	SDL_RenderPresent(gscreen);
}
bool game::MenuLoop()
{
	SDL_GetMouseState(&mouseposx, &mouseposy);
	//how to play
	if (howtoplay == true)
	{
		// escape how to play
		if (mouseposx > 264 * 2 && mouseposx < 311 * 2 && mouseposy >32 * 2 && mouseposy < 80 * 2)
		{
			Mix_PlayChannel(-1, menusoundclick, 0);
			howtoplay = false;
			mainmenu = true;
		}
	}

	//music
	if (setting == true)
	{
		if (MusicOn == true)
		{
			if (mouseposx > 100 * 2 && mouseposx < 150 * 2 && mouseposy > 136 * 2 && mouseposy < 176 * 2)
			{
				Mix_PlayChannel(-1, menusoundclick, 0);
				Mix_VolumeMusic(0);
				MusicOn = false;
			}
		}
		else
		if (MusicOn == false)
		{
			if (mouseposx > 100 * 2 && mouseposx < 150 * 2 && mouseposy > 136 * 2 && mouseposy < 176 * 2)
			{
				Mix_PlayChannel(-1, menusoundclick, 0);
				Mix_VolumeMusic(60);
				MusicOn = true;
			}
		}
		// escape setting
		if (mouseposx > 264 * 2 && mouseposx < 311 * 2 && mouseposy >32 * 2 && mouseposy < 80 * 2)
		{
			Mix_PlayChannel(-1, menusoundclick, 0);
			setting = false;
			mainmenu = true;
		}
	}

	if (mainmenu)
	{
		//start
		if (mouseposx > 105 * 2 && mouseposx < 279 * 2 && mouseposy > 97 * 2 && mouseposy < 143 * 2)
		{
			Mix_PlayChannel(-1, menusoundclick, 0);
			SDL_RenderCopy(gscreen, MenuText[1], NULL, NULL);
			playing = true;
			mainmenu = false;
			setting = false;
			howtoplay = false;
			SDL_RenderPresent(gscreen);
			SDL_Delay(90);
		}
		//quit
		if (mouseposx > 105 * 2 && mouseposx < 279 * 2 && mouseposy > 290 * 2 && mouseposy < 335 * 2)
		{
			Mix_PlayChannel(-1, menusoundclick, 0);
			SDL_RenderCopy(gscreen, MenuText[4], NULL, NULL);
			quit = true;
			SDL_RenderPresent(gscreen);
			SDL_Delay(90);
			return true;
		}
		//howtoplay
		if (mouseposx > 105 * 2 && mouseposx < 279 * 2 && mouseposy > 160 * 2 && mouseposy < 207 * 2)
		{
			Mix_PlayChannel(-1, menusoundclick, 0);
			SDL_RenderCopy(gscreen, MenuText[2], NULL, NULL);
			howtoplay = true;
			mainmenu = false;
			SDL_RenderPresent(gscreen);
			SDL_Delay(90);
		}
		//setting
		if (mouseposx > 105 * 2 && mouseposx < 279 * 2 && mouseposy > 225 * 2 && mouseposy < 270 * 2)
		{
			Mix_PlayChannel(-1, menusoundclick, 0);
			SDL_RenderCopy(gscreen, MenuText[3], NULL, NULL);
			setting = true;
			mainmenu = false;
			SDL_RenderPresent(gscreen);
			SDL_Delay(90);
		}
	}
	return false;
}
bool game::MenuRestartLoop()
{
	SDL_GetMouseState(&mouseposx, &mouseposy);
	//music
	if (setting == true)
	{
		if (MusicOn == true)
		{
			if (mouseposx > 100 * 2 && mouseposx < 150 * 2 && mouseposy > 136 * 2 && mouseposy < 176 * 2)
			{
				Mix_PlayChannel(-1, menusoundclick, 0);
				Mix_VolumeMusic(0);
				MusicOn = false;
			}
		}
		else
			if (MusicOn == false)
			{
				if (mouseposx > 100 * 2 && mouseposx < 150 * 2 && mouseposy > 136 * 2 && mouseposy < 176 * 2)
				{
					Mix_PlayChannel(-1, menusoundclick, 0);
					Mix_VolumeMusic(60);
					MusicOn = true;
				}
			}
		// escape setting
		if (mouseposx > 264 * 2 && mouseposx < 311 * 2 && mouseposy >32 * 2 && mouseposy < 80 * 2)
		{
			Mix_PlayChannel(-1, menusoundclick, 0);
			setting = false;
			menurestart = true;
		}
	}
	else
	if (menurestart)
	{
		//continue
		if (mouseposx > 105 * 2 && mouseposx < 279 * 2 && mouseposy > 97 * 2 && mouseposy < 143 * 2)
		{
			Mix_PlayChannel(-1, menusoundclick, 0);
			menurestart = false;
		}
		else//restart
			if (mouseposx > 105 * 2 && mouseposx < 279 * 2 && mouseposy > 160 * 2 && mouseposy < 207 * 2)
			{
				Mix_PlayChannel(-1, menusoundclick, 0);
				gamereset();
				menurestart = false;
			}
			else//setting
				if (mouseposx > 105 * 2 && mouseposx < 279 * 2 && mouseposy > 225 * 2 && mouseposy < 270 * 2)
				{
					Mix_PlayChannel(-1, menusoundclick, 0);
					menurestart = false;
					setting = true;
				}
				else
					if (mouseposx > 105 * 2 && mouseposx < 279 * 2 && mouseposy > 290 * 2 && mouseposy < 335 * 2)
					{
						Mix_PlayChannel(-1, menusoundclick, 0);
						SDL_RenderCopy(gscreen, MenuText[4], NULL, NULL);
						quit = true;
						SDL_RenderPresent(gscreen);
						SDL_Delay(90);
						return true;
					}
	}

	return false;
}
bool game::MenuLOSELoop()
{
	SDL_GetMouseState(&mouseposx, &mouseposy);
	if (mouseposx > 105 * 2 && mouseposx < 279 * 2 && mouseposy > 225 * 2 && mouseposy < 270 * 2)
	{
		playing = true;
		gamereset();
		menuLose = false;
	}
	else
		if (mouseposx > 105 * 2 && mouseposx < 279 * 2 && mouseposy > 290 * 2 && mouseposy < 335 * 2)
		{
			SDL_RenderCopy(gscreen, MenuText[4], NULL, NULL);
			quit = true;
			SDL_RenderPresent(gscreen);
			SDL_Delay(90);
			return true;
		}
	return false;

}
void game:: loadMainObj()
{
	g_Background = IMG_LoadTexture(gscreen, "img/bkground.png");
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
	GolbinTexture = IMG_LoadTexture(gscreen, "img/Golbin.png");
	//GolbinDead = IMG_LoadTexture(gscreen, "img/Golbin.png");

	//load blood
	blood[1] = IMG_LoadTexture(gscreen, "img/blood1.png");
	blood[2] = IMG_LoadTexture(gscreen, "img/blood2.png");
	blood[3] = IMG_LoadTexture(gscreen, "img/blood3.png");
	blood[4] = IMG_LoadTexture(gscreen, "img/blood4.png");
	blood[5] = IMG_LoadTexture(gscreen, "img/blood5.png");
	//load heart health player
	Heart = IMG_LoadTexture(gscreen, "img/blood.png");

	//load mushroom
	Mushroomtexture = IMG_LoadTexture(gscreen, "img/mushroom.png");
	mushroomscore = IMG_LoadTexture(gscreen, "img/score.png");

	//load font
	gFont = TTF_OpenFont("img/font.ttf", 20);
	textColor = { 0, 0, 0 };
}

void game::arrowActive()
{
	SDL_GetMouseState(&mouseposx, &mouseposy);
	p_arrow.ArrowUpdatePos(p_player.playerdesRect.x + 80, p_player.playerdesRect.y + 90);

	angle = atan2((mouseposy - p_arrow.ArrowdesRect.y), (mouseposx - p_arrow.ArrowdesRect.x)) * 180.0 / 3.14152;
	//add bullet base on mouse state
	if (mousedown)
	{
		Mix_VolumeChunk(shuttingsound,20 );
		Mix_PlayChannel(-1, shuttingsound, 0);
		bullet __bullet;
		__bullet.bulletDesRect.x = p_arrow.ArrowdesRect.x;
		__bullet.bulletDesRect.y = p_arrow.ArrowdesRect.y+15;
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
			if (golbin_list[j].isDead== false)
			{
				SDL_Rect GolbinDesRect2 = { golbin_list[j].GolbinDesRect.x + 52,golbin_list[j].GolbinDesRect.y + 52,66,80 };
				if (SDL_HasIntersection(&GolbinDesRect2, &_bullet[i].bulletDesRect) && _bullet[i].coll == false)
				{
					golbin_list[j].health --;
					if (golbin_list[j].health == 0)
					{
						Mix_PlayChannel(-1, golbindeathsound, 0);
						golbin_list[j].isDead = true;
					}
					_bullet[i].coll = true;
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

			if (golbin_list[i].isDead) {
				golbin_list[i].countdead++;

				SDL_Rect playerDesRect2 = { p_player.playerdesRect.x + 66 , p_player.playerdesRect.y + 68,60,54 };

				golbin_list[i].Show(gscreen, playerDesRect2, GolbinDead);

				if (golbin_list[i].countdead >= 200)
				{
					golbin_list.erase(golbin_list.begin() + i);
				}
			}
			if (!golbin_list[i].isDead)//the golbin must alive to be draw on the screen
			{
				SDL_Rect playerDesRect2 = { p_player.playerdesRect.x + 66 , p_player.playerdesRect.y + 68,60,54 };
				golbin_list[i].updatePos(playerDesRect2);
				SDL_Rect* current_clip = &clipgolbin.frame_clip_golbin[golbin_list[i].frame_y_][golbin_list[i].frame_x_];
				SDL_Rect renderQuad = { golbin_list[i].GolbinDesRect.x , golbin_list[i].GolbinDesRect.y, GOLBIN_FRAME_WIDTH, GOLBIN_FRAME_HEIGHT};
				SDL_Rect renderQuad2 = { golbin_list[i].GolbinDesRect.x +52, golbin_list[i].GolbinDesRect.y+42, 203/3,37/3 };
				if(GolbinTexture == NULL)
				{
					printf("GolbinTexture NULLLLLL \n");
				}
				SDL_Texture* GolbinSize = IMG_LoadTexture(gscreen, "img/Golbinsize.png");
				SDL_RenderCopyEx(gscreen, GolbinTexture, current_clip, &renderQuad, NULL, NULL, golbin_list[i].typeFlip);
				SDL_RenderCopy(gscreen, blood[golbin_list[i].health], NULL, &renderQuad2);
				//check if golbin attack player then player health --
				if (golbin_list[i].countinteraction > 5)
				{
					Mix_PlayChannel(-1, golbinattacksound, 0);
					p_player.health--;
					golbin_list[i].countinteraction = 0;
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
void game::createmushroom()
{
	if (mushroom_list.size() < maxmushroom)
	{
		mushroom __mushroom;
		if (__mushroom.MushroomDesRect.x > __mushroom.MushroomDesRect.w && __mushroom.MushroomDesRect.x < SCREEN_WIDTH - __mushroom.MushroomDesRect.w
			&& __mushroom.MushroomDesRect.y > __mushroom.MushroomDesRect.h && __mushroom.MushroomDesRect.y < SCREEN_HEIGHT - __mushroom.MushroomDesRect.h)
		{
			mushroom_list.push_back(__mushroom);
		}
	}
	for (int i = 0; i < mushroom_list.size(); i++)
	{
		SDL_Rect playerDesRect3 = { p_player.playerdesRect.x + 66 , p_player.playerdesRect.y + 68,60,54 };
		if (SDL_HasIntersection(&playerDesRect3, &mushroom_list[i].MushroomDesRect) && mushroom_list[i].picked == false)
		{
			Mix_PlayChannel(-1, pickmushroomsound, 0);
			score++;
			mushroom_list[i].picked = true;
		}

		if (mushroom_list[i].picked)
		{	
			mushroom_list[i].mushroomcountime++;
			if (mushroom_list[i].mushroomcountime > 200)
			{
				mushroom_list.erase(mushroom_list.begin() + i);
			}
		}
		
		if (!mushroom_list[i].picked) // show mushroom hasn't been picked to screen
		{
			SDL_RenderCopy(gscreen, Mushroomtexture, NULL, &mushroom_list[i].MushroomDesRect);
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
	
}

void game::statusbar()
{
	//freesurface to reduce memory
	string scoreText = to_string(score);
	SDL_FreeSurface(textSurface);
	textSurface = TTF_RenderText_Blended(gFont, scoreText.c_str(), textColor);

	//freetexture to reduce memory
	SDL_DestroyTexture(mTexture);
	mTexture = SDL_CreateTextureFromSurface(gscreen, textSurface);

	SDL_Rect Mushroomscore = { SCREEN_WIDTH - 120,-10,100,100 };
	SDL_RenderCopy(gscreen, mushroomscore, NULL, &Mushroomscore);
	scoreBOX = { SCREEN_WIDTH - 55, 20 , textSurface->w, textSurface->h };
	SDL_RenderCopy(gscreen, mTexture, NULL, &scoreBOX);

	//health p_player status
	for (int i = 0; i < p_player.health; i++)
	{
		SDL_Rect HeartStatusRect = { i*33,0,40,40 };
		SDL_RenderCopy(gscreen, Heart, NULL, &HeartStatusRect);
	}
}

void game::gamereset()
{
	_bullet.erase(_bullet.begin(), _bullet.end());
	golbin_list.erase(golbin_list.begin(), golbin_list.end());
	mushroom_list.erase(mushroom_list.begin(), mushroom_list.end());
	p_player.playerdesRect.x = SCREEN_WIDTH / 2;
	p_player.playerdesRect.y = SCREEN_HEIGHT / 2;
	p_player.health = 5;
	score = 0;
}
void game::gameloop()
{

	SDL_RenderClear(gscreen);
	SDL_GetMouseState(&mouseposx, &mouseposy);
		create();

		createmushroom();

		creategolbin();
		golbinActive();

		if (mouseposx - (p_player.playerdesRect.x + 96) <= 0)
		{
			p_player.typeFlip = SDL_FLIP_HORIZONTAL;
			p_arrow.typeFlip = SDL_FLIP_VERTICAL;
		}
		else
		{
			p_player.typeFlip = SDL_FLIP_NONE;
			p_arrow.typeFlip = SDL_FLIP_NONE;
		}
		p_player.Show(gscreen);
		p_player.Doplayer();

		arrowActive();

		p_arrow.Show(angle, gscreen, p_arrow.attack);

		SDL_Texture* playertest2 = IMG_LoadTexture(gscreen, "img/playersize2.png");
		SDL_Rect playerDesRect2 = { p_player.playerdesRect.x + 66 , p_player.playerdesRect.y + 68,60,54 };
		statusbar();
		//SDL_RenderCopy(gscreen, MenuText[10], NULL, NULL);
		SDL_Rect PauseDesRect = { SCREEN_WIDTH / 2 - 32 ,0,64,64 };
		if (mouseposx > SCREEN_WIDTH / 2 - 32 && mouseposx < SCREEN_WIDTH / 2 - 32 + 64
			&& mouseposy > 0 && mouseposy < 64 && mousedown && !menurestart)
		{
				Mix_PlayChannel(-1, menusoundclick, 0);
			//draw restart
			SDL_Rect PauseDesRect = { SCREEN_WIDTH / 2 - 32 ,0,64,64 };
			SDL_RenderCopy(gscreen, MenuText[9], NULL, &PauseDesRect);
			SDL_RenderPresent(gscreen);
			SDL_Delay(90);
			menurestart = true;
		}
		else
		{
			SDL_RenderCopy(gscreen, MenuText[8], NULL, &PauseDesRect);
		}

	SDL_RenderPresent(gscreen);
}


void game::GAME()
{
	if (!init())
	{
		printf("Failed to initialize!\n");
		return;
	}

	loadMainObj();
	loadMenuTexture();
	loadSound();

	bool quit = false;
	mainmenu = true;
	playing = false;
	setting = false;
	howtoplay = false;
	menurestart = false;
	menuLose = false;
	MusicOn = true;

	while (quit == false)
	{
		Mix_VolumeMusic(60);
		Mix_PlayMusic(gMusic, -1);
		//menu
		while (mainmenu == true || setting == true || howtoplay == true)
		{
			while (SDL_PollEvent(&g_event) != 0)
			{

				switch (g_event.type)
				{
					//user require quit
				case SDL_QUIT:
				{
					quit = true;
					break;
				}

				case SDL_MOUSEBUTTONDOWN:
				{
					quit = MenuLoop();
					if (quit == true)
						return;
					break;
				}
				case SDL_MOUSEBUTTONUP:
				{
					mousedown = false;
					break;
				}
				case SDL_WINDOWEVENT:
					switch (g_event.window.event) 
					{ 
					case SDL_WINDOWEVENT_CLOSE:
						close(); 
						break;
					};

				}

			}

			if (mainmenu == true || setting == true || howtoplay == true)
			{
				drawmenu();
			}
			
		}

		while (playing == true)
		{
			while (SDL_PollEvent(&g_event) != 0)
			{
				switch (g_event.type)
				{
					//user require quit
				case SDL_QUIT:
				{
					quit = true;
					break;
				}
				case SDL_MOUSEBUTTONDOWN:
				{
					mousedown = true;
					quit = MenuRestartLoop();
					if (quit == true)
					return;
					break;
				}
				case SDL_MOUSEBUTTONUP:
				{
					mousedown = false;
					break;
				}
				case SDL_WINDOWEVENT:
					switch (g_event.window.event)
					{
					case SDL_WINDOWEVENT_CLOSE:
						close();
						break;
					};

				default:
				{
					if (g_event.key.keysym.sym == SDLK_d || g_event.key.keysym.sym == SDLK_w || g_event.key.keysym.sym == SDLK_a|| g_event.key.keysym.sym == SDLK_s)
					Mix_PlayChannel(-1, p_playermovesound, 0);

					p_player.HandleInputAction(g_event, gscreen);
				}
				}

			}
			if (setting || menurestart)
			{
				drawmenu();
			}
			else
			{
				if (p_player.health > 0)
				{
					gameloop();
				}
				else
				{
					menuLose = true;
					playing = false;
					drawmenu();
					break;
				}
			}

		}
		while (menuLose == true)
		{
			while (SDL_PollEvent(&g_event) != 0)
			{
				switch (g_event.type)
				{
					//user require quit
				case SDL_QUIT:
				{
					quit = true;
					break;
				}
				case SDL_MOUSEBUTTONDOWN:
				{
					Mix_PlayChannel(-1, menusoundclick, 0);
					mousedown = true;
					quit = MenuLOSELoop();
					if (quit == true)
						return;
					break;
				}
				case SDL_MOUSEBUTTONUP:
				{
					mousedown = false;
					break;
				}

				}
				drawmenu();
			}
		}
		
	}
	close();
}
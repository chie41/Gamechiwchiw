#ifndef GAME_H_
#define GAME_H_

#include "CommFuction.h"
#include"player.h"
#include"BaseObject.h"
#include"Golbin.h"
#include"Arrow.h"
#include"Bullet.h"
class game
{
public:
	bool init();
	void loadMenuTexture();
	void loadMainObj();
	void loadOtherTexture();
	void create();
	void draw();
	void gamereset();
	void gameloop();
	void close();

	void creategolbin();
	void arrowActive();
	void golbinActive();
	void golbinActivefront();
	void checktouch();

	SDL_Event g_event;

private:
	SDL_Texture* g_Background;

	bool quit = false;
	bool lose = false;
	//player
	player p_player;
	long long health;
	long long score;


	//Arrow
	Arrow p_arrow;
	SDL_Texture* arrowtext;
	double angle;
	int mouseposx;
	int mouseposy;
	bool mousedown;
	
	//bullet
	vector<bullet> _bullet;
	SDL_Texture* bulletTex;

	//clipgolbin for setclip
	Golbin clipgolbin;
	vector <Golbin> golbin_list;
	int framex_golbin;
	int	framey_golbin;
	int maxgolbin = 50;
	SDL_Rect frame_clip_golbin[5][7];
	SDL_Texture* golbintexture[MAX_GOLBIN_NUM];

	
	//Town
	SDL_Texture* Town;
	SDL_Rect TownDesRect = { SCREEN_WIDTH/2 - 128/2 ,SCREEN_HEIGHT/2 - 256/2 ,128,256 } ;
	
	SDL_Renderer* gscreen2;
	//SDL_Window* gWindow;

	SDL_Texture* underTown;
	SDL_Rect UnderTownDesRect = { SCREEN_WIDTH / 2 - 45 ,SCREEN_HEIGHT / 2 + 45,85,55 };
	SDL_Texture* golbinone;
	SDL_Rect golbinoneDesRect = { 100 + GOLBIN_FRAME_HEIGHT/4 ,100 + GOLBIN_FRAME_WIDTH/4 ,74,79 };

};
#endif // 

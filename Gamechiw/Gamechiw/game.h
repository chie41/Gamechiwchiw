#ifndef GAME_H_
#define GAME_H_

#include "CommFuction.h"
#include"player.h"
#include"BaseObject.h"
#include"Golbin.h"
#include"Arrow.h"
#include"Bullet.h"
#include"Mushroom.h"

class game
{
public:
	void GAME();

private:
	SDL_Texture* g_Background;
	SDL_Event g_event;

	bool quit = false;
	int score;

	bool init();
	void loadMainObj();
	void create();

	void gamereset();
	void gameloop();
	void close();
/*-------------------------------*/
	//menu
	//menu fuction
	void loadMenuTexture();
	void drawmenu();
	bool MenuLoop();
	void statusbar();
	bool MenuRestartLoop();
	bool MenuLOSELoop();
	//menu object
	SDL_Texture* MenuText[20];
	bool howtoplay;
	bool setting;
	bool MusicOn;
	bool mainmenu;
	bool playing;
	bool menurestart;
	bool menuLose;
/*-------------------------------*/
	//player
	player p_player;
	SDL_Texture* Heart;
/*-------------------------------*/
	//Arrow
	//Gun fuction
	void arrowActive();
	//Gun obj
	Arrow p_arrow;
	SDL_Texture* arrowtext;
	double angle;
	int mouseposx;
	int mouseposy;
	bool mousedown;
	
	//bullet
	vector<bullet> _bullet;
	SDL_Texture* bulletTex;
/*-------------------------------*/
	//clipgolbin for setclip
	//golbin fuction
	void creategolbin();
	void golbinActive();
	//goblin obj
	Golbin clipgolbin;
	vector <Golbin> golbin_list;
	int framex_golbin;
	int	framey_golbin;
	int maxgolbin = 20;
	SDL_Texture* GolbinTexture;
	SDL_Texture* GolbinDead;
	SDL_Texture* blood[10];
/*-------------------------------*/
	//Mushroom
	SDL_Texture* Mushroomtexture;
	vector <mushroom> mushroom_list;
	void createmushroom();
	int maxmushroom = 3;
/*-------------------------------*/
	//font
	TTF_Font* Font1;
	SDL_Color textColor;
	SDL_Surface* textSurface;
	SDL_Texture* mTexture;
	string scoreText;
	SDL_Rect scoreBOX;
	SDL_Rect scoreFinal;
	TTF_Font* gFont;
	SDL_Texture* mushroomscore;
/*-------------------------------*/
	//sound
	Mix_Music* gMusic;
	Mix_Chunk* menusoundclick;
	Mix_Chunk* golbindeathsound;
	Mix_Chunk* golbinattacksound;
	Mix_Chunk* pickmushroomsound;
	Mix_Chunk* p_playermovesound;
	Mix_Chunk* shuttingsound;
	void loadSound();
};
#endif // 

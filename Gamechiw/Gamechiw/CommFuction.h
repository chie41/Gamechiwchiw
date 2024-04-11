#ifndef COMMFUCTION_H_
#define COMMFUCTION_H_

#include <SDL.h>
#include <stdio.h>
#include <string>
#include <SDL_image.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <SDL_ttf.h>
#include<fstream>
#include<string.h>
using namespace std;
//screen
const int SCREEN_WIDTH = 320*2;
const int SCREEN_HEIGHT = 320*2;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;
const int RENDER_DRAW_COLOR = 0xFF;

static SDL_Texture* bkgroundTexture = NULL;
static SDL_Window* gWindow = NULL;
static SDL_Renderer* gscreen = NULL;
static SDL_Event g_event;
//static SDL_Renderer* gscreen2=NULL;


namespace SDLCommFuction {

	SDL_Texture* LoadTexture(const std::string filepath, SDL_Renderer* render);
	void ApplyTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y);
	void CleanUp();

}

#define TILE_SIZE 48

#define MAX_MAP_X 400
#define MAX_MAP_Y 10

#define PLAYER_FRAME_HEIGHT 1152/6
#define PLAYER_FRAME_WIDTH 1152/6

#define ARROW_FRAME_HEIGHT 32
#define ARROW_FRAME_WIDTH 50

#define GOLBIN_FRAME_HEIGHT 960/5
#define GOLBIN_FRAME_WIDTH 1344/7

typedef struct Input
{
	int left_;
	int right_;
	int up_;
	int down_;
	int standing_;
	int attack_;
} Input;

struct Map
{
	int start_x_;
	int start_y_;

	int max_x_;
	int max_y_;

	int tile[MAX_MAP_Y][MAX_MAP_X];
	string file_name_;

};
#endif

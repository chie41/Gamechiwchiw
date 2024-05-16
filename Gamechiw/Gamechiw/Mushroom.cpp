#include "Mushroom.h"

mushroom::mushroom()
{
	MushroomDesRect.w = 64;
	MushroomDesRect.h = 64;
	MushroomDesRect.x = rand() % SCREEN_WIDTH - MushroomDesRect.w;
	MushroomDesRect.y = rand() % SCREEN_HEIGHT - MushroomDesRect.h;
	
	picked = false;
	mushroomcountime = 0;
	buff = ((rand() % 5) == 1) ? true : false;
	poisonous = ( (rand()%2) == 1) ? true : false;
	if (buff) poisonous = false;
};

void mushroom::show(SDL_Renderer* des, SDL_Texture* p_object)
{
	if(picked == false)
	SDL_RenderCopy(des, p_object, NULL, &MushroomDesRect);
}
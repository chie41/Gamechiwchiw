#ifndef MUSHROOM_H_
#define MUSHROOM_H_

#include"CommFuction.h"

class mushroom
{
public:
	mushroom();
	SDL_Rect MushroomDesRect;
	void show(SDL_Renderer* des, SDL_Texture* p_object);
	bool picked;
	int mushroomcountime;
	bool poisonous;
};

#endif // !MUSHROOM_H_

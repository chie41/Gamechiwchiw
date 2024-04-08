#pragma once
#include "CommFuction.h"
#include "BaseObject.h"
#define BULLET_SPEED 10
class bullet :public BaseObject
{
public:
	bullet();
	void updatebullet();
	float getWAYf1(int _mx, int _my, int _sx, int _sy);
	float getWAYf2(int _mx, int _my, int _sx, int _sy);
	bool outofscreen();
	bool disapear();
	bool coll;

	float f1;
	float f2;

	SDL_Rect bulletSourceRect;
	SDL_Rect bulletDesRect;

private:


};
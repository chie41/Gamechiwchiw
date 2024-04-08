#ifndef BASEOBJECT_H_
#define BASEOBJECT_H_

#include"CommFuction.h"

class BaseObject
{
public:
	BaseObject();
	~BaseObject();

	virtual bool loadImg(std::string file_path, SDL_Renderer* screen);// ham ao
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void Free();

	void SetRect(const float& x, const float& y)
	{
		rect_.x = x;
		rect_.y = y;
	}
	SDL_Rect GetRect() const { return rect_; }
	SDL_Texture* GetObject() const { return p_object_; }


protected:
	SDL_Rect rect_;
	SDL_Texture* p_object_;

};


#endif

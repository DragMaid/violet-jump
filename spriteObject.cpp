#include "spriteObject.hpp"

void gameObject::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &rectangle);
}

staticObject::staticObject(int x, int y, int w, int h, int gamespeed)
{
	this->gamespeed = gamespeed;

	pos_x = x;
	pos_y = y;
	width = w;
	height= h;
}

void staticObject::update()
{
	pos_x += gamespeed;

	rectangle.x = pos_x;
	rectangle.y = pos_y; 
	rectangle.w = width;
	rectangle.h = height;
}

dynamicObject::dynamicObject(int x, int y, int w, int h)
{
	pos_x = x;
	pos_y = y;
	width = w;
	height= h;
}

void dynamicObject::update()
{
	pos_x--;
	rectangle.x = pos_x;
	rectangle.y = pos_y; 
	rectangle.w = width;
	rectangle.h = height;
}

void dynamicObject::jump(int force)
{


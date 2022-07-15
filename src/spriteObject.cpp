#include "spriteObject.hpp"

gameObject::gameObject(int x, int y, int w, int h)
{
	pos_x = x;
	pos_y = y;
	size_w = w;
	size_h = h;
}

void gameObject::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &rectangle);
}

void gameObject::update()
{
	rectangle.x = pos_x;
	rectangle.y = pos_y;
	rectangle.w = size_w;
	rectangle.h = size_h;
}

void gameObject::reposition(int x, int y)
{
	pos_x = x;
	pos_y = y;
}

void gameObject::move(int direction, int velocity)
{
	switch (direction) {
		// Index (1, 2, 3, 4) is equivilent to (up, down, right, left)
		case 1:
			pos_y -= velocity;
		case 2:
			pos_y += velocity;
		case 3:
			pos_x += velocity;
		case 4:
			pos_x -= velocity;
	}
}

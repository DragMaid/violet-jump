#include "spriteObject.hpp"

gameObject::gameObject(int x, int y, int w, int h)
{
	pos_x = x;
	pos_y = y;
	size_w = w;
	size_h = h;
	this->update();
}

void gameObject::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &destRect);
}

void gameObject::update()
{
	destRect.x = pos_x;
	destRect.y = pos_y;
	destRect.w = size_w;
	destRect.h = size_h;
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

Player::Player(SDL_Renderer* renderer, char* sprite, int x, int y, int w, int h) : gameObject(x, y, w, h)
{
	for (int i=0; i < TOTAL_FRAMES; i++) {
		SDL_Rect tempRect;
		tempRect.x = i * FRAME_WIDTH;
		tempRect.y = 0;
		tempRect.w = FRAME_WIDTH;
		tempRect.h = FRAME_HEIGHT;
		this->WALK_CLIPS[i] = tempRect;
	}

	this->surface = IMG_Load(sprite);
	this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);
	SDL_free(this->surface);
}

void Player::update()
{
	if ( !this->isJumping ) {
		float deltaT = (SDL_GetTicks64() - this->startTime ) / 1000.0f;
		int totalFrames = floor( deltaT * this->ANIMATION_FPS);
		int currentIndex = totalFrames % WALK_FRAMES;
		this->currentClip = WALK_CLIPS[ currentIndex ];
	} else {
		this->currentClip = WALK_CLIPS[3];
	}
	this->gameObject::update();
}

void Player::render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, this->texture, &this->currentClip, &this->destRect);
}


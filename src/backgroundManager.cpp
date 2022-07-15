#include "../include/backgroundManager.hpp"

backgroundManager::backgroundManager(SDL_Renderer* renderer, bool isflip, int screen_w, int screen_h)
{
	this->renderer = renderer;
	this->isflip   = isflip;
	this->screen_w = screen_w;
	this->screen_h = screen_h;
}

void backgroundManager::initBackground()
{
	// Load background texture
	this->surface = IMG_Load("./assets/images/background.jpg");
	this->texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_free(this->surface);

	SDL_QueryTexture(texture, NULL, NULL, &IMG_w, &IMG_h);

	this->IMG_amount = ceil( (float)screen_w / (float)IMG_w );

	for (int i=0; i < IMG_amount; i++) {
		DestRect.x = i * IMG_w;
		DestRect.y = 0;
		DestRect.w = IMG_w;
		DestRect.h = IMG_h;
		DestRectContainer.push_back(DestRect);
		quickRender(DestRectContainer.size());
	}
}

void backgroundManager::scrollBackground()
{
	for (int i=0; i < DestRectContainer.size(); i++) {
		SDL_Rect* rect = &DestRectContainer[i];
		rect->x -= bgscrollspeed;
	}

	SDL_Rect* firstRect = &DestRectContainer.front();
	SDL_Rect* lastRect  = &DestRectContainer.back();

	if ( firstRect->x + firstRect->w <= 0 ) {
		DestRectContainer.erase(DestRectContainer.begin());
	}

	if ( lastRect->x + lastRect->w <= screen_w ) {
		DestRect.x = lastRect->x + lastRect->w;
		DestRect.y = 0;
		DestRect.w = IMG_w;
		DestRect.h = IMG_h;
		DestRectContainer.push_back(DestRect);
		quickRender(DestRectContainer.size());
	}
}

void backgroundManager::updateBackground()
{
	this->scrollBackground();
}

void backgroundManager::quickRender(int index)
{
	// Render all instance to screen once and perform checking
	if ( index % 2 == 0 ) {
		this->flip = SDL_FLIP_NONE;
	} else { this->flip = SDL_FLIP_HORIZONTAL; };
	SDL_RenderCopyEx(renderer, texture, NULL, &DestRectContainer[index], 0, NULL, flip);
}

void backgroundManager::renderBackground()
{
	// REFACTOR the whole shit please
	for (int i=0; i < DestRectContainer.size(); i++) {
			SDL_RenderCopyEx(renderer, texture, NULL, &DestRectContainer[i], 0, NULL, SDL_FLIP_NONE);
	}
}

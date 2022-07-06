#include "backgroundManager.hpp"

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
	this->texture1 = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_free(this->surface);
	this->surface = IMG_Load("./assets/images/background2.jpg");
	this->texture2 = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_free(this->surface);

	SDL_QueryTexture(texture1, NULL, NULL, &IMG_w, &IMG_h);

	this->IMG_amount = ceil( (float)screen_w / (float)IMG_w);

	for (int i=0; i < IMG_amount; i++) {
		DestRect.x = i * IMG_w;
		DestRect.y = 0;
		DestRect.w = IMG_w;
		DestRect.h = IMG_h;
		DestRectContainer.push_back(DestRect);
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
	}
}

void backgroundManager::updateBackground()
{
	this->scrollBackground();
}

void backgroundManager::renderBackground()
{
	// REFACTOR the whole shit please
	for (int i=0; i < DestRectContainer.size(); i++) {
		if ( i % 2 == 0 ) {
			SDL_RenderCopyEx(renderer, texture1, NULL, &DestRectContainer[i], 0, NULL, flip);
		} else {
			SDL_RenderCopyEx(renderer, texture2, NULL, &DestRectContainer[i], 0, NULL, flip);
		}
	}
}

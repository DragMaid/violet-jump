#include "../include/backgroundManager.hpp"

backgroundManager::backgroundManager(SDL_Renderer* renderer, char* sprite, int startPointY, int screen_w, int screen_h)
{
	this->renderer = renderer;
	this->sprite   = sprite;
	this->startPointY = startPointY;
	this->screen_w = screen_w;
	this->screen_h = screen_h;
}

void backgroundManager::addBackground(int x, int y, int w, int h)
{
	bool beFlip = false;
	if (bgFlip) {
		if (DestRectContainer.size() > 0) {
			beFlip = (DestRectContainer.back().beFlip)? false : true;
		}
	}
	indexRectangle bgRect;
	bgRect.beFlip = beFlip;
	bgRect.DestRect.x = x;
	bgRect.DestRect.y = y;
	bgRect.DestRect.w = w;
	bgRect.DestRect.h = h;
	DestRectContainer.push_back(bgRect);
}

void backgroundManager::initBackground()
{
	// Load background texture
	this->surface = IMG_Load(sprite);
	this->texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_free(this->surface);

	SDL_QueryTexture(texture, NULL, NULL, &IMG_w, &IMG_h);
	this->SLIDE_w = screen_w ? IMG_w : IMG_w < screen_w;
	this->SLIDE_h = screen_h - (startPointY * 2);

	this->IMG_amount = ceil( (float)screen_w / (float)IMG_w );

	for (int i=0; i < IMG_amount; i++) {
		addBackground((i* SLIDE_w), startPointY, SLIDE_w, SLIDE_h);
	}
}

void backgroundManager::scrollBackground()
{
	for (int i=0; i < DestRectContainer.size(); i++) {
		SDL_Rect* rect = &(DestRectContainer[i].DestRect);
		rect->x -= bgscrollspeed;
	}

	SDL_Rect* firstRect = &(DestRectContainer.front().DestRect);
	SDL_Rect* lastRect  = &(DestRectContainer.back().DestRect);

	if ( firstRect->x + firstRect->w <= 0 ) {
		DestRectContainer.erase(DestRectContainer.begin());
	}

	if ( lastRect->x + lastRect->w <= screen_w ) {
		addBackground((lastRect->x + lastRect->w), startPointY, SLIDE_w, SLIDE_h);
	}
}

void backgroundManager::updateBackground()
{
	this->scrollBackground();
}

void backgroundManager::renderBackground()
{
	for (int i=0; i < DestRectContainer.size(); i++) {
		SDL_RendererFlip flip = (DestRectContainer[i].beFlip)? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
		SDL_RenderCopyEx(renderer, texture, NULL, &(DestRectContainer[i].DestRect), 0, NULL, flip);
	}
}

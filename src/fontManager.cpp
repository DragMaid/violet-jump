#include "fontManager.hpp"

Label::Label()
{
	if ( TTF_Init() < 0 ) {
		std::cout << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
	} 
}

void Label::configureText(SDL_Renderer* renderer, char* text, char* textFont, int textSize, int textColor[3], int padding[2], int x, int y)
{
	this->textSize = textSize;
	this->text = text;
	memcpy(this->textColor, textColor, sizeof(textColor));
	memcpy(this->textPadding, padding, sizeof(padding));

	this->pos_x = x;
	this->pos_y = y;

	this->Color.r = textColor[0];
	this->Color.g = textColor[1];
	this->Color.b = textColor[2];

	if (this->textFont != NULL) {
		bool isChanged = false;
		if ( this->lastFont != textFont ) {
			isChanged = true;
			this->lastFont = textFont;
		}
		if ( this->lastSize != textSize ) {
			isChanged = true;
			this->lastSize = textSize;
		}
		if ( isChanged ) {
			TTF_CloseFont(this->textFont);
			this->textFont = TTF_OpenFont(textFont, this->textSize);
		}
	} else { 
		this->textFont = TTF_OpenFont(textFont, this->textSize);
		this->lastFont = textFont;
	}

	if (this->textSurface != NULL && this->textTexture != NULL) {
		SDL_free(this->textSurface);
		SDL_DestroyTexture(this->textTexture);
	}

	this->textSurface = TTF_RenderText_Solid(this->textFont, this->text, this->Color);

	if ( textSurface == NULL ) {
		std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
	} else {
		this->textTexture = SDL_CreateTextureFromSurface(renderer, this->textSurface);
	}
}

void Label::updateText()
{
	this->destRect.x = this->pos_x + this->textPadding[0];
	this->destRect.y = this->pos_y + this->textPadding[1];
	if (this->textSurface != NULL) {
		//this->destRect.w = this->textSurface->w + this->textPadding[0];
		//this->destRect.h = this->textSurface->h + this->textPadding[1];
		this->destRect.w = this->textSurface->w;
		this->destRect.h = this->textSurface->h;
	}
}

void Label::renderText(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, this->textTexture, NULL, &this->destRect);
}

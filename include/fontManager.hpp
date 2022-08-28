#include "game.hpp"

class Label {
public:
	Label();
	~Label(){};

	virtual void renderText(SDL_Renderer* renderer);
	virtual void updateText();

	virtual void configureText(SDL_Renderer* renderer, char* text, char* textFont, int textSize, int textColor[3], int padding[2], int x, int y);
protected:
	char* text;
	char* lastFont;
	int lastSize;
	int textSize;
	int textColor[3];
	int textPadding[2];

	SDL_Color Color;
	TTF_Font* textFont = NULL;
	SDL_Surface* textSurface = NULL;
	SDL_Texture* textTexture = NULL;
	
	int pos_x, pos_y, size_w, size_h;
	SDL_Rect destRect;
};

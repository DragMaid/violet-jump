#include "game.hpp"

#define bgscrollspeed 5

class backgroundManager
{
public:
	backgroundManager(SDL_Renderer* renderer, bool isflip, int screen_w, int screen_h);
	~backgroundManager();

	void initBackground();
	void scrollBackground();
	void quickRender(int index);
	void updateBackground();
	void renderBackground();
private:
	bool isflip = false;

	int screen_w;
	int screen_h;

	int IMG_w;
	int IMG_h;

	int IMG_amount;

	SDL_Renderer* renderer;
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	SDL_Rect DestRect;
	std::vector<SDL_Rect> DestRectContainer;

	SDL_Texture* texture;
	SDL_Surface* surface;
};

#include "game.hpp"

#define bgscrollspeeddef 5
#define bgFlip true

struct indexRectangle
{
	bool beFlip;
	SDL_Rect DestRect;
};

class backgroundManager
{
public:
	backgroundManager(SDL_Renderer* renderer, char* sprite, int startPointY, int screen_w, int screen_h);
	~backgroundManager();

	void initBackground();
	void addBackground(int x, int y, int w, int h);
	void scrollBackground();
	void updateBackground();
	void renderBackground();
	void setspeed(int speed) { this->bgscrollspeed = speed; };
private:
	int bgscrollspeed = bgscrollspeeddef;
	char* sprite;
	int startPointY;
	int screen_w;
	int screen_h;

	int IMG_w;
	int IMG_h;
	int SLIDE_w;
	int SLIDE_h;

	int IMG_amount;

	SDL_Renderer* renderer;

	std::vector<indexRectangle> DestRectContainer;

	SDL_Texture* texture;
	SDL_Surface* surface;
};

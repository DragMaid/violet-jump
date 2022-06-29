#include "game.hpp"

class gameObject {
public:
	// Destination rectangle
	SDL_Rect rectangle;
	int pos_x;
	int pos_y;
	int width;
	int height;

	// Update game datas 
	void update();
	// Render function (Draw image to screen)
	void render(SDL_Renderer* renderer);
};

class staticObject : public gameObject
{
public:
	// Class constructor
	staticObject(int x, int y, int w, int h, int gamespeed);
	~staticObject();

	// Override update function
	void update();

private:
	int gamespeed;
};

class dynamicObject : public gameObject
{
public:
	// Class constructor
	dynamicObject(int x, int y, int w, int h);
	~dynamicObject();
	
	// Override update function
	void update();
};

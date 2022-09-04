#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "iostream"
#include <math.h>
#include <map>
#include <vector>
#include <string>
#include <tuple>

class Game {
public:
	Game();
	~Game();
	void init(const char* title, int x, int y, int Swidth, int Sheight, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running(){ return isRunning; };
private:
	int width;
	int height;

	bool isRunning;
	SDL_Window *window;
	SDL_Renderer *renderer;
};

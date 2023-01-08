#include "game.hpp"
#include "entityManager.hpp"
#include "backgroundManager.hpp"

Game::Game(){}
Game::~Game(){}

entityManager* eManager;
backgroundManager* bgManager;
backgroundManager* lakeManager;

SDL_Texture* texture;
void Game::init(const char *title, int x, int y, int Swidth, int Sheight, bool fullscreen)
{
	int flags = 0;
	if (SDL_VideoInit(NULL) != 0) {
		SDL_LogError(0, "Error initializing SDL video:  %s\n", SDL_GetError());
	} 
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
		SDL_DisplayMode DM;
		if (SDL_GetCurrentDisplayMode(0, &DM) != 0) {
			SDL_LogError(0, "SDL_GetCurrentDisplayMode failed: %s", SDL_GetError());
		}
		this->width = DM.w;
		this->height = DM.h;
	} else {
		this->width = Swidth;
		this->height = Sheight;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		SDL_Log("Initializing window ... ");
		// Having trouble using fullscreen mode so disabled it
		window = SDL_CreateWindow(title, x, y, width, height, false);
		
		if (window)
		{
			SDL_Log("Succesfully created window");
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_Log("Succesfully created renderer");
		}
		isRunning = true;
	} else {
		isRunning = false;
	}

	//bgManager = new backgroundManager(renderer, (char*)"./assets/images/background.jpg", 0, width, height);
	//bgManager->initBackground();

	lakeManager = new backgroundManager(renderer, (char*)"./lakeview.jpg", 100, width, height);
	lakeManager->initBackground();

	eManager = new entityManager(renderer, width, height);
	eManager->startLevel();
}

void Game::handleEvents()
{
	SDL_Event Event;
	SDL_PollEvent(&Event);
	switch (Event.type)
	{
		case SDL_QUIT:
			isRunning = false;
			break;
		//case SDL_KEYDOWN:
			//SDL_Keysym* keysym = &Event.key.keysym;
			//if ((keysym->sym) == SDLK_SPACE) {
				//eManager->playerJump();
			//}
			//break;
	}	

	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_SPACE]) {
		eManager->setSpaceState(true);
	} else {
		eManager->setSpaceState(false);
	}
}

void Game::update()
{
	//bgManager->updateBackground();
	lakeManager->updateBackground();
	eManager->updateEntity();
}

void Game::render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	// All entities' rendering goes here
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	//bgManager->renderBackground();
	lakeManager->renderBackground();
	eManager->renderEntity();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

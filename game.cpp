#include "game.hpp"
#include "entityManager.hpp"
#include "backgroundManager.hpp"

Game::Game(){}
Game::~Game(){}

entityManager* eManager;
backgroundManager* bgManager;

SDL_Texture* texture;
void Game::init(const char *title, int x, int y, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Started" << std::endl;
		window = SDL_CreateWindow(title, x, y, width, height, fullscreen);
		
		if (window)
		{
			std::cout << "Created window" << std::endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Created renderer" << std::endl;
		}
		isRunning = true;
	} else {
		isRunning = false;
	}

	bgManager = new backgroundManager(renderer, true, width, height);
	bgManager->initBackground();

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
		eManager->playerJump();
		eManager->setSpaceState(true);
	} else {
		eManager->setSpaceState(false);
	}
}

void Game::update()
{
	bgManager->updateBackground();
	eManager->updateEntity();
}

void Game::render()
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);
	// All entities' rendering goes here
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	bgManager->renderBackground();
	eManager->renderEntity();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

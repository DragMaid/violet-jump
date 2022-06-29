#include "game.hpp"
#include "entityManager.hpp"

Game::Game(){}
Game::~Game(){}

entityManager* eManager;

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

	eManager = new entityManager(renderer);
	eManager->randomspawn();
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
		case SDL_KEYDOWN:
		case SDL_KEYUP:
		//default:
			//break;
	}	
}


void Game::update()
{
	eManager->updateEntity();
}

void Game::render()
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);
	// All entities' rendering goes here
	eManager->renderEntity();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

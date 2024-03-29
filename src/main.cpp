#include "game.hpp"
#define FPS 60
#define SWIDTH 900
#define SHEIGHT 600

Game *game = nullptr;
int main(int argv, char** args) {
	game = new Game();
	game->init("Hello", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SWIDTH, SHEIGHT, false);
	Uint64 start_tick;
	while ( game->running() ) {
		start_tick = SDL_GetTicks64();
		game->handleEvents();
		game->update();
		game->render();
		if ( ( 1000 / FPS ) > SDL_GetTicks64() - start_tick ) {
			SDL_Delay( 1000 / FPS - ( SDL_GetTicks64() - start_tick ) );
		}
	}
	game->clean();
	return 0;
}

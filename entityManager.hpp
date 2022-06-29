#include "game.hpp"
#include "spriteObject.hpp"
#include <vector>

#define gamespeed 5
#define maxdistance 200

class entityManager
{
public:
	entityManager(SDL_Renderer* renderer) {this->renderer=renderer;};
	~entityManager();
	void spawnEntity(int eType, int x, int y, int w, int h);
	void removeEntity();
	void randomspawn();
	void updateEntity();
	void renderEntity();
private:
	SDL_Renderer* renderer;
	std::vector<staticObject*> leafContainer;
	std::vector<dynamicObject*> playerContainer;
};

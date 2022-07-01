#include "game.hpp"
#include "spriteObject.hpp"

#define gamespeed 0
#define maxdistance 200
#define leafposy 500
#define playerposx 50
#define gravityForce 10

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
	void collisionDetect();
	void physicCalculate();
	void playerJump();
private:
	SDL_Renderer* renderer;
	gameObject* player;
	std::vector<gameObject*> leafContainer;
	int Force = gravityForce;
	int maxJump = 100;
	int jumpDistance = 0;
};

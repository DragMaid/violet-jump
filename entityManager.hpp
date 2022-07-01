#include "game.hpp"
#include "spriteObject.hpp"

#define gamespeed 0
#define maxdistance 500
#define leafposy 500
#define playerposx 50
#define gravityForce 10
#define glidespeed 3
#define maxJumpHeight 200

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
	void setSpaceState(bool state) { this->isSpaceBar = state; };
private:
	SDL_Renderer* renderer;
	Player* player;
	std::vector<gameObject*> leafContainer;

	int Force = gravityForce;
	int jumpDistance = 0;

	bool isSpaceBar = false;
};

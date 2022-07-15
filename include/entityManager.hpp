#include "game.hpp"
#include "spriteObject.hpp"

#define gamespeed 5
#define maxdistance 1000
#define mindistance 100
#define leafposy 500
#define playerposx 500
#define gravityForce 6
#define glidespeed 3
#define maxJumpHeight 200
#define minJumpHeight 100

class entityManager
{
public:
	entityManager(SDL_Renderer* renderer, int screen_w, int screen_h)
	{
		this->screen_w = screen_w;
		this->screen_h = screen_h;
		this->renderer=renderer;
	};
	~entityManager();
	void spawnEntity(int eType, int x, int y, int w, int h);
	void removeEntity();
	void randomspawn();
	void updateEntity();
	void renderEntity();
	void collisionDetect();
	void physicCalculate();
	void playerJump();
	void leafControl();
	void startLevel();
	void setSpaceState(bool state) { this->isSpaceBar = state; };
private:
	SDL_Renderer* renderer;
	Player* player;
	std::vector<gameObject*> incomingLeafs;
	std::vector<gameObject*> leafContainer;

	int Force = gravityForce;
	int jumpDistance = 0;
	int jumpHeight = 0; 

	int screen_w;
	int screen_h;

	bool isSpaceBar = false;
};

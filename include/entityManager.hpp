#include "game.hpp"
#include "spriteObject.hpp"
#include "fontManager.hpp"

#define gamespeed 5
#define maxdistance 1000
#define mindistance 100
//#define leafposy 500
#define playerposx 500
#define gravityForce 6
#define glidespeed 3
#define maxJumpHeight 300
#define minJumpHeight 100

class entityManager
{
public:
	entityManager(SDL_Renderer* renderer, int screen_w, int screen_h)
	{
		this->screen_w = screen_w;
		this->screen_h = screen_h;
		this->renderer = renderer;
		this->label = new Label();
		this->label->configureText(renderer, (char*)"SCORE: 0", (char*)"./pricedown.otf", 30, new int[3]{0, 0, 0}, new int[2]{0, 0}, 0, 0);
		this->leafposy = screen_h * 3 / 4;
	};
	~entityManager();
	void spawnEntity(int eType, bool customHB, rectangle dRect, rectangle hBox);
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
	Label* label;
	std::vector<gameObject*> incomingLeafs;
	std::vector<gameObject*> leafContainer;

	int playerScore = 0;
	int Force = gravityForce;
	int jumpDistance = 0;
	int jumpHeight = 0; 

	int screen_w;
	int screen_h;

	bool isSpaceBar = false;
	int leafposy;
};

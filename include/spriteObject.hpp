#include "game.hpp"
#define frameW 600
#define frameH 800

/* ========================================GAME_OBJECT=============================================== */
class gameObject {
public:
	// Basic class constructor
	gameObject(int x, int y, int w, int h);
	~gameObject(){};

	// Basic return statements
	std::tuple<int, int> getPos() { return {pos_x, pos_y}; };
	std::tuple<int, int> getSize() { return {size_w, size_h}; };

	// Basic object movement
	void move(int direction, int velocity);
	void reposition(int x, int y);

	// Render function (Draw image to screen)
	virtual void update();
	virtual void render(SDL_Renderer* renderer);

protected:
	// Destination rectangle
	SDL_Rect destRect;
	int pos_x;
	int pos_y;
	int size_w;
	int size_h;
};

class Player : public gameObject {
public:
	Player(SDL_Renderer* renderer, char* sprite, int x, int y, int w, int h);
	~Player(){};

	// Overriden methods from base class
	void update() override;
	void render(SDL_Renderer* renderer) override;
	
	// Basic functions for jump movement
	void setJumpable(bool state) { this->isJumpable = state; };
	void setisJumping(bool state) { this->isJumping = state; };
	bool checkJumpable() { return this->isJumpable; };
	bool checkisJumping() { return this->isJumping; };
private:
	// Basic animation configurations
	Uint64 startTime = SDL_GetTicks64();
	const float ANIMATION_FPS = 10.0f;

	const int FRAME_WIDTH = 600;
	const int FRAME_HEIGHT = 800;

	const static int WALK_FRAMES = 3;
	const static int JUMP_FRAMES = 1;
	const static int TOTAL_FRAMES = WALK_FRAMES + JUMP_FRAMES;
	
	SDL_Rect WALK_CLIPS[ TOTAL_FRAMES ];
	SDL_Rect currentClip;
	
	SDL_Surface* surface;
	SDL_Texture* texture;

	bool isJumpable = false;
	bool isJumping  = false;
};

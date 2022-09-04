#include "game.hpp"
#define frameW 600
#define frameH 800

struct rectangle {
	int x, y, w, h;
	// Constructor for fast initialization
	rectangle(int X, int Y, int W, int H) {
		x = X; y = Y; w = W; h = H;
	}
};

/* ========================================GAME_OBJECT=============================================== */
class gameObject {
public:
	// Basic class constructor
	// customHB stands for custom hitbox which set hBox = dRect
	gameObject(bool customHB, rectangle dRect, rectangle hBox);
	~gameObject(){};

	// Basic return statements
	std::tuple<int, int> getPos() { return {h_pos_x, h_pos_y}; };
	std::tuple<int, int> getSize() { return {h_size_w, h_size_h}; };

	// Basic object movement
	void move(int direction, int velocity);
	void reposition(int x, int y);

	// Render function (Draw image to screen)
	virtual void update();
	virtual void render(SDL_Renderer* renderer);

protected:
	bool customHB = false;

	// Destination rectangle
	SDL_Rect destRect;
	int pos_x, pos_y;
	int size_w, size_h;

	SDL_Rect hitBox;
	int h_pos_x, h_pos_y;
	int h_size_w, h_size_h;
};

class Player : public gameObject {
public:
	Player(SDL_Renderer* renderer, char* sprite, bool customHB, rectangle dRect, rectangle hBox);
	~Player(){};

	// Overriden methods from base class
	void update() override;
	void render(SDL_Renderer* renderer) override;
	
	// Basic functions for jump movement
	void setState(std::string state);
	int getState(){ return this->state; };
	void runAnimation();
private:
	// Basic animation configurations
	Uint64 startTime = SDL_GetTicks64();
	const float ANIMATION_FPS = 10.0f;

	const int FRAME_WIDTH = 600;
	const int FRAME_HEIGHT = 800;

	const int SPRITE_SIZE[2] = {1800, 2400};
	const int sigmaRows = SPRITE_SIZE[1] / FRAME_HEIGHT;
	const int sigmaCols = SPRITE_SIZE[0] / FRAME_WIDTH;
	const static int TOTAL_FRAMES = 7;
	const static int RUN_FRAMES = 3;
	
	int state = 1;
	std::map<std::string, int> stateMap = {
		{"running", 1},
		{"jumping", 2},
		{"falling", 3},
		{"gliding", 4},
		{"landing", 5},
	};

	SDL_Rect ALL_CLIPS[ TOTAL_FRAMES ];
	SDL_Rect currentClip;
	
	SDL_Surface* surface;
	SDL_Texture* texture;
};

#include "game.hpp"

/* ========================================GAME_OBJECT=============================================== */
class gameObject {
public:
	// Basic class constructor
	gameObject(int x, int y, int w, int h);
	~gameObject();

	// Basic return statements
	std::tuple<int, int> getPos() { return {pos_x, pos_y}; };
	std::tuple<int, int> getSize() { return {size_w, size_h}; };

	// Basic object movement
	void move(int direction, int velocity);
	void reposition(int x, int y);

	// Render function (Draw image to screen)
	void update();
	void render(SDL_Renderer* renderer);

private:
	// Destination rectangle
	SDL_Rect rectangle;
	int pos_x;
	int pos_y;
	int size_w;
	int size_h;
};

class Player : gameObject {
public:
	void setJumpable(bool state) { this->isJumpable = state; };
	bool check_isJumpable() { return this->isJumpable; };
private:
	bool isJumpable;
};

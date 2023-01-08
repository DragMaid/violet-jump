#include "spriteObject.hpp"

gameObject::gameObject(bool customHB, rectangle dRect, rectangle hBox)
{
	this->customHB = customHB;

	pos_x = dRect.x;
	pos_y = dRect.y;
	size_w = dRect.w;
	size_h = dRect.h;

	if (!customHB) {
		h_pos_x = pos_x;
		h_pos_y = pos_y;
		h_size_w = size_w;
		h_size_h = size_h;
	} else {
		h_pos_x = hBox.x;
		h_pos_y = hBox.y;
		h_size_w = hBox.w;
		h_size_h = hBox.h;
	}
	this->update();
}

void gameObject::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &hitBox);
}

void gameObject::update()
{
	if (!this->customHB) {
		h_pos_x = pos_x;
		h_pos_y = pos_y;
		h_size_w = size_w;
		h_size_h = size_h;
	}

	destRect.x = pos_x;
	destRect.y = pos_y;
	destRect.w = size_w;
	destRect.h = size_h;

	hitBox.x = h_pos_x;
	hitBox.y = h_pos_y;
	hitBox.w = h_size_w;
	hitBox.h = h_size_h;
}

void gameObject::reposition(int x, int y)
{
	pos_x = x;
	pos_y = y;

	h_pos_x = x;
	h_pos_y = y;
}

void gameObject::move(int direction, int velocity)
{
	switch (direction) {
		// Index (1, 2, 3, 4) is equivilent to (up, down, right, left)
		case 1:
			pos_y -= velocity;
		case 2:
			pos_y += velocity;
		case 3:
			pos_x += velocity;
		case 4:
			pos_x -= velocity;
	}
}

Leaf::Leaf(SDL_Renderer* renderer, SDL_Texture* texture, bool customHB, rectangle dRect, rectangle hBox) : gameObject(customHB, dRect, hBox)
{
	this->texture = texture;
}

void Leaf::update()
{
	if (this->customHB) {
		this->h_pos_x = pos_x + (size_w - h_size_w) / 2;
		this->h_pos_y = pos_y + (size_h / 2) - h_size_h;
	}
	this->gameObject::update();
}

void Leaf::render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, this->texture, NULL,  &this->destRect);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &this->hitBox);
} 

Player::Player(SDL_Renderer* renderer, char* sprite, bool customHB, rectangle dRect, rectangle hBox) : gameObject(customHB, dRect, hBox)
{
	for (int i=0; i < TOTAL_FRAMES; i++) {
		int currentRow = std::round(i / sigmaCols) + 1; 
		SDL_Rect tempRect;
		tempRect.x = (i % sigmaCols) * FRAME_WIDTH;
		tempRect.y = (currentRow - 1) * FRAME_HEIGHT;
		tempRect.w = FRAME_WIDTH;
		tempRect.h = FRAME_HEIGHT;
		this->ALL_CLIPS[i] = tempRect;
	}

	this->surface = IMG_Load(sprite);
	this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);
	SDL_free(this->surface);
}

void Player::setState(std::string state) {
	auto i = this->stateMap.find(state);
	this->state = i->second;
}

void Player::runAnimation() {
	switch (this->getState()) {
		case 1:
		{
			float deltaT = (SDL_GetTicks64() - this->startTime ) / 1000.0f;
			int totalFrames = floor( deltaT * this->ANIMATION_FPS);
			int currentIndex = totalFrames % RUN_FRAMES;
			this->currentClip = ALL_CLIPS[ currentIndex ];
			break;
		}
		case 2:
			this->currentClip = ALL_CLIPS[3];
			break;
		case 3:
			this->currentClip = ALL_CLIPS[4];
			break;
		case 4:
			this->currentClip = ALL_CLIPS[5];
			break;
		case 5:
			this->currentClip = ALL_CLIPS[6];
			break;
		default:
			std::cout << "Undefined action!" << "\n";
	}
}

void Player::update()
{
	if (this->customHB) {
		this->h_pos_x = pos_x + (size_w - h_size_w) / 2;
		this->h_pos_y = pos_y + size_h - h_size_h - 40;
	}

	this->runAnimation();
	this->gameObject::update();
}

void Player::render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, this->texture, &this->currentClip, &this->destRect);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &this->hitBox);
}


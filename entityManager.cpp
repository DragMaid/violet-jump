#include "entityManager.hpp"

void entityManager::spawnEntity(int eType, int x, int y, int w, int h)
{
	switch (eType) {
		case 1:
			gameObject* leaf;
			leaf = new gameObject(x, y, w, h);
			leafContainer.push_back(leaf);
			break;
		case 2:
			player = new gameObject(x, y, w, h);
			break;
	}
}

void entityManager::randomspawn()
{
	int distance = rand() % maxdistance + 1;
	spawnEntity(1, playerposx, leafposy, 50, 50);
	spawnEntity(2, playerposx, 50, 50, 50);
}

void entityManager::physicCalculate()
{
	// Force < 0 -> Player is in jump animation
	if (Force < 0) {
		// Reached max height -> return to falling state
		if (this->jumpDistance >= this->maxJump) {
			this->Force = gravityForce;
		} else {
			this->jumpDistance += abs(Force);
		}
	}
	player->move(2, this->Force);
}

void entityManager::playerJump()
{
	this->Force = -10;
}

void entityManager::collisionDetect()
{
	auto [p_x, p_y] = player->getPos();
	auto [p_w, p_h] = player->getSize();
	float p_cen_x = (p_x + p_w / 2), p_cen_y = (p_y + p_h / 2);

	auto [l_x, l_y] = leafContainer[0]->getPos(); 
	auto [l_w, l_h] = leafContainer[0]->getSize();
	float l_cen_x = (l_x + l_w / 2), l_cen_y = (l_y + l_h / 2);

	float deltaX = (p_cen_x - l_cen_x);
	float deltaY = (p_cen_y - l_cen_y);

	float intersectX = abs(deltaX) - (p_w + l_w) / 2;
	float intersectY = abs(deltaY) - (p_h + l_h) / 2;

	if ( intersectX < 0.0f && intersectY < 0.0f ) {
		player->reposition(playerposx, leafposy - p_h + 1);
		//player->setJumpable(true);
	}
	else {
		physicCalculate();
		//player->setJumpable(false);
	}
}

void entityManager::updateEntity()
{
	// Physics calculations
	collisionDetect();

	// Update all game object variables
	player->update();
	for (gameObject* leaf : leafContainer) {
		leaf->update();
	}
}

void entityManager::renderEntity()
{
	player->render(renderer);
	for (gameObject* leaf : leafContainer) {
		leaf->render(renderer);
	}
}

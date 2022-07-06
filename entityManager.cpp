#include "entityManager.hpp"

void entityManager::spawnEntity(int eType, int x, int y, int w, int h)
{
	switch (eType) {
		case 1:
			gameObject* leaf;
			leaf = new gameObject(x, y, w, h);
			leafContainer.push_back(leaf);
			incomingLeafs.push_back(leaf);
			break;
		case 2:
			player = new Player(x, y, w, h);
			break;
	}
}

void entityManager::startLevel() 
{
	spawnEntity(1, playerposx, leafposy, 50, 50);
	spawnEntity(2, playerposx,  0, 50, 50);
}

void entityManager::randomspawn()
{
	int distance = rand() % maxdistance + mindistance;

	auto [l_x, l_y] = leafContainer.back()->getPos(); 
	auto [l_w, l_h] = leafContainer.back()->getSize();

	if (screen_w - l_x - l_w > distance) {
		spawnEntity(1, screen_w, leafposy, 50, 50);
	}
}

void entityManager::leafControl()
{
	auto [l_x, l_y] = leafContainer[0]->getPos(); 
	auto [l_w, l_h] = leafContainer[0]->getSize();

	if (incomingLeafs.size() > 0) {
		auto [il_x, il_y] = incomingLeafs[0]->getPos(); 
		auto [il_w, il_h] = incomingLeafs[0]->getSize();

		if (il_x + il_w < playerposx) {
			incomingLeafs.erase(incomingLeafs.begin());
		}
	}

	if (l_x + l_w < 0) {
		leafContainer.erase(leafContainer.begin());
	}

	for (gameObject* leaf : leafContainer) {
		leaf->move(4, gamespeed);
	}

	randomspawn();
}

void entityManager::physicCalculate()
{
	// Reached max height -> return to falling state
	if (this->jumpDistance >= this->jumpHeight) {
		this->jumpDistance = 0;
		this->jumpHeight = 0;
		player->setisJumping(false);
	}

	// Force < 0 -> Player is in jump animation
	if (player->checkisJumping()) {
		this->Force = -10;
		this->jumpDistance += abs(Force);
	} else {
		if (this->isSpaceBar) {
			this->Force = glidespeed;
		} else {
			this->Force = gravityForce;
		}
	}

	// Make player constantly falls down
	player->move(2, this->Force);
}

void entityManager::playerJump()
{
	if (player->checkJumpable() || player->checkisJumping()) {
		player->setisJumping(true);
		this->jumpHeight += 10;

		if (this->jumpHeight > maxJumpHeight) {
			jumpHeight = maxJumpHeight;
		}

		if (this->jumpHeight < minJumpHeight) {
			jumpHeight = minJumpHeight;
		}
	}
}

void entityManager::collisionDetect()
{
	auto [p_x, p_y] = player->getPos();
	auto [p_w, p_h] = player->getSize();
	float p_cen_x = (p_x + p_w / 2), p_cen_y = (p_y + p_h / 2);

	auto [l_x, l_y] = incomingLeafs[0]->getPos(); 
	auto [l_w, l_h] = incomingLeafs[0]->getSize();
	float l_cen_x = (l_x + l_w / 2), l_cen_y = (l_y + l_h / 2);

	float deltaX = (p_cen_x - l_cen_x);
	float deltaY = (p_cen_y - l_cen_y);

	float intersectX = abs(deltaX) - (p_w + l_w) / 2;
	float intersectY = abs(deltaY) - (p_h + l_h) / 2;

	if ( intersectX < 0.0f && intersectY < 0.0f && p_y + p_h / 2 < l_y) {
		player->reposition(playerposx, leafposy - p_h);
		this->jumpDistance = 0;
		player->setJumpable(true);
	} else {
		player->setJumpable(false);
	}
}

void entityManager::updateEntity()
{
	// Physics calculations
	physicCalculate();
	collisionDetect();
	leafControl();

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

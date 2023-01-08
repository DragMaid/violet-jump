#include "entityManager.hpp"

void entityManager::spawnEntity(int eType, bool customHB, rectangle dRect, rectangle hBox)
{
	switch (eType) {
		case 1:
			gameObject* leaf;
			leaf = new Leaf(renderer, this->texture, customHB, dRect, hBox);
			leafContainer.push_back(leaf);
			incomingLeafs.push_back(leaf);
			break;
		case 2:
			player = new Player(renderer, (char*)"./violet-sprite.png", customHB, dRect, hBox);
			break;
	}
}

void entityManager::startLevel() 
{
	spawnEntity(1, true, rectangle(playerposx, leafposy, leafsizew, leafsizeh), rectangle(playerposx, leafposy, leafhitw, leafhith));
	spawnEntity(2, true, rectangle(playerposx, playerposy, playersizew, playersizeh), rectangle(playerposx, 0, playerhitw, playerhith));
}

void entityManager::randomspawn()
{
	int distance = rand() % maxdistance + mindistance;

	auto [l_x, l_y] = leafContainer.back()->getPos(); 
	auto [l_w, l_h] = leafContainer.back()->getSize();

	if (screen_w - l_x - l_w > distance) {
		spawnEntity(1, true, rectangle(screen_w, leafposy, leafsizew, leafsizeh), rectangle(playerposx, leafposy, leafhitw, leafhith));
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

			// Score counter
			this->playerScore++;
			std::string score = "SCORE: " + std::to_string(this->playerScore);
			const char* textScore = score.c_str();
			this->label->configureText(renderer, (char*)textScore, (char*)"./pricedown.otf", 30, new int[3]{0, 0, 0}, new int[2]{5, 0}, 0, 0);
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
	if (this->jumpHeight >= 0 && this->jumpDistance >= this->jumpHeight) {
		this->jumpDistance = 0;
		this->jumpHeight = 0;
		player->setState("falling");
	}

	// Set state of player based on condition
	if (player->getState() == 2) {
		this->Force = -10;
		this->jumpDistance += abs(Force);
	} else if (player->getState() != 1 && player->getState() != 5) {
		if (this->isSpaceBar) {
			this->Force = glidespeed;
			player->setState("gliding");
		} else {
			this->Force = gravityForce;
			player->setState("falling");
		}
	}

	// Make player constantly falls down
	player->move(2, this->Force);
}

void entityManager::playerJump()
{
	// if player is currently in running or landing state -> allow to jump
	static bool pJump = false;
	if (player->getState() == 1 || player->getState() == 5) {
		if (pJump) {
			player->setState("jumping");
			pJump = false;
			this->gamespeed = gamespeeddef;
		}
		if (isSpaceBar) {
			this->jumpHeight += 20;
			if (this->jumpHeight > maxJumpHeight) {
				jumpHeight = maxJumpHeight;
				pJump = true;
			}
		}
		if (!isSpaceBar && jumpHeight > 0) {
			if (this->jumpHeight < minJumpHeight) { jumpHeight = minJumpHeight; };
			pJump = true;
		}
	}
}

void entityManager::collisionDetect()
{
	for (int i=0; i < incomingLeafs.size(); i++) {
		auto [p_x, p_y] = player->getPos();
		auto [p_w, p_h] = player->getSize();
		float p_cen_x = (p_x + p_w / 2), p_cen_y = (p_y + p_h / 2);

		auto [l_x, l_y] = incomingLeafs[i]->getPos(); 
		auto [l_w, l_h] = incomingLeafs[i]->getSize();
		float l_cen_x = (l_x + l_w / 2), l_cen_y = (l_y + l_h / 2);

		float deltaX = (p_cen_x - l_cen_x);
		float deltaY = (p_cen_y - l_cen_y);

		float intersectX = abs(deltaX) - (p_w + l_w) / 2;
		float intersectY = abs(deltaY) - (p_h + l_h) / 2;

		if ( p_y > screen_h ) { player->reposition(playerposx, 0); };
		if ( intersectX < 0.0f && intersectY < 0.0f && player->getState() != 2 ) { 
			player->reposition(playerposx, l_y - playersizeh - playerhith + 50 + 1);
			this->jumpDistance = 0;
			player->setState("landing");
			this->gamespeed = 1;
			break;
		}
		if (p_y > l_y + l_h) {
			if ( player->getState() != 3 && player->getState() != 4) { player->setState("falling"); };
			this->jumpHeight = 0;
		};
	}
}

void entityManager::updateEntity()
{
	// Physics calculations
	playerJump();
	physicCalculate();
	collisionDetect();
	leafControl();

	// Update all game object variables
	player->update();
	for (gameObject* leaf : leafContainer) {
		leaf->update();
	}
	this->label->updateText();
}

void entityManager::renderEntity()
{
	player->render(renderer);
	for (gameObject* leaf : leafContainer) {
		leaf->render(renderer);
	}
	this->label->renderText(renderer);
}

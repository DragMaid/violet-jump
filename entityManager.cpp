#include "entityManager.hpp"

void entityManager::spawnEntity(int eType, int x, int y, int w, int h)
{
	switch (eType) {
		case 1:
			staticObject* leaf;
			leaf = new staticObject(x, y, w, h, gamespeed);
			leafContainer.push_back(leaf);
			break;
		case 2:
			dynamicObject* player;
			player = new dynamicObject(x, y, w, h);
			playerContainer.push_back(player);
			break;
	}
}

void entityManager::randomspawn()
{
	int distance = rand() % maxdistance + 1;
	spawnEntity(1, distance, 50, 50, 50);
}

void entityManager::updateEntity()
{
	for ( auto & object : leafContainer ) {
		object->update();
	}
}

void entityManager::renderEntity()
{
	for ( auto & object : leafContainer ) {
		object->render(renderer);
	}
}

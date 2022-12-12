#include "GameModel.h"

GameModel::GameModel()
{
}

GameObject GameModel::getObject(int id)
{
	for (auto&i : objects) {
		if (i.getID() == id) {
			return i;
		}
	}
	return GameObject();
}

void GameModel::addObject(GameObject obj)
{
	objects.push_back(obj);
}

GameModel::~GameModel()
{
}

#pragma once
#include "GameObject.h"
#include <vector>
//Everything storage related
class GameModel
{
	std::vector<GameObject> objects;

public:
	~GameModel();
	GameObject getObject(int id);
	void addObject(GameObject obj);
};

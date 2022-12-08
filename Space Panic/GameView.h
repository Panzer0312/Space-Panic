#pragma once
#include "GameController.h"
//Everything UI related
class GameView
{
public:
	~GameView();
	int initialize(GameController &g);
	void Render();
};


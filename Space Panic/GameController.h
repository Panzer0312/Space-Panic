#pragma once
#include "GameModel.h"
#include "GameView.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//Everything logic related
class GameController
{
public:
	~GameController();
	GameController(GameModel* model, GameView* view);
	void keyboardInput(GLFWwindow* window);

private:
	void moveObject(Vector2f pos, int id);
	GameModel* m;
	GameView* v;
};



#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "SpriteBatch.h"
#include "Math.h"
//Everything UI related
class GameView
{
public:
	GameView();
	~GameView();
	int initializeView();
	void RenderScene(std::vector<SpriteBatch::SpriteInfo> Sprites);

	GLFWwindow* window;
};


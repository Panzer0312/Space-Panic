#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "SpriteBatch.h"
#include "Math.h"

//A game class for everything logic related
class GameView
{
public:
	/** Constructor for a new GameView */
	GameView();
	/** Creates everything within a new window */
	int initializeView();
	/** Renders a given Vector of Sprites */
	void RenderScene(std::vector<SpriteBatch::SpriteInfo> Sprites);

	GLFWwindow* window;
};


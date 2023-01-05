#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "SpriteBatch.h"
#include "Math.h"
#include "ObjectAnimation.h"

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

	void initAnimations();

	int addAnimation(std::string name, float speed, std::vector<Vector2i> animSprites);

	Vector2i nextAnimation(int*currAnim,int* counter, std::string name);

	GLFWwindow* window;
	std::vector<ObjectAnimation> Animations;
	int animationsCount;
};


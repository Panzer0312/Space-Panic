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
	void RenderScene(std::vector<DrawingObjectProps> Objects);
	/** Returns the next ObjectAnimation Vector2i for a Texture on the spritesheet based on a specific counter and name */
//	Vector2i nextAnimation(int*currAnim,int* counter, std::string name);

	/** The game window */
	GLFWwindow* window;
	/** A vector with all possible ObjectAnimations instantiated from a given text file */
	std::vector<ObjectAnimation> Animations;
	/** The size of the Animations vector */
	int animationsCount;

private:
	/** Instantiates all animations from a given text file */
	void initAnimations();
	ObjectAnimation getAnimation(std::string name);
	/** Helper function for initAnimations to add an Animation to the Animations vector*/
	int addAnimation(std::string name, float speed, std::vector<Vector2i> animSprites);

	SpriteBatch::SpriteInfo changeObjectToSprite(DrawingObjectProps in);
	Vector2i getTextureFromInfo(GameObjectState state, ObjectProps props, ControlledObjectDecision dec, int counter);
	ObjectAnimation getPlayerAnimationFromDecision(GameObjectState state, ObjectProps props, ControlledObjectDecision dec);
	ObjectAnimation getBrickAnimation(ObjectProps props);
	ObjectAnimation getEnemyAnimationFromDecision(GameObjectState state, ObjectProps props, ControlledObjectDecision dec);
};


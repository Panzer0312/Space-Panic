#include "ObjectAnimation.h"

/**
 * .
 * Dummy Constructor
 */
ObjectAnimation::ObjectAnimation() {
	name = "";
	speed = 0;
	ID = -1;
	animations = { Vector2i(0,0) };
	currAnimCounter = 0;
	currTimeCounter = 0;
}

/**
 * .
 * 
 * \param animName Name of the ObjectAnimation to find it in vector Animations in GameModel
 * \param animSpeed How fast the ObjectAnimation should be played (faster -> lower number, slower -> higher number)
 * \param animID ID of the Animation
 * \param animationsVector Vector with every Index of Sprites the Animation should change into
 */
ObjectAnimation::ObjectAnimation(std::string animName, float animSpeed, int animID, std::vector<Vector2i> animationsVector)
{
	name = animName;
	speed = animSpeed;
	ID = animID;
	animations = animationsVector;
	currAnimCounter = 0;
	currTimeCounter = 0;
}

/**
 * .
 * 
 * \return Name of Animation
 */
std::string ObjectAnimation::getName()
{
	return name;
}

/**
 * .
 * 
 * \return ID of Animation
 */
int ObjectAnimation::getID()
{
	return ID;
}

/**
 * .
 * 
 * \return Animation Speed of Animation (faster -> lower number, slower -> higher number)
 */
float ObjectAnimation::getSpeed()
{
	return speed;
}

/**
 * .
 * 
 * \param newSpeed Animation Speed of Animation (faster -> lower number, slower -> higher number)
 */
void ObjectAnimation::setSpeed(float newSpeed)
{
	speed = newSpeed;
}

/**
 * .
 * sets CurrAnimCounter and CurrTimeCounter to 0 to restart Animation
 */
void ObjectAnimation::resetAnimationCounter() {
	currAnimCounter = 0;
	currTimeCounter = 0;
}

/**
 * .
 * Function to increment currTimeCounter which Increments currAnimCounter once it reaches the specified speed figure
 */
void ObjectAnimation::addCount() {
	currTimeCounter++;
	if (currTimeCounter >= speed) {
		currAnimCounter++;
		currTimeCounter = 0;
	}

	if (currAnimCounter > animations.size() - 1) {
		currAnimCounter = 0;
	}

}

/**
 * .
 * 
 * \return Index of next Sprite to change into
 */
Vector2i ObjectAnimation::getNextAnimation()
{
	return animations[currAnimCounter];
}

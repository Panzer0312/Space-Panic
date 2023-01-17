#include "ObjectAnimation.h"

/**
 * .
 * Dummy Constructor
 */
ObjectAnimation::ObjectAnimation() {
	name = "";
	speed = 0;
	animations = { Vector2i(0,0) };
}

/**
 * .
 * 
 * \param animName Name of the ObjectAnimation to find it in vector Animations in GameModel
 * \param animSpeed How fast the ObjectAnimation should be played (faster -> lower number, slower -> higher number)
 * \param animID ID of the Animation
 * \param animationsVector Vector with every Index of Sprites the Animation should change into
 */
ObjectAnimation::ObjectAnimation(std::string animName, int animSpeed,std::vector<Vector2i> animationsVector)
{
	name = animName;
	speed = animSpeed;
	animations = animationsVector;
}

std::string ObjectAnimation::getName()
{
	return name;
}


/**
 * .
 * 
 * \return Index of next Sprite to change into
 */
Vector2i ObjectAnimation::getNextAnimation(int* currAnim,int* objCount)
{
	*objCount += 1;
	if (*objCount >= speed) {
		*currAnim += 1;
		if (*currAnim >= animations.size()) {
			*currAnim = 0;
		}
		*objCount = 0;
	}
	return animations[*currAnim];
}

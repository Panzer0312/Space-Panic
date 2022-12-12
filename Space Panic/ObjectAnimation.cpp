#include "ObjectAnimation.h"


ObjectAnimation::ObjectAnimation() {

}

ObjectAnimation::ObjectAnimation(std::string animName, float animSpeed, int animID, std::vector<Vector2i> animationsVector)
{
	name = animName;
	speed = animSpeed;
	ID = animID;
	animations = animationsVector;
	currAnimCounter = 0;
	currTimeCounter = 0;
}

std::string ObjectAnimation::getName()
{
	return name;
}

int ObjectAnimation::getID()
{
	return ID;
}

float ObjectAnimation::getSpeed()
{
	return speed;
}

void ObjectAnimation::setSpeed(float newSpeed)
{
	speed = newSpeed;
}

void ObjectAnimation::resetAnimationCounter() {
	currAnimCounter = 0;
}

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

Vector2i ObjectAnimation::getNextAnimation()
{
	return animations[currAnimCounter];
}

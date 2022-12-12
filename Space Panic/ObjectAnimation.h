#pragma once
#include <vector>
#include "Math.h"
#include <string>
class ObjectAnimation
{

public:
	ObjectAnimation();
	ObjectAnimation(std::string animName, float animSpeed, int animID, std::vector<Vector2i> animationsVector);

	std::string getName();
	int getID();
	float getSpeed();
	void setSpeed(float newSpeed);
	void resetAnimationCounter();
	void addCount();
	Vector2i getNextAnimation();
private:
	std::string name;
	float speed;
	int ID;
	std::vector<Vector2i> animations;
	int currAnimCounter;
	int currTimeCounter;
};


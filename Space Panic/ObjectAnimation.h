#pragma once
#include <vector>
#include "Math.h"
#include <string>
class ObjectAnimation
{

public:
	/** Empty Constructor of a dummy ObjectAnimation */
	ObjectAnimation();
	/** Constructor for a new Object Animation to animate GameObjects */
	ObjectAnimation(std::string animName, int animSpeed,std::vector<Vector2i> animationsVector);
	/** Getter for Name to find in Animations vector in GameModel */
	std::string getName();

	/** returns the Animation at currAnimCounter in Vector Animations*/
	Vector2i getNextAnimation(int* currAnim,int* counter);
private:
	std::string name;
	int speed;
	std::vector<Vector2i> animations;
};


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
	/** Returns the Animation at currAnimCounter in Vector Animations*/
	Vector2i getNextAnimation(int* currAnim,int* counter);
private:
	/** The name of the animation */
	std::string name;
	/** How fast it should be played (high numbers = slower | small numbers = faster) */
	int speed;
	/** The different textures on the spritesheet that are in the animations */
	std::vector<Vector2i> animations;
};


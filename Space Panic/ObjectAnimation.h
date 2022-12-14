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
	ObjectAnimation(std::string animName, float animSpeed, int animID, std::vector<Vector2i> animationsVector);
	/** Getter for Name to find in Animations vector in GameModel */
	std::string getName();
	/** Getter for the ID of an Animation */
	int getID();
	/** How fast the ObjectAnimation should be played (faster -> lower number, slower -> higher number) */
	float getSpeed();
	/** Setter for speed of Animation change */
	void setSpeed(float newSpeed);
	/** Sets the ObjectAnimation to its first Sprite by setting currAnimCounter to 0 */
	void resetAnimationCounter();
	/** Increases currTimeCounter to achieve Sprite change sometime*/
	void addCount();
	/** returns the Animation at currAnimCounter in Vector Animations*/
	Vector2i getNextAnimation();
private:
	std::string name;
	float speed;
	int ID;
	std::vector<Vector2i> animations;
	int currAnimCounter;
	int currTimeCounter;
};


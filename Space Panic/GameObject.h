#pragma once
#include "math.h"
#include <vector>
#include <string>
class GameObject
{
public:
	/** Empty Constructor of a dummy GameObject */
	GameObject();
	/** Contructor for a new GameObject */
	GameObject(int objSpriteID, std::string objName, Vector2f objPos, float objSpeed, objectType objType);
	/** Sets the Position of a GameObject to reference position where it's sprite is drawn on the screen positon */
	void setPos(Vector2f pos);
	/** returns ID of the GameObject's sprite */
	int getID();
	/** returns postion of a GameObject*/
	Vector2f getPos();
	/** returns type of a GameObject to differentiate those in the Model's vector Objects */
	objectType getType();
	/** returns speed how fast the GameObject should be moved */
	float getSpeed();
	/** returns name of the specific GameObject */
	std::string getName();
	/** returns the position where the Object is facing to */
	Vector2i getFacing();
	/** sets the position where the Object is facing to */
	void setFacing(Vector2i dir);

private:
	objectType type;
	Vector2f pos;
	float speed;
	int spriteID;
	std::string name;
	bool animate;
	Vector2i facing;

};


#pragma once
#include "math.h"
#include <string>
class GameObject
{
public:
	GameObject();
	GameObject(int objSpriteID, std::string objName, Vector2f objPos, float objSpeed, objectType objType);
	void setPos(Vector2f pos);
//	void changeSprite(int width, Vector2i pos);
	int getID();
	Vector2f getPos();
	objectType getType();
	float getSpeed();
	std::string getName();
private:
	objectType type;
	Vector2f pos;
	float speed;
	int spriteID;
	std::string name;

};


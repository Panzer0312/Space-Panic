#pragma once
#include "math.h"
#include <vector>
#include <string>
class GameObject
{
public:
	GameObject();
	GameObject(int objSpriteID, std::string objName, Vector2f objPos, float objSpeed, objectType objType);
//	GameObject(int objSpriteID, std::string objName, Vector2f objPos, float objSpeed, objectType objType, std::vector<Vector2i> animationsArray, float animSpeed);
	void setPos(Vector2f pos);
//	void changeSprite(int width, Vector2i pos);
	int getID();
	Vector2f getPos();
	objectType getType();
	float getSpeed();
	std::string getName();
	Vector2i getFacing();
	void setFacing(Vector2i dir);

//	bool isAnimated();
//	void setAnimated(bool a);


private:
	objectType type;
	Vector2f pos;
	float speed;
	int spriteID;
	std::string name;
	bool animate;
	Vector2i facing;
};


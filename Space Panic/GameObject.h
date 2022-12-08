#pragma once
#include "math.h"
class GameObject
{
public:
	GameObject();
	GameObject(int ID, Vector2f pos,float speed, objectType type);
	int getID();
	Vector2f getPos();
	void setPos(Vector2f v);
	objectType getType();
	float getSpeed();
private:
	objectType type;
	Vector2f position;
	float speed;
	int ID;
};


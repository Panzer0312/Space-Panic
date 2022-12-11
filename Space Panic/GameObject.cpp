#include "GameObject.h"
//USE FOR ENEMY ETC STORAGE


GameObject::GameObject()
{
}

GameObject::GameObject(int objSpriteID, std::string objName, Vector2f objPos, float objSpeed, objectType objType){
	spriteID = objSpriteID;
	name = objName;
	pos = objPos;
	speed = objSpeed;
	type = objType;
}

void GameObject::setPos(Vector2f position) {
	pos = position;
}

int GameObject::getID()
{
	return spriteID;
}

Vector2f GameObject::getPos()
{
	return pos;
}

objectType GameObject::getType()
{
	return type;
}

float GameObject::getSpeed()
{
	return speed;
}

std::string GameObject::getName()
{
	return name;
}

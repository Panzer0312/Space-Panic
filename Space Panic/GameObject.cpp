#include "GameObject.h"

GameObject::GameObject()
{
	ID = -1;
	speed = 0;
	type =  BRICK;
}

GameObject::GameObject(int newID, Vector2f pos, float s, objectType ot)
{
	ID = newID;
	position = pos;
	speed = s;
	type = ot;
}


int GameObject::getID()
{
	return ID;
}

Vector2f GameObject::getPos()
{
	return position;
}

void GameObject::setPos(Vector2f v)
{
	position = v;
}

objectType GameObject::getType()
{
	return type;
}

float GameObject::getSpeed()
{
	return speed;
}

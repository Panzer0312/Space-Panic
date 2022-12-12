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
	facing = Vector2i(0, 0);
	//animate = false;
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

Vector2i GameObject::getFacing()
{
	return facing;
}

void GameObject::setFacing(Vector2i dir)
{
	facing = dir;
}

/*
bool GameObject::isAnimated()
{
	return animate;
}

void GameObject::setAnimated(bool a)
{
	animate = a;
}

std::vector<Vector2i> GameObject::getAnimations() {
	return animations;
}


float GameObject::getAnimationSpeed() {
	return animationSpeed;
}

void GameObject::setAnimationSpeed(float newSpeed) {
	animationSpeed = newSpeed;
}
*/

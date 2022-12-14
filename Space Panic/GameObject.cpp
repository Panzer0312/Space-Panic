#include "GameObject.h"

/**
 * .
 * Dummy constructor
 */
GameObject::GameObject()
{
	type = BRICK;
	pos = Vector2f(0,0);
	speed = -1;
	spriteID = -1;
	name = "";
	animate = false;
	facing = Vector2i(0,0);
}

/**
 * .
 * 
 * \param objSpriteID ID of the associated Sprite to the GameObject 
 * \param objName Name of the GameObject to find it easier in Objects vector in GameModel
 * \param objPos Position where the Sprite of the GameObject is drawn
 * \param objSpeed Speed with which Object will be moved
 * \param objType Type of a GameObject to differentiate those in the Model's vector Objects
 */
GameObject::GameObject(int objSpriteID, std::string objName, Vector2f objPos, float objSpeed, objectType objType){
	spriteID = objSpriteID;
	name = objName;
	pos = objPos;
	speed = objSpeed;
	type = objType;
}
/** setter method */
void GameObject::setPos(Vector2f position) {
	pos = position;
}
/** getter method */
int GameObject::getID()
{
	return spriteID;
}
/** getter method */
Vector2f GameObject::getPos()
{
	return pos;
}
/** getter method */
objectType GameObject::getType()
{
	return type;
}
/** getter method */
float GameObject::getSpeed()
{
	return speed;
}
/** getter method */
std::string GameObject::getName()
{
	return name;
}
/** getter method */
Vector2i GameObject::getFacing()
{
	return facing;
}
/** setter method */
void GameObject::setFacing(Vector2i dir)
{
	facing = dir;
}

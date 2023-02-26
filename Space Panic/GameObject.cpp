#include "GameObject.h"

GameObject::~GameObject() {}


/**
 * .
 * Dummy constructor
 */
/*
GameObject::GameObject()
{
	type = BRICK;
	pos = Vector2f(0,0);
	speed = -1;
	spriteID = -1;
	name = "";
	animate = false,falling = false;
	facing = Vector2i(0,0);
	counter = 0,currAnim = 0, pushUps = 0;
	dec = RIGHT;
	killed = false;
}
*/

/**
 * .
 *
 * \param objSpriteID ID of the associated Sprite to the GameObject
 * \param objName Name of the GameObject to find it easier in Objects vector in GameModel
 * \param objPos Position where the Sprite of the GameObject is drawn
 * \param objSpeed Speed with which Object will be moved
 * \param objType Type of a GameObject to differentiate those in the Model's vector Objects
 */
GameObject::GameObject(int objSpriteID, std::string objName, Vector2f objPos,ObjectType objType) {
	ID = objSpriteID;
	name = objName;
	pos = objPos;
	type = objType;
}

/** Setter method */
void GameObject::setPos(Vector2f position) {
	pos = position;
}
/** Getter method */
int GameObject::getID()
{
	return ID;
}
Vector2f GameObject::getSize()
{
	return size;
}
std::string GameObject::IDAsString()
{
	std::string out ="";
	return out;
}
void GameObject::setSize(Vector2f s)
{
	size = s;
}
/** Getter method */
Vector2f GameObject::getPos()
{
	return pos;
}
/** Getter method */
ObjectType GameObject::getType()
{
	return type;
}

/** Getter method */
std::string GameObject::getName()
{
	return name;
}

bool GameObject::getDrawing()
{
	return drawing;
}

void GameObject::setDrawing(bool b)
{
	drawing = b;
}

bool GameObject::hasCollision(Vector2f enemyBounds, Vector2f enemyPos)
{
	Vector2f selfTopLeft = Vector2f(pos.x,pos.y+size.y);
	Vector2f selfBottomRight = Vector2f(pos.x+size.x,pos.y);
	Vector2f enemyTopLeft = Vector2f(enemyPos.x+ enemyBounds.x, enemyPos.y);
	Vector2f enemyBottomRight = Vector2f(enemyPos.x, enemyPos.y + enemyBounds.y);
	if (selfTopLeft.x<enemyBottomRight.x && selfBottomRight.x > enemyTopLeft.x && selfTopLeft.y < enemyBottomRight.y && selfBottomRight.y > enemyTopLeft.y) {
		return true;
	}
	return false;
}



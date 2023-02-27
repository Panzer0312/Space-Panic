#include "GameObject.h"

GameObject::~GameObject() {}

/**
 * .
 *
 * \param objSpriteID ID of the associated Sprite to the GameObject
 * \param objName Name of the GameObject to find it easier in Objects vector in GameModel
 * \param objPos Position where the Sprite of the GameObject is drawn
 * \param objSpeed Speed with which Object will be moved
 * \param objType Type of a GameObject to differentiate those in the Model's vector Objects
 */
GameObject::GameObject(int objSpriteID, std::string objName, Vector2f objPos,ObjectType objType, int objWidth) {
	ID = objSpriteID;
	name = objName;
	pos = objPos;
	type = objType;
	width = objWidth;
	state = ALIVE;
}

void GameObject::setState(GameObjectState s) {
	state = s;
}

GameObjectState GameObject::getState() {
	return state;
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
int GameObject::getWidth()
{
	return width;
}
ObjectProps GameObject::getObjectProps()
{
	return props;
}
void GameObject::setWidth(int w)
{
	width = w;
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


DrawingObjectProps GameObject::getDrawingObjectProps()
{
	return DrawingObjectProps();
}

bool GameObject::hasCollision(int enemyWidth, Vector2f enemyPos)
{
	Vector2f selfTopLeft = Vector2f(pos.x,pos.y+ width);
	Vector2f selfBottomRight = Vector2f(pos.x+ width,pos.y);
	Vector2f enemyTopLeft = Vector2f(enemyPos.x+ enemyWidth, enemyPos.y);
	Vector2f enemyBottomRight = Vector2f(enemyPos.x, enemyPos.y + enemyWidth);
	if (selfTopLeft.x<enemyBottomRight.x && selfBottomRight.x > enemyTopLeft.x && selfTopLeft.y < enemyBottomRight.y && selfBottomRight.y > enemyTopLeft.y) {
		return true;
	}
	return false;
}


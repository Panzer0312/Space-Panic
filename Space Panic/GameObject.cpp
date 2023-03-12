#include "GameObject.h"

GameObject::~GameObject() {}

/**
 * .
 *
 * \param objID ID of the associated Sprite to the GameObject
 * \param objName Name of the GameObject to find it easier in Objects vector in GameModel
 * \param objPos Position where the Sprite of the GameObject is drawn
 * \param objSpeed Speed with which Object will be moved
 * \param objType Type of a GameObject to differentiate those in the Model's vector Objects
 */
GameObject::GameObject(int objID, Vector2f objPos, ObjectType objType,int objWidth) {
	this->counter = 0;
	this->ID = objID;
	this->pos = objPos;
	this->type = objType;
	this->width = objWidth;
	this->state = ALIVE;

}

void GameObject::setState(GameObjectState s) {
	this->state = s;
}

GameObjectState GameObject::getState() {
	return this->state;
}

/** Setter method */
void GameObject::setPos(Vector2f position) {
	this->pos = position;
}
/** Getter method */
int GameObject::getID()
{
	return this->ID;
}
int GameObject::getWidth()
{
	return this->width;
}
ObjectProps GameObject::getObjectProps()
{
	return this->props;
}
void GameObject::setWidth(int w)
{
	this->width = w;
}
/** Getter method */
Vector2f GameObject::getPos()
{
	return this->pos;
}
/** Getter method */
ObjectType GameObject::getType()
{
	return this->type;
}

void GameObject::addCounter() {
		this->counter++;
}

void GameObject::lowerCounter() {
	if (this->counter > 0){
		this->counter--;
	}
}

int GameObject::getCounter() {
	return this->counter;
}

void GameObject::resetCounter() {
	this->counter = 0;
}
DrawingObjectProps GameObject::getDrawingObjectProps()
{
	return DrawingObjectProps();
}


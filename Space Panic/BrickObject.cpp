#include "BrickObject.h"

BrickObject::BrickObject(int objID, Vector2f objPos,BrickType bType, int objWidth):
	GameObject(objID, objPos, BRICK, objWidth)
{
	this->occupied = false;
	this->occupiedBy = -1;
	this->dugOut = false;
	this->brickType = bType;
	this->props.id = objID;
	this->props.type = BRICK;
	this->props.closerType = bType;
}

void BrickObject::setDugOut(bool b)
{
	this->dugOut = b;
}

void BrickObject::setOccupied(bool b, int enemyID)
{
   	this->occupied = b;
	this->occupiedBy = enemyID;
}

int BrickObject::getOccupiedBy() {
	return this->occupiedBy;
}

bool BrickObject::isDugOut()
{
	return this->dugOut;
}

bool BrickObject::isOccupied()
{
	return this->occupied;
}

DrawingObjectProps BrickObject::getDrawingObjectProps()
{
	return DrawingObjectProps(this->props, this->pos, this->width, this->state, this->counter);
}

BrickType BrickObject::getBrickType()
{
	return this->brickType;
}

#include "BrickObject.h"

BrickObject::BrickObject(int objSpriteID, std::string objName, Vector2f objPos, ObjectType objType, BrickType bType, int objWidth):
	GameObject(objSpriteID, objName, objPos, objType, objWidth)
{
	occupied = false;
	dugOut = false;
	brickType = bType;
	props.id = objSpriteID;
	props.type = 'B';
	props.closerType = bType;
}

void BrickObject::setDugOut(bool b)
{
	dugOut = b;
}

void BrickObject::setOccupied(bool b)
{
	occupied = b;
}

bool BrickObject::isDugOut()
{
	return dugOut;
}

bool BrickObject::isOccupied()
{
	return occupied;
}

DrawingObjectProps BrickObject::getDrawingObjectProps()
{
	return DrawingObjectProps(props,drawing,pos,width,state);
}

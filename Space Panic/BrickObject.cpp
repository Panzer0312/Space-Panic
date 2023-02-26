#include "BrickObject.h"

BrickObject::BrickObject(int objSpriteID, std::string objName, Vector2f objPos, ObjectType objType, BrickType bType):
	GameObject(objSpriteID, objName, objPos, objType)
{
	occupied = false;
	dugOut = false;
	brickType = bType;
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

std::string BrickObject::IDAsString() {
	std::string out = "B";
	if (brickType == BRICK0) {
		out.append("0#");
	}
	else {
		out.append("1#");
	}
	out.append(std::to_string(ID));
	return out;
}

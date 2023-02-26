#include "ControllableObject.h"


ControllableObject::~ControllableObject() {}

ControlledObjectDecision ControllableObject::getDecision()
{
	return dec;
}

void ControllableObject::setDecision(ControlledObjectDecision decision)
{
	dec = decision;
}

void ControllableObject::setFacing(Vector2i f)
{
	facing = f;
}

Vector2i ControllableObject::getFacing()
{
	return facing;
}


ControllableObject::ControllableObject(int objSpriteID, std::string objName, Vector2f objPos, ObjectType objType, float objSpeed):
	GameObject(objSpriteID, objName, objPos, objType)
{
	falling = false;
	killed = false;
	speed = objSpeed;
	dec = NOTHING;
}

/** Getter method */
bool ControllableObject::isFalling()
{
	return falling;
}
/** Setter method */
void ControllableObject::setFalling(bool f)
{
	falling = f;
}

/** Getter method */
bool ControllableObject::iskilled()
{
	return killed;
}
/** Setter method */
void ControllableObject::setKilled(bool k)
{
	killed = k;
}

float ControllableObject::getSpeed()
{
	return speed;
}
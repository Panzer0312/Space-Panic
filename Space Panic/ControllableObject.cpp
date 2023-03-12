 #include "ControllableObject.h"


ControllableObject::~ControllableObject() {}

ControlledObjectDecision ControllableObject::getDecision()
{
	return this->dec;
}

void ControllableObject::setDecision(ControlledObjectDecision decision)
{
	if (this->dec != decision) {
		resetCounter();
	}

	this->dec = decision;
}

void ControllableObject::setFacing(Vector2i f)
{
	this->facing = f;
}

Vector2i ControllableObject::getFacing()
{
	return this->facing;
}


ControllableObject::ControllableObject(int objSpriteID, Vector2f objPos, float objSpeed, int objWidth, ObjectType t):
	GameObject(objSpriteID, objPos, t, objWidth)
{
	this->falling = false;
	this->killed = false;
	this->speed = objSpeed;
	this->dec = NOTHING;
}

/** Getter method */
bool ControllableObject::isFalling()
{
	return this->falling;
}
/** Setter method */
void ControllableObject::setFalling(bool f)
{
	this->falling = f;
}

/** Getter method */
bool ControllableObject::iskilled()
{
	return this->killed;
}
/** Setter method */
void ControllableObject::setKilled(bool k)
{
	this->killed = k;
}

float ControllableObject::getSpeed()
{
	return this->speed;
}
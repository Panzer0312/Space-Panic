#include "PlayerObject.h"

PlayerObject::PlayerObject(int objID, Vector2f objPos, float objSpeed, int objWidth):
	ControllableObject(objID, objPos, objSpeed, objWidth, PLAYER)
{
	this->props.id = objID;
	this->props.type = PLAYER;
}

DrawingObjectProps PlayerObject::getDrawingObjectProps()
{
	return DrawingObjectProps(this->props, this->dec, this->pos, this->width, this->state, this->counter);
}

#include "LadderObject.h"

LadderObject::LadderObject(int objID, Vector2f objPos, int objWidth):
	GameObject(objID, objPos, LADDER, objWidth)
{
	this->props.id = objID;
	this->props.type = LADDER;
}

DrawingObjectProps LadderObject::getDrawingObjectProps()
{
	return DrawingObjectProps(this->props, this->pos, this->width, this->state, this->counter);
}


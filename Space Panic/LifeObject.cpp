#include "LifeObject.h"

LifeObject::LifeObject(int objID, Vector2f objPos, int objWidth):
	GameObject(objID, objPos, LIFE, objWidth)
	{
		this->props.id = objID;
		this->props.type = LIFE;
}

DrawingObjectProps LifeObject::getDrawingObjectProps()
{
    return DrawingObjectProps(this->props, this->pos, this->width, this->state, this->counter);
}

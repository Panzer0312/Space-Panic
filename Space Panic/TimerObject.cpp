#include "TimerObject.h"

TimerObject::TimerObject(int objID, Vector2f objPos,TimerType tType, int objWidth):
	GameObject(objID, objPos, TIMER, objWidth)
{
	this->timerType = tType;
	this->props.id = objID;
	this->props.type = TIMER;
	this->props.closerType = tType;
}

DrawingObjectProps TimerObject::getDrawingObjectProps()
{
	return DrawingObjectProps(this->props, this->pos, this->width, this->state, this->counter);
}


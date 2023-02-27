#include "TimerObject.h"

TimerObject::TimerObject(int objSpriteID, std::string objName, Vector2f objPos, ObjectType objType, int objWidth):
	GameObject(objSpriteID, objName, objPos, objType, objWidth)
{
	props.id = objSpriteID;
	props.type = 'T';
}

DrawingObjectProps TimerObject::getDrawingObjectProps()
{
	return DrawingObjectProps(props, drawing, pos, width,state);
}


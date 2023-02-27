#include "LifeObject.h"

LifeObject::LifeObject(int objSpriteID, std::string objName, Vector2f objPos, ObjectType objType, int objWidth):
	GameObject(objSpriteID, objName, objPos, objType, objWidth)
	{
		props.id = objSpriteID;
		props.type = 'H';
}

DrawingObjectProps LifeObject::getDrawingObjectProps()
{
    return DrawingObjectProps(props, drawing, pos, width,state);
}

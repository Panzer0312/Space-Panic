#include "LadderObject.h"

LadderObject::LadderObject(int objSpriteID, std::string objName, Vector2f objPos, ObjectType objType, int objWidth):
	GameObject(objSpriteID, objName, objPos, objType, objWidth)
{
	props.id = objSpriteID;
	props.type = 'L';
}

DrawingObjectProps LadderObject::getDrawingObjectProps()
{
	return DrawingObjectProps(props, drawing, pos, width,state);
}


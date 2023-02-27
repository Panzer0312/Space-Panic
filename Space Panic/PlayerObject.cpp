#include "PlayerObject.h"

PlayerObject::PlayerObject(int objSpriteID, std::string objName, Vector2f objPos, ObjectType objType, float objSpeed, int objWidth):
	ControllableObject(objSpriteID, objName, objPos, objType, objSpeed, objWidth)
{
	props.id = objSpriteID;
	props.type = 'P';
}

DrawingObjectProps PlayerObject::getDrawingObjectProps()
{
	return DrawingObjectProps(props, drawing,dec, pos, width,state);
}

#include "LadderObject.h"

LadderObject::LadderObject(int objSpriteID, std::string objName, Vector2f objPos, ObjectType objType):
	GameObject(objSpriteID, objName, objPos, objType)
{
}


std::string LadderObject::IDAsString() {
	return "L#" + std::to_string(ID);
}

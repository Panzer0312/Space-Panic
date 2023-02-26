#include "PlayerObject.h"

PlayerObject::PlayerObject(int objSpriteID, std::string objName, Vector2f objPos, ObjectType objType, float objSpeed):
	ControllableObject(objSpriteID, objName, objPos, objType, objSpeed)
{

}

std::string PlayerObject::IDAsString() {
	return "P#" + std::to_string(ID);
}

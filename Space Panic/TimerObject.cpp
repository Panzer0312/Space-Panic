#include "TimerObject.h"

TimerObject::TimerObject(int objSpriteID, std::string objName, Vector2f objPos, ObjectType objType):
	GameObject(objSpriteID, objName, objPos, objType)
{

}

std::string TimerObject::IDAsString() {
	return "T#" + std::to_string(ID);
}

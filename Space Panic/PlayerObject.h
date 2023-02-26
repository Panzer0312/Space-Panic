#pragma once
#include "ControllableObject.h"
class PlayerObject :
    public ControllableObject
{
public:
    PlayerObject(int objSpriteID, std::string objName, Vector2f objPos, ObjectType objType, float objSpeed);
    std::string IDAsString();
};
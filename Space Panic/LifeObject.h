#pragma once
#include "GameObject.h"
class LifeObject :
    public GameObject
{
public:
    LifeObject(int objSpriteID, std::string objName, Vector2f objPos, ObjectType objType, int objWidth);
    DrawingObjectProps getDrawingObjectProps();
};


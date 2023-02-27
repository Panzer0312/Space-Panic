#pragma once
#include "GameObject.h"
class LadderObject :
    public GameObject
{
public:
    LadderObject(int objSpriteID, std::string objName, Vector2f objPos, ObjectType objType, int objWidth);
    DrawingObjectProps getDrawingObjectProps();
};


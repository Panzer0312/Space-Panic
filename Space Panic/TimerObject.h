#pragma once
#include "GameObject.h"
class TimerObject :
    public GameObject
{
public:
    TimerObject(int objSpriteID, std::string objName, Vector2f objPos, ObjectType objType, int objWidth);
    DrawingObjectProps getDrawingObjectProps();
};


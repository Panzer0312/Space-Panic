#pragma once
#include "GameObject.h"
class LifeObject :
    public GameObject
{
public:
    LifeObject(int objSpriteID,Vector2f objPos, int objWidth);
    DrawingObjectProps getDrawingObjectProps();
};


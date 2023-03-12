#pragma once
#include "GameObject.h"
class LadderObject :
    public GameObject
{
public:
    LadderObject(int objSpriteID, Vector2f objPos, int objWidth);
    DrawingObjectProps getDrawingObjectProps();
};


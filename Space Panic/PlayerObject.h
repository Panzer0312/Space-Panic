#pragma once
#include "ControllableObject.h"
class PlayerObject :
    public ControllableObject
{
public:
    PlayerObject(int objSpriteID, Vector2f objPos, float objSpeed, int objWidth);
    DrawingObjectProps getDrawingObjectProps();
};
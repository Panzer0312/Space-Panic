#pragma once
#include "GameObject.h"
class TimerObject :
    public GameObject
{
public:
    TimerObject(int objSpriteID, Vector2f objPos, TimerType tType, int objWidth);
    DrawingObjectProps getDrawingObjectProps();
private:
    TimerType timerType;
};


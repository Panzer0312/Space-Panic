#pragma once
#include "GameObject.h"
class BrickObject :
    public GameObject
{
public:
    BrickObject(int objID, std::string objName, Vector2f objPos, ObjectType objType, BrickType bType, int objWidth);
    DrawingObjectProps getDrawingObjectProps();
    void setDugOut(bool b);
    void setOccupied(bool b);
    bool isDugOut();
    bool isOccupied();
private:
    bool occupied;
    bool dugOut;
    BrickType brickType;
};


#pragma once
#include "GameObject.h"
class BrickObject :
    public GameObject
{
public:
    BrickObject(int objID, Vector2f objPos, BrickType bType, int objWidth);
    DrawingObjectProps getDrawingObjectProps();
    BrickType getBrickType();
    void setDugOut(bool b);
    void setOccupied(bool b, int enemyID);
    int getOccupiedBy();
    bool isDugOut();
    bool isOccupied();
private:
    bool occupied;
    bool dugOut;
    int occupiedBy;
    BrickType brickType;
};


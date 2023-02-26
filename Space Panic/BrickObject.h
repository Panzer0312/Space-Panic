#pragma once
#include "GameObject.h"
class BrickObject :
    public GameObject
{
public:
    BrickObject(int objID, std::string objName, Vector2f objPos, ObjectType objType, BrickType bType);

    void setDugOut(bool b);
    void setOccupied(bool b);
    bool isDugOut();
    bool isOccupied();
    std::string IDAsString();
private:
    bool occupied;
    bool dugOut;
    BrickType brickType;
};


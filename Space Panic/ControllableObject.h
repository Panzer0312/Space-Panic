#pragma once
#include "GameObject.h"
class ControllableObject :
    public GameObject
{
public:
    ControllableObject(int objSpriteID,Vector2f objPos, float objSpeed, int objWidth, ObjectType t);
    virtual ~ControllableObject() = 0;
    bool isFalling();
    void setFalling(bool f);
    bool iskilled();
    void setKilled(bool k);
    float getSpeed();
    ControlledObjectDecision getDecision();
    void setDecision(ControlledObjectDecision decision);
    void setFacing(Vector2i f);
    Vector2i getFacing();
protected:
    float speed;
    ControlledObjectDecision dec;
    bool falling, killed;
    Vector2i facing;
};


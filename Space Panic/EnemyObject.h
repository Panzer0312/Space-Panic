#pragma once
#include "math.h"
#include "ControllableObject.h"
class EnemyObject :
    public ControllableObject
{
public:
    EnemyObject(int objSpriteID, std::string objName, Vector2f objPos, ObjectType objType,EnemyType eType, float objSpeed, int objWidth);
    int getDecisionCounter();
    void setDecisionCounter(int newDecCount);
    void resetDecisionCounter();
    int getPushUps();
    void setPushUps(int i);
    DrawingObjectProps getDrawingObjectProps();
private:
    int pushUps,decCount,fallenStages;
    EnemyType enemyType;
};


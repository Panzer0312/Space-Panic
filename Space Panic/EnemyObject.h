#pragma once
#include "math.h"
#include "ControllableObject.h"
class EnemyObject :
    public ControllableObject
{
public:
    EnemyObject(int objSpriteID, std::string objName, Vector2f objPos, ObjectType objType,EnemyType eType, float objSpeed);

    void resetDecisionCounter();
    std::string IDAsString();
private:
    int pushUps,decCount,fallenStages;
    EnemyType enemyType;
};


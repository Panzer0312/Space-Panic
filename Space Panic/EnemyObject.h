#pragma once
#include "math.h"
#include "ControllableObject.h"
class EnemyObject :
    public ControllableObject
{
public:
    EnemyObject(int objSpriteID, Vector2f objPos, EnemyType eType, float objSpeed, int objWidth);
    void setIgnoreNextStage(bool b);
    bool getIgnoreNextStage();
    Vector2f getDiePos();
    EnemyType getEnemyType();
    void setDiePos(Vector2f pos);
    int getDecisionCounter();
    void setDecisionCounter(int newDecCount);
    void resetDecisionCounter();
    int getPushUps();
    void setPushUps(int i);
    int getFeltInBrickID();
    void setFeltInBrickID(int i);
    DrawingObjectProps getDrawingObjectProps();
private:
    int pushUps,decCount,fallenStages,feltInBrickId;
    EnemyType enemyType;
    Vector2f diePos;
    bool ignoreNextStage;
};


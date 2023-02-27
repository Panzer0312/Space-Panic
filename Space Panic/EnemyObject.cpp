#include "EnemyObject.h"


EnemyObject::EnemyObject(int objSpriteID, std::string objName, Vector2f objPos, ObjectType objType, EnemyType eType, float objSpeed, int objWidth):
	ControllableObject(objSpriteID, objName,objPos, objType,objSpeed, objWidth)
{
	decCount = 0;
	fallenStages = 0;
	pushUps = 0;
	enemyType = eType;
	props.id = objSpriteID;
	props.type = 'E';
	props.closerType = eType;
}

int EnemyObject::getDecisionCounter()
{
	return decCount;
}

void EnemyObject::setDecisionCounter(int newDecCount)
{
	decCount = newDecCount;
}

void EnemyObject::resetDecisionCounter() {
	decCount = 0;
}

int EnemyObject::getPushUps()
{
	return pushUps;
}

void EnemyObject::setPushUps(int i)
{
	pushUps = i;
}

DrawingObjectProps EnemyObject::getDrawingObjectProps()
{
	return DrawingObjectProps(props, drawing,dec, pos, width,state);
}

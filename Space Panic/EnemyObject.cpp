#include "EnemyObject.h"


EnemyObject::EnemyObject(int objID, Vector2f objPos, EnemyType eType, float objSpeed, int objWidth):
	ControllableObject(objID, objPos, objSpeed, objWidth, ENEMY)
{
	this->decCount = 0;
	this->fallenStages = 0;
	this->pushUps = 0;
	this->enemyType = eType;
	this->props.id = objID;
	this->props.type = ENEMY;
	this->props.closerType = eType;
	this->dec = rand() % 2 == 0 ? LEFT : RIGHT;
	this->diePos = Vector2f(0, 0);
	this->ignoreNextStage = false;
	this->feltInBrickId = -1;
}

void EnemyObject::setIgnoreNextStage(bool b) {
	this->ignoreNextStage = b;
}
bool EnemyObject::getIgnoreNextStage() {
	return this->ignoreNextStage;
}


Vector2f EnemyObject::getDiePos() {
	return this->diePos;
}

EnemyType EnemyObject::getEnemyType()
{
	return this->enemyType;
}

void EnemyObject::setDiePos(Vector2f pos) {
	this->diePos = pos;
}

int EnemyObject::getDecisionCounter()
{
	return this->decCount;
}

void EnemyObject::setDecisionCounter(int newDecCount)
{
	this->decCount = newDecCount;
}

void EnemyObject::resetDecisionCounter() {
	this->decCount = 0;
}

int EnemyObject::getPushUps()
{
	return this->pushUps;
}

void EnemyObject::setPushUps(int i)
{
	this->pushUps = i;
}

int EnemyObject::getFeltInBrickID()
{
	return this->feltInBrickId;
}

void EnemyObject::setFeltInBrickID(int i)
{
	this->feltInBrickId = i;
}

DrawingObjectProps EnemyObject::getDrawingObjectProps()
{
	return DrawingObjectProps(this->props, this->dec, this->pos, this->width, this->state, this->counter);
}

#include "EnemyObject.h"


EnemyObject::EnemyObject(int objSpriteID, std::string objName, Vector2f objPos, ObjectType objType, EnemyType eType, float objSpeed):
	ControllableObject(objSpriteID, objName,objPos, objType,objSpeed)
{
	decCount = 0;
	fallenStages = 0;
	pushUps = 0;
	enemyType = eType;
}

void EnemyObject::resetDecisionCounter() {
	decCount = 0;
}

std::string EnemyObject::IDAsString() {
	std::string out = "E";
	if (enemyType == NORMENEMY) {
		out.append("0#");
	}
	else {
		out.append("1#");
	}
	out.append(std::to_string(ID));
	return out;
}

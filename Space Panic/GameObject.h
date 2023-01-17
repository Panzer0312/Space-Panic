#pragma once
#include "math.h"
#include <vector>
#include <string>
class GameObject
{
public:
	/** Empty Constructor of a dummy GameObject */
	GameObject();
	/** Contructor for a new GameObject */
	GameObject(int objSpriteID, std::string objName, Vector2f objPos, float objSpeed, objectType objType);
	/** Sets the Position of a GameObject to reference position where it's sprite is drawn on the screen positon */
	void setPos(Vector2f pos);
	/** Returns ID of the GameObject's sprite */
	int getID();
	/** Returns postion of a GameObject*/
	Vector2f getPos();
	/** Returns type of a GameObject to differentiate those in the GameModel's vector Objects */
	objectType getType();
	/** Returns speed how fast the GameObject should be moved */
	float getSpeed();
	/** Returns name of the specific GameObject */
	std::string getName();
	/** Returns the position where the Object is facing to */
	Vector2i getFacing();
	/** Sets the position where the Object is facing to */
	void setFacing(Vector2i dir);
	/** Changes the name for the current ObjectAnimation */
	void changeCurrAnimName(std::string name);
	std::string getCurrAnimName();
	int* getCurrAnim();
	int* getCurrCounter();
	bool isFalling();
	void setFalling(bool f);
	enemyDecision getDecision();
	void setDecision(enemyDecision decision);
	void resetDecisionCounter();
	int getDecisionCounter();
	void setDecisionCounter(int newDecCount);
	bool iskilled();
	void setKilled(bool k);
	int getPushUps();
	void setPushUps(int i);
private:
	/** The Type of the GameObject (BRICK,ENEMY,LADDER,LIFE,TIMER) */
	objectType type;
	Vector2f pos;
	float speed;
	int spriteID, counter, currAnim,decCount,pushUps;
	std::string name,currAnimName;
	bool animate,falling, killed;
	Vector2i facing;
	enemyDecision dec;


};


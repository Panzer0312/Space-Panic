#pragma once
#include "math.h"
#include <vector>
#include <string>
class GameObject
{
public:
	virtual ~GameObject() = 0;

	/** Contructor for a new GameObject */
	GameObject(int objSpriteID, std::string objName, Vector2f objPos, ObjectType objType);

	//GameObject(int objSpriteID, std::string objName, Vector2f objPos, float objSpeed, objectType objType);
	/** Returns ID of the GameObject's sprite */
	int getID();
	Vector2f getSize();
	virtual std::string IDAsString();
	void setSize(Vector2f s);
	/** Sets the Position of a GameObject to reference position where it's sprite is drawn on the screen positon */
	void setPos(Vector2f pos);
	/** Returns postion of a GameObject*/
	Vector2f getPos();
	/** Returns type of a GameObject to differentiate those in the GameModel's vector Objects */
	ObjectType getType();
	/** Returns name of the specific GameObject */
	std::string getName();
	bool getDrawing();
	void setDrawing(bool b);
	
	/** Returns speed how fast the GameObject should be moved */
	//float getSpeed();
	/** Returns the position where the Object is facing to */
	//Vector2i getFacing();
	/** Sets the position where the Object is facing to */
	//void setFacing(Vector2i dir);
	/** Changes the name for the current ObjectAnimation */

	//void changeCurrAnimName(std::string name); //!!!
	//std::string getCurrAnimName(); //!!!
	//int* getCurrAnim(); //!!!
	//int* getCurrCounter();//!!!

	//bool isFalling();
	//void setFalling(bool f);
	//controlledObjectDecision getDecision();
	//void setDecision(controlledObjectDecision decision);
	//void resetDecisionCounter();
	//int getDecisionCounter();
	//void setDecisionCounter(int newDecCount);
	//bool iskilled();
	//void setKilled(bool k);
	//int getPushUps();
	//void setPushUps(int i);

	bool hasCollision(Vector2f enemyBounds, Vector2f enemyPos);


protected:
	/** The Type of the GameObject (BRICK,ENEMY,LADDER,LIFE,TIMER) */
	ObjectType type;
	Vector2f pos,size;
	int ID;
	std::string name;
	bool drawing;
	//float speed;
	//int pushUps;
	// counter, currAnim,decCount;
	//string currAnimName;bool animate;
	//falling, killed;
	//Vector2i facing;
	//controlledObjectDecision dec;


};


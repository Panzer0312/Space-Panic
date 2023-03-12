#pragma once
#include "math.h"
#include <vector>
#include <string>
class GameObject
{
public:
	virtual ~GameObject() = 0;

	/** Contructor for a new GameObject */
	GameObject(int objSpriteID, Vector2f objPos, ObjectType objType, int objWidth);

	void setState(GameObjectState s);

	GameObjectState getState();

	//GameObject(int objSpriteID, std::string objName, Vector2f objPos, float objSpeed, objectType objType);
	/** Returns ID of the GameObject's sprite */
	int getID();
	int getWidth();
	ObjectProps getObjectProps();
	void setWidth(int w);
	/** Sets the Position of a GameObject to reference position where it's sprite is drawn on the screen positon */
	void setPos(Vector2f pos);
	/** Returns postion of a GameObject*/
	Vector2f getPos();
	/** Returns type of a GameObject to differentiate those in the GameModel's vector Objects */
	ObjectType getType();
	void addCounter();
	void lowerCounter();
	int getCounter();
	void resetCounter();
	/** Returns name of the specific GameObject */
	 //std::string getName();
	virtual DrawingObjectProps getDrawingObjectProps();
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

	//void setDecisionCounter(int newDecCount);
	//bool iskilled();
	//void setKilled(bool k);
	//int getPushUps();
	//void setPushUps(int i);


protected:
	/** The Type of the GameObject (BRICK,ENEMY,LADDER,LIFE,TIMER) */
	ObjectProps props;
	ObjectType type;
	Vector2f pos;
	int ID, width,counter;
	GameObjectState state;
	//float speed;
	//int pushUps;
	// counter, currAnim,decCount;
	//string currAnimName;bool animate;
	//falling, killed;
	//Vector2i facing;
	//controlledObjectDecision dec;


};


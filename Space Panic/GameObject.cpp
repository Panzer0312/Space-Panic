#include "GameObject.h"

/**
 * .
 * Dummy constructor
 */
GameObject::GameObject()
{
	type = BRICK;
	pos = Vector2f(0,0);
	speed = -1;
	spriteID = -1;
	name = "";
	animate = false,falling = false;
	facing = Vector2i(0,0);
	counter = 0,currAnim = 0, pushUps = 0;
	dec = RIGHT;
	killed = false;
}

/**
 * .
 * 
 * \param objSpriteID ID of the associated Sprite to the GameObject 
 * \param objName Name of the GameObject to find it easier in Objects vector in GameModel
 * \param objPos Position where the Sprite of the GameObject is drawn
 * \param objSpeed Speed with which Object will be moved
 * \param objType Type of a GameObject to differentiate those in the Model's vector Objects
 */
GameObject::GameObject(int objSpriteID, std::string objName, Vector2f objPos, float objSpeed, objectType objType){
	spriteID = objSpriteID;
	name = objName;
	pos = objPos;
	speed = objSpeed;
	type = objType;
	counter = 0, currAnim = 0, pushUps = 0, decCount = 0;
	falling = false;
	dec = RIGHT;
	killed = false;
}
/** setter method */
void GameObject::setPos(Vector2f position) {
	pos = position;
}
/** getter method */
int GameObject::getID()
{
	return spriteID;
}
/** getter method */
Vector2f GameObject::getPos()
{
	return pos;
}
/** getter method */
objectType GameObject::getType()
{
	return type;
}
/** getter method */
float GameObject::getSpeed()
{
	return speed;
}
/** getter method */
std::string GameObject::getName()
{
	return name;
}
/** getter method */
Vector2i GameObject::getFacing()
{
	return facing;
}
/** setter method */
void GameObject::setFacing(Vector2i dir)
{
	facing = dir;
}

void GameObject::changeCurrAnimName(std::string name) {
	currAnimName = name;
}

std::string GameObject::getCurrAnimName() {
	return currAnimName;
}

int* GameObject::getCurrAnim() {
	return &currAnim;
}
int* GameObject::getCurrCounter() {
	return &counter;
}

bool GameObject::isFalling()
{
	return falling;
}

void GameObject::setFalling(bool f)
{
	falling = f;
}

enemyDecision GameObject::getDecision()
{
	return dec;
}

void GameObject::setDecision(enemyDecision decision)
{
	dec = decision;
}

void GameObject::resetDecisionCounter(){
	decCount = 0;
}

int GameObject::getDecisionCounter(){
	return decCount;
}

void GameObject::setDecisionCounter(int newDecCount) {
	decCount = newDecCount;
}

bool GameObject::iskilled()
{
	return killed;
}

void GameObject::setKilled(bool k)
{
	killed = k;
}

int GameObject::getPushUps(){
	return pushUps;
}

void GameObject::setPushUps(int i)
{
	pushUps = i;
}

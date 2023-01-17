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
/** Setter method */
void GameObject::setPos(Vector2f position) {
	pos = position;
}
/** Getter method */
int GameObject::getID()
{
	return spriteID;
}
/** Getter method */
Vector2f GameObject::getPos()
{
	return pos;
}
/** Getter method */
objectType GameObject::getType()
{
	return type;
}
/** Getter method */
float GameObject::getSpeed()
{
	return speed;
}
/** Getter method */
std::string GameObject::getName()
{
	return name;
}
/** Getter method */
Vector2i GameObject::getFacing()
{
	return facing;
}
/** Setter method */
void GameObject::setFacing(Vector2i dir)
{
	facing = dir;
}
/** Setter method */
void GameObject::changeCurrAnimName(std::string name) {
	currAnimName = name;
}
/** Getter method */
std::string GameObject::getCurrAnimName() {
	return currAnimName;
}
/** Getter method */
int* GameObject::getCurrAnim() {
	return &currAnim;
}
/** Getter method */
int* GameObject::getCurrCounter() {
	return &counter;
}
/** Getter method */
bool GameObject::isFalling()
{
	return falling;
}
/** Setter method */
void GameObject::setFalling(bool f)
{
	falling = f;
}
/** Getter method */
enemyDecision GameObject::getDecision()
{
	return dec;
}
/** Setter method */
void GameObject::setDecision(enemyDecision decision)
{
	dec = decision;
}
/** Sets the decision counter to 0*/
void GameObject::resetDecisionCounter(){
	decCount = 0;
}
/** Getter method */
int GameObject::getDecisionCounter(){
	return decCount;
}
/** Setter method */
void GameObject::setDecisionCounter(int newDecCount) {
	decCount = newDecCount;
}
/** Getter method */
bool GameObject::iskilled()
{
	return killed;
}
/** Setter method */
void GameObject::setKilled(bool k)
{
	killed = k;
}
/** Getter method */
int GameObject::getPushUps(){
	return pushUps;
}
/** Setter method */
void GameObject::setPushUps(int i)
{
	pushUps = i;
}

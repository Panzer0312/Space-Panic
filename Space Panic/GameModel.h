#pragma once
#include <vector>
#include "EnemyObject.h"
#include "TimerObject.h"
#include "BrickObject.h"
#include "LadderObject.h"
#include "PlayerObject.h"
#include "LifeObject.h"

//A game class for everything storage related
class GameModel
{
public:
	//!!!!!
	/** Structure for saving Texture information in GameModel --> GameController retrieves them and sends them to GameView to be drawn on screen*/
	/*struct SpriteInformation {
		/** X Coordinate of Texture on screen 
		unsigned int PixelX = 0;
		/** Y Coordinate of Texture on screen 
		unsigned int PixelY = 0;
		/** Sprite location in the sprite sheet - row 
		unsigned int SpriteRow = 0;
		/** Sprite location in the sprite sheet - col  
		unsigned int SpriteCol = 0;
		/** How tall the sprite should be drawn 
		unsigned int SpriteWidth = 0;
	};
	*/
	/** Instantiates the GameModel and sets all its counter to 0*/
	GameModel();
	//ObjectProps StringToProps(std::string s); //!!!!!!!!!

	std::vector<DrawingObjectProps> getDrawingInformation();

	/** Instantiates a GameObject with also calling addSprite and adds it to the GameObject vector (Objects) */
	
	void addBrickObject(Vector2f pos, int width, BrickType bType);
	void addLadderObject(Vector2f pos, int width);
	void addTimerObject(Vector2f pos, int width, TimerType tType);
	void addEnemyObject(Vector2f pos, int width, EnemyType eType, float speed);
	void addPlayerObject(Vector2f pos, int width, float speed);
	void addLifeObject(Vector2f pos, int width);
	/** Changes the position of a object in Objects and the associated Sprite in Sprites to move it on the screen */
	void changeObjPos(ObjectProps o, Vector2f pos);
	/** Deletes an object from the vector Objects */
	//void deleteObject(int objectPos, std::string objectID);
	std::vector<BrickObject> getBricks();
	/**  Returns the vector Objects with all instantiated GameObjects */
	PlayerObject* getPlayer();
	/** Returns replacedBricks vector */
	std::vector<BrickObject> getReplacedBricks();
	/** Returns Enemies vector*/
	std::vector<EnemyObject>* getEnemies();
	std::vector<LifeObject> getLifes();
	std::vector<LadderObject> getLadders();
	/** Returns a GameObject pointer from the given ID (Searches the Objects vector)*/
	//GameObject* getObjP(std::string ID);
	/** Searches the vector Objects after a given name */
	int findObject(std::string name);
	/** Adds a brick GameObject if it doesn't exist in the replacedBrick vector yet otherwise deletes it*/
	bool addReplacedBrick(int id);
	/** Returns the last index of the timer vector */
	int timerCount();
	/** Returns the GameObject pointer of the first GameObject in the timer vector */
	TimerObject* getNextTimer();
	/** Deletes the first GameObject in the timer vector, returns true at sucess */
	bool removeNextTimer();
	/** Returns the GameObject pointer of the GameObject at the given position in the Lifes vector*/
	GameObject* getLife(int pos);
	/** Clears every vector used in GameModel and resets the counter */
	void deleteAll();
	void setReplacedBrickOccupied(int id, int enemyID);
	void lowerBrickCounter(int id);
	void addBrickCounter(int id);
	void setEnemyDead(int id);
	bool isBrickDugOut(int id);
	void addEnemyCounter(int id);
	/** Returns the sprite at a given position in the vector Sprites */
	//SpriteInformation getSprite(int i);
	//void deleteEnemy(int enemyPos);
	/** Returns the vector Sprites with all instantiated Sprites*/
	//std::vector<SpriteInformation> getSprites();
	/** Deletes a sprite from the vector Sprites */
	//void deleteSprite(int sprite);
	/** Changes the position of a sprite in Sprites to move it on the screen*/
	//void changeSpritePos(int sprite, Vector2f pos);
	/** Changes the appearance of an instantiated Sprite in the vector Sprites */
	//void changeSpriteSheet(int sprite, Vector2i pos);
	/** Adds a sprite to the vector with all sprites (Sprites) that will be drawn to the screen */
	//int addSprite(Vector2f pos, Vector2i spritesheetPos, int width);
private:
	/** Stores all instantiated Sprites */
	//std::vector<SpriteInformation> Sprites;
	/** Stores all instantiated Objects */
	//std::vector<GameObject> Objects;
	PlayerObject* Player;

	/** Stores all instantiated Aliens */
	std::vector<EnemyObject> Enemies;

	std::vector<BrickObject> Bricks;
	/** Stores all replaced bricks for efficiency */
	std::vector<BrickObject> ReplacedBricks;
	std::vector<LadderObject> Ladders;
	/** Stores all instantiated timer objects (the yellow/red bar at the top) */
	std::vector<TimerObject> Timer;
	/** Stores all player lifes for visualization*/
	std::vector<LifeObject> Lifes;

};

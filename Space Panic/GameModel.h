#pragma once
#include "GameObject.h"
#include <vector>
//A game class for everything storage related
class GameModel
{
public:

	/** Structure for saving Texture information in GameModel --> GameController retrieves them and sends them to GameView to be drawn on screen*/
	struct SpriteInformation {
		/** X Coordinate of Texture on screen */
		unsigned int PixelX = 0;
		/** Y Coordinate of Texture on screen */
		unsigned int PixelY = 0;
		/** Sprite location in the sprite sheet - row */
		unsigned int SpriteRow = 0;
		/** Sprite location in the sprite sheet - col  */
		unsigned int SpriteCol = 0;
		/** How tall the sprite should be drawn */
		unsigned int SpriteWidth = 0;
	};

	/** Instantiates the GameModel and sets all its counter to 0*/
	GameModel();
	/** Adds a sprite to the vector with all sprites (Sprites) that will be drawn to the screen */
	int addSprite(Vector2f pos, Vector2i spritesheetPos, int width);
	/** Instantiates a GameObject with also calling addSprite and adds it to the GameObject vector (Objects) */
	int addObject(Vector2f pos, Vector2i spritesheetPos, int width, std::string name, int speed, objectType type);
	/** Changes the position of a sprite in Sprites to move it on the screen*/
	void changeSpritePos(int sprite, Vector2f pos);
	/** Changes the appearance of an instantiated Sprite in the vector Sprites */
	void changeSpriteSheet(int sprite, Vector2i pos);
	/** Changes the position of a object in Objects and the associated Sprite in Sprites to move it on the screen */
	void changeObjPos(int object, Vector2f pos);
	/** Deletes a sprite from the vector Sprites */
	void deleteSprite(int sprite);
	/** Deletes an object from the vector Objects */
	void deleteObject(int objectPos);
	void deleteEnemy(int enemyPos);
	/** Returns the vector Sprites with all instantiated Sprites*/
	std::vector<SpriteInformation> getSprites();
	/**  Returns the vector Objects with all instantiated GameObjects */
	std::vector<GameObject> getObjects();
	/** Returns the sprite at a given position in the vector Sprites */
	SpriteInformation getSprite(int i);
	/** Searches the vector Objects after a given name */
	int findObject(std::string name);
	/** Adds a brick GameObject if it doesn't exist in the replacedBrick vector yet otherwise deletes it*/
	bool addReplacedBrick(int id);
	/** Returns replacedBricks vector */
	std::vector<GameObject> getReplacedBricks();
	/** Returns Enemies vector*/
	std::vector<GameObject> getEnemies();
	/** Returns a GameObject pointer from the given ID (Searches the Objects vector)*/
	GameObject* getObjP(int id);
	/** Returns the last index of the timer vector */
	int timerCount();
	/** Returns the GameObject pointer of the first GameObject in the timer vector */
	GameObject* getNextTimer();
	/** Deletes the first GameObject in the timer vector, returns true at sucess */
	bool removeNextTimer();
	/** Returns the GameObject pointer of the GameObject at the given position in the Lifes vector*/
	GameObject* getLife(int pos);
	/** Changes the variable facing of a GameObject at a given position in vector Objects */
	void changeObjectFacing(int obj,Vector2i dir);
	/** Clears every vector used in GameModel and resets the counter */
	void deleteAll();

private:
	/** Stores all instantiated Sprites */
	std::vector<SpriteInformation> Sprites;
	/** Stores all instantiated Objects */
	std::vector<GameObject> Objects;
	/** Stores all instantiated Aliens */
	std::vector<GameObject> Enemies;
	/** Stores all replaced bricks for efficiency */
	std::vector<GameObject> replacedBricks;
	/** Stores all instantiated timer objects (the yellow/red bar at the top) */
	std::vector<GameObject> timer;
	/** Stores all player lifes for visualization*/
	std::vector<GameObject> Lifes;
	/** Counter for how much Sprites are stored */
	int spriteCount;
	/** Counter for how much GameObjects are stored */
	int objectsCount;

};

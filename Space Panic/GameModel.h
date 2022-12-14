#pragma once
#include "GameObject.h"
#include <vector>
#include "SpriteBatch.h"
#include "ObjectAnimation.h"
//A game class for everything storage related
class GameModel
{
public:
	/** Instantiates the GameModel and sets all its counter to 0*/
	GameModel();
	/** Adds a sprite to the vector with all sprites (Sprites) that will be drawn to the screen */
	int addSprite(Vector2f pos, Vector2i spritesheetPos, int width);
	/** Instantiates a GameObject with also calling addSprite and adds it to the GameObject vector (Objects) */
	int addObject(Vector2f pos, Vector2i spritesheetPos, int width, std::string name, int speed, objectType type);
	/** Instantiates a ObjectAnimation and adding it to the ObjectAnimation vector (Animations) */
	int addAnimation(std::string name, float speed, std::vector<Vector2i> animSprites);
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
	/** Returns the vector Sprites with all instantiated Sprites*/
	std::vector<SpriteBatch::SpriteInfo> getSprites();
	/**  Returns the vector Objects with all instantiated GameObjects */
	std::vector<GameObject> getObjects();
	/** Returns a GameObject from Type objectType at a given Position */
	int getObjectAtPos(objectType type, Vector2f pos);
	/** Returns the sprite at a given position in the vector Sprites */
	SpriteBatch::SpriteInfo getSprite(int i);
	/** Returns the vector with all instantiated ObjectAnimations */
	std::vector <ObjectAnimation> getAnimations();
	/** Searches the vector Objects after a given name */
	int findObject(std::string name);
	/** Searches the vector Animations after a given name */
	int findAnimation(std::string name);
	/** Changes the variable facing of a GameObject at a given position in vector Objects */
	void changeObjectFacing(int obj,Vector2i dir);
	/** Calls the function addCount of a given ObjectAnimation to further animate it*/
	void changeAnimCounter(int id);

private:
	/** Stores all instantiated ObjectAnimations */
	std::vector<ObjectAnimation> Animations;
	/** Stores all instantiated Sprites */
	std::vector<SpriteBatch::SpriteInfo> Sprites;
	/** Stores all instantiated Objects */
	std::vector<GameObject> Objects;
	/** Counter for how much Sprites are stored */
	int spriteCount;
	/** Counter for how much GameObjects are stored */
	int objectsCount;
	/** Counter for how much Animations are stored */
	int animationsCount;
};

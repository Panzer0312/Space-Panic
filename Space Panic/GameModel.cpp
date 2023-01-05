#include "GameModel.h"

/**
 * . 
 * 
 * Constructor for the GameModel Class
 * Sets all counters to 0
 */
GameModel::GameModel()
{
	spriteCount = 0;
	objectsCount = 0;
}
/**
 * \param pos Position where the Sprite will be drawn at
 * \param spritesheetPos Index which sprite from Spritesheet should be drawn
 * \param width Size of the Sprite
 * \return 
 */
int GameModel::addSprite(Vector2f pos, Vector2i spritesheetPos, int width)
{
	spriteCount++;
	Sprites.resize(spriteCount);
	Sprites[spriteCount - 1].PixelX = pos.x;
	Sprites[spriteCount - 1].PixelY = pos.y;
	Sprites[spriteCount - 1].SpriteCol = spritesheetPos.x; //x
	Sprites[spriteCount - 1].SpriteRow = spritesheetPos.y; //y
	Sprites[spriteCount - 1].SpriteWidth = width;
	return spriteCount - 1;
}

/**
 * .
 * 
 * \param pos Position where the GameObject's Sprite will be drawn at
 * \param spritesheetPos Index which sprite from Spritesheet should be drawn
 * \param width Sets the Size of the Sprite
 * \param name Name of the Object to find it through findObject()
 * \param speed How fast the Object should be moved 
 * \param type The objectType (BRICK,ENEMY,LADDER,PLAYER)
 * \return 
 */
int GameModel::addObject(Vector2f pos, Vector2i spritesheetPos, int width, std::string name, int speed, objectType type) {
	int spriteID = addSprite(pos,spritesheetPos,width);
	objectsCount++;
	Objects.resize(objectsCount);
	Objects[objectsCount-1] = GameObject(spriteID, name, pos, speed, type);
	return objectsCount - 1;
}

/**
 * .
 * 
 * \param sprite Specific Sprite in the Sprites vector
 * \param pos Vector2f where the specific Sprite should be moved to
 */
void GameModel::changeSpritePos(int sprite, Vector2f pos) {
	Sprites[sprite].PixelX = pos.x;
	Sprites[sprite].PixelY = pos.y;
}

/**
 * .
 * 
 * \param sprite Specific Sprite in the Sprites vector
 * \param pos Vector2i index to which other Sprite on the Spritesheet the Sprite should be changed
 */
void GameModel::changeSpriteSheet(int sprite, Vector2i pos) {
	Sprites[sprite].SpriteCol = pos.x;
	Sprites[sprite].SpriteRow = pos.y;
}

/**
 * .
 * 
 * \param object Specific GameObject in the Objects vector
 * \param pos Vector2f where the specific GameObject should be moved to
 */
void GameModel::changeObjPos(int object, Vector2f pos) {
	int spritePos = Objects[object].getID();
	changeSpritePos(spritePos, pos);
	Objects[object].setPos(pos);
}

/**
 * .
 * 
 * \param sprite Deletes the specific Sprite in Sprites at the given position, sets the Sprite counter to spriteCount-1 and resizes the Vector
 */
void GameModel::deleteSprite(int sprite) {
	Sprites.erase(Sprites.begin() + sprite);
	spriteCount--;
	Sprites.resize(spriteCount);
}

/**
 * .
 * 
 * \param objectPos Deletes the specific Object in Objects at the given position, sets the Object counter to objectsCount-1 and resizes the Vector
 */
void GameModel::deleteObject(int objectPos) {
	deleteSprite(Objects[objectPos].getID());
	Objects.erase(Objects.begin() + objectPos);
	objectsCount--;
	Objects.resize(objectsCount);
}

/**
 * .
 * 
 * \return All instantiated Sprites in the Vector
 */
std::vector<SpriteBatch::SpriteInfo> GameModel::getSprites()
{
	return Sprites;
}

/**
 * .
 * 
 * \return All instantiated Objects in the Vector
 */
std::vector<GameObject> GameModel::getObjects()
{
	return Objects;
}


/**
 * .
 * 
 * \param i Sprite in Sprites at given position
 * \return the found sprite or a dummy Sprite
 */
SpriteBatch::SpriteInfo GameModel::getSprite(int i)
{
	if (i < Sprites.size()) {
		return Sprites[i];
	}
	printf("Sprite %i not found!!", i);
	return SpriteBatch::SpriteInfo();
}

/**
 * .
 * 
 * \param name The name of the GameObject you are looking for
 * \return The position of the found GameObject in the vector Objects or -1
 */
int GameModel::findObject(std::string name)
{
	for (int i = 0; i < Objects.size();i++ ) {
		if (Objects[i].getName() == name) {
			return i;
		}
	}
	printf("Object %s not found!!", name);
	return -1;
}

/**
 * .
 * brick not in list = true, brick already in list = false --> set back to original sprite
 * \param id
 * \return 
 */
bool GameModel::addReplacedBrick(int id)
{
	int i = 0;
	for (GameObject o : replacedBricks) {
		i++;
		if (o.getID() == id) {
			replacedBricks.erase(replacedBricks.begin()+i);
			return false;
		}
	}
	replacedBricks.push_back(Objects[id]);
	return true;
}

std::vector<GameObject> GameModel::getReplacedBricks()
{
	return replacedBricks;
}



GameObject* GameModel::getObjP(int id)
{
	return &Objects[id];
}

/**
 * Used for animation like digging
 *
 * \param obj The GameObject which facing Positon should be changed
 * \param dir The Vector2i where the Object is facing now
 */
void GameModel::changeObjectFacing(int obj, Vector2i dir)
{
	Objects[obj].setFacing(dir);
}
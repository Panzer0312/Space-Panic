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
 * \param type The objectType (BRICK,ENEMY,LADDER,PLAYER|TIMER|LIFE)
 * \return 
 */
int GameModel::addObject(Vector2f pos, Vector2i spritesheetPos, int width, std::string name, int speed, objectType type) {
	int spriteID = addSprite(pos,spritesheetPos,width);
	objectsCount++;
	Objects.resize(objectsCount);
	GameObject obj = GameObject(spriteID, name, pos, speed, type);
	Objects[objectsCount - 1] = obj;
	if (type == ENEMY) {
		Enemies.push_back(obj);
	}
	else if (type == TIMER) {
		timer.push_back(obj);
	}
	else if (type == LIFE) {
		Lifes.push_back(obj);
	}
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
 * \param enemyPos The specific position of the alien GameObject in the Enemies vector
 */
void GameModel::deleteEnemy(int enemyPos) {
	Enemies.erase(Enemies.begin() + enemyPos);
}

/**
 * .
 * 
 * \return All instantiated Sprites in the Vector
 */
std::vector<GameModel::SpriteInformation> GameModel::getSprites()
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
GameModel::SpriteInformation GameModel::getSprite(int i)
{
	if (i < Sprites.size()) {
		return Sprites[i];
	}
	printf("Sprite %i not found!!", i);
	return GameModel::SpriteInformation();
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
	printf("Object %s not found!!", name.c_str());
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
		if (o.getID() == id) {
			replacedBricks.erase(replacedBricks.begin()+i);
			return false;
		}
		i++;
	}
	replacedBricks.push_back(Objects[id]);
	return true;
}

/**
 * .
 * 
 * \return replacedBricks vector
 */
std::vector<GameObject> GameModel::getReplacedBricks()
{
	return replacedBricks;
}
/**
 * .
 * 
 * \return Enemies vector
 */
std::vector<GameObject> GameModel::getEnemies()
{
	return Enemies;
}
/**
 * .
 * 
 * \param id ID of the GamObject --> The position of the GameObject in the Objects vector
 * \return GameObject pointer of the found GameObject 
 */
GameObject* GameModel::getObjP(int id)
{
	return &Objects[id];
}

/**
 * .
 * 
 * \return The last index of the timer vector 
 */
int GameModel::timerCount() {
	return timer.size()-1;
}

/**
 * .
 * 
 * \return The first GameObject (Type == TIMER) in timer vector
 */
GameObject* GameModel::getNextTimer() {
	return &timer[0];
}

/**
 * .
 * 
 * \return success in removing the next timer GameObject
 */
bool GameModel::removeNextTimer() {
	if (timer.size() > 0) {
		timer.erase(timer.begin());
		return true;
	}
	else {
		return false;
	}
}

/**
 * .
 * 
 * \param pos The position of the searched GameObject in the Lifes vector
 * \return The GameObject (Type == LIFE) at the position in the Lifes vector
 */
GameObject* GameModel::getLife(int pos)
{
	return &Lifes[pos];
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

/**
 * .
 * For restarting or changing a game level
 */
void GameModel::deleteAll()
{
	Objects.clear();
	Enemies.clear();
	replacedBricks.clear();
	Sprites.clear();
	timer.clear();
	Lifes.clear();
	spriteCount = 0;
	objectsCount = 0;
}

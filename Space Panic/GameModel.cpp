#include "GameModel.h"

GameModel::~GameModel()
{
}

GameModel::GameModel()
{
	spriteCount = 0;
	objectsCount = 0;
	animationsCount = 0;
}

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

int GameModel::addObject(Vector2f pos, Vector2i spritesheetPos, int width, std::string name, int speed, objectType type) {
	int spriteID = addSprite(pos,spritesheetPos,width);
	objectsCount++;
	Objects.resize(objectsCount);
	Objects[objectsCount-1] = GameObject(spriteID, name, pos, speed, type);
	return objectsCount - 1;
}

int GameModel::addAnimation(std::string name, float speed, std::vector<Vector2i> animSprites)
{
	animationsCount++;
	Animations.resize(animationsCount);
	Animations[animationsCount - 1] = ObjectAnimation(name,speed,animationsCount-1, animSprites);
	return animationsCount - 1;
}

void GameModel::changeSpritePos(int sprite, Vector2f pos) {
	Sprites[sprite].PixelX = pos.x;
	Sprites[sprite].PixelY = pos.y;
}

void GameModel::changeSpriteSheet(int sprite, Vector2i pos) {
	Sprites[sprite].SpriteCol = pos.x;
	Sprites[sprite].SpriteRow = pos.y;
}

void GameModel::changeObjPos(int object, Vector2f pos) {
	int spritePos = Objects[object].getID();
	changeSpritePos(spritePos, pos);
	Objects[object].setPos(pos);
}


void GameModel::deleteSprite(int sprite) {
	Sprites.erase(Sprites.begin() + sprite);
	spriteCount--;
	Sprites.resize(spriteCount);
}

void GameModel::deleteObject(int objectPos) {
	deleteSprite(Objects[objectPos].getID());
	Objects.erase(Objects.begin() + objectPos);
	objectsCount--;
	Objects.resize(objectsCount);
}


std::vector<SpriteBatch::SpriteInfo> GameModel::getSprites()
{
	return Sprites;
}


std::vector<GameObject> GameModel::getObjects()
{
	return Objects;
}


SpriteBatch::SpriteInfo GameModel::getSprite(int i)
{
	if (i < Sprites.size()) {
		return Sprites[i];
	}
	printf("Sprite %i not found!!", i);
	return SpriteBatch::SpriteInfo();
}


std::vector <ObjectAnimation> GameModel::getAnimations()
{
	return Animations;
}

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

int GameModel::findAnimation(std::string name)
{
	for (int i = 0; i < Animations.size(); i++) {
		if (Animations[i].getName() == name) {
			return i;
		}
	}
	printf("Animation %s not found!!", name);
	return -1;
}
void GameModel::changeObjectFacing(int obj,Vector2i dir)
{
	Objects[obj].setFacing(dir);
}
void GameModel::changeAnimCounter(int id)
{
	Animations[id].addCount();
}
/*GameObject GameModel::getObject(int id)
{
	for (auto&i : Sprites) {
		if (i.getID() == id) {
			return i;
		}
	}
	return GameObject();
}

void GameModel::addObject(GameObject obj)
{
	objects.push_back(obj);
}
*/

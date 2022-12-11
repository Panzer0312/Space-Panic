#pragma once
#include "GameObject.h"
#include <vector>
#include "SpriteBatch.h"
//Everything storage related
class GameModel
{
public:
	~GameModel();
	GameModel();
	int addSprite(Vector2f pos, Vector2i spritesheetPos, int width);
	int addObject(Vector2f pos, Vector2i spritesheetPos, int width, std::string name, int speed, objectType type);
	void changeSpritePos(int sprite, Vector2f pos);
	void changeSpriteSheet(int sprite, Vector2i pos);
	void changeObjPos(int object, Vector2f pos);
	void deleteSprite(int sprite);
	void deleteObject(int objectPos);
	std::vector<SpriteBatch::SpriteInfo> getSprites();
	std::vector<GameObject> getObjects();
	SpriteBatch::SpriteInfo getSprite(int i);


	int findObject(std::string name);


private:
	std::vector<SpriteBatch::SpriteInfo> Sprites;
	std::vector<GameObject> Objects;
	int spriteCount;
	int objectsCount;
//	GameObject getObject(int id);
//	void addObject(GameObject obj);
};

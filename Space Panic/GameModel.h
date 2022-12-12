#pragma once
#include "GameObject.h"
#include <vector>
#include "SpriteBatch.h"
#include "ObjectAnimation.h"
//Everything storage related
class GameModel
{
public:
	~GameModel();
	GameModel();
	int addSprite(Vector2f pos, Vector2i spritesheetPos, int width);
	int addObject(Vector2f pos, Vector2i spritesheetPos, int width, std::string name, int speed, objectType type);
//	int addObject(Vector2f pos, Vector2i spritesheetPos, int width, std::string name, int speed, objectType type, std::vector<Vector2i> animationsArray, float animSpeed);
	int addAnimation(std::string name, float speed, std::vector<Vector2i> animSprites);
	void changeSpritePos(int sprite, Vector2f pos);
	void changeSpriteSheet(int sprite, Vector2i pos);
	void changeObjPos(int object, Vector2f pos);
	void deleteSprite(int sprite);
	void deleteObject(int objectPos);
	std::vector<SpriteBatch::SpriteInfo> getSprites();
	std::vector<GameObject> getObjects();
	SpriteBatch::SpriteInfo getSprite(int i);

	std::vector <ObjectAnimation> getAnimations();
	int findObject(std::string name);
	int findAnimation(std::string name);
	void changeObjectFacing(int obj,Vector2i dir);
	void changeAnimCounter(int id);

private:

	std::vector<ObjectAnimation> Animations;
	std::vector<SpriteBatch::SpriteInfo> Sprites;
	std::vector<GameObject> Objects;
	int spriteCount;
	int objectsCount;
	int animationsCount;
//	GameObject getObject(int id);
//	void addObject(GameObject obj);
};

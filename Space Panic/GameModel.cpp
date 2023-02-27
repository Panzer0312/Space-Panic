#include "GameModel.h"
/**
 * . 
 * 
 * Constructor for the GameModel Class
 * Sets all counters to 0
 */
GameModel::GameModel()
{
}


ObjectProps GameModel::StringToProps(std::string s) {
	ObjectProps o{};
	o.type = s[0];
	std::string temp = s;
	int delPos = temp.find("#");
	temp = temp.substr(delPos, temp.size() - 1);
	o.id = stoi(temp);
	return o;
}


std::vector<DrawingObjectProps> GameModel::getDrawingInformation() {
	std::vector<DrawingObjectProps> objects;
	for (BrickObject b : Bricks) {
		DrawingObjectProps temp = b.getDrawingObjectProps();
		if (temp.drawing) {
			objects.push_back(temp);
		}
	}
	for (LadderObject l : Ladders) {
		DrawingObjectProps temp = l.getDrawingObjectProps();
		if (temp.drawing) {
			objects.push_back(temp);
		}
	}
	for (EnemyObject b : Enemies) {
		DrawingObjectProps temp = b.getDrawingObjectProps();
		if (temp.drawing) {
			objects.push_back(temp);
		}
	}
	DrawingObjectProps pDrawingProps = Player->getDrawingObjectProps();
	if (pDrawingProps.drawing) {
		objects.push_back(pDrawingProps);
	}
	for (TimerObject t : Timer) {
		DrawingObjectProps temp = t.getDrawingObjectProps();
		if (temp.drawing) {
			objects.push_back(temp);
		}
	}
	for (LifeObject h : Lifes) {
		DrawingObjectProps temp = h.getDrawingObjectProps();
		if (temp.drawing) {
			objects.push_back(temp);
		}
	}
	return objects;
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
void GameModel::addBrickObject(Vector2f pos, int width, std::string name, ObjectType type, BrickType bType) {
	BrickObject obj = BrickObject(Bricks.size(), name, pos, type, bType, width);
	Bricks.push_back(obj);
}

void GameModel::addLadderObject(Vector2f pos,int width, std::string name, ObjectType type) {
	LadderObject obj = LadderObject(Ladders.size(), name, pos, type, width);
	Ladders.push_back(obj);
}

void GameModel::addLifeObject(Vector2f pos, int width, std::string name, ObjectType type) {
	LifeObject obj = LifeObject(Lifes.size(), name, pos, type, width);
	Lifes.push_back(obj);
}

void GameModel::addTimerObject(Vector2f pos, int width, std::string name, ObjectType type) {
	TimerObject obj = TimerObject(Timer.size(), name, pos, type, width);
	Timer.push_back(obj);
}

void GameModel::addEnemyObject(Vector2f pos, int width, std::string name, ObjectType type, EnemyType eType, float speed) {
	EnemyObject obj = EnemyObject(Enemies.size(), name, pos, type,eType,speed, width);
	Enemies.push_back(obj);
}

void GameModel::addPlayerObject(Vector2f pos, int width, std::string name, ObjectType type, float speed) {
	PlayerObject obj = PlayerObject(0, name, pos, type, speed, width);
	Player = &obj;
}

/**
 * .
 * 
 * \param object Specific GameObject in the Objects vector
 * \param pos Vector2f where the specific GameObject should be moved to
 */
void GameModel::changeObjPos(std::string objectID,Vector2f pos) {
	ObjectProps o = StringToProps(objectID);
	switch (o.type) {
	case 'B':
		Bricks[o.id].setPos(pos);
	case 'L':
		Ladders[o.id].setPos(pos);
	case 'P':
		Player->setPos(pos);
	case 'E':
		Enemies[o.id].setPos(pos);
	case 'H':
		Lifes[o.id].setPos(pos);
	}
}

/**
 * .
 * 
 * \param objectPos Deletes the specific Object in Objects at the given position, sets the Object counter to objectsCount-1 and resizes the Vector
 */
void GameModel::deleteObject(int objectPos, std::string objectID) {
	//deleteSprite(Objects[objectPos].getID());
	//Objects.erase(Objects.begin() + objectPos);
	ObjectProps o = StringToProps(objectID);
	switch (o.type) {
	case 'B':
		Bricks.erase(Bricks.begin() + objectPos);
	case 'L':
		Ladders.erase(Ladders.begin() + objectPos);
	case 'P':
		Player = NULL;
	case 'E':
		Enemies.erase(Enemies.begin() + objectPos);
	case 'H':
		Lifes.erase(Lifes.begin() + objectPos);
	}
}

/**
 * .
 * 
 * \return All instantiated Objects in the Vector
 */
std::vector<BrickObject> GameModel::getBricks()
{
	return Bricks;
}

PlayerObject* GameModel::getPlayer() {
	return Player;
}
/**
 * .
 *
 * \return replacedBricks vector
 */
std::vector<BrickObject> GameModel::getReplacedBricks()
{
	return ReplacedBricks;
}
/**
 * .
 *
 * \return Enemies vector
 */
std::vector<EnemyObject>* GameModel::getEnemies()
{
	return &Enemies;
}

std::vector<LifeObject> GameModel::getLifes() {
	return Lifes;
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
	for (BrickObject o : ReplacedBricks) {
		if (o.getID() == id) {
			ReplacedBricks.erase(ReplacedBricks.begin()+i);
			return false;
		}
		i++;
	}
	ReplacedBricks.push_back(Bricks[id]);
	return true;
}

/**
 * .
 * 
 * \param id ID of the GamObject --> The position of the GameObject in the Objects vector
 * \return GameObject pointer of the found GameObject 
 */
GameObject* GameModel::getObjP(std::string ID)
{
	ObjectProps o = StringToProps(ID);
	switch (o.type) {
	case 'B':
		return &Bricks[o.id];
	case 'L':
		return &Ladders[o.id];
	case 'P':
		return Player;
	case 'E':
		return &Enemies[o.id];
	case 'H':
		return &Lifes[o.id];
	}
	return nullptr;
}

/**
 * .
 * 
 * \return The last index of the timer vector 
 */
int GameModel::timerCount() {
	return Timer.size()-1;
}

/**
 * .
 * 
 * \return The first GameObject (Type == TIMER) in timer vector
 */
GameObject* GameModel::getNextTimer() {
	return &Timer[0];
}

/**
 * .
 * 
 * \return success in removing the next timer GameObject
 */
bool GameModel::removeNextTimer() {
	if (Timer.size() > 0) {
		Timer.erase(Timer.begin());
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
void GameModel::changePlayerFacing(int obj, Vector2i dir)
{
	Player->setFacing(dir);
}

/**
 * Used for animation like digging
 *
 * \param obj The GameObject which facing Positon should be changed
 * \param dir The Vector2i where the Object is facing now
 */
void GameModel::changeEnemyFacing(int obj, Vector2i dir)
{
	Enemies[obj].setFacing(dir);
}


/**
 * .
 * For restarting or changing a game level
 */
void GameModel::deleteAll()
{
	//Objects.clear();
	//Sprites.clear();
	Enemies.clear();
	ReplacedBricks.clear();
	Timer.clear();
	Lifes.clear();
	Bricks.clear();
	Ladders.clear();
}

//Maybe not needed anymore
/**
 * .
 *
 * \param name The name of the GameObject you are looking for
 * \return The position of the found GameObject in the vector Objects or -1
 */
 /** int GameModel::findObject(std::string name)
 {
	 for (int i = 0; i < Objects.size();i++ ) {
		 if (Objects[i].getName() == name) {
			 return i;
		 }
	 }
	 printf("Object %s not found!!", name.c_str());
	 return -1;
 }
 */

/**
 * .
 *
 * \param sprite Deletes the specific Sprite in Sprites at the given position, sets the Sprite counter to spriteCount-1 and resizes the Vector
 */
 /*void GameModel::deleteSprite(int sprite) {
	 Sprites.erase(Sprites.begin() + sprite);
	 spriteCount--;
	 Sprites.resize(spriteCount);
 }
 */

 /**
  * .
  *
  * \param i Sprite in Sprites at given position
  * \return the found sprite or a dummy Sprite
  */
  /** GameModel::SpriteInformation GameModel::getSprite(int i)
  {
	  if (i < Sprites.size()) {
		  return Sprites[i];
	  }
	  printf("Sprite %i not found!!", i);
	  return GameModel::SpriteInformation();
  }
  */

  /**
   * .
   *
   * \return All instantiated Sprites in the Vector
   */
   /*std::vector<GameModel::SpriteInformation> GameModel::getSprites()
   {
	   return Sprites;
   }
   */


   /**
	* .
	*
	* \param sprite Specific Sprite in the Sprites vector
	* \param pos Vector2f where the specific Sprite should be moved to
	*/
	/*
	void GameModel::changeSpritePos(int sprite, Vector2f pos) {
		Sprites[sprite].PixelX = pos.x;
		Sprites[sprite].PixelY = pos.y;
	}
	*/
	/**
	 * .
	 *
	 * \param sprite Specific Sprite in the Sprites vector
	 * \param pos Vector2i index to which other Sprite on the Spritesheet the Sprite should be changed
	 */
	 /*
	 void GameModel::changeSpriteSheet(int sprite, Vector2i pos) {
		 Sprites[sprite].SpriteCol = pos.x;
		 Sprites[sprite].SpriteRow = pos.y;
	 }
	 */


	 /**
	  * \param pos Position where the Sprite will be drawn at
	  * \param spritesheetPos Index which sprite from Spritesheet should be drawn
	  * \param width Size of the Sprite
	  * \return
	  */
	  /*
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
	  */
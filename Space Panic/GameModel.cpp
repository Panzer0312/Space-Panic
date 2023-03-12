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

/*
ObjectProps GameModel::StringToProps(std::string s) {
	ObjectProps o{};
	o.type = s[0];
	std::string temp = s;
	int delPos = temp.find("#");
	temp = temp.substr(delPos, temp.size() - 1);
	o.id = stoi(temp);
	return o;
}
*/

std::vector<DrawingObjectProps> GameModel::getDrawingInformation() {
	std::vector<DrawingObjectProps> objects;
	for (BrickObject b : Bricks) {
		DrawingObjectProps temp = b.getDrawingObjectProps();
		objects.push_back(*&temp);
	}
	for (LadderObject l : Ladders) {
		DrawingObjectProps temp = l.getDrawingObjectProps();
		objects.push_back(temp);
	}
	for (EnemyObject b : Enemies) {
		DrawingObjectProps temp = b.getDrawingObjectProps();
		objects.push_back(temp);
	}
	DrawingObjectProps pDrawingProps = Player->getDrawingObjectProps();
	objects.push_back(pDrawingProps);
	for (TimerObject t : Timer) {
		DrawingObjectProps temp = t.getDrawingObjectProps();
		objects.push_back(temp);
	}
	for (LifeObject h : Lifes) {
		DrawingObjectProps temp = h.getDrawingObjectProps();
		objects.push_back(temp);
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
void GameModel::addBrickObject(Vector2f pos, int width, BrickType bType) {
	BrickObject *obj = new BrickObject(Bricks.size(), pos, bType, width);
	obj->setState(VISABLE);
	Bricks.push_back(*obj);
}

void GameModel::addLadderObject(Vector2f pos,int width) {
	LadderObject* obj = new LadderObject(Ladders.size(), pos, width);
	Ladders.push_back(*obj);
}

void GameModel::addLifeObject(Vector2f pos, int width) {
	LifeObject* obj = new LifeObject(Lifes.size(),pos, width);
	Lifes.push_back(*obj);
}

void GameModel::addTimerObject(Vector2f pos, int width, TimerType tType) {
	TimerObject* obj = new TimerObject(Timer.size(),pos,tType, width);
	Timer.push_back(*obj);
}

void GameModel::addEnemyObject(Vector2f pos, int width, EnemyType eType, float speed) {
	EnemyObject* obj = new EnemyObject(Enemies.size(), pos, eType,speed, width);
	Enemies.push_back(*obj);
}

void GameModel::addPlayerObject(Vector2f pos, int width, float speed) {
	Player = new PlayerObject(0, pos, speed, width);
}

/**
 * .
 * 
 * \param object Specific GameObject in the Objects vector
 * \param pos Vector2f where the specific GameObject should be moved to
 */
void GameModel::changeObjPos(ObjectProps o,Vector2f pos) {
	switch (o.type) {
	case BRICK:
		Bricks[o.id].setPos(pos);
		break;
	case LADDER:
		Ladders[o.id].setPos(pos);
		break;
	case PLAYER:
		Player->setPos(pos);
		break;
	case ENEMY:
		Enemies[o.id].setPos(pos);
		break;
	case LIFE:
		Lifes[o.id].setPos(pos);
		break;
	}
}

/**
 * .
 * 
 * \param objectPos Deletes the specific Object in Objects at the given position, sets the Object counter to objectsCount-1 and resizes the Vector
 */
/*void GameModel::deleteObject(int objectPos, std::string objectID) {
	//deleteSprite(Objects[objectPos].getID());
	//Objects.erase(Objects.begin() + objectPos);
	ObjectProps o = StringToProps(objectID);
	switch (o.type) {
	case 'B':
		Bricks.erase(Bricks.begin() + objectPos);
		break;
	case 'L':
		Ladders.erase(Ladders.begin() + objectPos);
		break;
	case 'P':
		Player = NULL;
		break;
	case 'E':
		Enemies.erase(Enemies.begin() + objectPos);
		break;
	case 'H':
		Lifes.erase(Lifes.begin() + objectPos);
		break;
	}
}
*/
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

std::vector<LadderObject> GameModel::getLadders()
{
	return Ladders;
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
			ReplacedBricks.erase(ReplacedBricks.begin() + i);
			Bricks[id].setDugOut(false);
			Bricks[id].setState(VISABLE);
			Bricks[id].resetCounter();
			Bricks[id].setOccupied(false,-1);
			return false;
		}
		i++;
	}
  	Bricks[id].setState(VANISHED);
	Bricks[id].setDugOut(true);
	Bricks[id].setOccupied(false,-1);
	ReplacedBricks.push_back(Bricks[id]);
	return true;
}


void GameModel::setReplacedBrickOccupied(int id, int enemyID){
	std::vector<BrickObject> * rep = &ReplacedBricks;
	for (auto b = rep->begin(); b != rep->end(); ++b) {
		if (b->getID() == id) {
			b->setOccupied(!b->isOccupied(),enemyID);
		}
	}
}

void GameModel::addBrickCounter(int id) {
	if (Bricks[id].getState() == VISABLE) {
		Bricks[id].setState(DIGSTART);
	}
	if (Bricks[id].getState() == DIGSTART && Bricks[id].getCounter() < 3) {
		Bricks[id].addCounter();
		//printf("added Counter to %i\n", Bricks[id].getCounter());
	}
}

void GameModel::lowerBrickCounter(int id) {
	if (Bricks[id].getState() == VANISHED) {
		Bricks[id].setState(DIGSTART);
	}
	if (Bricks[id].getState() == DIGSTART && Bricks[id].getCounter() > 1) {
		Bricks[id].lowerCounter();
		//printf("lowered Counter to %i\n", Bricks[id].getCounter());
	}
}

bool GameModel::isBrickDugOut(int id) {
	return Bricks[id].isDugOut();
}

void GameModel::setEnemyDead(int id) {
	Enemies[id].setState(DEAD);
	Enemies[id].setKilled(true);
}

void GameModel::addEnemyCounter(int id) {
	Enemies[id].addCounter();
}

/**
 * .
 * 
 * \param id ID of the GamObject --> The position of the GameObject in the Objects vector
 * \return GameObject pointer of the found GameObject 
 */
/*
GameObject* GameModel::getObjP(std::string ID)
{
	ObjectProps o = StringToProps(ID);
	switch (o.type) {
	case 'B':
		return &Bricks[o.id];
		break;
	case 'L':
		return &Ladders[o.id];
		break;
	case 'P':
		return Player;
		break;
	case 'E':
		return &Enemies[o.id];
		break;
	case 'H':
		return &Lifes[o.id];
		break;
	}
	return nullptr;
}
*/
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
TimerObject* GameModel::getNextTimer() {
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
 * .
 * For restarting or changing a game level
 */
void GameModel::deleteAll()
{
	//Objects.clear();
	//Sprites.clear();
	Player = nullptr;
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
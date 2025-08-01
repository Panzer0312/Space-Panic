#include "GameController.h"
#include <fstream>
/** X&Y Coordinates match window size --> To check if a GameObject is able to move or would vanish behind window borders*/
const Vector2f boundaries = Vector2f(1800, 1000);
/** Name of Map File */
std::string map1 = "Map1.txt";
/** Player position in Model Vector */
int Player;
/** Pointer to Player GameObject */
GameObject * PlayerPointer;
/** Some Variables to track Game Play */
int playTime, playTimeCounter,air,maxTimers, killedEnemiesCounter, dig_Timer,currPlayerLifes,playerDeaths = 0;
/** Timer before Player dies */
int maxAir = 180;
/** wait = stop GamePlay, redPlayer = Player near Death */
bool wait,redPlayer = false;
/** Wariable to set distance between different sprites in y axis during level instantiation */
int y_Spacing = 32;
/** Wariable to set distance between different sprites in y axis during level instantiation */
int y_correction = 13;
/** Time the player has to dig before brick vanishes */
int max_dig_Timer = 60;
/** Time the Enemy has to wait before it is able to make next decision */
int shortDec = 2;
/** Starting player lifes after each Level change, == 0 -> Player lost */
int startingPlayerLifes = 3;
/** Starting level */
int gLevel = 1;
/** Variable where player facing is saved in during gravitation --> after falling, the player faces to where he went before */
Vector2i player_falling_Face;
/**
 * .
 * \param model Model to save every Game Information
 * \param view View to render Model inforamtion and change it with the implemented Controller Logic
 */
GameController::GameController(GameModel *model,GameView *view)
{
	m = model;
	v = view;
}

/**
 * .
 * \return View got initiaized sucessfully?
 */
int GameController::Init() {
	int i = v->initializeView();
	air = maxAir;
	srand(time(NULL));
	//load test Map
	printf("initializing player");
	initVisualizedTimer();
	visualizePlayerLifes(startingPlayerLifes);
	LoadMap(gLevel);
	//start game loop
	Game();
	return i;
}

/** For testing purposes, returns the current GameModel Pointer */
GameModel* GameController::GetModel() {
	return m;
}
/** For testing purposes, returns the current GameView Pointer */
GameView* GameController::GetView() {
	return v;
}

/**
 * .
 * \param gameLevel Level to instantiate (currently between 1-4)
 */
void GameController::LoadMap(int gameLevel) {
	printf("loading map...");
	std::ifstream mapFile(map1);
	std::string content, line, subLine;
	std::vector<std::string> mapLines;
	std::string delimiter = "|";
	printf("Instantiate Map: %i", gameLevel);

	while (mapFile >> content) {
		mapLines.insert(mapLines.begin(), content);
	}
	for (int i = 0; i < mapLines.size(); i++) {
		line = mapLines[i];
		for (int l = 0; l < gameLevel; l++) {
			int pos = line.find(delimiter);
			subLine = line.substr(0, pos);
			line.erase(0, pos + delimiter.length());
		}
		printf("\n%s , %i", subLine.c_str(), subLine.length());
		LoadLine(subLine, i, 79);
	}
	for (int i = 0; i < mapLines.size(); i++) {
		line = mapLines[i];
		for (int l = 0; l < gameLevel; l++) {
			int pos = line.find(delimiter);
			subLine = line.substr(0, pos);
			line.erase(0, pos + delimiter.length());
		}
		LoadEnemies(subLine, i, 79);
	}
	printf("loading complete...");

}

/**
 * .
 *  (collision, enemy movement etc.)
 *  Here the Controller gets the Player Input, retrieves all GameObjects and sends them to the View to render them
 */
void GameController::Game() {
	int enemyMovementCounter = 0;
	Player = m->findObject("player");
	PlayerPointer = m->getObjP(Player);
	std::string animName;
	printf("starting gameLoop");
	while (!glfwWindowShouldClose(v->window)) {
		if (!wait) {
			playTimeCounter++;
			if (playTimeCounter >= 35) {
				playTime++;
				air--;
				updateTimer();
				//printf("\n%i", playTime);
				playTimeCounter = 0;
			}
			if (air <= 0) {
				//Player Death
				addLevel(false);
			}

			if (Player == NULL|| PlayerPointer == NULL) {
				Player = m->findObject("player");
				PlayerPointer = m->getObjP(Player);
				//printf("Test");
				//printf("%s", PlayerPointer->getName().c_str());
			}

			if (CheckEnemyCollision(Player)) {
				//kill player -> reset stage
				addLevel(false);
			}
			if (PlayerPointer->isFalling()) {
				animName = "Player_Down";
				if (redPlayer) {
					animName = "Red_" + animName;
				}	
				MoveObject(Vector2i(0, -1), "player", animName, true);
			}
			else {
				KeyboardInput(v->window);
			}
			int pPpos = PlayerPointer->getPos().y;
			if (pPpos % 160 == 0 && PlayerPointer->isFalling()) {
				PlayerPointer->setFalling(false);
				if (player_falling_Face == Vector2i(-1, 0)) {
					animName = "Player_Left";
					if (redPlayer) {
						animName = "Red_" + animName;
					}
					animateObject(PlayerPointer, animName);
				}
				else {
					animName = "Player_Right";
					if (redPlayer) {
						animName = "Red_" + animName;
					}
					animateObject(PlayerPointer, animName);
				}
			}
			Gravitation(PlayerPointer);

			if (enemyMovementCounter >= 2) {
				MoveEnemies(PlayerPointer->getPos());
				enemyMovementCounter = 0;
			}
			else {
				enemyMovementCounter++;
			}
			v->RenderScene(changeModelSpritesToViewSprites(m->getSprites()));
		}
		else {
			Player = NULL;
			PlayerPointer = NULL;
		}
	}
	glfwTerminate();
	exit(0);
}

/**
 * .
 * \param modelSprites The sprites from GameModel
 * \return The Sprites to draw in GameView 
 */
std::vector<SpriteBatch::SpriteInfo> GameController::changeModelSpritesToViewSprites(std::vector<GameModel::SpriteInformation> modelSprites) {
	std::vector<SpriteBatch::SpriteInfo> out;
	for (GameModel::SpriteInformation mS : modelSprites) {
		SpriteBatch::SpriteInfo info;
		info.PixelX = mS.PixelX;
		info.PixelY = mS.PixelY;
		info.SpriteCol = mS.SpriteCol; //x
		info.SpriteRow = mS.SpriteRow; //y
		info.SpriteWidth = mS.SpriteWidth;
		out.push_back(info);
	}
	return out;
}

/**
 * . 
 * \param p The GameObject to apply gravitation on (player)
*/
void GameController::Gravitation(GameObject* p) {
	Vector2f currPos = p->getPos();

	if (currPos.y > 1) {
		int i = FindReplacedBrick(currPos);
		if (i != -1) {
			//printf("on replaced brick");
			if (!p->isFalling()) {
				player_falling_Face = p->getFacing();
				float bPos = m->getObjP(i)->getPos().x;
				int x = p->getFacing().x;
				if (x < 0) {
					x = x * 10;
				}
				else {
					x = x * - 10;
				}
				p->setPos(Vector2f(bPos + x, p->getPos().y));
			}
			p->setFalling(true);
		}
	}
}

/**
 * .
 * \param choices Possible decisions enemy is allowed to do
 * \param forcedRandomChoice The choice in choices vector enemy could do to move near the player position
 * \return EnemyDecion --> where the enemy tries to move next
 */
enemyDecision GameController::randomiseChoice(std::vector<enemyDecision> choices, int forcedRandomChoice) {
	int rand = std::rand() % choices.size();
	int rand2 = std::rand() % choices.size();
	int rand3 = std::rand() % choices.size();
	if (forcedRandomChoice > -1 && forcedRandomChoice < choices.size())
	{
		if (rand == forcedRandomChoice || rand2 == forcedRandomChoice|| rand3 == forcedRandomChoice) {
			return choices[forcedRandomChoice];
		}
	}
	return choices[rand];

}

/**
 * .
 * \param curr The Current enemy decision
 * \param from The Enemy position
 * \param to The Player position
 * \return The next enemy decision
 */
enemyDecision GameController::calcEnemyDecision(enemyDecision curr, Vector2f from, Vector2f to) {
	int diff = int(from.y) % 160;
	int rand = std::rand();
	int nextLadderposUp, nextPosDown;
	switch (curr) {
	case LADDERUP:
		nextLadderposUp = findObjectPosOver(LADDER, from);
		//more up or change dec?
		if (diff > 140) {
			if (nextLadderposUp != -1) {
				return randomiseChoice({ LEFT,RIGHT,LADDERUP }, -1);
			}
			return randomiseChoice({LEFT,RIGHT},-1);
		}
		return LADDERUP;
		break;
	case LADDERDOWN:
		nextPosDown = FindObjectPosUnder(BRICK, from, Vector2i(25, 25));
		if (nextPosDown != -1) {
			return randomiseChoice({ LEFT,RIGHT}, -1);
		}
		//more down or change dec?
		if (diff < 15) {
			if (nextPosDown == -1) {
				return randomiseChoice({ LEFT,RIGHT,LADDERDOWN }, -1);
			}
			return randomiseChoice({ LEFT,RIGHT }, -1);
		}
		return LADDERDOWN;
		break;

	default:
		nextPosDown = FindObjectPosUnder(BRICK, from,Vector2i(15,35));
		nextLadderposUp = findObjectPosOver(LADDER, from);
		//left/right walking and then found ladder
		std::vector<enemyDecision> choices = {LEFT,RIGHT};
		if (nextPosDown == -1 && from.y >1) {
			//printf("\nLadderD");
			choices.push_back(LADDERDOWN);
		}
		if (nextLadderposUp != -1) {
			if (from.y / 160 < 5) {
				//printf("\nLadderU");
				choices.push_back(LADDERUP);
			}
		}

		//force randomise for better enemy movement
		if (from.y - 2 < to.y && from.y + 2 > to.y) {
			return randomiseChoice(choices, rand%2);
		}
		else if (from.y > to.y) {
			if (choices.size() > 2 && choices[2] == LADDERDOWN) {
				return randomiseChoice(choices, 2);
			}
			return randomiseChoice(choices, rand % 2);
		}
		else {
			if (choices.size() > 2 && choices[2] == LADDERUP) {
				return randomiseChoice(choices, 2);
			}
			return randomiseChoice(choices, rand % 2);
		}

		break;
	}

	return RIGHT;

}
/**
 * .
 */
void GameController::initVisualizedTimer() {
	int i = 0;
	for (int x = 300; x < boundaries.x - 300;x= x +20) {
		if (x<1200) {
			m->addObject(Vector2f(x, 1000), Vector2i(3, 0), 70, "timer1", 15, TIMER);
		}
		else {
			m->addObject(Vector2f(x, 1000), Vector2i(4, 0), 70, "timer2", 15, TIMER);
		}
		i++;
	}
	maxTimers = i;
	//printf("\nTimer Count : %i", m->timerCount());
}
/**
 * .
 */
void GameController::updateTimer() {
	int currTimers = m->timerCount();
	float ratio = maxTimers/(float)maxAir;
	int nextTimer = ratio * air;
	int t = currTimers - nextTimer;

	for (; t > 0; t--) {
		GameObject* timer = m->getNextTimer();
		int timerInt = timer->getID();
		if (timer->getName().at(5) == '2') {
			redPlayer = true;
			//printf("RED");
		}
		m->changeSpriteSheet(timerInt, Vector2i(2, 0));
		m->removeNextTimer();
	}
	
}

/**
 * .
 * \param dec The decision the alien has done
 * \return Vector in which direction the alien will be moving in
 */
Vector2i GameController::translateEnemyDec(enemyDecision dec) {
	Vector2i dir;
	switch (dec) {
	case LADDERUP:
		dir = Vector2i(0, 1);
		break;
	case LADDERDOWN:
		dir = Vector2i(0, -1);
		break;
	case LEFT:
		dir = Vector2i(-1, 0);
		break;
	case RIGHT:
		dir = Vector2i(1, 0);
		break;
	}
	return dir;
}

/**
 * .
 * \param to The player position
 */
void GameController::MoveEnemies(Vector2f to) {
	int movingEnemies = 0;
	for (GameObject object : m->getEnemies()) {
		std::string animName = "Enemy_Walk";
		GameObject* o = m->getObjP(object.getID());
		if (!o->iskilled()) {
			movingEnemies++;
			bool pauseMove = false;
			int dec = o->getDecisionCounter() + 1;
			o->setDecisionCounter(dec);

			Vector2f currPos = o->getPos();
			enemyDecision currDec = o->getDecision();

			//printf("\nTEST %f,%f", currPos.x, currPos.y);

			int space = FindReplacedBrick(currPos);
			if (space != -1) {
				//at space pos
				animName = "Enemy_PushUp";
				//printf("\nIM FLYING!!!");
				pauseMove = true;
				//printf("%i pu", o->getPushUps());
				if (o->getPushUps() >= 20) {
					//printf("\nPUSHING");
					animateObject(o, animName + o->getName().at(5));
				}
				else {
					animName = "Enemy_Hanging";
					animateObject(o, animName + o->getName().at(5));
				}

				if (!o->isFalling()) {
					m->changeObjPos(o->getID(), m->getObjects()[space].getPos() - Vector2f(8, 12));
					o->setFalling(true);
				}
				else {
					int diff = (int(currPos.y) - 12) % 160;
					if (diff - 150 >= 0) {
						o->setFalling(false);
						int times = float(currPos.y) / 160;
						int face;
						if (currPos.x < boundaries.x / 2) {
							face = 50;
							currDec = RIGHT;
						}
						else {
							face = -50;
							currDec = LEFT;
						}
						o->setDecision(currDec);
						m->changeObjPos(o->getID(), Vector2f(currPos.x + face, times * 160));
						o->setPushUps(0);
					}
				}
				o->resetDecisionCounter();
			}
			else {
				if (o->isFalling()) {
					//Kill enemy
					//printf("\nenemy got killed\n");
					o->setKilled(true);
					killedEnemiesCounter++;
					m->changeObjPos(o->getID(),boundaries + Vector2f(100,100));
				}
			}
			if (currPos.x + 16 > boundaries.x) {
				//go left
				currDec = LEFT;
				o->resetDecisionCounter();
			}
			else if (currPos.x - 16 < 0) {
				//go right
				currDec = RIGHT;
				o->resetDecisionCounter();
			}


			//Hier fehlt wenn gegner im Loch dann darf n�chster gegner nicht auch noch rein!! 

			enemyDecision newDec;
			int l = GetObjectAtPos(LADDER, currPos);
			if (l != -1) {
				//printf("\nl!=-1");
				if (dec > shortDec) {
					//on Ladder/ standing in front of ladder
					//printf("\enemy found ladder");
					newDec = calcEnemyDecision(currDec, currPos, to);
					if (currDec == LADDERUP || currDec == LADDERDOWN) {
						if (newDec == LEFT || newDec == RIGHT) {
							int times = currPos.y / 160;
							int diff = int(currPos.y) % 160;
							Vector2f temp;
							if (diff > 140) {
								temp = Vector2f(currPos.x, (times + 1) * 160);
							}
							else {
								temp = Vector2f(currPos.x, times * 160);
							}

							m->changeObjPos(o->getID(), temp);
							pauseMove = true;
						}
						else {
							int lu = findObjectPosOver(LADDER, currPos);
							if (newDec == LADDERUP && lu == -1) {
								newDec = randomiseChoice({LADDERDOWN,LEFT,RIGHT},-1);
							}
						}
					}
					o->resetDecisionCounter();
					currDec = newDec;
				}

			}
			else {
				//printf("\nL==-1");
			}

			//printf("\ndecision %i,%i", translateEnemyDec(currDec).x, translateEnemyDec(currDec).y);
			o->setDecision(currDec);
			if (!pauseMove) {
				MoveObject(translateEnemyDec(currDec), o->getName(), animName + o->getName().at(5), false);
			}
		}
	}
	if (movingEnemies == 0) {
		printf("\n YOU WON THIS MAP");
		addLevel(true);
	}
}

/**
 * .
 * \param Lifes the current player lifes
 */
void GameController::visualizePlayerLifes(int lifes) {
	currPlayerLifes = lifes;
	for (int i = 0; i < lifes; i++) {
		int model = m->addObject(Vector2f(i*80, 985), Vector2i(1, 0), 100, "life", 15, LIFE);
		GameObject* obj = m->getObjP(model);
		animateObject(obj, "Life_Change");
	}
}

/**
 * .
 * \param next If true then load next level else restart current level 
 */
void GameController::addLevel(bool next) {
	wait = true;
	Player = NULL;
	PlayerPointer = NULL;
	redPlayer = false;
	m->deleteAll();
	if(next){
		gLevel++;
	}
	else {
		currPlayerLifes--;
	}

	if (gLevel < 5) {
		if (currPlayerLifes > 0) {
			air = maxAir;
			initVisualizedTimer();
			if (next) {
				visualizePlayerLifes(startingPlayerLifes);
			}
			else {
				visualizePlayerLifes(currPlayerLifes);
			}
			LoadMap(gLevel);
			Player = m->findObject("player");
			PlayerPointer = m->getObjP(Player);
			//printf("\n%s", PlayerPointer->getName().c_str());
			wait = false;
			//m->changeSpriteSheet(Player, Vector2i(0, 3));
		}
		else {
			//no lifes left
			glfwDestroyWindow(v->window);

			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n|--------------------------------------------|");
			printf("\n|--------------------------------------------|");
			printf("\n|--------------------------------------------|");
			printf("\n|--------------------------------------------|");
			printf("\n|--------------!!!YOU DIED!!!----------------|");
			printf("\n|--------------------------------------------|");
			printf("\n|--------------------------------------------|");
			printf("\n|---------!!!TRY AGAIN NEXT TIME!!!----------|");
			printf("\n|--------------------------------------------|");
			printf("\n|--------------------------------------------|");
			printf("\n|--------------------------------------------|");
			printf("\n|--------------------------------------------|");
			printf("\n|--------------------------------------------|\n\n\n\n\n\n\n\n\n");
		}
	}
	else {
		glfwDestroyWindow(v->window);

		int random = rand() % 20 + 10;
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n|--------------------------------------------|");
		printf("\n|--------------------------------------------|");
		printf("\n|--------------------------------------------|");
		printf("\n|--------------------------------------------|");
		printf("\n|------------!!!CONGRATULATIONS!!!-----------|");
		printf("\n|--------------------------------------------|");
		printf("\n|--------------------------------------------|");
		printf("\n|---------!!!YOU FINISHED THE GAME!!!--------|");
		printf("\n|--------------------------------------------|");
		printf("\n|--------------------------------------------|");
		printf("\n|------------YOUR TOTAL SCORE IS:------------|");
		printf("\n|--------------------%i---------------------|", ((killedEnemiesCounter * random)- (playTime / ((playerDeaths+1)*10))) * 10);
		printf("\n|--------------------------------------------|");
		printf("\n|--------------------------------------------|");
		printf("\n|--------------------------------------------|");
		printf("\n|--------------------------------------------|\n\n\n\n\n\n\n\n\n");
	}
}

/**
 * .
 * \param dir Direction to move to
 * \param name Name of the Object
 * \param animation Animation to play while moving the Object
 * \param force If true, the object is allowed to move freely without constraints of ladders/bricks
 * \return Object position has changed or not
 */
bool GameController::MoveObject(Vector2i dir, std::string name, std::string animation,bool force)
{
	int objID = m->findObject(name);
	GameObject *obj = m->getObjP(objID);
	int speed = obj->getSpeed();
	Vector2f currPos = obj->getPos();
	Vector2f newPos = currPos + dir*speed;
	m->changeObjectFacing(objID, dir);


	animateObject(obj, animation);

	if (newPos < boundaries && newPos.x >=0 && newPos.y >= 0){
		if (!force) {
			if (CheckWalk(currPos, newPos, dir, *obj)) {
				if (dir.x == 0 && (int(currPos.y)%160 >155 || int(currPos.y) % 160 < 15)) {
					int id = GetObjectAtPos(LADDER, newPos);
					m->changeObjPos(objID, Vector2f(m->getObjP(id)->getPos().x-15,newPos.y));
				}
				else {
					m->changeObjPos(objID, newPos);
				}
				return true;
			}
			else {
				return false;
			}
		}
		else {
			m->changeObjPos(objID, newPos);
			return true;
		}
	}
	return false;
}

/**
 * .
 * \param in String to instantiate GameObjects from
 * \param stage On which y position (y * 26) to place the objects
 * \param spacing How much space should be left between the GameObjects
 */
void GameController::LoadLine(std::string in, int stage, int spacing) {
	//classic = 5 stages with 24 tiles
	int x = 0;	
	GameObject* object;
	for (char c : in) {
		switch (c) {
		case 'b':
			//brick
			if (x % 2) {
				m->addObject(Vector2f(x*spacing, y_Spacing *stage- y_correction), Vector2i(15, 1), 108, "brick1" + std::to_string(x),0,BRICK);
			}
			else {
				m->addObject(Vector2f(x*spacing, y_Spacing *stage- y_correction), Vector2i(14, 1), 108, "brick2" + std::to_string(x), 0, BRICK);
			}
			break;
		case 'l':
			//ladder
			m->addObject(Vector2f(x * spacing+15, y_Spacing * stage), Vector2i(0, 0), 80, "ladder" + std::to_string(x), 0, LADDER);
			break;
		case '#':
			//nothing but replace lost bricks at level 4,9,14,19,24
			if (stage >0 && stage % 5 == 4) {
				int t = 0;
				if (x % 2) {
					t = m->addObject(Vector2f(x * spacing, y_Spacing * stage - y_correction), Vector2i(15, 1), 108, "brick1" + std::to_string(x), 0, BRICK);
					object = m->getObjP(t);
					animateObject(object, "Brick_1_Change");
					//printf("\nreplaced brick at: %f,%f\n", object->getPos().x, object->getPos().y);
				}
				else {
					t = m->addObject(Vector2f(x * spacing, y_Spacing * stage - y_correction), Vector2i(14, 1), 108, "brick2" + std::to_string(x), 0, BRICK);
					object = m->getObjP(t);
					animateObject(object, "Brick_2_Change");
					//printf("\nreplaced brick at: %f,%f\n", object->getPos().x, object->getPos().y);
				}
				m->addReplacedBrick(t);
			}

			break;
		}
		x++;
	}

}

/**
 * .
 * \param line String of a level stage
 * \param stage The specific stage 
 * \param spacing The amount of how far the aliens should be drawn away from each other
 */
void GameController::LoadEnemies(std::string line, int stage, int spacing) {
	int x = 0;
	for (char c : line) {
		//enemy
		if (c == 'e') {
			printf("\nLOADING ENEMY");
			int i = rand()%2;
			if (i == 0) {
				m->addObject(Vector2f(x * spacing, y_Spacing * stage), Vector2i(0, 1), 120, "enemy1" + std::to_string(x), 15, ENEMY);
			}
			else {
				m->addObject(Vector2f(x * spacing, y_Spacing * stage), Vector2i(7, 1), 120, "enemy2" + std::to_string(x), 15, ENEMY);
			}
	
		}
		else if (c == 'p') {
			//init player
			m->addObject(Vector2f(x * spacing, y_Spacing * stage), Vector2i(0, 3), 120, "player", 5, PLAYER);
		}
		x++;
	}
}

/**
 * .
 * \param currPos Current Postion of the GameObject
 * \param nextPos Position where the Object should be moved to
 * \param dir Direction in which the Object should be moved to
 * \param object The GameObject which should be moved
 * \return The Object is able to move
 */
bool GameController::CheckWalk(Vector2f currPos, Vector2f nextPos,Vector2i dir, GameObject object) {
	bool out = false;

	if (dir == Vector2i(0, 1)) {//standing in front of ladder for y movement
		int id = GetObjectAtPos(LADDER, nextPos);
		if (id != -1) {
			out = true;
		}
	}else if (dir == Vector2i(0, -1)) {
		int id = GetObjectAtPos(LADDER, nextPos);
		int test = GetObjectAtPos(BRICK, nextPos -Vector2f(5,5)); //to correct slight offset of getObjectAtPos
		if (id != -1 && test == -1) {
			out = true;
		}
	}else{	//standing on brick or y <= 1 for x movement
		int id = GetObjectAtPos(LADDER, currPos);
		int diff = int(nextPos.y) % 160;
		int times = nextPos.y / 160;
		if (id != -1) {
			if (diff < 40) {
				m->changeObjPos(m->findObject(object.getName()), Vector2f(nextPos.x, times * 160));
				out = false;
			}
			else if (diff >135) {
				m->changeObjPos(m->findObject(object.getName()), Vector2f(nextPos.x, (times+1) * 160));
				out = false;
			}
		}
		else {
			out = true;
		}
	}
	return out;
}

/**
 * .
 * \param player The player object ID
 * \return Is true if player is inside an alien position 
 */
bool GameController::CheckEnemyCollision(int player) {
	Vector2f pos = m->getObjects()[player].getPos();
	int i = GetCollisionAtPos(ENEMY, pos);
	if (i != -1) {
		//printf("\ncollided with enemy!!!");
		return true;
	}
	return false;
}

/**
 * .
 * \param object The GameObject Pointer to animate
 * \param name The name of the animation
 */
void GameController::animateObject(GameObject *object, std::string name) {
	if (object->getCurrAnimName().compare(name) > 0 || object->getCurrAnimName().compare(name) < 0) {
		*object->getCurrCounter() = 0;
		*object->getCurrAnim() = 0;
		object->changeCurrAnimName(name);
	}
	int currAnimInt = *object->getCurrAnim();
	Vector2i animV = v->nextAnimation(object->getCurrAnim(), object->getCurrCounter(), name);
	m->changeSpriteSheet(object->getID(), animV);

	if (currAnimInt != *object->getCurrAnim() && object->getType() == ENEMY && object->isFalling()) { //animate enemy pulling itself out of hole
		if (object->getPushUps() >= 20) {
			m->changeObjPos(object->getID(), object->getPos() + Vector2f(0, 6));
		}
		else {
			object->setPushUps(object->getPushUps() + 1);
		}
	}

}

/**
 * .
 * \param The specific brick GameObject 
 */
void GameController::dig(GameObject* brick) {
	char anim = brick->getName().at(5);
	//printf("%c",anim);
	if (anim == '1') {
		animateObject(brick, "Brick_1_Change");
	}
	else {
		animateObject(brick, "Brick_2_Change");
	}
	m->addReplacedBrick(brick->getID());
}

/**
 * .
 * \param continuing If the player continues to press nothing other than the digging key
 */
void GameController::digging(bool continuing) {
	if (continuing) {
		if (dig_Timer < max_dig_Timer) {
			dig_Timer++;
		}
		else {
			//change Block 
			dig_Timer = 0;

			int objID = m->findObject("player");
			GameObject* obj = m->getObjP(objID);
			//printf("\n\nDIGGING BLOCk at pos: (%f,%f)", obj->getPos().x, obj->getPos().y );
			int brickUnderPos = FindReplacedBrick(obj->getPos()+obj->getFacing()*35);
			if (brickUnderPos != -1) {
				GameObject* brick = m->getObjP(brickUnderPos);
				dig(brick);
			}
			else {
				brickUnderPos = FindObjectPosUnder(BRICK,obj->getPos() + obj->getFacing() * 45, Vector2i(35, 35));
				if (brickUnderPos != -1) {
   					GameObject* brick = m->getObjP(brickUnderPos);
					dig(brick);
				}
				else {
					//printf("\nnot over a brick\n");
				}
			}
		}
	}
	else {
		dig_Timer = 0;
	}
}

/**
 * .
 * \param window From which window the input should be
 */
void GameController::KeyboardInput(GLFWwindow* window)
{
	std::string playerAnim;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		//std::cout << "UP" << std::endl;
		playerAnim ="Player_Up";
		if (redPlayer) {
			playerAnim = "Red_" + playerAnim;
		}

		MoveObject(Vector2i(0, 1),"player", playerAnim,false);
		digging(false);
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		//std::cout << "LEFT" << std::endl;
		playerAnim = "Player_Left";
		if (redPlayer) {
			playerAnim = "Red_" + playerAnim;
		}

		MoveObject(Vector2i(-1, 0), "player", playerAnim,false);
		digging(false);
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		//std::cout << "DOWN" << std::endl;
		playerAnim = "Player_Up";
		if (redPlayer) {
			playerAnim = "Red_" + playerAnim;
		}

		MoveObject(Vector2i(0, -1), "player", playerAnim, false);
		digging(false);
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		//std::cout << "RIGHT" << std::endl;
		playerAnim = "Player_Right";
		if (redPlayer) {
			playerAnim = "Red_" + playerAnim;
		}

		MoveObject(Vector2i(1, 0), "player", playerAnim, false);
		digging(false);
	}
	else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		//std::cout << "SPACE" << std::endl;
		int objID = m->findObject("player");
		GameObject *obj = m->getObjP(objID);
		if (obj->getFacing() == Vector2i(-1, 0)) {
			playerAnim = "Player_Shovel_Left";
			if (redPlayer) {
				playerAnim = "Red_" + playerAnim;
			}

			animateObject(obj, playerAnim);

		}
		else {
			playerAnim = "Player_Shovel_Right";
			if (redPlayer) {
				playerAnim = "Red_" + playerAnim;
			}

			animateObject(obj, playerAnim);
		}
		digging(true);
	}

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		std::cout << "EXITING GAME" << std::endl;
		glfwDestroyWindow(window);
		glfwTerminate();
		exit(0);
	}

}

/**
 * .
 * \param type Which type the Object to return has to be
 * \param pos Position where the GameObject in the GameModel's objects vector has to be
 * \return The ID of the found GameObject or -1
 */
int GameController::GetObjectAtPos(objectType type, Vector2f pos) {
	
	for (GameObject o : m->getObjects()) {
		if (o.getType() == type) {
			if (o.getPos().y + 20 > pos.y && o.getPos().y - 20 < pos.y) {
				if (o.getPos().x + 15 > pos.x && o.getPos().x - 35 < pos.x) {
					return o.getID();
				}
				//printf("\nobject at %f , %f", o.getPos().x, o.getPos().y)
			}
		}
	}
	return  -1;
}

/**
 * .
 * \param type Which type the Object to return has to be
 * \param pos Position where the GameObject in the GameModel's objects vector has to be
 * \return The ID of the found GameObject or -1
 */
int GameController::GetCollisionAtPos(objectType type, Vector2f pos) {
	for (GameObject o : m->getObjects()) {
		if (o.getType() == type) {
			if (o.getPos() + Vector2f(80, 1) > pos && o.getPos() - Vector2f(80, 1) < pos) {
				return o.getID();
			}
		}
	}
	return  -1;
}

/**
 * .
 * \param pos Position where the GameObject in the GameModel's replacedBricks vector has to be
 * \return The ID of the found GameObject or -1
 */
int GameController::FindReplacedBrick(Vector2f pos)
{
	for (GameObject o : m->getReplacedBricks()) {
		if (pos.y - 55 <= o.getPos().y&& pos.y+15>= o.getPos().y) {
			if (pos.x - 25 <= o.getPos().x && pos.x + 25 > o.getPos().x) {
				return o.getID();
			}
		}
	}
	return -1;
}

/**
 * .
 * \param type Which type the Object to return has to be
 * \param pos Position where the GameObject in the GameModel's objects vector has to be
 * \param bounds The bounds in which the GameObject to be
 * \return The ID of the found GameObject or -1
 */
int GameController::FindObjectPosUnder(objectType type,Vector2f pos,Vector2i bounds) {
	for (GameObject o : m->getObjects()) {
		if (o.getType() == type) {
			if (pos.y - 50 <= o.getPos().y && pos.y+5 >= o.getPos().y) {
				if (pos.x - bounds.x <= o.getPos().x && pos.x + bounds.y > o.getPos().x) {
					return o.getID();
				}
			}
		}
	}
	return -1;
}

/**
 * .
 * \param type Which type the Object to return has to be
 * \param pos Position where the GameObject in the GameModel's objects vector has to be
 * \return The ID of the found GameObject or -1
 */
int GameController::findObjectPosOver(objectType type, Vector2f pos) {
	for (GameObject o : m->getObjects()) {
		if (o.getType() == type) {
			if (pos.y + 25 <= o.getPos().y && pos.y+80 >= o.getPos().y) {
				if (o.getPos().x + 50 > pos.x && o.getPos().x - 50 < pos.x) {
					return o.getID();
				}
			}
		}
	}
	return -1;
}

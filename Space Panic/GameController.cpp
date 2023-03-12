#include "GameController.h"
#include <fstream>
/** X&Y Coordinates match window size --> To check if a GameObject is able to move or would vanish behind window borders*/
const Vector2f boundaries = Vector2f(1800, 1000);
/** Name of Map File */
std::string map1 = "Map1.txt";
std::string testMap = "TestMap1.txt";
/** Player position in Model Vector */
//int Player;
/** Pointer to Player GameObject */
//GameObject * PlayerPointer;
/** Some Variables to track Game Play */
int playTime, playTimeCounter, air, maxTimers, killedEnemiesCounter, dig_Timer, currPlayerLifes, playerDeaths = 0;
/** Timer before Player dies */
int maxAir = 180;
/** wait = stop GamePlay, redPlayer = Player near Death */
bool wait, redPlayer = false;
/** Wariable to set distance between different sprites in y axis during level instantiation */
int y_Spacing = 32;
/** Wariable to set distance between different sprites in y axis during level instantiation */
int y_correction = 13;
/** Time the player has to dig before brick vanishes */
int max_dig_Timer = 75;
int max_waitTime = 3;
int waitTimer = 0;
/** Time the Enemy has to wait before it is able to make next decision */
int shortDec = 2;
/** Starting player lifes after each Level change, == 0 -> Player lost */
int startingPlayerLifes = 3;
/** Starting level */
int gLevel = 1;
/** How many level exist */
int levelCount = 4;
/** Variable where player facing is saved in during gravitation --> after falling, the player faces to where he went before */
Vector2i player_falling_Face;
bool onlyGreen = true;
int testTimer = 0;
int maxNextLevelTimer =100;
int nextLeveltimer = 0;
/**
 * TODO:
 * Collision Width / 2
 *
 */


 /**
  * .
  * \param model Model to save every Game Information
  * \param view View to render Model inforamtion and change it with the implemented Controller Logic
  */
GameController::GameController(GameModel* model, GameView* view)
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
	std::ifstream mapFile(testMap);
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
	//Player = m->findObject("player");
	PlayerObject* PlayerPointer = m->getPlayer();
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
			if (air <= 0 || CheckEnemyCollision()) {
				//Player Death
				m->getPlayer()->setState(DEAD);
				addLevel(false);
			}

			if (!m->getPlayer()->isFalling() && m->getPlayer()->getDecision() == FALLING) {
				m->getPlayer()->setDecision(NOTHING);
			}

			if (m->getPlayer()->isFalling()) {
				m->getPlayer()->setDecision(FALLING);
				MoveObject(Vector2i(0, -1), m->getPlayer(), true);
			}
			else {
				KeyboardInput(v->window);
			}
			int pPpos = m->getPlayer()->getPos().y;
			if (pPpos % 160 == 0 && m->getPlayer()->isFalling()) {
				m->getPlayer()->setFalling(false);

			}
			Gravitation(m->getPlayer());

			if (enemyMovementCounter >= 2) {
				MoveEnemies(m->getPlayer()->getPos());
				enemyMovementCounter = 0;
			}
			else {
				enemyMovementCounter++;
			}
			v->RenderScene(m->getDrawingInformation());
		}
	}
	glfwTerminate();
	exit(0);
}



/**
 * .
 * \param p The GameObject to apply gravitation on (player)
*/
void GameController::Gravitation(ControllableObject* p) {
	Vector2f currPos = p->getPos();

	if (currPos.y > 1) {
		BrickObject* i = FindBrick(currPos + Vector2f(55, 0), 1, true);
		if (i) {
			//printf("on replaced brick");
			if (!m->getPlayer()->isFalling()) {
				player_falling_Face = p->getFacing();
				float bPos = i->getPos().x;
				int x = p->getFacing().x;
				if (x < 0) {
					x = x * 5;
				}
				else {
					x = x * -5;
				}
				p->setPos(Vector2f(bPos + x, p->getPos().y));
			}
			p->setFalling(true);
			p->setDecision(FALLING);
		}
	}
}

/**
 * .
 * \param choices Possible decisions enemy is allowed to do
 * \param forcedRandomChoice The choice in choices vector enemy could do to move near the player position
 * \return EnemyDecion --> where the enemy tries to move next
 */
ControlledObjectDecision GameController::randomiseChoice(std::vector<ControlledObjectDecision> choices, int forcedRandomChoice) {
	int rand = std::rand() % choices.size();
	int rand2 = std::rand() % choices.size();
	int rand3 = std::rand() % choices.size();
	if (forcedRandomChoice > -1 && forcedRandomChoice < choices.size())
	{
		if (rand == forcedRandomChoice || rand2 == forcedRandomChoice || rand3 == forcedRandomChoice) {
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
ControlledObjectDecision GameController::calcEnemyDecision(ControlledObjectDecision curr, Vector2f from, Vector2f to, int width) {
	int diff = int(from.y) % 160;
	int rand = std::rand();
	LadderObject* nextLadderUp;
	BrickObject* nextBrickDown;
	switch (curr) {
	case LADDERUP:
		nextLadderUp = FindLadder(from, 32);
		//more up or change dec?
		if (diff > 140) {
			if (nextLadderUp) {
				return randomiseChoice({ LEFT,RIGHT,LADDERUP }, -1);
			}
			return randomiseChoice({ LEFT,RIGHT }, -1);
		}
		return LADDERUP;
		break;
	case LADDERDOWN:
		nextBrickDown = FindBrick(from + Vector2f(0, -width), width, false); //FindObjectPosUnder bounds:(25,25)
		if (nextBrickDown) {
			return randomiseChoice({ LEFT,RIGHT }, -1);
		}
		//more down or change dec?
		if (diff < 15) {
			if (!nextBrickDown) {
				return randomiseChoice({ LEFT,RIGHT,LADDERDOWN }, -1);
			}
			return randomiseChoice({ LEFT,RIGHT }, -1);
		}
		return LADDERDOWN;
		break;

	default:
		nextBrickDown = FindBrick(from, 32, false); //FindObjectPosUnder bounds:(15,35)
		nextLadderUp = FindLadder(from, 32);
		//left/right walking and then found ladder
		std::vector<ControlledObjectDecision> choices = { LEFT,RIGHT };
		if (!nextBrickDown && from.y > 1) {
			//printf("\nLadderD");
			choices.push_back(LADDERDOWN);
		}
		if (nextLadderUp) {
			if (from.y / 160 < 5) {
				//printf("\nLadderU");
				choices.push_back(LADDERUP);
			}
		}

		//force randomise for better enemy movement
		if (from.y - 2 < to.y && from.y + 2 > to.y) {
			return randomiseChoice(choices, rand % 2);
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
	for (int x = 300; x < boundaries.x - 300; x = x + 20) {
		if (x < 1200) {
			m->addTimerObject(Vector2f(x, 1000), 70, TIMER0); //Vector2i(3, 0)
		}
		else {
			m->addTimerObject(Vector2f(x, 1000), 70, TIMER1); //Vector2i(4, 0)
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
	float ratio = maxTimers / (float)maxAir;
	int nextTimer = ratio * air;
	int t = currTimers - nextTimer;

	for (; t > 0; t--) {
		TimerObject* timer = m->getNextTimer();
		int timerInt = timer->getID();
		if (timer->getObjectProps().closerType == TIMER1) {
			redPlayer = true;
			m->getPlayer()->setState(AIRLESS);
			//printf("RED");
		}

		//m->changeSpriteSheet(timerInt, Vector2i(2, 0)); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		m->removeNextTimer();
	}

}

/**
 * .
 * \param dec The decision the alien has done
 * \return Vector in which direction the alien will be moving in
 */
Vector2i GameController::translateEnemyDec(ControlledObjectDecision dec) {
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
	std::vector<EnemyObject>* enemies = m->getEnemies();
	for (auto o = enemies->begin(); o != enemies->end(); ++o) {
		//std::string animName = "Enemy_Walk";
		//EnemieObject* o = m->getObjP(object.getID());
		if (!o->iskilled()) {
			movingEnemies++;
			bool pauseMove = false;
			int dec = o->getDecisionCounter() + 1;
			o->setDecisionCounter(dec);
			Vector2f currPos = o->getPos();
			ControlledObjectDecision currDec = o->getDecision();
			//printf("%i\n", currDec);
			//printf("\nTEST %f,%f", currPos.x, currPos.y);
			Vector2f dir = currPos + translateEnemyDec(currDec) * 40 - Vector2f(0, 10);
			int width = 32;
			//printf("%f,%f\n", dir.x,dir.y);
			if (currDec == 4) {
				dir = dir + Vector2f(15, 0);
				width = 64;
			}
			BrickObject* spaceToFall = FindBrick(currPos, 32, true);
			BrickObject* spaceToOccupy = FindBrick(dir, width, true);
			if (spaceToOccupy && spaceToOccupy->isOccupied()) {
				pauseMove = true;
			}
			if (spaceToFall) {
				//m->getBricks()[space->getID()].setOccupied(true);
				//printf("testSPACE");
				//at space pos
				//animName = "Enemy_PushUp";
				//printf("\nIM FLYING!!!");
				pauseMove = true;
				if (!spaceToFall->isOccupied() || o->isFalling()) { 
					int spaceToFallId = spaceToFall->getID();
					Vector2f spaceToFallPos = spaceToFall->getPos();
					//printf("%i pu", o->getPushUps());
					//printf("brick id: %i", space->getID());
					if (o->getPushUps() >= 80) {
						o->setDecision(PUSHUP);
						m->changeObjPos(o->getObjectProps(), currPos + Vector2f(0, 4));
						m->addEnemyCounter(o->getID());
					}
					else if(o->isFalling()){
						o->setPushUps(o->getPushUps()+1);
						//animName = "Enemy_Hanging";
			//			animateObject(o, animName + o->getName().at(5));
					}

					m->addEnemyCounter(o->getID());
					if (o->getDecision() != HANGING && !o->isFalling() && o->getDecision() != PUSHUP) {
						if (o->getFeltInBrickID() == spaceToFallId || o->getFeltInBrickID() == -1) {
							m->changeObjPos(o->getObjectProps(), spaceToFallPos - Vector2f(8, 12));
							o->setFeltInBrickID(spaceToFallId);
							o->setDecision(HANGING);
							o->setFalling(true);
							m->setReplacedBrickOccupied(spaceToFallId, o->getID());
						}
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
							BrickObject b = m->getBricks()[o->getFeltInBrickID()];
							m->changeObjPos(o->getObjectProps(), Vector2f(currPos.x + face, times * 160));
							o->setFeltInBrickID(-1);
							o->setPushUps(0);
							m->addReplacedBrick(b.getID());
						}
					}
					o->resetDecisionCounter();
				}
				if (o->getState() == DEAD) {
					//Kill enemy
					//printf("\nenemy got killed\n");
					o->setFeltInBrickID(-1);
					o->setKilled(true);
					killedEnemiesCounter++;
					m->changeObjPos(o->getObjectProps(), boundaries + Vector2f(100, 100));
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

			//printf("currDec: %i\n", currDec);
			//Hier fehlt wenn gegner im Loch dann darf nächster gegner nicht auch noch rein!! 

			ControlledObjectDecision newDec;
			LadderObject* l = FindLadder(currPos, 16);
			if (l) {
				//printf("\nl!=-1");
				if (dec > shortDec) {
					//on Ladder/ standing in front of ladder
					//printf("\enemy found ladder");
					newDec = calcEnemyDecision(currDec, currPos, to, 45);

					//printf("newDec: %i", newDec);
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

							m->changeObjPos(o->getObjectProps(), temp);
							pauseMove = true;
						}
						else {
							l = FindLadder(currPos + Vector2f(0, 15), 16);
							if (newDec == LADDERUP && !l) {
								newDec = randomiseChoice({ LADDERDOWN,LEFT,RIGHT }, -1);
							}
						}
					}
					o->resetDecisionCounter();
					currDec = newDec;
				}

			}
			if (o->getDecision() != HANGING && o->getDecision()!=PUSHUP) {
				//printf("\ndecision %i,%i", translateEnemyDec(currDec).x, translateEnemyDec(currDec).y);
				o->setDecision(currDec);

				if (!pauseMove) {
					MoveObject(translateEnemyDec(currDec), &*o, false);
					m->addEnemyCounter(o->getID());
				}
			}
		}
		else if (o->getState() == DEAD) {
			Vector2f pos = o->getPos();
			m->changeObjPos(o->getObjectProps(), o->getPos() - Vector2f(0,4));
			
			BrickObject* b = FindBrick(pos,32,true);
			int id = -1;
			if (b) {
				id = b->getID();
				m->addReplacedBrick(id);
			}
			EnemyType eType = o->getEnemyType();
			if (eType == BIGENEMY) {
				b = FindBrick(pos, 16, false);
				BrickObject* b2 = FindBrick(pos-Vector2f(0,20), 128, true);
				if (b2) { o->setIgnoreNextStage(true); }
				if (!o->getIgnoreNextStage()) {
					if ((b && pos.y - o->getDiePos().y < 200) || pos.y <= 10) {
						o->setState(ALIVE);
						o->setKilled(false);
						o->setFalling(false);
						o->setIgnoreNextStage(false);
						o->setFeltInBrickID(-1);
					}
				}
				
			}

			//printf("pos: %f,%f of Die POS %f,%f\n" , pos.x, pos.y, o->getDiePos().x, o->getDiePos().y);
			if (GetCollisionAtPos(pos,o->getDiePos(),64,64)){
				printf("Enemy Died\n");
				o->setState(VANISHED);
			}
		}
		else if (o->getState() == VANISHED) {
			m->changeObjPos(o->getObjectProps(), Vector2f(2000, 2000));
		}
	}
	if (movingEnemies == 0) {
		if (nextLeveltimer >= maxNextLevelTimer) {
			printf("\n YOU WON THIS MAP");
			addLevel(true);
		}
		else {
			nextLeveltimer++;
		}
	}
}

/**
 * .
 * \param Lifes the current player lifes
 */
void GameController::visualizePlayerLifes(int lifes) {
	currPlayerLifes = lifes;
	for (int i = 0; i < lifes; i++) {
		m->addLifeObject(Vector2f(i * 80, 985), 100); // Vector2i(1, 0)
		//	GameObject* obj = m->getObjP(model); // !!!
		//	animateObject(obj, "Life_Change"); // !!!
	}
}

/**
 * .
 * \param next If true then load next level else restart current level
 */
void GameController::addLevel(bool next) {
	wait = true;
	redPlayer = false;
	nextLeveltimer = 0;

	m->deleteAll();
	if (next) {
		gLevel++;
	}
	else {
		currPlayerLifes--;
	}

	if (gLevel <= levelCount) {
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
		printf("\n|--------------------%i---------------------|", ((killedEnemiesCounter * random) - (playTime / ((playerDeaths + 1) * 10))) * 10);
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
bool GameController::MoveObject(Vector2i dir, ControllableObject* obj, bool force)
{
	//int objID = m->findObject(name);
	//GameObject *obj = m->getObjP(objID);
	int speed = obj->getSpeed();
	Vector2f currPos = obj->getPos();
	Vector2f newPos = currPos + dir * speed;
	if (obj->getType() == PLAYER) {
		obj->setFacing(dir);
		//printf("(%f,%f)\n", currPos.x, currPos.y);
	}
	//!!!
		//animateObject(obj, animation);

	if (newPos < boundaries && newPos.x >= 0 && newPos.y >= 0) {
		ObjectProps props = obj->getObjectProps();
		if (!force) {
			if (CheckWalk(currPos, newPos, dir, obj)) {
				if (dir.x == 0 && (int(currPos.y) % 160 > 155 || int(currPos.y) % 160 < 15)) {
					LadderObject* l = FindLadder(newPos - Vector2f(0, 10), 32);
					//printf("changed");
					m->changeObjPos(props, Vector2f(obj->getPos().x, newPos.y));
				}
				else {
					m->changeObjPos(props, newPos);
				}
				return true;
			}
			else {
				return false;
			}
		}
		else {
			m->changeObjPos(props, newPos);
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
			m->addBrickObject(Vector2f(x * spacing, y_Spacing * stage - y_correction), 108, static_cast<BrickType>(x % 2)); // Vector2i(15, 1),Vector2i(14,1)
			break;
		case 'l':
			//ladder
			m->addLadderObject(Vector2f(x * spacing + 15, y_Spacing * stage), 80); //  Vector2i(0, 0)
			break;
		case '#':
			//nothing but replace lost bricks at level 4,9,14,19,24
		/*	if (stage >0 && stage % 5 == 4) {
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
*/
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
			int i = rand() % 2;
			if (onlyGreen) {
				i = 1;
			}
			if (i == 0) {
				m->addEnemyObject(Vector2f(x * spacing, y_Spacing * stage), 120, NORMENEMY, 15); //Vector2i(0, 1)
			}
			else {
				m->addEnemyObject(Vector2f(x * spacing, y_Spacing * stage), 120, BIGENEMY, 15); //Vector2i(7, 1)
			}


		}
		else if (c == 'p') {
			//init player
			m->addPlayerObject(Vector2f(x * spacing, y_Spacing * stage), 120, 5); //Vector2i(0, 3)
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
bool GameController::CheckWalk(Vector2f currPos, Vector2f nextPos, Vector2i dir, ControllableObject* object) {
	bool out = false;
	LadderObject* l;
	if (dir == Vector2i(0, 1)) {//standing in front of ladder for y movement
		l = FindLadder(nextPos, 32);
		if (l) {
			out = true;
		}
	}
	else if (dir == Vector2i(0, -1)) {
		l = FindLadder(nextPos, 32);
		if (l) {

			//printf("Ladder %f,%f", l->getPos().x, l->getPos().y);
		}
		//BrickObject* b = FindBrick(nextPos,32,false);
		if (l) {
			out = true;
		}
	}
	else {	//standing on brick or y <= 1 for x movement
		l = FindLadder(currPos, 32);
		int diff = int(nextPos.y) % 160;
		int times = nextPos.y / 160;
		if (l) {
			if (diff < 40) {
				m->changeObjPos(object->getObjectProps(), Vector2f(nextPos.x, times * 160));
				out = false;
			}
			else if (diff > 135) {
				m->changeObjPos(object->getObjectProps(), Vector2f(nextPos.x, (times + 1) * 160));
				out = false;
			}
		}
		else {

			out = true;
			//no ladder --> just brick movement
			if (object->getType() == PLAYER) {
				BrickObject* placedSpaceToOccupy;
				if (dir == Vector2i(1, 0)) {
					placedSpaceToOccupy = FindBrick(nextPos + Vector2f(45, 0), 64);
				}
				else {
					placedSpaceToOccupy = FindBrick(nextPos, 32);
				}
				if (placedSpaceToOccupy) {
					int id = placedSpaceToOccupy->getID();
					//printf("BRICK STATE: %i + ID : %i\n", m->getBricks()[id].getState(), id);
					if (m->getBricks()[id].getState() == DIGSTART) {
						out = false;
					}
				}
			}
		}
	}
	return out;
}

/**
 * .
 * \param player The player object ID
 * \return Is true if player is inside an alien position
 */
bool GameController::CheckEnemyCollision() {
	std::vector<EnemyObject>* enemies = m->getEnemies();
	PlayerObject* p = m->getPlayer();
	for (auto o = enemies->begin(); o != enemies->end(); ++o) {
		if (o->getState() == ALIVE && GetCollisionAtPos(o->getPos(), p->getPos(), 64, 64)) {
			return true;
		}
	}
	return false;
}

//!!!!!!!!!!!!!!!!!!

/**
 * .
 * \param object The GameObject Pointer to animate
 * \param name The name of the animation
 */
 /*
 void GameController::animateObject(GameObject* object, std::string name) {
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
 */
 /**
  * .
  * \param The specific brick GameObject
  */
void GameController::dig(BrickObject* brick) {
	//printf("brick dig %i",brick->getID());
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
			if (dig_Timer % 15 == 0) {
				PlayerObject* obj = m->getPlayer();
				BrickObject* brickUnderPos;
				if (obj->getFacing() == Vector2i(1, 0)) {
					brickUnderPos = FindBrick(obj->getPos() + Vector2f(85, 0), 64);
				}
				else {
					brickUnderPos = FindBrick(obj->getPos() + obj->getFacing() * 10, 32);
				}
				if (brickUnderPos) {
					int ID = brickUnderPos->getID();
					bool dugOut = m->isBrickDugOut(ID);
					if (dig_Timer > 20) {
						dugOut ? m->lowerBrickCounter(ID) : m->addBrickCounter(ID);
					}
					else if (waitTimer >= max_waitTime) {
						waitTimer = 0;
						dugOut ? m->lowerBrickCounter(ID) : m->addBrickCounter(ID);
					}
					else {
						waitTimer++;
					}
				}
			}
		}
		else {
			//change Block 
			//printf("\n\nDIGGING BLOCk at pos: (%f,%f)", obj->getPos().x, obj->getPos().y );
		/*	BrickObject* brickUnderPos = FindReplacedBrick(obj->getPos() + obj->getFacing() * 35, obj->getWidth());
			if (brickUnderPos) {
				dig(brickUnderPos);
			}
			else {
				brickUnderPos = FindObjectPosUnder(BRICK,obj->getPos() + obj->getFacing() * 45, Vector2i(35, 35));
				if (brickUnderPos) {
					dig(brick);
				}
				else {
					//printf("\nnot over a brick\n");
				}
			}
			*/
			/*
			if (!brickUnderPos) {
				brickUnderPos = FindBrick(obj->getPos() + obj->getFacing() *10, 32, false);
			}
		*/
			PlayerObject* obj = m->getPlayer();
			BrickObject* brickUnderPos;
			if (obj->getFacing() == Vector2i(1, 0)) {
				brickUnderPos = FindBrick(obj->getPos() + Vector2f(85, 0), 64);
			}
			else {
				brickUnderPos = FindBrick(obj->getPos() + obj->getFacing() * 10, 32);
			}
   			if (brickUnderPos) {
				if (waitTimer >= max_waitTime) {
					int occ = brickUnderPos->getOccupiedBy();
					if (occ >= 0) {
						m->setEnemyDead(occ);
						EnemyObject* o = &(*m->getEnemies())[occ];
						if (o->getEnemyType() == NORMENEMY) { o->setDiePos(o->getPos() - Vector2f(0, 160)); }
						else { o->setDiePos(o->getPos() - Vector2f(0, 260)); }
					}


					dig(brickUnderPos);
					waitTimer = 0;
					dig_Timer = 0;
				}
				else {
					waitTimer++;
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
	bool pressed = false;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		//std::cout << "UP" << std::endl;
		m->getPlayer()->setDecision(LADDERUP);
		MoveObject(Vector2i(0, 1), m->getPlayer(), false);
		digging(false);
		pressed = true;
		waitTimer = 0;
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		//std::cout << "LEFT" << std::endl;
		m->getPlayer()->setDecision(LEFT);
		MoveObject(Vector2i(-1, 0), m->getPlayer(), false);
		digging(false);
		pressed = true;
		waitTimer = 0;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		//std::cout << "DOWN" << std::endl;
		m->getPlayer()->setDecision(LADDERDOWN);
		MoveObject(Vector2i(0, -1), m->getPlayer(), false);
		digging(false);
		pressed = true;
		waitTimer = 0;
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		//std::cout << "RIGHT" << std::endl;
		m->getPlayer()->setDecision(RIGHT);
		MoveObject(Vector2i(1, 0), m->getPlayer(), false);
		digging(false);
		pressed = true;
		waitTimer = 0;
	}
	else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		//std::cout << "SPACE" << std::endl;
		PlayerObject* obj = m->getPlayer();
		if (obj->getFacing() == Vector2i(-1, 0)) {
			m->getPlayer()->setDecision(DIGLEFT);
		}
		else {
			m->getPlayer()->setDecision(DIGRIGHT);
		}
		digging(true);
		pressed = true;
	}

	if (pressed) {
		testTimer++;
		pressed = false;

		if (testTimer >= 9) {
			m->getPlayer()->addCounter();
			testTimer = 0;
		}
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
 /*
 int GameController::GetObjectAtPos(ObjectType type, Vector2f pos) {

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

 */

bool GameController::GetCollisionAtPos(Vector2f pos1, Vector2f pos2, int width1, int width2)
{
	/*Vector2f selfTopLeft = Vector2f(pos1.x, pos1.y + width1 / 2);
	Vector2f selfBottomRight = Vector2f(pos1.x+ width1 / 2, pos1.y);
	Vector2f enemyTopLeft = Vector2f(pos2.x , pos2.y + width2 / 2);
	Vector2f enemyBottomRight = Vector2f(pos2.x + width2 / 2, pos2.y);

	if (selfTopLeft.x<enemyBottomRight.x && selfBottomRight.x > enemyTopLeft.x) {
		printf("%b\n");
	}

	if (selfTopLeft.x<enemyBottomRight.x && selfBottomRight.x > enemyTopLeft.x && selfTopLeft.y < enemyBottomRight.y && selfBottomRight.y > enemyTopLeft.y) {
		printf("true\n");
		return true;
	}
	return false;
	*/

	Vector2f bottomLeft1 = pos1;
	Vector2f bottomLeft2 = pos2;
	Vector2f topRight1 = pos1 + Vector2f(width1, width1) / 2;
	Vector2f topRight2 = pos2 + Vector2f(width2, width2) / 2;

	if (topRight1.y < bottomLeft2.y || bottomLeft1.y > topRight2.y) {
		return false;
	}
	if (topRight1.x < bottomLeft2.x || bottomLeft1.x > topRight2.x) {
		return false;
	}
	return true;

}



/**
 * .
 * \param pos Position where the GameObject in the GameModel's replacedBricks vector has to be
 * \return The ID of the found GameObject or -1
 */
BrickObject* GameController::FindBrick(Vector2f pos, int width, bool replaced)
{
	if (replaced) {
		for (BrickObject o : m->getReplacedBricks()) {
			if (GetCollisionAtPos(pos, o.getPos(), width, o.getWidth())) {
				return &o;
			}
		}
	}
	else {
		for (BrickObject o : m->getBricks()) {
			if (!o.isDugOut() && GetCollisionAtPos(pos, o.getPos(), width, o.getWidth())) {
				return &o;
			}
		}
	}

	return nullptr;
}


BrickObject* GameController::FindBrick(Vector2f pos, int width)
{
	for (BrickObject o : m->getReplacedBricks()) {
		if (GetCollisionAtPos(pos, o.getPos(), width, o.getWidth())) {
			return &o;
		}
	}
	for (BrickObject o : m->getBricks()) {
		if (!o.isDugOut() && GetCollisionAtPos(pos, o.getPos(), width, o.getWidth())) {
			return &o;
		}
	}

	return nullptr;
}

LadderObject* GameController::FindLadder(Vector2f pos, int width) {
	for (LadderObject o : m->getLadders()) {
		if (GetCollisionAtPos(pos, o.getPos() - Vector2f(20, 0), 32, 32)) {
			//printf("Hit at %f,%f", o.getPos().x, o.getPos().y);
			return &o;
		}
	}
}


/**
 * .
 * \param type Which type the Object to return has to be
 * \param pos Position where the GameObject in the GameModel's objects vector has to be
 * \param bounds The bounds in which the GameObject to be
 * \return The ID of the found GameObject or -1
 */
 /*
 int GameController::FindObjectPosUnder(ObjectType type,Vector2f pos,Vector2i bounds) {
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
 */
 /**
  * .
  * \param type Which type the Object to return has to be
  * \param pos Position where the GameObject in the GameModel's objects vector has to be
  * \return The ID of the found GameObject or -1
  */
  /*
  int GameController::findObjectPosOver(ObjectType type, Vector2f pos) {
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
  */

#include "GameController.h"
#include <fstream>
const Vector2f boundaries = Vector2f(1800, 1000);
std::string map1 = "Map1.txt";
int y_Spacing = 32;
int y_correction = 13;
bool player_falling = false;
Vector2i player_falling_Face;
/**
 * .
 * 
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
 * 
 * \return View got initiaized sucessfull?
 */
int GameController::init() {
	int i = v->initializeView();

	//init Animations
	/*
	m->addAnimation("Player_Right", 10, std::vector<Vector2i>{Vector2i(0, 3), Vector2i(1, 3)});
	m->addAnimation("Player_Left", 10, std::vector<Vector2i>{Vector2i(15, 3), Vector2i(14, 3)});
	m->addAnimation("Player_Down", 10, std::vector<Vector2i>{Vector2i(5, 3)});
	m->addAnimation("Player_Up", 10, std::vector<Vector2i>{Vector2i(4, 3), Vector2i(11, 3)});
	m->addAnimation("Player_Shovel_Left", 20, std::vector<Vector2i>{Vector2i(12, 3), Vector2i(13, 3)});
	m->addAnimation("Player_Shovel_Right", 20, std::vector<Vector2i>{ Vector2i(3, 3), Vector2i(2, 3)});
	*/
	//load test Map
	printf("loading map...");
	std::ifstream mapFile(map1);
	std::string content;
	std::vector<std::string> mapLines;
	while (mapFile >> content) {
		mapLines.insert(mapLines.begin(),content);
	}
	for (int i = 0; i < mapLines.size(); i++) {
		loadLine(mapLines[i], i, 79);
	}
	printf("loading complete...");
	printf("initializing player");

	//init Player
	m->addObject(Vector2f(1, 1), Vector2i(0, 3), 120, "player", 5, PLAYER);

	//start game loop
	game();
	return i;
}

/**
 * .
 *  Game Loop to get Input and Render everything
 */
void GameController::game() {
	int p = m->findObject("player");
	GameObject* pP = m->getObjP(p);
	printf("starting gameLoop");
	while (!glfwWindowShouldClose(v->window)) {
		if (checkEnemyCollision(p)) {
			m->changeSpriteSheet(p, Vector2i(0, 1));
		}
		if (player_falling) {
			moveObject(Vector2i(0, -1), "player", "Player_Down", true);
		}
		else {
			keyboardInput(v->window);
		}
		int pPpos = pP->getPos().y;
		if (pPpos%160 == 0&& player_falling) {
			player_falling = false;
			if (player_falling_Face == Vector2i(-1, 0)) {
				animateObject(pP, "Player_Left");
			}
			else {
				animateObject(pP, "Player_Right");
			}
		}
		gravitation(pP);
		v->RenderScene(m->getSprites());
	}
	glfwTerminate();
	exit(0);
}

void GameController::gravitation(GameObject* p) {
	Vector2f currPos = p->getPos();

	if (currPos.y > 1) {
		int i = findReplacedBrick(currPos);
		if (i != -1) {
			printf("on replaced brick");
			if (!player_falling) {
				player_falling_Face = p->getFacing();
				float bPos = m->getObjP(i)->getPos().x;
				p->setPos(Vector2f(bPos, p->getPos().y));
			}
			player_falling = true;
		}
	}
}


/**
 * .
 * 
 * \param dir Direction to move to
 * \param name Name of the Object
 * \param animation Animation to play while moving the Object
 */
void GameController::moveObject(Vector2i dir, std::string name, std::string animation,bool force)
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
			if (checkWalk(currPos, newPos, dir, *obj)) {
				m->changeObjPos(objID, newPos);
			}
		}
		else {
			m->changeObjPos(objID, newPos);
		}
	}
}

/**
 * .
 * 
 * \param in String to instantiate GameObjects from
 * \param stage on which y position (y * 26) to place the objects
 * \param spacing How much space should be left between the GameObjects
 */
void GameController::loadLine(std::string in, int stage, int spacing) {
	//classic = 5 stages with 24 tiles
	int x = 0;	
	for (char c : in) {
		switch (c) {
		case 'e':
			//enemy
			if (x % 2) {
				m->addObject(Vector2f(x * spacing, y_Spacing * stage), Vector2i(0, 1), 120, "enemy" + std::to_string(x), 0, ENEMY);
			}
			else {
				m->addObject(Vector2f(x * spacing, y_Spacing * stage), Vector2i(7, 1), 120, "enemy" + std::to_string(x), 0, ENEMY);
			}
			break;
		case 'b':
			//brick
			if (x % 2) {
				m->addObject(Vector2f(x*spacing, y_Spacing *stage- y_correction), Vector2i(15, 1), 108, "brick" + std::to_string(x),0,BRICK);
			}
			else {
				m->addObject(Vector2f(x*spacing, y_Spacing *stage- y_correction), Vector2i(14, 1), 108, "brick" + std::to_string(x), 0, BRICK);
			}
			break;
		case 'l':
			//ladder
			m->addObject(Vector2f(x * spacing+15, y_Spacing * stage), Vector2i(0, 0), 80, "ladder" + std::to_string(x), 0, LADDER);
			break;
		case '#':
			//nothing but replace lost bricks at level 4,9,14,19,24
			if (stage >0 && stage % 5 == 4) {
				int t = m->addObject(Vector2f(x * spacing, y_Spacing * stage - y_correction), Vector2i(14, 1), 108, "brick" + std::to_string(x), 0, BRICK);
				bool out = m->addReplacedBrick(t);
				if (out) {
					GameObject* object = m->getObjP(t);
					animateObject(object,"Brick_1_Change");
					printf("\nreplaced brick at: %f,%f\n", object->getPos().x, object->getPos().y);
				}
			}

			break;
		}
		x++;
	}

}

/**
 * .
 * 
 * \param currPos Current Postion of the GameObject
 * \param nextPos Position where the Object should be moved to
 * \param dir Direction in which the Object should be moved to
 * \param object The GameObject which should be moved
 * \return The Object is able to move
 */
bool GameController::checkWalk(Vector2f currPos, Vector2f nextPos,Vector2i dir, GameObject object) {
	bool out = false;

	printf("\nPlayer pos: (%f|%f)", currPos.x, currPos.y);
	if (dir == Vector2i(0, 1)) {//standing in front of ladder for y movement
		int id = getObjectAtPos(LADDER, nextPos);
		if (id != -1) {
			out = true;
		}
	}else if (dir == Vector2i(0, -1)) {
		int id = getObjectAtPos(LADDER, nextPos);
		int test = getObjectAtPos(BRICK, nextPos -Vector2f(5,5)); //to correct slight offset of getObjectAtPos
		if (id != -1 && test == -1) {
			out = true;
		}
	}else{	//standing on brick or y <= 1 for x movement
		int id = getObjectAtPos(LADDER, currPos);
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

bool GameController::checkEnemyCollision(int player) {
	Vector2f pos = m->getObjects()[player].getPos();
	int i = getCollisionAtPos(ENEMY, pos);
	if (i != -1) {
		printf("\ncollided with enemy!!!");
		return true;
	}
	return false;
}

void GameController::animateObject(GameObject *object, std::string name) {
	if (object->getCurrAnimName().compare(name) > 0 || object->getCurrAnimName().compare(name) < 0) {
		*object->getCurrCounter() = 0;
		*object->getCurrAnim() = 0;
		object->changeCurrAnimName(name);
	}
	Vector2i animV = v->nextAnimation(object->getCurrAnim(), object->getCurrCounter(), name);
	m->changeSpriteSheet(object->getID(), animV);
}


/**
 * .
 * Player Input
 * \param window From which Window should be the Input
 */
void GameController::keyboardInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		//std::cout << "UP" << std::endl;
		moveObject(Vector2i(0, 1),"player", "Player_Up",false);
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		//std::cout << "LEFT" << std::endl;
		moveObject(Vector2i(-1, 0), "player", "Player_Left",false);
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		//std::cout << "DOWN" << std::endl;
		moveObject(Vector2i(0, -1), "player", "Player_Down", false);
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		//std::cout << "RIGHT" << std::endl;
		moveObject(Vector2i(1, 0), "player", "Player_Right", false);
	}
	else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		std::cout << "SPACE" << std::endl;
		int objID = m->findObject("player");
		GameObject *obj = m->getObjP(objID);
		if (obj->getFacing() == Vector2i(-1, 0)) {
			animateObject(obj, "Player_Shovel_Left");

		}
		else {
			animateObject(obj, "Player_Shovel_Right");
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
 *
 * \param type Which type the Object to return has to be
 * \param pos Position where the GameObject in Objects has to be
 * \return The ID of the found GameObject or -1
 */
int GameController::getObjectAtPos(objectType type, Vector2f pos) {

	for (GameObject o : m->getObjects()) {
		if (o.getType() == type) {
			if (o.getPos() + Vector2f(0, 20) > pos && o.getPos() - Vector2f(25, 20) < pos) {
				printf("\nobject at %f , %f", o.getPos().x, o.getPos().y);
				return o.getID();
			}
		}
	}
	return  -1;
}

int GameController::getCollisionAtPos(objectType type, Vector2f pos) {
	for (GameObject o : m->getObjects()) {
		if (o.getType() == type) {
			if (o.getPos() + Vector2f(80, 1) > pos && o.getPos() - Vector2f(80, 1) < pos) {
				printf("\ncollided at %f , %f", o.getPos().x, o.getPos().y);
				return o.getID();
			}
		}
	}
	return  -1;
}

int GameController::findReplacedBrick(Vector2f pos)
{
	for (GameObject o : m->getReplacedBricks()) {
		if (pos.y - 50 <= o.getPos().y&& pos.y>= o.getPos().y) {
			if (pos.x - 25 <= o.getPos().x && pos.x + 25 > o.getPos().x) {
				return o.getID();
			}
		}
	}
	return -1;
}
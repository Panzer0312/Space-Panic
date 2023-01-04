#include "GameController.h"
#include <fstream>
const Vector2f boundaries = Vector2f(1800, 1000);
std::string map1 = "Map1.txt";
int y_Spacing = 32;
int y_correction = 13;

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
	m->addAnimation("Player_Right", 10, std::vector<Vector2i>{Vector2i(0, 3), Vector2i(1, 3)});
	m->addAnimation("Player_Left", 10, std::vector<Vector2i>{Vector2i(15, 3), Vector2i(14, 3)});
	m->addAnimation("Player_Down", 10, std::vector<Vector2i>{Vector2i(5, 3)});
	m->addAnimation("Player_Up", 10, std::vector<Vector2i>{Vector2i(4, 3), Vector2i(11, 3)});
	m->addAnimation("Player_Shovel_Left", 20, std::vector<Vector2i>{Vector2i(12, 3), Vector2i(13, 3)});
	m->addAnimation("Player_Shovel_Right", 20, std::vector<Vector2i>{ Vector2i(3, 3), Vector2i(2, 3)});

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
	printf("starting gameLoop");
	while (!glfwWindowShouldClose(v->window)) {
		keyboardInput(v->window);
		if (checkEnemyCollision(p)) {
			m->changeSpriteSheet(p, Vector2i(0, 1));
		}
		v->RenderScene(m->getSprites());
	}
	glfwTerminate();
	exit(0);
}

/**
 * .
 * 
 * \param dir Direction to move to
 * \param name Name of the Object
 * \param animation Animation to play while moving the Object
 */
void GameController::moveObject(Vector2i dir, std::string name, std::string animation)
{
	int objID = m->findObject(name);
	GameObject obj = m->getObjects()[objID];
	int speed = obj.getSpeed();
	Vector2f currPos = obj.getPos();
	Vector2f newPos = currPos + dir*speed;
	m->changeObjectFacing(objID, dir);
	animateObject(obj, animation);

	if (newPos < boundaries && newPos > Vector2f(-1, -1)){
		if (checkWalk(currPos,newPos, dir, obj)) {
			m->changeObjPos(objID, newPos);
		}
	}
	printf("Pos: (%f|%f)\n",newPos.x,newPos.y);
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
			//nothing
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
	if (dir == Vector2i(0, 1)) {//standing in front of ladder for y movement
		int id = m->getObjectAtPos(LADDER, nextPos);
		if (id != -1) {
			out = true;
		}
	}else if (dir == Vector2i(0, -1)) {
		int id = m->getObjectAtPos(LADDER, nextPos);
		int test = m->getObjectAtPos(BRICK, nextPos -Vector2f(5,5)); //to correct slight offset of getObjectAtPos
		if (id != -1 && test == -1) {
			out = true;
		}
	}else{	//standing on brick or y <= 1 for x movement
		int id = m->getObjectAtPos(LADDER, currPos);
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
	int i = m->getCollisionAtPos(ENEMY, pos);
	if (i != -1) {
		printf("collided with enemy!!!");
		return true;
	}
	return false;
}

/**
 * .
 * 
 * \param obj Object to change the sprite
 * \param animation Name of the ObjectAnimation
 */
void GameController::animateObject(GameObject obj, std::string animation) {

	int animID = m->findAnimation(animation);
	m->changeSpriteSheet(obj.getID(), m->getAnimations()[animID].getNextAnimation());
	m->changeAnimCounter(animID);
}

/**
 * .
 * Player Input
 * \param window From which Window should be the Input
 */
void GameController::keyboardInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		std::cout << "UP" << std::endl;
		moveObject(Vector2i(0, 1),"player", "Player_Up");
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		//std::cout << "LEFT" << std::endl;
		moveObject(Vector2i(-1, 0), "player", "Player_Left");
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		std::cout << "DOWN" << std::endl;
		moveObject(Vector2i(0, -1), "player", "Player_Down");
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		//std::cout << "RIGHT" << std::endl;
		moveObject(Vector2i(1, 0), "player", "Player_Right");
	}
	else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		std::cout << "SPACE" << std::endl;
		int objID = m->findObject("player");
		GameObject obj = m->getObjects()[objID];
		if (obj.getFacing() == Vector2i(-1, 0)) {
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


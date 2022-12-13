#include "GameController.h"
const Vector2f boundaries = Vector2f(1800, 1000);

GameController::~GameController()
{
}

GameController::GameController(GameModel *model,GameView *view)
{
	m = model;
	v = view;

	maxStages = 10;
}


int GameController::init() {
	int i = v->initializeView();
	//glfwSetKeyCallback(v->window,keyboardInput);
	//MB INIT SPRITESHEET IN MODEL


	//init Animations
	std::vector<Vector2i> playerRight{ Vector2i(0,3),Vector2i(1,3) };
	std::vector<Vector2i> playerLeft{ Vector2i(15,3),Vector2i(14,3) };
	std::vector<Vector2i> playerDown{ Vector2i(5,3)};
	std::vector<Vector2i> playerUp{ Vector2i(4,3),Vector2i(11,3) };
	std::vector<Vector2i> playerShovelLeft{ Vector2i(12,3),Vector2i(13,3) };
	std::vector<Vector2i> playerShovelRight{ Vector2i(3,3),Vector2i(2,3) };

	m->addAnimation("Player_Right", 10, playerRight);
	m->addAnimation("Player_Left", 10, playerLeft);
	m->addAnimation("Player_Down", 10, playerDown);
	m->addAnimation("Player_Up", 10, playerUp);
	m->addAnimation("Player_Shovel_Left", 20, playerShovelLeft);
	m->addAnimation("Player_Shovel_Right", 20, playerShovelRight);

	Vector2i t = Vector2i(0, 3);
	Vector2f pos = Vector2f(1, 1);
	//init Player

	m->addObject(pos, t, 64, "player", 5, PLAYER);

	Vector2f posi = Vector2f(0, 0);

	//load test Map
	std::string temp2 = "bbbbbbbbbblbbbbbbbbblbbbbbbblbbbbbbbbbb";
	std::string temp1 = "bbbbbbbbbblbbbbbbbbbbbbbbbbblbbbbbbbbbb";
	std::string temp3 = "##########l#################l##########";
	std::string temp4 = "##########l#########l#######l##########";
	loadLine(temp3, 0, 48);
	loadLine(temp3, 1, 48);
	loadLine(temp3, 2, 48);
	loadLine(temp1, 3, 48);
	loadLine(temp4, 4, 48);
	loadLine(temp4, 5, 48);
	loadLine(temp4, 6, 48);
	loadLine(temp2, 7, 48);
	loadLine(temp4, 8, 48);
	loadLine(temp3, 9, 48);


	game();
	return i;
}

void GameController::game() {
	while (!glfwWindowShouldClose(v->window)) {
		keyboardInput(v->window);
		v->RenderScene(m->getSprites());
	}
	glfwTerminate();
	exit(0);
}

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

//classic = 22 stages with 24 tiles
void GameController::loadLine(std::string in, int stage, int spacing) {
	int x = 0;
	
	for (char c : in) {
		switch (c) {
		case 'e':
			//enemy
			break;
		case 'b':
			//brick
			if (x % 2) {
				m->addObject(Vector2f(x*spacing, 26*stage), Vector2i(15, 1), 64, "brick" + std::to_string(x),0,BRICK);
			}
			else {
				m->addObject(Vector2f(x*spacing, 26*stage), Vector2i(14, 1), 64, "brick" + std::to_string(x), 0, BRICK);
			}
			break;
		case 'l':
			//ladder
			m->addObject(Vector2f(x * spacing, 26 * stage), Vector2i(0, 0), 64, "ladder" + std::to_string(x), 0, LADDER);
			break;
		case '#':
			//nothing
			break;
		}
		x++;
	}

}

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
		int diff = int(nextPos.y) % 104;
		int times = nextPos.y / 104;
		if (id != -1) {
			if (diff < 20) {
				m->changeObjPos(m->findObject(object.getName()), Vector2f(nextPos.x, times * 104));
				out = false;
			}
			else if (diff >90) {
				m->changeObjPos(m->findObject(object.getName()), Vector2f(nextPos.x, (times+1) * 104));
				out = false;
			}
		}
		else {
			out = true;
		}
	/*	else if (diff < 20) { //for easier stairs
			m->changeObjPos(m->findObject(object.getName()), nextPos-Vector2f(0, int(nextPos.y) - diff));
			out = false;
		}
		else if (int(nextPos.y) % 102 > 90) {
			out = false;
		}
	*/
	}
	return out;
}

bool GameController::onStage(Vector2f pos) {
	float calcYPos = 0;
	for (int i = 0; i < maxStages; i++) {
		calcYPos = i * (4 * 26);
		if (pos.y + 20 > calcYPos && pos.y - 10 < calcYPos) {
			return true;
		}
	}
	return false;
}

void GameController::animateObject(GameObject obj, std::string animation) {

	int animID = m->findAnimation(animation);
	m->changeSpriteSheet(obj.getID(), m->getAnimations()[animID].getNextAnimation());
	m->changeAnimCounter(animID);
}

bool GameController::generateStage(const std::string &fileName) {
	return false;
}

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


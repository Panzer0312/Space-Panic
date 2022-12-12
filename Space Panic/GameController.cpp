#include "GameController.h"

const Vector2f boundaries = Vector2f(1800, 1000);

GameController::~GameController()
{
}

GameController::GameController(GameModel *model,GameView *view)
{
	m = model;
	v = view;
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
	m->addAnimation("Player_Shovel_Left", 10, playerShovelLeft);
	m->addAnimation("Player_Shovel_Right", 10, playerShovelRight);

	Vector2i t = Vector2i(0, 3);
	Vector2f pos = Vector2f(10, 10);
	//init Player
	m->addObject(pos, t, 128, "player", 10, PLAYER);


	/*
	m->addSprite(pos,t,64);

	t = Vector2i(14, 3);
	pos = Vector2f(100, 150);

	m->addSprite(pos, t, 64);

	t = Vector2i(15, 3);
	pos = Vector2f(170, 160);

	m->addSprite(pos, t, 64);
*/	

	

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

	if (newPos < boundaries && newPos > Vector2f(0, 0)) {
		m->changeObjPos(objID, newPos);
	}
	printf("Pos: (%f|%f)\n",newPos.x,newPos.y);
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
		//std::cout << "UP" << std::endl;
		moveObject(Vector2i(0, 1),"player", "Player_Up");
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		//std::cout << "LEFT" << std::endl;
		moveObject(Vector2i(-1, 0), "player", "Player_Left");
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		//std::cout << "DOWN" << std::endl;
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


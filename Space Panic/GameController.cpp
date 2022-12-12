#include "GameController.h"

const Vector2f boundaries = Vector2f(1856, 1034);

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


	Vector2i t = Vector2i(11, 3);
	Vector2f pos = Vector2f(10, 10);

	m->addObject(pos, t, 64, "player", 10, PLAYER);


//	m->addObject(pos, t+Vector2i(1,0), 64, "player", 10, PLAYER);
//	m->addObject(pos+ Vector2f(200,200), t + Vector2i(1, 0), 64, "player", 10, PLAYER);


	m->addSprite(pos,t,64);

	t = Vector2i(14, 3);
	pos = Vector2f(100, 150);

	m->addSprite(pos, t, 64);

	t = Vector2i(15, 3);
	pos = Vector2f(170, 160);

	m->addSprite(pos, t, 64);
	
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

void GameController::moveObject(Vector2f dir, std::string name)
{
	int objID = m->findObject(name);
	Vector2f currPos = m->getObjects()[objID].getPos();
	Vector2f newPos = currPos + dir;
	if (newPos < boundaries && newPos > Vector2f(0, 0)) {
		m->changeObjPos(objID, newPos);
	}
	printf("Pos: (%f|%f)\n",newPos.x,newPos.y);
}


bool GameController::generateStage(const std::string &fileName) {
	return false;
}

void GameController::keyboardInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		//std::cout << "UP" << std::endl;
		moveObject(Vector2f(0, 1),"player");
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		//std::cout << "LEFT" << std::endl;
		moveObject(Vector2f(-1, 0), "player");
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		//std::cout << "DOWN" << std::endl;
		moveObject(Vector2f(0, -1), "player");
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		//std::cout << "RIGHT" << std::endl;
		moveObject(Vector2f(1, 0), "player");
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		std::cout << "SPACE" << std::endl;
	}

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		std::cout << "EXITING GAME" << std::endl;
		glfwDestroyWindow(window);
		glfwTerminate();
		exit(0);
	}
}


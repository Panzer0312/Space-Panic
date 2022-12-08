#include "GameController.h"

GameController::~GameController()
{
}

GameController::GameController(GameModel* model, GameView* view)
{
	m = model;
	v = view;
	v->initialize(*this);
}

void GameController::moveObject(Vector2f dir, int id)
{
	GameObject obj = m->getObject(id);
	Vector2f currPos = obj.getPos();
	obj.setPos(currPos + (dir * obj.getSpeed()));
}

void GameController::keyboardInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		std::cout << "UP" << std::endl;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {

		std::cout << "LEFT" << std::endl;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {

		std::cout << "DOWN" << std::endl;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {

		std::cout << "RIGHT" << std::endl;
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


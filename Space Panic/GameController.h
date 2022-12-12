#include "GameModel.h"
#include "GameView.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//Everything logic related
class GameController
{
public:
	GameController(GameModel* model, GameView * view);
	int init();
	void game();
	~GameController();
	void moveObject(Vector2f dir, std::string name);
	bool generateStage(const std::string& fileName);
	void keyboardInput(GLFWwindow* window);

private:
	void moveObject(Vector2f pos, int id);

	GameModel* m;
	GameView* v;
};

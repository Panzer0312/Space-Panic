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
	~GameController();

private:

	void game();
	bool generateStage(const std::string& fileName);
	void keyboardInput(GLFWwindow* window);
	void moveObject(Vector2i dir, std::string name, std::string animation);
	void animateObject(GameObject objID, std::string animation);
	void loadLine(std::string in, int stage, int spacing);
	bool checkWalk(Vector2f currPos, Vector2f nextPos, Vector2i dir, GameObject object);
	bool onStage(Vector2f pos);
	int maxStages;
	GameModel* m;
	GameView* v;
};

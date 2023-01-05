#include "GameModel.h"
#include "GameView.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//A game class for everything logic related
class GameController
{
public:
	/** Constructor fo GameController Class */
	GameController(GameModel* model, GameView * view);
	/** Initialize every ObjectAnimation,GameObject,Sprite etc. and then start the game loop */
	/** Also loads a Map from a .txt file (l = Ladder| e = Enemy| b = Brick|# = Nothing) */
	int init();
private:
	/** Starts the game loop */
	void game();
	void gravitation(GameObject* p);
	/** Defines the keyboardinput and tries to move the player accordingly */
	void keyboardInput(GLFWwindow* window);
	int getObjectAtPos(objectType type, Vector2f pos);
	int getCollisionAtPos(objectType type, Vector2f pos);
	int findReplacedBrick(Vector2f pos);
	/** Logic for Object movement */
	void moveObject(Vector2i dir, std::string name, std::string animation,bool force);
	/** Instantiates a string with map-information at stage (defines y-axes) */
	void loadLine(std::string in, int stage, int spacing);
	/** Collision check if object is allowed to move in that direction */
	bool checkWalk(Vector2f currPos, Vector2f nextPos, Vector2i dir, GameObject object);
	/** Checks if enemy collides with player */
	bool checkEnemyCollision(int player);

	void animateObject(GameObject *object, std::string name);

	GameModel* m;
	GameView* v;
};

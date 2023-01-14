#include "GameModel.h"
#include "GameView.h"
#include <iostream>
//A game class for everything logic related
class GameController
{
public:
	/** Constructor fo GameController Class */
	GameController(GameModel* model, GameView * view);
	/** Initialize every ObjectAnimation,GameObject,Sprite etc. and then start the game loop */
	/** Also loads a Map from a .txt file (l = Ladder| e = Enemy| b = Brick|# = Nothing) */
	int Init();
	GameModel* GetModel();
	GameView* GetView();

private:
	/** Starts the game loop */
	void Game();
	void MoveEnemies(Vector2f to);
	void LoadMap(int gameLevel);
	void Gravitation(GameObject* p);
	/** Defines the keyboardinput and tries to move the player accordingly */
	void KeyboardInput(GLFWwindow* window);
	int GetObjectAtPos(objectType type, Vector2f pos);
	int GetCollisionAtPos(objectType type, Vector2f pos);
	int FindReplacedBrick(Vector2f pos);
	int FindObjectPosUnder(objectType type,Vector2f pos, Vector2i bounds);
	/** Logic for Object movement */
	bool MoveObject(Vector2i dir, std::string name, std::string animation,bool force);
	/** Instantiates a string with map-information at stage (defines y-axes) */
	void LoadLine(std::string in, int stage, int spacing);
	void LoadEnemies(std::string line, int stage, int spacing);
	/** Collision check if object is allowed to move in that direction */
	bool CheckWalk(Vector2f currPos, Vector2f nextPos, Vector2i dir, GameObject object);
	/** Checks if enemy collides with player */
	bool CheckEnemyCollision(int player);

	void visualizePlayerLifes(int lifes);
	void digging(bool dig);
	void dig(GameObject* brick);
	void animateObject(GameObject *object, std::string name);
	int findObjectPosOver(objectType type, Vector2f pos);
	enemyDecision calcEnemyDecision(enemyDecision curr,Vector2f from, Vector2f to);
	void addLevel(bool next);
	void updateTimer();
	void initVisualizedTimer();
	Vector2i translateEnemyDec(enemyDecision dec);

	enemyDecision randomiseChoice(std::vector<enemyDecision> choices, int forcedRandomChoice);

	GameModel* m;
	GameView* v;
};

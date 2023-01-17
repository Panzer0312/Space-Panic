#include "GameModel.h"
#include "GameView.h"
#include <iostream>

//A game class for everything logic related
class GameController
{
public:
	/** Constructor for the GameController class */
	GameController(GameModel* model, GameView* view);
	/** Function to setup the game, also starts the Game Loop. */
	int Init();
	
	GameModel* GetModel();
	GameView* GetView();

private:
	/** Starts the game loop */
	void Game();
	/** Core function to move each alien GameObject */
	void MoveEnemies(Vector2f to);
	/** Loads a map from a.txt file with map information (l = Ladder | e = Enemy | b = Brick | #   = Nothing) */
	void LoadMap(int gameLevel);
	/** Pulls player down to next stage if player stepped on hole in Stage */
	void Gravitation(GameObject* p);
	/** Defines the player's possible keyboard input and tries to move the player accordingly to it */
	void KeyboardInput(GLFWwindow* window);
	/** Moves a specific GameObject position into a specific direction and animates it */
	bool MoveObject(Vector2i dir, std::string name, std::string animation,bool force);
	/** Instantiates the bricks and ladders from a given string with map information (l = Ladder | b = Brick | #   = Nothing) */
	void LoadLine(std::string in, int stage, int spacing);
	/** Function to create the aliens. This allows to call it separatly after the map initialization so the aliens wont be drawn behind the ladders etc. (e = Enemy) */
	void LoadEnemies(std::string line, int stage, int spacing);
	/** Collision check if object is allowed to move in that direction */
	bool CheckWalk(Vector2f currPos, Vector2f nextPos, Vector2i dir, GameObject object);
	/** Checks if enemy collides with player */
	bool CheckEnemyCollision(int player);
	/** Changes the model-object information into view-object information to unchain the GameModel and GameView */
	std::vector<SpriteBatch::SpriteInfo> changeModelSpritesToViewSprites(std::vector<GameModel::SpriteInformation> modelSprites);
	/** Updates the player life sprites in the top left corner (in case player died or next level initialization) */
	void visualizePlayerLifes(int lifes);
	/** The core function to dig a hole in the stage */
	void digging(bool dig);
	/** If player dug enough, create hole and change the specific brick gameObject*/
	void dig(GameObject* brick);
	/** Animate any given GameObject */
	void animateObject(GameObject *object, std::string name);
	/** Determines what decision an enemy is capable to do based on its position */
	enemyDecision calcEnemyDecision(enemyDecision curr,Vector2f from, Vector2f to);
	/** Loads the next level or restarts the current level */
	void addLevel(bool next);
	/** Calculates the sprites of the oxygen timer visualization */
	void updateTimer();
	/** Adds the player life sprites in the top left corner */
	void initVisualizedTimer();
	/** Translates a given EnemyDecision into Vector2i direction */
	Vector2i translateEnemyDec(enemyDecision dec);
	/** Creates semi-random movement with more possibility of moving to choices["forcedRandomChoice"] if not == -1 */
	enemyDecision randomiseChoice(std::vector<enemyDecision> choices, int forcedRandomChoice);
	/** Returns a found object at the given position */
	int GetObjectAtPos(objectType type, Vector2f pos);
	/** Returns a object the given position overlaps with */
	int GetCollisionAtPos(objectType type, Vector2f pos);
	/** Returns a Brick that has been dug out at the given position if it exists*/
	int FindReplacedBrick(Vector2f pos);
	/** Returns a found object under the given position */
	int FindObjectPosUnder(objectType type, Vector2f pos, Vector2i bounds);
	/** Returns a found object over the given position */
	int findObjectPosOver(objectType type, Vector2f pos);

	/** The GameModel object pointer the GameController got instantiated with*/
	GameModel* m;
	/** The GameView object pointer the GameController got instantiated with*/
	GameView* v;
};

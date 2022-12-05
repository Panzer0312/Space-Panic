#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// Represents the current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game
{
public:
    // game state
    GameState    State;
    bool         Keys[1024];
    unsigned int Width, Height;
    // constructor/destructor
    Game(unsigned int width, unsigned int height);
    ~Game();
    // initialize game state (load all shaders/textures/levels)
    void Init();
    //place for player input
    void ProcessInput(float dt, GLFWwindow* window);
    //place for code needed to be executed every tick
    void Update(float dt);
    //place to render textures
    void Render();
};


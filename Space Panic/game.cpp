#include "game.h"
/*
//player input function
void keyboardInput(GLFWwindow* window, float* x_direction, float* y_direction);

// Player Speed
const double SPEED = 0.01;
// Player Pos
float x_dir = 0.0f, y_dir = 0.f;


Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{

}
//initialize the game
void Game::Init()
{
    printf("Game init\n"); 

	ResourceManager::initShader();
    ResourceManager::LoadTextures("Spritesheet_64_64.DDS");


}
//place for player input
void Game::Update(float dt)
{

}
//place for code needed to be executed every tick
void Game::ProcessInput(float dt, GLFWwindow* window)
{
    //read Keyboard
    keyboardInput(window, &x_dir, &y_dir);
}
//place to render textures
void Game::Render()
{
	unsigned int shaderProgram = ResourceManager::getShaderProgram();
    glUseProgram(shaderProgram);
    glUniform1f(glGetUniformLocation(shaderProgram, "x_dir"), x_dir);
    glUniform1f(glGetUniformLocation(shaderProgram, "y_dir"), y_dir);

	glBindVertexArray(ResourceManager::getShaderObjects()[0]);
	
	Texture2D t = ResourceManager::GetTextures();
	t.Draw(2, 2, 1);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//ResourceManager::GetTextures().Bind();


}

//controlls player input
void keyboardInput(GLFWwindow* window, float* x_direction, float* y_direction)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		std::cout << "UP" << std::endl;
		*y_direction += SPEED;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {

		std::cout << "LEFT" << std::endl;
		*x_direction -= SPEED;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {

		std::cout << "DOWN" << std::endl;
		*y_direction -= SPEED;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {

		std::cout << "RIGHT" << std::endl;
		*x_direction += SPEED;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		std::cout << "SPACE" << std::endl;
	}

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		std::cout << "EXITING GAME" << std::endl;
		glfwDestroyWindow(window);
		glfwTerminate();
	}
}

*/
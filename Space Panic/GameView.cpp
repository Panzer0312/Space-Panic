#include "GameView.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "SpriteBatch.h"
#define WINDOW_WIDTH  1920
#define WINDOW_HEIGHT 1080

//changes the window resolution if a new monitor is dis/connected
void monitor_callback(GLFWmonitor* monitor, int event);
void RenderScene();

// The Width of the screen
const unsigned int SCREEN_WIDTH = 1080;
// The height of the screen
const unsigned int SCREEN_HEIGHT = 920;

SpriteTechnique m_texTech;
Texture* m_pTexture = NULL;
SpriteBatch* m_pSpriteBatch = NULL;
long long m_prevTime = 0;

int anim_row = 7;
int anim_col = 0;
int anim_pixelX = 0;

unsigned int NumSpritesX = 16;
unsigned int NumSpritesY = 4;

GLFWwindow* window;


GameView::GameView()
{
}

int GameView::initialize(GameController &g) {
    //init glfw library
    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    //create windowed mode window
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Space Panic", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    //make windwo's context current
    glfwMakeContextCurrent(window);
    glewInit();

    // OpenGL configuration
    glfwSetMonitorCallback(monitor_callback);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_pSpriteBatch = new SpriteBatch("Spritesheet_64_64_Flipped.DDS", NumSpritesX, NumSpritesY, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!m_texTech.Init()) {
        printf("Error initializing the texture technique\n");
        exit(1);
    }

    m_texTech.Enable();
    m_texTech.SetTextureUnit(0);

    // deltaTime variables
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    //loop until user closes the window
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT);
        // calculate delta time
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        RenderScene();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    exit(0);
    return 0;
}


//changes the window resolution if a new monitor is dis/connected
void monitor_callback(GLFWmonitor* monitor, int event)
{
    if (event == GLFW_CONNECTED)
    {
        // The monitor is connected
        float xscale, yscale;
        glfwGetMonitorContentScale(monitor, &xscale, &yscale);
        glViewport(0, 0, SCREEN_WIDTH * xscale + 100, SCREEN_HEIGHT * yscale + 100);
    }
    else if (event == GLFW_DISCONNECTED)
    {
        // The monitor is disconnected
    }
}

void RenderScene()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    std::vector<SpriteBatch::SpriteInfo> Sprites;
    Sprites.resize(100);

    /*
    Sprites[0].PixelX = 64;
    Sprites[0].PixelY = 64;
    Sprites[0].SpriteCol = 15; //x
    Sprites[0].SpriteRow = 1; //y
    Sprites[0].SpriteWidth = 64;
    */

    for (int i = 0; i < 15; i++) {
        if (i % 2 == 0) {
            Sprites[i].PixelX = 48 * (i + 1);
            Sprites[i].PixelY = 64;
            Sprites[i].SpriteCol = 15; //x
            Sprites[i].SpriteRow = 1; //y
            Sprites[i].SpriteWidth = 64;
        }
        else {
            Sprites[i].PixelX = 48 * (i + 1);
            Sprites[i].PixelY = 64;
            Sprites[i].SpriteCol = 14; //x
            Sprites[i].SpriteRow = 1; //y
            Sprites[i].SpriteWidth = 64;
        }
    }

    int i = 17;
    Sprites[i].PixelX = 48;
    Sprites[i].PixelY = 90;
    Sprites[i].SpriteCol = 3; //x
    Sprites[i].SpriteRow = 3; //y
    Sprites[i].SpriteWidth = 96;

    double CurTime = glfwGetTime();
    m_pSpriteBatch->Render(Sprites);
    //m_pSpriteBatch->RenderAll();

    m_texTech.Enable();


}

#include "GameView.h"
#define WINDOW_WIDTH  1920
#define WINDOW_HEIGHT 1080

//changes the window resolution if a new monitor is dis/connected
void monitor_callback(GLFWmonitor* monitor, int event);

//Vector2i t = Vector2i(15, 3);
//Vector2f pos = Vector2f(10, 10);

// The Width of the screen
const unsigned int SCREEN_WIDTH = 1080;
// The height of the screen
const unsigned int SCREEN_HEIGHT = 920;

SpriteTechnique m_texTech;
Texture* m_pTexture = NULL;
SpriteBatch* m_pSpriteBatch = NULL;
long long m_prevTime = 0;


unsigned int NumSpritesX = 16;
unsigned int NumSpritesY = 4;



GameView::GameView()
{
}

GameView::~GameView()
{
}

int GameView::initializeView() {
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
        printf("initializing the texture technique\n");
        exit(1);
    }


    m_texTech.Enable();
    m_texTech.SetTextureUnit(0);

    // deltaTime variables
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
}

//void GameView::RenderView() {
 //   std::vector<SpriteBatch::SpriteInfo> Sprites;
 //   Sprites.resize(10);

    //loop until user closes the window

    // calculate delta time
//    float currentFrame = glfwGetTime();
//  deltaTime = currentFrame - lastFrame;
//  lastFrame = currentFrame;


//    RenderScene(Sprites);
//}


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

void GameView::RenderScene(std::vector<SpriteBatch::SpriteInfo> Sprites)
{
    glClearColor(0.2f, 0.3f, 0.3f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Sprites.resize(500);
    double CurTime = glfwGetTime();
    m_pSpriteBatch->Render(Sprites);
    m_texTech.Enable();
    glfwSwapBuffers(window);
    glfwPollEvents();
}

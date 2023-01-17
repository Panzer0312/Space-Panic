#include "GameView.h"
#include <fstream>
#define WINDOW_WIDTH  1920
#define WINDOW_HEIGHT 1080


/** Changes the window resolution if a new monitor is dis/connected */
void monitor_callback(GLFWmonitor* monitor, int event);

// The Width of the screen
const unsigned int SCREEN_WIDTH = 804;
// The height of the screen
const unsigned int SCREEN_HEIGHT = 804;

SpriteTechnique m_texTech;
Texture* m_pTexture = NULL;
SpriteBatch* m_pSpriteBatch = NULL;

/** SpriteSheet horizontal textures count*/
unsigned int NumSpritesX = 16;
/** SpriteSheet vertical textures count*/
unsigned int NumSpritesY = 4;

std::string animationsFile = "Animations.txt";

/**
 * .
 * Constructor for GameView
 */
GameView::GameView()
{
    window = NULL;
    animationsCount = 0;
}

/**
 * .
 * Creates a window and inits OpenGL libraries. 
 * \return sucess 0 on success
 */
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

    m_pSpriteBatch = new SpriteBatch("Spritesheet_64_64_Flipped_v2.DDS", NumSpritesX, NumSpritesY, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!m_texTech.Init()) {
        printf("initializing the texture technique\n");
        exit(1);
    }
    initAnimations();
    m_texTech.Enable();
    m_texTech.SetTextureUnit(0);

    return 0;
}
/**
 * .
 * Changes the window resolution if a new monitor is dis/connected
 * \param monitor Connected Monitor
 * \param event GLFW_CONNECTED/DISCONNECTED
 */
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
/**
 * .
 * 
 * \param Sprites Vector of Sprites to render
 */
void GameView::RenderScene(std::vector<SpriteBatch::SpriteInfo> Sprites)
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Sprites.resize(500);
    m_pSpriteBatch->Render(Sprites);
    m_texTech.Enable();
    glfwSwapBuffers(window);
    glfwPollEvents();
}
/**
 * .
 * 
 */
void GameView::initAnimations(){
    //Vector2i|Vector2i|....|Vector2i#TimeToNextAnimation#AnimationName
    //BSP: 14,1|2,0#20#Brick_2_Change
    printf("\nloading Animations...");
    std::ifstream animationsF(animationsFile);
    std::string content;
    std::vector<std::string> AnimationLines;
    while (animationsF >> content) {
        AnimationLines.insert(AnimationLines.begin(), content);
    }
    for (int i = 0; i < AnimationLines.size(); i++) {
        std::string line = AnimationLines[i];
        std::vector<std::string> info;
        std::vector<Vector2i> animations;
        size_t pos,vecPos = 0;
        std::string token;
        while ((pos = line.find("#")) != std::string::npos) {
            token = line.substr(0, pos);
            info.push_back(token);
            line.erase(0, pos + 1);
        }
        line = info[0];
        while ((pos = line.find("|")) != std::string::npos) {
            token = line.substr(0, pos);
            vecPos = line.find(",");
            int x = stoi(line.substr(0, vecPos));
            int y = stoi(line.substr(vecPos +1, pos));
            animations.push_back(Vector2i(x, y));
            line.erase(0, pos + 1);
        }
        
        addAnimation(info[2],stoi(info[1]),animations);
    }

}

/**
 * .
 *
 * \param name Name of the Animation to find it through findAnimation()
 * \param speed How fast the Animation should be played (the higher the number, the slower the animation)
 * \param animSprites The different Sprite sequence for the animation
 * \return
 */
int GameView::addAnimation(std::string name, float speed, std::vector<Vector2i> animSprites)
{
    animationsCount++;
    Animations.resize(animationsCount);
    Animations[animationsCount - 1] = ObjectAnimation(name, speed, animSprites);
    return animationsCount - 1;
}
/**
 * .
 * 
 * \param currAnim The counter which texture is currently displayed during the animation
 * \param counter The counter when the texture of the animation should change next
 * \param name The name of the animation
 * \return The next texture of the animation
 */
Vector2i GameView::nextAnimation(int*currAnim,int*counter, std::string name)
{
    Vector2i temp;
    for (int i = 0; i < Animations.size(); i++) {
        if (Animations[i].getName() == name) {
            temp = Animations[i].getNextAnimation(currAnim, counter);
            return temp;
        }
    }
    printf("\nAnimation %s not found!!", name.c_str());
    return temp;
}

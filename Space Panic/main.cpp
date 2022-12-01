#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "SpriteBatch.h"

/*
#include "game.h"
#include "resourceManager.h"

#include <iostream>

//changes the window resolution if a new monitor is dis/connected
void monitor_callback(GLFWmonitor* monitor, int event);

// The Width of the screen
const unsigned int SCREEN_WIDTH = 1080;
// The height of the screen
const unsigned int SCREEN_HEIGHT = 920;


Game SpacePanic(SCREEN_WIDTH, SCREEN_HEIGHT);
//the core function to run this game
int main(int argc, char* argv[])
{
	GLFWwindow *window;

	//init glfw library
	if (!glfwInit()) {
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	//create windowed mode window
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Space Panic", NULL,NULL);
	
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

	// initialize game
	SpacePanic.Init();

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

		
		// manage user input
		SpacePanic.ProcessInput(deltaTime,window);

		// update game state
		SpacePanic.Update(deltaTime);

		// render OpenGL
		SpacePanic.Render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// delete all resources as loaded using the resource manager
	ResourceManager::Clear();

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
		glViewport(0, 0, SCREEN_WIDTH * xscale+100, SCREEN_HEIGHT * yscale+100);
	}
	else if (event == GLFW_DISCONNECTED)
	{
		// The monitor is disconnected
	}
}
*/


#define WINDOW_WIDTH  1920
#define WINDOW_HEIGHT 1080

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void CursorPosCallback(GLFWwindow* window, double x, double y);
static void MouseButtonCallback(GLFWwindow* window, int Button, int Action, int Mode);


class Tutorial33
{
public:

    Tutorial33()
    {
    }

    void Init()
    {
        glfwInit();
        glewInit();
        CreateWindow();

        InitCallbacks();

        //InitCamera();

        //InitMesh();

        InitShaders();

        InitSpriteBatch();
    }


    void Run()
    {
        while (!glfwWindowShouldClose(window)) {
            RenderSceneCB();
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }


    void RenderSceneCB()
    {
       // if (m_mobileCamera) {
       //     m_pGameCamera->OnRender();
       // }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        std::vector<SpriteBatch::SpriteInfo> Sprites;
        Sprites.resize(5);

        Sprites[0].PixelX = anim_pixelX;
        Sprites[0].PixelY = 0;
        Sprites[0].SpriteRow = anim_row;
        Sprites[0].SpriteCol = 5;
        Sprites[0].SpriteWidth = 1000;

        Sprites[1].PixelX = 500;
        Sprites[1].PixelY = 0;
        Sprites[1].SpriteRow = anim_row;
        Sprites[1].SpriteCol = 5;
        Sprites[1].SpriteWidth = 500;

        Sprites[2].PixelX = 750;
        Sprites[2].PixelY = 0;
        Sprites[2].SpriteRow = anim_row;
        Sprites[2].SpriteCol = 5;
        Sprites[2].SpriteWidth = 250;

        Sprites[3].PixelX = 875;
        Sprites[3].PixelY = 0;
        Sprites[3].SpriteRow = anim_row;
        Sprites[3].SpriteCol = 5;
        Sprites[3].SpriteWidth = 125;

        Sprites[4].PixelX = 875 + 73;
        Sprites[4].PixelY = 0;
        Sprites[4].SpriteRow = anim_row;
        Sprites[4].SpriteCol = 5;
        Sprites[4].SpriteWidth = 73;

        double CurTime = glfwGetTime();

        if ((CurTime - m_prevTime) > 100) {
            anim_row--;

            if (anim_row == 0) {
                anim_row = 7;
            }

            m_prevTime = CurTime;

            anim_pixelX += 4;

            if (anim_pixelX == 1000) {
                anim_pixelX = 0;
            }
        }

        m_pSpriteBatch->Render(Sprites);
        //m_pSpriteBatch->RenderAll();

        m_texTech.Enable();
        //m_pTexture->Bind(GL_TEXTURE0);
      //  m_pMesh->Render();

    }


    void KeyboardCB(unsigned int key, int state)
    {
        if (key == GLFW_KEY_ESCAPE) {
            glfwDestroyWindow(window);
            glfwTerminate();
            exit(0);
        }
    }


  //  void PassiveMouseCB(int x, int y)
  //  {
  //      if (m_mobileCamera) {
  //          m_pGameCamera->OnMouse(x, y);
  //      }
  //  }


    void MouseCB(int button, int action, int x, int y)
    {
    }

private:

    void CreateWindow()
    {
        int major_ver = 0;
        int minor_ver = 0;
        bool is_full_screen = false;
        window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Space Panic", NULL, NULL);

        //glfwSetCursorPos(window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    }


    void InitCallbacks()
    {
        glfwSetKeyCallback(window, KeyCallback);
        glfwSetCursorPosCallback(window, CursorPosCallback);
        glfwSetMouseButtonCallback(window, MouseButtonCallback);
    }

/*
    void InitCamera()
    {
        Vector3f Pos(0.0f, 5.0f, -22.0f);
        Vector3f Target(0.0f, -0.2f, 1.0f);
        Vector3f Up(0.0, 1.0f, 0.0f);

        float FOV = 45.0f;
        float zNear = 0.1f;
        float zFar = 100.0f;
        PersProjInfo persProjInfo = { FOV, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, zNear, zFar };

        m_pGameCamera = new BasicCamera(persProjInfo, Pos, Target, Up);
    }
*/

    void InitShaders()
    {
        if (!m_texTech.Init()) {
            printf("Error initializing the texture technique\n");
            exit(1);
        }

        m_texTech.Enable();
        m_texTech.SetTextureUnit(0);
    }

/*
    void InitMesh()
    {
        m_pMesh = new BasicMesh();

        m_pMesh->LoadMesh("../Content/fs_quad.obj");

        m_pTexture = new Texture(GL_TEXTURE_2D, "../Content/craftpix.net.Cartoon_Forest_BG_01.png");
        m_pTexture->Load();
    }
    */

    void InitSpriteBatch()
    {
        unsigned int NumSpritesX = 6;
        unsigned int NumSpritesY = 8;
        m_pSpriteBatch = new SpriteBatch("Spritesheet_64_64.DDS", NumSpritesX, NumSpritesY, WINDOW_WIDTH, WINDOW_HEIGHT);
    }

    GLFWwindow* window = NULL;
    SpriteTechnique m_texTech;
  //  BasicCamera* m_pGameCamera = NULL;
  //  bool m_mobileCamera = false;
  //  BasicMesh* m_pMesh = NULL;
   // Texture* m_pTexture = NULL;
    SpriteBatch* m_pSpriteBatch = NULL;
    long long m_prevTime = 0;

    int anim_row = 7;
    int anim_col = 0;
    int anim_pixelX = 0;
};


Tutorial33* app = NULL;

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    app->KeyboardCB(key, action);
}


static void CursorPosCallback(GLFWwindow* window, double x, double y)
{
   // app->PassiveMouseCB((int)x, (int)y);
}


static void MouseButtonCallback(GLFWwindow* window, int Button, int Action, int Mode)
{
    double x, y;

    glfwGetCursorPos(window, &x, &y);

    app->MouseCB(Button, Action, (int)x, (int)y);
}


/*
int main(int argc, char** argv)
{
    app = new Tutorial33();

    app->Init();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    GLint num;
    glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &num);
    printf("%d\n", num);
    glGetIntegerv(GL_MAX_VERTEX_UNIFORM_BLOCKS, &num);
    printf("%d\n", num);
    glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &num);
    printf("%d\n", num);
    glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &num);
    printf("%d\n", num);
    //    exit(0);
    app->Run();

    delete app;

    return 0;
}
*/
//----------------------------------------------------------------------------------

//changes the window resolution if a new monitor is dis/connected
void monitor_callback(GLFWmonitor* monitor, int event);
void RenderScene();

// The Width of the screen
const unsigned int SCREEN_WIDTH = 1080;
// The height of the screen
const unsigned int SCREEN_HEIGHT = 920;

GLFWwindow* window = NULL;
SpriteTechnique m_texTech;
//  BasicCamera* m_pGameCamera = NULL;
//  bool m_mobileCamera = false;
//  BasicMesh* m_pMesh = NULL;
Texture* m_pTexture = NULL;
SpriteBatch* m_pSpriteBatch = NULL;
long long m_prevTime = 0;

int anim_row = 7;
int anim_col = 0;
int anim_pixelX = 0;


//the core function to run this game
int main(int argc, char* argv[])
{
    GLFWwindow* window;

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

    unsigned int NumSpritesX = 16;
    unsigned int NumSpritesY = 4;
    m_pSpriteBatch = new SpriteBatch("Spritesheet_64_64.DDS", NumSpritesX, NumSpritesY, WINDOW_WIDTH, WINDOW_HEIGHT);
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
    // if (m_mobileCamera) {
    //     m_pGameCamera->OnRender();
    // }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    std::vector<SpriteBatch::SpriteInfo> Sprites;
    Sprites.resize(120);

  /*  Sprites[0].PixelX = 64;
    Sprites[0].PixelY = 64;
    Sprites[0].SpriteRow = 0;
    Sprites[0].SpriteCol = 0;
    Sprites[0].SpriteWidth = 64;

    Sprites[1].PixelX = 500;
    Sprites[1].PixelY = 40;
    Sprites[1].SpriteRow = 10;
    Sprites[1].SpriteCol = 5;
    Sprites[1].SpriteWidth = 60;

    Sprites[2].PixelX = 750;
    Sprites[2].PixelY = 0;
    Sprites[2].SpriteRow = anim_row;
    Sprites[2].SpriteCol = 5;
    Sprites[2].SpriteWidth = 60;

    Sprites[3].PixelX = 100;
    Sprites[3].PixelY = 80;
    Sprites[3].SpriteRow = 15;
    Sprites[3].SpriteCol = 1;
    Sprites[3].SpriteWidth = 64;

    Sprites[4].PixelX = 875 + 73;
    Sprites[4].PixelY = 0;
    Sprites[4].SpriteRow = 14;
    Sprites[4].SpriteCol = 14;
    Sprites[4].SpriteWidth = 64;
    */

    for (int h = 0; h < 15; h++) {
        Sprites[h].PixelX = h*64;
        Sprites[h].PixelY = 0;
        Sprites[h].SpriteRow = h;
        Sprites[h].SpriteCol = 0;
        Sprites[h].SpriteWidth = 64;
    }
    for (int h = 0; h < 15; h++) {
        Sprites[h+16].PixelX = h * 64;
        Sprites[h + 16].PixelY = 64;
        Sprites[h + 16].SpriteRow = h;
        Sprites[h + 16].SpriteCol = 1;
        Sprites[h + 16].SpriteWidth = 64;
    }
    for (int h = 0; h < 15; h++) {
        Sprites[h + 32].PixelX = h * 64;
        Sprites[h + 32].PixelY = 128;
        Sprites[h + 32].SpriteRow = h;
        Sprites[h + 32].SpriteCol = 2;
        Sprites[h + 32].SpriteWidth = 64;
    }
    for (int h = 0; h < 15; h++) {
        Sprites[h+48].PixelX = h * 64;
        Sprites[h + 48].PixelY = 194;
        Sprites[h + 48].SpriteRow = h;
        Sprites[h + 48].SpriteCol = 3;
        Sprites[h + 48].SpriteWidth = 64;
    }

    double CurTime = glfwGetTime();

    if ((CurTime - m_prevTime) > 100) {
        anim_row--;

        if (anim_row == 0) {
            anim_row = 7;
        }

        m_prevTime = CurTime;

        anim_pixelX += 4;

        if (anim_pixelX == 1000) {
            anim_pixelX = 0;
        }
    }

    m_pSpriteBatch->Render(Sprites);
    //m_pSpriteBatch->RenderAll();

    m_texTech.Enable();
 //   m_pTexture->Bind(GL_TEXTURE0);
    //  m_pMesh->Render();

}
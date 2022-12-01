#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

#include "texture.h"

class ResourceManager
{
public:
    // resource storage
    static Texture2D Sheet;
    // loads (and generates) a texture from file
    static Texture2D GetTextures();
    static Texture2D LoadTextures(const char* file);
    ResourceManager();
    static void Clear();
    static void initShader();
    static unsigned int getShaderProgram();
    static unsigned int* getShaderObjects();
private:
    // loads a single texture from file
    static Texture2D LoadDDSTextureFromFile(const char* file);
 
};
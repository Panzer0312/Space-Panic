#pragma once
#include <iostream>
#include <GL/glew.h>
// Texture2D is able to store and configure a texture in OpenGL.
// It also hosts utility functions for easy management.
class Texture2D
{
public:
    // holds the ID of the texture object, used for all texture operations to reference to this particlar texture
    // texture image dimensions
    unsigned int Width, Height, Format, Size, ID; // width, height and format of loaded image
    // constructor (sets default texture modes)
    Texture2D();
    // generates texture from image data
    void Generate(unsigned int width, unsigned int height, unsigned int formatRAW, unsigned char* data);
    // binds the texture as the current active GL_TEXTURE_2D texture object
    void Bind() const;
    void Draw(float posX, float posY, int frameIndex);
};

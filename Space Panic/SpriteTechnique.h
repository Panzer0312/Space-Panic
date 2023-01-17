#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Technique.h"
#define SPRITE_TECH_MAX_QUADS 1000

class SpriteTechnique : public Technique
{
public:
    /**  Constructor */
    SpriteTechnique();
    /** Initialize the Shaders */
    virtual bool Init();
    /** Binds texture unit with data buffer */
    void SetTextureUnit(unsigned int TextureUnit);
    /** Update Quad Info */
    void SetQuad(int Index,
        float NDCX, float NDCY, float Width, float Height,    // tile base position and dimensions
        float u, float v, float TexWidth, float TexHeight);   // texture coordinates
    /** Update the program */
    void UpdateProgram();

private:
    /**  Creates a uniform block for efficient rendering  */
    void ConfigUniformBlock();

    struct {
        GLuint BasePos = -1;
        GLuint WidthHeight = -1;
        GLuint TexCoords = -1;
        GLuint TexWidthHeight = -1;
    } m_quadsLoc[SPRITE_TECH_MAX_QUADS];

    struct {
        GLuint BasePos = -1;
        GLuint WidthHeight = -1;
        GLuint TexCoords = -1;
        GLuint TexWidthHeight = -1;
    } m_quads1Loc;

    struct {
        GLint BasePos = 0;
        GLint WidthHeight = 0;
        GLint TexCoords = 0;
        GLint TexWidthHeight = 0;
    } m_quadInfoOffsets;

    GLuint m_samplerLoc = -1;
    GLubyte* m_quadInfoBuffer = NULL;
    GLuint m_uniformBuffer = 0;
    GLint m_blockSize = 0;
};


#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class QuadArray
{
public:
    QuadArray(unsigned int MaxNumQuads);

    ~QuadArray();

    void Render(unsigned int NumQuads = 0);

private:

    void CreateVertexBuffer();
    void CreateQuadIDBuffer();

    enum BUFFER_TYPE {
        POS_VB = 0,
        QUAD_ID_VB = 1,
        NUM_BUFFERS = 2
    };

    int m_maxNumQuads = 0;
    GLuint m_VAO = -1;
    GLuint m_Buffers[NUM_BUFFERS] = { 0 };
};
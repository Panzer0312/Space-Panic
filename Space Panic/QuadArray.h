#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class QuadArray
{
public:
    /** Constructor to set the max number of quads that can be used */
    QuadArray(unsigned int MaxNumQuads);
    /** Destuctor */
    ~QuadArray();
    /** Render the given number of quads  */
    void Render(unsigned int NumQuads = 0);

private:
    /** Creates a new vertexBuffer Object */
    void CreateVertexBuffer();
    /** Creates a new QuadIDBoffer Object */
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
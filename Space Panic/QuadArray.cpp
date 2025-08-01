#include "QuadArray.h"
#include <vector>
#include "Math.h"

#define POSITION_LOCATION 0
#define PRIM_ID_LOCATION  1

#define NUM_VERTICES 6

/**
 * .
 * Constructor to create a new QuadArray
 * \param MaxNumQuads the maximum of Quads that should be used
 */
QuadArray::QuadArray(unsigned int MaxNumQuads)
{
    m_maxNumQuads = MaxNumQuads;

    glGenVertexArrays(1, &m_VAO);

    glBindVertexArray(m_VAO);
    
    glGenBuffers(sizeof(m_Buffers)/sizeof(m_Buffers[0]), m_Buffers);

    CreateVertexBuffer();

    CreateQuadIDBuffer();

    // Make sure the VAO is not changed from the outside
    glBindVertexArray(0);
}

/**
 * .
 * Destructor
 */
QuadArray::~QuadArray()
{

}

/**
 * .
 * Creates a new Vertex Buffer Object
 */
void QuadArray::CreateVertexBuffer()
{
    Vector2f vertices[] = { Vector2f(0.0f, 0.0f),   // bottom left
                            Vector2f(0.0f, 1.0f),   // top left
                            Vector2f(1.0f, 1.0f),   // top right
                            Vector2f(0.0f, 0.0f),   // bottom left
                            Vector2f(1.0f, 1.0f),   // top right
                            Vector2f(1.0f, 0.0f) }; // bottom right

    std::vector<Vector2f> vertices_vec;
    vertices_vec.resize(m_maxNumQuads * NUM_VERTICES);

    for (GLuint i = 0; i < m_maxNumQuads; i++) {
        for (int j = 0; j < NUM_VERTICES; j++) {
            vertices_vec[i * NUM_VERTICES + j] = vertices[j];
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[POS_VB]);
    glBufferData(GL_ARRAY_BUFFER, vertices_vec.size() * sizeof(Vector2f), &vertices_vec[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(POSITION_LOCATION);
    glVertexAttribPointer(POSITION_LOCATION, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

/**
 * .
 * sets a running Index in the QuadIDBuffer
 */
void QuadArray::CreateQuadIDBuffer()
{
    std::vector<GLuint> quad_id_vec;
    quad_id_vec.resize(m_maxNumQuads * NUM_VERTICES);

    for (GLuint i = 0; i < m_maxNumQuads; i++) {
        for (int j = 0; j < NUM_VERTICES; j++) {
            quad_id_vec[i * NUM_VERTICES + j] = i;
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[QUAD_ID_VB]);
    glBufferData(GL_ARRAY_BUFFER, quad_id_vec.size() * sizeof(GLuint), &quad_id_vec[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(PRIM_ID_LOCATION);
    glVertexAttribIPointer(PRIM_ID_LOCATION, 1, GL_UNSIGNED_INT, 0, 0);
}

/**
 * .
 * Rendering the Quads
 * \param NumQuads Number of Quads to render
 */
void QuadArray::Render(unsigned int NumQuads)
{
    if (NumQuads == 0) {
        NumQuads = m_maxNumQuads;
    }

    glBindVertexArray(m_VAO);

    glDrawArrays(GL_TRIANGLES, 0, NumQuads * NUM_VERTICES);

    glBindVertexArray(0);
}
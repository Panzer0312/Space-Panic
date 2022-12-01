#include "SpriteTechnique.h"
#include "Math.h"
#include <iostream>
#include "Technique.h"
#define SPRITE_BUFFER_BINDING 0

const char* vShaderC;
const char* fShaderC;

SpriteTechnique::SpriteTechnique()
{
}

bool SpriteTechnique::Init()
{
    // shaders
    vShaderC =
        "#version 330 core\n"
        "layout (location = 0) in vec2 Position;\n"
        "layout (location = 1) in uint QuadID;\n"
        "#define MAX_QUADS 100\n"
        "uniform QuadInfo {\n"
        "   vec2 BasePos[MAX_QUADS];\n"
        "   vec2 WidthHeight[MAX_QUADS];\n"
        "   vec2 TexCoords[MAX_QUADS];\n"
        "   vec2 TexWidthHeight[MAX_QUADS];\n"
        "};\n"
        "out vec2 TexCoords0;\n"
        "void main() {\n"
        "   vec3 BasePos = vec3(BasePos[QuadID], 0.5);\n"
        "   vec2 WidthHeight = Position * WidthHeight[QuadID];\n"
        "   vec3 NewPosition = BasePos + vec3(WidthHeight, 0.0);\n"
        "   gl_Position = vec4(NewPosition, 1.0);\n"
        "   vec2 BaseTexCoords = TexCoords[QuadID];\n"
        "   vec2 TexWidthHeight = Position * TexWidthHeight[QuadID];\n"
        "   TexCoords0 = BaseTexCoords +(TexWidthHeight);\n"
        "}\0";
    fShaderC =
        "#version 410 core\n"
        "layout(location = 0) out vec4 FragColor;\n"
        "uniform sampler2D gSampler;\n"
        "in vec2 TexCoords0;\n"
        "void main(){\n"
        "    FragColor = texture2D(gSampler, TexCoords0.xy);\n"
        "    if (FragColor == vec4(0.0)) {\n"
        "       discard;\n"
        "    }\n"
        "}\0";

    if (!Technique::Init()) {
        return false;
    }

    if (!initShader(GL_VERTEX_SHADER, vShaderC)) {
        return false;
    }

    if (!initShader(GL_FRAGMENT_SHADER, fShaderC)) {
        return false;
    }

    if (!Finalize()) {
        return false;
    }

    m_samplerLoc = GetUniformLocation("gSampler");

    if (m_samplerLoc == GL_INVALID_OPERATION) {
        return false;
    }

    ConfigUniformBlock();

    return true;
}


void SpriteTechnique::ConfigUniformBlock()
{
    GLuint BlockIndex = glGetUniformBlockIndex(m_shaderProg, "QuadInfo");

    glUniformBlockBinding(m_shaderProg, SPRITE_BUFFER_BINDING, BlockIndex);
    printf("BlockIndex %d\n", BlockIndex);

    glGetActiveUniformBlockiv(m_shaderProg, BlockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &m_blockSize);

    printf("Size %d\n", m_blockSize);

    m_quadInfoBuffer = (GLubyte*)malloc(m_blockSize);

    const GLchar* Names[] = { "BasePos", "WidthHeight", "TexCoords", "TexWidthHeight" };
    GLuint Indices[4] = { 0 };
    glGetUniformIndices(m_shaderProg, 4, Names, Indices);

    GLint Offsets[4];
    glGetActiveUniformsiv(m_shaderProg, 4, Indices, GL_UNIFORM_OFFSET, Offsets);

    m_quadInfoOffsets.BasePos = Offsets[0];
    m_quadInfoOffsets.WidthHeight = Offsets[1];
    m_quadInfoOffsets.TexCoords = Offsets[2];
    m_quadInfoOffsets.TexWidthHeight = Offsets[3];

    for (unsigned int i = 0; i < 4; i++) {
        printf("%s: %d %d\n", Names[i], Indices[i], Offsets[i]);
    }

    glGenBuffers(1, &m_uniformBuffer);
    printf("Uniform buffer %d\n", m_uniformBuffer);
}


void SpriteTechnique::SetTextureUnit(unsigned int TextureUnit)
{
    glUniform1i(m_samplerLoc, TextureUnit);
}


void SpriteTechnique::SetQuad(int Index,
    float NDCX, float NDCY, float Width, float Height,
    float u, float v, float TexWidth, float TexHeight)
{
    Vector2f* pBasePos = (Vector2f*)(m_quadInfoBuffer + m_quadInfoOffsets.BasePos);
    Vector2f* pWidthHeight = (Vector2f*)(m_quadInfoBuffer + m_quadInfoOffsets.WidthHeight);
    Vector2f* pTexCoords = (Vector2f*)(m_quadInfoBuffer + m_quadInfoOffsets.TexCoords);
    Vector2f* pTexWidthHeight = (Vector2f*)(m_quadInfoBuffer + m_quadInfoOffsets.TexWidthHeight);

    pBasePos[Index].x = NDCX;
    pBasePos[Index].y = NDCY;
    pWidthHeight[Index].x = Width;
    pWidthHeight[Index].y = Height;
    pTexCoords[Index].x = u;
    pTexCoords[Index].y = v;
    pTexWidthHeight[Index].x = TexWidth;
    pTexWidthHeight[Index].y = TexHeight;
}


void SpriteTechnique::UpdateProgram()
{
    glBindBuffer(GL_UNIFORM_BUFFER, m_uniformBuffer);
    glBufferData(GL_UNIFORM_BUFFER, m_blockSize, m_quadInfoBuffer, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, SPRITE_BUFFER_BINDING, m_uniformBuffer);
}
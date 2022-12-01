#pragma once
#include <list>
#include <GL/glew.h>

class Technique
{
public:

    Technique();

    virtual ~Technique();

    virtual bool Init();

    void Enable();

    GLuint GetProgram() const { return m_shaderProg; }

protected:

    bool Finalize();
    bool initShader(GLenum ShaderType, const char* code);
    GLint GetUniformLocation(const char* pUniformName);

    GLuint m_shaderProg = 0;

private:

    typedef std::list<GLuint> ShaderObjList;
    ShaderObjList m_shaderObjList;
};

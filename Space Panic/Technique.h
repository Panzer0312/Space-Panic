#pragma once
#include <list>
#include <GL/glew.h>

class Technique
{
public:
    /** Constructor */
    Technique();
    /** Destructor */
    virtual ~Technique();
    /** Initialize Shaderprogram */
    virtual bool Init();
    /** Tell OpenGL to use Shaderprogram */
    void Enable();
    /** Return the shaderProgram*/
    GLuint GetProgram() const { return m_shaderProg; }

protected:
    /** After all the shaders have been added to the program call this function */
    bool Finalize();
    /** Function to initialize different Shader */
    bool initShader(GLenum ShaderType, const char* code);
    /** Uniform location as a variable within a program object */
    GLint GetUniformLocation(const char* pUniformName);

    GLuint m_shaderProg = 0;

private:

    typedef std::list<GLuint> ShaderObjList;
    ShaderObjList m_shaderObjList;
};

#include <stdio.h>
#include <string.h>

#include "Technique.h"
/**
 * .
 * Constructor for a new Technique
 */
Technique::Technique()
{
    m_shaderProg = 0;
}

/**
 * .
 * Delete the intermediate shader objects that have been added to the program
 * The list will only contain something if shaders were compiled but the object itself
 * was destroyed prior to linking.
 */
Technique::~Technique()
{
    for (ShaderObjList::iterator it = m_shaderObjList.begin(); it != m_shaderObjList.end(); it++)
    {
        glDeleteShader(*it);
    }

    if (m_shaderProg != 0)
    {
        glDeleteProgram(m_shaderProg);
        m_shaderProg = 0;
    }
}

/** Initializes Technique */
bool Technique::Init()
{
    m_shaderProg = glCreateProgram();

    if (m_shaderProg == 0) {
        fprintf(stderr, "Error creating shader program\n");
        return false;
    }

    return true;
}

/**
 * .
 * Function to initialize different Shader
 * \param ShaderType Type of Shader
 * \param code Code from shader written in GLSL
 * \return sucess
 */
bool Technique::initShader(GLenum ShaderType, const char* code)
{
    GLuint ShaderObj = glCreateShader(ShaderType);
    if (ShaderObj == 0) {
        fprintf(stderr, "Error creating shader type %d\n", ShaderType);
        return false;
    }
    m_shaderObjList.push_back(ShaderObj);

    glShaderSource(ShaderObj, 1, &code, NULL);
    glCompileShader(ShaderObj);
    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);

    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling '%i': '%s'\n", ShaderType, InfoLog);
        return false;
    }

    glAttachShader(m_shaderProg, ShaderObj);

    return true;
}
/**
 * .
 * After all the shaders have been added to the program call this function
 * to link and validate the program.
 * \return sucess
 */
bool Technique::Finalize()
{
    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(m_shaderProg);

    glGetProgramiv(m_shaderProg, GL_LINK_STATUS, &Success);
    if (Success == 0) {
        glGetProgramInfoLog(m_shaderProg, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        return false;
    }

    glValidateProgram(m_shaderProg);
    glGetProgramiv(m_shaderProg, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(m_shaderProg, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        //   return false;
    }

    // Delete the intermediate shader objects that have been added to the program
    for (ShaderObjList::iterator it = m_shaderObjList.begin(); it != m_shaderObjList.end(); it++) {
        glDeleteShader(*it);
    }

    m_shaderObjList.clear();
    return true;
}

/**
 * .
 * Tell OpenGL to use Shaderprogram
 */
void Technique::Enable()
{
    glUseProgram(m_shaderProg);
}

/**
 * .
 *  
 * \param pUniformName
 * \return uniform location as a variable within a program object
 */
GLint Technique::GetUniformLocation(const char* pUniformName)
{
    GLuint Location = glGetUniformLocation(m_shaderProg, pUniformName);

    if (Location == GL_INVALID_OPERATION) {
        fprintf(stderr, "Warning! Unable to get the location of uniform '%s'\n", pUniformName);
    }

    return Location;
}
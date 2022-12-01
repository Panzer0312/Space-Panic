#include "resourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>
//Texture Size
const unsigned int TEXTUREVEC = 64;
const char* vShaderCode;
const char* fShaderCode;

unsigned int shaderProgram;

//shaderObjects 0|VAO, 1|VBO, 2|EBO;
unsigned int shaderObjects[3];

Texture2D ResourceManager::Sheet;


// Initialize the shader-program
void ResourceManager::initShader() 
{
	// shaders
	vShaderCode =
	"#version 410 core\n"
	"layout (location = 0) in vec2 vertex_position;\n"
	"uniform float x_dir;\n"
	"uniform float y_dir;\n"
	"out vec2 TexCoord;\n"
	"void main() {\n"
	"    gl_Position = vec4(vertex_position.x + x_dir - 0.1, vertex_position.y + y_dir - 0.1, 0.0, 1.0);\n"
	"    TexCoord = vec2(vertex_position.x, 1.0-vertex_position.y)*10;\n"
	"}\0";
	fShaderCode =
	"#version 410 core\n"
	"uniform sampler2D imgTexture;\n"
	"in vec2 TexCoord;\n"
	"out vec4 frag_color;\n"
	"void main(){\n"
	"    frag_color = texture(imgTexture, TexCoord);\n"
	//"    frag_color = vec4(0.1412, 0.1608, 0.1843, 1.0);\n"
	"}\0";

	unsigned int vShader, fShader;
	vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vShaderCode, NULL);
	glCompileShader(vShader);
	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fShaderCode, NULL);
	glCompileShader(fShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vShader);
	glAttachShader(shaderProgram, fShader);
	glLinkProgram(shaderProgram);

	// vertices & indices
	float vertices[] = {
		0.0, 0.1,
		0.1, 0.1,
		0.1, 0.0,
		0.0, 0.0
	};
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	//shaderObjects 0|VAO, 1|VBO, 2|EBO;
	glGenVertexArrays(1, &shaderObjects[0]);
	glGenBuffers(1, &shaderObjects[1]);
	glGenBuffers(1, &shaderObjects[2]);
	glBindVertexArray(shaderObjects[0]);

	glBindBuffer(GL_ARRAY_BUFFER, shaderObjects[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shaderObjects[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

}
//returns an already loaded texture with the given name
Texture2D ResourceManager::GetTextures()
{
    return Sheet;
}
//loads a texture from memory and saves it in the array with the given name 
Texture2D ResourceManager::LoadTextures(const char* file)
{
	Sheet = LoadDDSTextureFromFile(file);
	return Sheet;
}
//function to load a dds file format texture
Texture2D ResourceManager::LoadDDSTextureFromFile(const char* file)
{
	bool sucess = false;
	FILE* fp;
	Texture2D texture;
	unsigned char header[124];

	/* try to open the file */
	fp = fopen(file, "rb");
	if (fp == NULL) {
		printf("%s could not be opened x\n", file); getchar();
		return texture;
	}

	/* verify that file has type DDS */
	char filecode[4];
	fread(filecode, 1, 4, fp);
	if (strncmp(filecode, "DDS ", 4) != 0) {
		fclose(fp);
		printf("%s has wrong data format... only .dds supported x\n", file); getchar();
		return texture;
	}

	/* get the header info */
	fread(&header, 124, 1, fp);
	unsigned int height = *(unsigned int*)&(header[8]);
	unsigned int width = *(unsigned int*)&(header[12]);
	unsigned int linearSize = *(unsigned int*)&(header[16]);
	unsigned int mipMapCount = *(unsigned int*)&(header[24]);
	unsigned int fourCC = *(unsigned int*)&(header[80]);


	unsigned char* buffer;
	unsigned int bufsize;
	/* how big is it going to be including all mipmaps? */
	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));

	fread(buffer, 1, bufsize, fp);
	/* close the file pointer */
	fclose(fp);
	texture.Generate(width, height, fourCC, buffer);
	free(buffer);
	printf("New Texture loaded from File: %i \n", texture.ID);

	return texture;
}

// clears the textures
void ResourceManager::Clear()
{
    // (properly) delete all textures
    glDeleteTextures(1, &Sheet.ID);
}
// returns the initialized shaderProgram
unsigned int ResourceManager::getShaderProgram()
{
	return shaderProgram;
}
// returns the initialized shaderObject (0|VAO, 1|VBO, 2|EBO)
unsigned int* ResourceManager::getShaderObjects()
{
	return shaderObjects;
}
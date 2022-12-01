#include "texture.h"


#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

//initializing the texture with empty values
Texture2D::Texture2D()
    : Width(0), Height(0), Size(0), Format(0)
{
    glGenTextures(1, &this->ID);
}

//generate a texture to the given memory data 
void Texture2D::Generate(unsigned int width, unsigned int height, unsigned int formatRAW, unsigned char* data)
{
    this->Width = width;
    this->Height = height;
    this->Size = width * height;
    
    //specify given texture format
    switch (formatRAW)
    {
    case FOURCC_DXT1:
        this->Format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
        break;
    case FOURCC_DXT3:
        this->Format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
        break;
    case FOURCC_DXT5:
        this->Format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
        break;
    default:
        printf("format not supported!!\n");
    }

    // Create texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glCompressedTexImage2D(GL_TEXTURE_2D, 0, Format, Width, Height, 0, Size, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // unbind texture
    //glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Draw(float posX,float posY, int frameIndex) {
        int spriteWidth = 64;
        int spriteHeight = 64;
        const float verts[] = {
            posX, posY,
            posX + spriteWidth, posY,
            posX + spriteWidth, posY + spriteHeight,
            posX, posY + spriteHeight
        };
        const float tw = float(spriteWidth) / Width;
        const float th = float(spriteHeight) / Height;
        const int numPerRow = Width/ spriteWidth;
        const float tx = (frameIndex % numPerRow) * tw;
        const float ty = (frameIndex / numPerRow + 1) * th;
        const float texVerts[] = {
            tx, ty,
            tx + tw, ty,
            tx + tw, ty + th,
            tx, ty + th
        };

        // ... Bind the texture, enable the proper arrays

        glVertexPointer(2, GL_FLOAT,0, verts);
        glTexCoordPointer(2, GL_FLOAT,0, texVerts);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

//bind a texture to it's ID 
void Texture2D::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, ID);
}
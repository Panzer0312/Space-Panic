#include "Textur.h"


#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

/**
 * .
 * Constructor of a new Texture
 * \param TextureTarget Type of Texture (=Texture2D)
 * \param FileName Name of File
 */
Texture::Texture(GLenum TextureTarget, const std::string& FileName)
{
    m_textureTarget = TextureTarget;
    m_fileName = FileName;
}
/**
 * .
 * Load Texture from FileName
 * \return sucess
 */
bool Texture::Load()
{
    FILE* fp;
    unsigned char header[124];

    fp = fopen(m_fileName.c_str(), "rb");
    if (fp == NULL) {
        printf("%s could not be opened x\n", m_fileName.c_str()),getchar();
        return false;
    }
    /* verify that file has type DDS */
    char filecode[4];
    fread(filecode, 1, 4, fp);
    if (strncmp(filecode, "DDS ", 4) != 0) {
        fclose(fp);
        printf("%s has wrong data format... only .dds supported x\n", m_fileName.c_str()); getchar();
        return false;
    }
    /* get the header info */
    fread(&header, 124, 1, fp);
    m_imageHeight = *(unsigned int*)&(header[8]);
    m_imageWidth  = *(unsigned int*)&(header[12]);
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

    switch (fourCC)
    {
    case FOURCC_DXT1:
        this->m_imageBPP = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
        break;
    case FOURCC_DXT3:
        this->m_imageBPP = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
        break;
    case FOURCC_DXT5:
        this->m_imageBPP = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
        break;
    default:
        printf("format not supported!!\n");
    }
    printf("Width %d, height %d, fourCC %d\n", m_imageWidth, m_imageHeight, fourCC);
    LoadInternal(buffer);
    free(buffer);

    return true;
}
/**
 * .
 * Loads compressed image Data into Texture
 * \param image_data loaded image Data
 */
void Texture::LoadInternal(void* image_data)
{
    glGenTextures(1, &m_textureObj);
    glBindTexture(m_textureTarget, m_textureObj);

    glCompressedTexImage2D(GL_TEXTURE_2D, 0, m_imageBPP, m_imageWidth, m_imageHeight, 0, m_imageWidth * m_imageHeight, image_data);

    glTexParameterf(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(m_textureTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(m_textureTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(m_textureTarget, 0);
}
/**
 * .
 * Loads File inte Texture
 * \param Filename
 */
void Texture::Load(const std::string& Filename)
{
    m_fileName = Filename;

    if (!Load()) {
        exit(0);
    }
}
/**
 * .
 * Binds a Texture to TextureUnit to get Drawn
 * \param TextureUnit
 */
void Texture::Bind(GLenum TextureUnit)
{
    glActiveTexture(TextureUnit);
    glBindTexture(m_textureTarget, m_textureObj);
}
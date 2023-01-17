#pragma once
#include <string>
#include <GL/glew.h>


class Texture
{
public:
    /** Initializes a new Texure */
    Texture(GLenum TextureTarget, const std::string& FileName);
    /** Should be called once to load the SpriteSheet */
    bool Load();
    /** Loads a given File into this Texture Object */
    void Load(const std::string& Filename);
    /** Must be called at least once for the specific texture unit */
    void Bind(GLenum TextureUnit);
    /** Writes TextureSizes to given variables*/
    void GetImageSize(int& ImageWidth, int& ImageHeight)
    {
        ImageWidth = m_imageWidth;
        ImageHeight = m_imageHeight;
    }

private:
    /** Loads Texture from Compressed Image Data */
    void LoadInternal(void* image_data);

    std::string m_fileName;
    GLenum m_textureTarget;
    GLuint m_textureObj;
    int m_imageWidth = 0;
    int m_imageHeight = 0;
    int m_imageBPP = 0;

};

#pragma once
#include "QuadArray.h"
#include <vector>
#include "SpriteTechnique.h"
#include "Textur.h"

class SpriteBatch
{
public:

    struct SpriteInfo {
        unsigned int PixelX = 0;
        unsigned int PixelY = 0;
        unsigned int SpriteRow = 0;    // Sprite location in the sprite sheet - row
        unsigned int SpriteCol = 0;    // Sprite location in the sprite sheet - col
        unsigned int SpriteWidth = 0;
    };

    SpriteBatch(const char* pFilename, unsigned int NumSpritesX, unsigned int NumSpritesY, unsigned int WindowWidth, unsigned int WindowHeight);

    void Render(const std::vector<SpriteInfo>& sprites);

    void RenderAll();

private:

    void InitSpriteSheet();

    void InitSpriteTech();

    void CalcSpriteInfo();

    void ScreenPosToNDC(float mouse_x, float mouse_y, float& ndc_x, float& ndc_y);

    // constructor params
    int maxNumSprites = 1000;
    const char* m_pFilename = NULL;
    float m_numSpritesX = 0.0f;
    float m_numSpritesY = 0.0f;
    float m_windowWidth = 0.0f;
    float m_windowHeight = 0.0f;
    // internal params
    float m_spriteAspectRatio = 0.0f;   // height/width of the sprite in the sprite sheet
    float m_texUSize = 0.0f;  // Sprite size in tex space - U
    float m_texVSize = 0.0f;  // Sprite size in tex space - V
    float m_windowAR = 0.0f;
    float m_ndcPixelX = 0.0f; // Size of pixel in NDC space - X
    float m_ndcPixelY = 0.0f; // Size of pixel in NDC space - y
    float m_tileHeightInPixels = 0.0f;
    float m_tileWidthInPixels = 0.0f;
    float m_tileWidthNDC = 0.0f;
    float m_tileHeightNDC = 0.0f;
    Texture* m_pSpriteSheet = NULL;
    QuadArray* m_pQuads = NULL;
    SpriteTechnique m_spriteTech;
};
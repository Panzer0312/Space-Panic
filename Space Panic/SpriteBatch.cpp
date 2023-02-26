#include "SpriteBatch.h"

/**
 * .
 * Constructor and initiator
 * \param pFilename Spritesheet path
 * \param NumSpritesX Count of different Textures in x axes
 * \param NumSpritesY Count of different Textures in y axes
 * \param WindowWidth Width of the window
 * \param WindowHeight Height of the window
 */
SpriteBatch::SpriteBatch(const char* pFilename, unsigned int NumSpritesX, unsigned int NumSpritesY, unsigned int WindowWidth, unsigned int WindowHeight)
{
    m_pFilename = pFilename;
    m_numSpritesX = (float)NumSpritesX;
    m_numSpritesY = (float)NumSpritesY;
    m_windowWidth = (float)WindowWidth;
    m_windowHeight = (float)WindowHeight;
    m_windowAR = m_windowHeight / m_windowWidth;

    
    m_pQuads = new QuadArray(maxNumSprites);

    InitSpriteSheet();

    InitSpriteTech();

    CalcSpriteInfo();
}

/**
 * .
 * Instantiates the Spritesheet from the input pFilename
 */
void SpriteBatch::InitSpriteSheet()
{
    m_pSpriteSheet = new Texture(GL_TEXTURE_2D, m_pFilename);

    if (!m_pSpriteSheet->Load()) {
        printf("Error loading sprite sheet\n");
    }
}

/**
 * .
 * Initiates SpriteTexhnique used to instantiate the vertex/fragment shaders and enables it
 */
void SpriteBatch::InitSpriteTech()
{
    if (!m_spriteTech.Init()) {
        printf("Error initializing the sprite technique\n");
        exit(1);
    }

    m_spriteTech.Enable();
    m_spriteTech.SetTextureUnit(GL_TEXTURE0);
}

/**
 * .
 * Some calculation for access to the different textures on the initialized spritesheet 
 */
void SpriteBatch::CalcSpriteInfo()
{
    int ImageWidth, ImageHeight;
    m_pSpriteSheet->GetImageSize(ImageWidth, ImageHeight);

    float SpriteWidth = (float)ImageWidth / m_numSpritesX;
    float SpriteHeight = (float)ImageHeight / m_numSpritesY;

    m_spriteAspectRatio = SpriteHeight / SpriteWidth;

    m_texUSize = 1.0f / m_numSpritesX;
    m_texVSize = 1.0f / m_numSpritesY;

    m_ndcPixelX = 2.0f / m_windowWidth;
    m_ndcPixelY = 2.0f / m_windowHeight;

    m_tileHeightInPixels = 0.0f;
    m_tileWidthInPixels = 0.0f;

    float ImageWidthToWindowWidthRatio = ImageWidth / m_windowWidth;
    float ImageHeightToWindowHeightRatio = ImageHeight / m_windowHeight;

    if (ImageWidthToWindowWidthRatio < ImageHeightToWindowHeightRatio) {
        m_tileHeightInPixels = m_windowHeight / m_numSpritesY;
        m_tileWidthInPixels = m_tileHeightInPixels / m_spriteAspectRatio;
    }
    else {
        m_tileWidthInPixels = m_windowWidth / m_numSpritesX;
        m_tileHeightInPixels = m_tileWidthInPixels * m_spriteAspectRatio;
    }

    m_tileWidthNDC = m_ndcPixelX * m_tileWidthInPixels;
    m_tileHeightNDC = m_ndcPixelY * m_tileHeightInPixels;
}

/** Screen coords to Texture coords (Normalized Device Coordinates) */
void SpriteBatch::ScreenPosToNDC(float mouse_x, float mouse_y, float& ndc_x, float& ndc_y)
{
    ndc_x = (2.0f * mouse_x) / m_windowWidth - 1.0f;
    ndc_y = (2.0f * mouse_y) / m_windowHeight - 1.0f;
}

/**
 * .
 * Renders Vector of given Sprites
 * \param sprites input vector to draw
 */
void SpriteBatch::Render(const std::vector<SpriteInfo>& sprites)
{
    m_spriteTech.Enable();

    float NDCX, NDCY;

    for (int SpriteIndex = 0; SpriteIndex < sprites.size(); SpriteIndex++) {

        const SpriteInfo& Info = sprites[SpriteIndex];

        ScreenPosToNDC((float)Info.PixelX, (float)Info.PixelY, NDCX, NDCY);

        float TileWidthNDC = m_ndcPixelX * Info.SpriteWidth;
        float TileHeightNDC = TileWidthNDC / m_spriteAspectRatio;

        float UBase = (float)Info.SpriteCol * m_texUSize;
        float VBase = (float)Info.SpriteRow * m_texVSize;

        m_spriteTech.SetQuad(SpriteIndex,
            NDCX, NDCY, TileWidthNDC, TileHeightNDC,
            UBase, VBase, m_texUSize, m_texVSize);
    }

    m_spriteTech.UpdateProgram();

    m_pSpriteSheet->Bind(GL_TEXTURE0);
    m_pQuads->Render((int)sprites.size());
}
#include "graphics/sfml/SfmlSpriteRessource.hpp"
#include "graphics/sfml/SfmlIliadeGraphics.hpp"

namespace Iliade::Graphics::Sfml
{

    SfmlSpriteRessource::SfmlSpriteRessource(SfmlIliadeGraphics &graphicEngine, std::string texturePath)
    {
        
        mSprite.setTexture(graphicEngine.getTexture(texturePath));      // Add texture id tracing 
    }

    SfmlSpriteRessource::~SfmlSpriteRessource()
    {

    }

    void SfmlSpriteRessource::setFrame(Frame &frame)
    {
        mSprite.setTextureRect(sf::IntRect{frame.x, frame.y, frame.w, frame.h});
        mSprite.setOrigin(mSprite.getGlobalBounds().width / 2, mSprite.getGlobalBounds().height / 2);
    }

    void SfmlSpriteRessource::setScale(float scale)
    {
        mSprite.scale(scale, scale);
    }

    void SfmlSpriteRessource::changeResolution(int w, int h)
    {

    }

    void SfmlSpriteRessource::setSmooth(bool smooth)
    {
        
    }

    void SfmlSpriteRessource::setColor(int r, int g, int b, int alpha)
    {
        mSprite.setColor(sf::Color{static_cast<sf::Uint8>(r), static_cast<sf::Uint8>(g), static_cast<sf::Uint8>(b), static_cast<sf::Uint8>(alpha)});
    }


    
} // namespace Iliade::Graphics::Sfml

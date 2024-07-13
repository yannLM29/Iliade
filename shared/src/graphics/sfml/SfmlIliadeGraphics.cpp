#include "graphics/sfml/SfmlIliadeGraphics.hpp"

#include <stdexcept>
#include <exception>
#include <algorithm>
#include <string>

#include "graphics/sfml/SfmlSpriteRessource.hpp"
#include "core/IliadeEngine.hpp"
#include "core/IliadeErrors.hpp"
#include "graphics/SpriteAsset.hpp"
#include "graphics/SpriteLayer.hpp"

int Iliade::Graphics::Sfml::SfmlIliadeGraphics::mIdCounter = 0;

namespace Iliade::Graphics::Sfml
{

    int SfmlIliadeGraphics::loadTexture(std::string path)
    {
        sf::Texture texture;
        if (!texture.loadFromFile(path))
        {
            getEngineRef().errorLog(Iliade::eLoading, "Couldn't load texture");
            throw std::runtime_error("Couldn't load texture");
        }
        
        mTextures.push_back({++mIdCounter, texture, path});

        return mIdCounter;
    }

    sf::Texture &SfmlIliadeGraphics::getTexture(std::string path)
    {
        auto texture_it = std::find_if(mTextures.begin(), mTextures.end(), [&](auto &t){
            return !path.compare(t.mPath);
        });

        if(texture_it == mTextures.end())
        {
            getEngineRef().errorLog(eNotLoadedRessource, "Couldn't get texture " + path + " it seems it is not loaded");
        }

        return texture_it->mTexture;
    }

    sf::Texture &SfmlIliadeGraphics::getTexture(int id)
    {
        auto texture_it = std::find_if(mTextures.begin(), mTextures.end(), [&](auto &t){
            return t.mId == id;
        });

        if(texture_it == mTextures.end())
        {
            getEngineRef().errorLog(eNotLoadedRessource, "Couldn't get texture, it seems it is not loaded");
        }

        return texture_it->mTexture;
    }


    std::string SfmlIliadeGraphics::getLoadedTextureList()
    {
        std::string texture_list = "";
        for(auto &t : mTextures)
        {
            texture_list += "- " + std::to_string(t.mId) + ": " + t.mPath + "\n";
        }

        return texture_list;
    }

    std::vector<int> SfmlIliadeGraphics::getLoadedTextureIdList()
    {
        std::vector<int> texture_list;
        for(auto &t : mTextures)
        {
            texture_list.emplace_back(t.mId);
        }
        
        return texture_list;
    }

    void SfmlIliadeGraphics::render(SpriteLayer &sprite)
    {
        sprite.setPosition(sprite.getPositionX() * getMeterToPixelCoef(), - sprite.getPositionY() * getMeterToPixelCoef());
        mRenderWindow.draw(static_cast<SfmlSpriteRessource&>(sprite.getSpriteImplem()).getSfSprite());

        auto sfSpriteRef = static_cast<SfmlSpriteRessource&>(sprite.getSpriteImplem()).getSfSprite();

    }

    void SfmlIliadeGraphics::render(const DebugRect &rect)
    {
        sf::RectangleShape shape(sf::Vector2f(rect.w * getMeterToPixelCoef(), rect.h * getMeterToPixelCoef()));
        shape.setOrigin(shape.getLocalBounds().width / 2, shape.getLocalBounds().height / 2);
        shape.setPosition(rect.x* getMeterToPixelCoef(), -rect.y * getMeterToPixelCoef());
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineColor(sf::Color::Red);
        shape.setOutlineThickness(2);
        mRenderWindow.draw(shape);
    }

    void SfmlIliadeGraphics::render(const DebugCircle &circle)
    {

    }

    void SfmlIliadeGraphics::render(const DebugPolygon &poly)
    {

    }


    void SfmlIliadeGraphics::clearWindow()
    {
        clearSpritesToShow();
        mRenderWindow.clear();
    }

    void SfmlIliadeGraphics::renderWindow()
    {
        for(auto &ground : getSpritesToShow())
        {
            for(auto &sprite : ground)
            {
                sprite->display(*this);
            }
        }

        for(const auto fixture : getFixturesToShow())
        {
            fixture->display(*this);

            // sf::RectangleShape shape(sf::Vector2f(rect.w * getMeterToPixelCoef(), rect.h * getMeterToPixelCoef()));
            // shape.setOrigin(shape.getLocalBounds().width / 2, shape.getLocalBounds().height / 2);
            // shape.setPosition(rect.x* getMeterToPixelCoef(), -rect.y * getMeterToPixelCoef());
            // shape.setFillColor(sf::Color::Transparent);
            // shape.setOutlineColor(sf::Color::Red);
            // shape.setOutlineThickness(2);
            // mRenderWindow.draw(shape);
        }
        
        mRenderWindow.display();    
    }

} // namespace 

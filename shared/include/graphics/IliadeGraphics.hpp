/**
 * @file IliadeGraphics.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-05-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <string>
#include <array>
#include <vector>
#include <SFML/Graphics.hpp>
#include "graphics/DebugShapes.hpp"
#include "physics/GameFixture.hpp"

#define ILIADE_GRAPHICS_NUMBER_OF_GROUNDS 3

namespace Iliade
{
    class IliadeEngine;
}



namespace Iliade::Graphics
{
    class SpriteAsset;
    class SpriteLayer;

    /**
     * @brief Graphic Engine Interface
     * 
     */
    class IliadeGraphics
    {
    private:
        Iliade::IliadeEngine &mEngineRef;
        float mMeterToPixelCoef = 15;

        std::array<std::vector<SpriteAsset*>, ILIADE_GRAPHICS_NUMBER_OF_GROUNDS> mSpritesToShow;
        std::vector<const Iliade::Physics::GameFixture*> mFixturesToShow;

    public:
        // virtual ~IliadeGraphics() = default;

        IliadeGraphics(Iliade::IliadeEngine &engine);


        virtual int loadTexture(std::string path) = 0;
        virtual sf::Texture &getTexture(std::string path) = 0;
        virtual sf::Texture &getTexture(int id) = 0;
        virtual std::string getLoadedTextureList() = 0;
        virtual std::vector<int> getLoadedTextureIdList() = 0;

        inline Iliade::IliadeEngine &getEngineRef() noexcept
        {
            return mEngineRef;
        }

        inline std::array<std::vector<SpriteAsset*>, ILIADE_GRAPHICS_NUMBER_OF_GROUNDS> &getSpritesToShow() noexcept
        {
            return mSpritesToShow;
        }

        inline std::vector<const Iliade::Physics::GameFixture*> &getFixturesToShow() noexcept
        {
            return mFixturesToShow;
        }

        inline float getMeterToPixelCoef() const noexcept
        {
            return mMeterToPixelCoef;
        }

        inline void setMeterToPixelCoef(float newCoef) noexcept
        {
            mMeterToPixelCoef = newCoef;
        }

        void show(SpriteAsset *sprite, int groundIndex);
        void show(const Iliade::Physics::GameFixture &fixture);

        void clearSpritesToShow();

        virtual void render(SpriteLayer &sprite) = 0;
        virtual void render(const DebugRect &rect) = 0;
        virtual void render(const DebugCircle &circle) = 0;
        virtual void render(const DebugPolygon &poly) = 0;
        virtual void clearWindow() = 0;
        virtual void renderWindow() = 0;

    };
    
} // namespace Iliade::Graphics

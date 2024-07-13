/**
 * @file SfmlIliadeGraphics.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-05-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#define SFML_GRAPHICS_VERSION_MAJOR 0
#define SFML_GRAPHICS_VERSION_MINOR 0
#define SFML_GRAPHICS_VERSION_PATCH 1

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>

#include "graphics/IliadeGraphics.hpp"
#include "SfmlTextureContainer.hpp"

namespace Iliade
{
    class IliadeEngine;
} // namespace Iliade

namespace Iliade::Graphics
{
    struct SpriteAsset;
} // namespace Iliade::Graphics


namespace Iliade::Graphics::Sfml
{
    
    class SfmlSpriteRessource;
    /**
     * @brief SFML Graphic Engine
     * 
     */
    
    class SfmlIliadeGraphics : public Iliade::Graphics::IliadeGraphics
    {
    private:
        

        std::vector<SfmlTextureContainer> mTextures;
        sf::RenderWindow mRenderWindow;

    public:
        static int mIdCounter;

    public:
        SfmlIliadeGraphics(Iliade::IliadeEngine &engine) : Iliade::Graphics::IliadeGraphics(engine), mRenderWindow(sf::VideoMode(800, 600), "Iliade")
        {

        }
        ~SfmlIliadeGraphics() 
        {
            // mRenderWindow.close();
        }

        int loadTexture(std::string path) override;

        /**
         * @brief TODO
         * @todo Add a traceback of who is using each texture to prevent them to look at unloaded textures
         * @param id 
         * @return sf::Texture& 
         */
        sf::Texture &getTexture(std::string path) override;
        sf::Texture &getTexture(int id) override;
        std::string getLoadedTextureList() override;
        std::vector<int> getLoadedTextureIdList() override;

        

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ GET ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /**
         * @brief Get the Version of SFML Graphic Engine
         * 
         * @return std::string representing the version X.X.X
         */
        inline std::string getVersion() const noexcept
        {
            return std::to_string(getVersionMajor()) + "." + std::to_string(getVersionMinor()) + "." + std::to_string(getVersionPatch()) + " on sfml version: " + std::to_string(SFML_VERSION_MAJOR) + "." + std::to_string(SFML_VERSION_MINOR) + "." + std::to_string(SFML_VERSION_PATCH);
        }

        /**
         * @brief Get the Version of SFML Graphic Engine
         * 
         * @return int representing the major value of version
         */
        inline int getVersionMajor() const noexcept
        {
            return SFML_GRAPHICS_VERSION_MAJOR;
        }

        /**
         * @brief Get the Version of SFML Graphic Engine
         * 
         * @return int representing the minor value of version
         */
        inline int getVersionMinor() const noexcept
        {
            return SFML_GRAPHICS_VERSION_MINOR;
        }

        /**
         * @brief Get the Version of SFML Graphic Engine
         * 
         * @return int representing the patch value of version
         */
        inline int getVersionPatch() const noexcept
        {
            return SFML_GRAPHICS_VERSION_PATCH;
        }

        inline sf::RenderWindow &getWindow() noexcept
        {
            return mRenderWindow;
        }

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SHOW ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        void render(SpriteLayer &sprite) override;
        void render(const DebugRect &rect) override;
        void render(const DebugCircle &circle) override;
        void render(const DebugPolygon &poly) override;

        void clearWindow() override;

        void renderWindow() override;
    };
    
    
} // namespace Iliade::Graphics

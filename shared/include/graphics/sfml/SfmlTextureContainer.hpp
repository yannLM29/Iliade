/**
 * @file SfmlTextureContainer.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-05-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <string>
#include <SFML/Graphics.hpp>

namespace Iliade::Graphics::Sfml
{
    struct SfmlTextureContainer
    {
        int mId;
        sf::Texture mTexture;  
        std::string mPath;  
    };
}


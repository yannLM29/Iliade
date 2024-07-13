/**
 * @file SfmlLocalInputManager.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-05-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <SFML/Graphics.hpp>
#include "inputs/ILocalInputManager.hpp"
#include "utils/BitManips.hpp"

namespace Iliade::Inputs::Sfml
{
    class SfmlLocalInputManager : public ILocalInputManager
    {
    private:
        sf::RenderWindow &mWindowRef;
        std::vector<InputEvent> mEvents;
        std::vector<uint32_t> mData;
        bool mWindowOpenedState = true;
        bool mIsFocused = true;

    public:
        SfmlLocalInputManager(sf::RenderWindow &window) : mWindowRef(window)
        {

        }
        
        inline bool getWindowOpenedState() override
        {
            return mWindowOpenedState;
        }

        inline const std::vector<InputEvent> &getInputEvents() override
        {
            return mEvents;
        }

        inline bool isFocused() const noexcept
        {
            return mIsFocused;
        }

        inline const std::vector<uint32_t> &getInputData() override
        {
            
            return mData;
        }


        /**
         * TODO: Has to be changed by a reinterpreting system
        */
        inline std::vector<uint8_t> getRawInputData() override 
        {
            std::vector<uint8_t> r;
            for(auto &input : mData) {
                addValueToByteVector(input, r);
            }

            return std::move(r);
        }

        void schedule()
        {
            
            sf::Event event;

            while (mWindowRef.pollEvent(event))
            {
                switch (event.type)
                {
                    // window closed
                    case sf::Event::Closed:
                        
                        mWindowOpenedState = false;
                        break;
                    
                    case sf::Event::LostFocus:
                        mIsFocused = false;
                        break;

                    case sf::Event::GainedFocus:
                        mIsFocused = true;
                        break;
                }
            }

            if(!isFocused())
            {
                return;
            }

            mData.clear();
            mEvents.clear();

            // Keyboard   
            for(int i = 0; i < sf::Keyboard::KeyCount; i++)
            {
                sf::Keyboard::Key key = static_cast<sf::Keyboard::Key>(i);
                if(sf::Keyboard::isKeyPressed(key))
                {
                    mData.emplace_back((i + 40) << 16);
                }
            }

            // Mouse

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                mData.emplace_back(kMouseLeft << 16);
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                mData.emplace_back(kMouseRight << 16);
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Middle))
            {
                mData.emplace_back(kMouseMiddle << 16);
            }

            sf::Vector2i globalPosition = sf::Mouse::getPosition();
            mData.emplace_back((kGlobalMousePosX << 16) | static_cast<uint16_t>(globalPosition.x));
            mData.emplace_back((kGlobalMousePosY << 16) | static_cast<uint16_t>(globalPosition.y));

            sf::Vector2i localPosition = sf::Mouse::getPosition(mWindowRef);
            mData.emplace_back((kMousePosX << 16) | static_cast<uint16_t>(localPosition.x));
            mData.emplace_back((kMousePosY << 16) | static_cast<uint16_t>(localPosition.y));

            

        }
    };
    
    
} // namespace Iliade::Inputs:/Sfml

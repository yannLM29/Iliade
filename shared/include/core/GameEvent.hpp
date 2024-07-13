/**
 * @file GameEvent.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-04-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

/**
 * @brief 
 * 
 */
class GameEvent
{
    enum eEventType {

    };

private:
    eEventType mEventType;
    std::vector<uint8_t> mOptionalData;
public:
    GameEvent(/* args */);
    ~GameEvent();
};


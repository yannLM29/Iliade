/**
 * @file ExternalTypeComponent.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-04-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include "GameComponent.hpp"
#include <type_traits>
#include <iostream>

namespace Iliade
{
    class IliadeEngine;
    class GameScene;

    /**
     * @brief DO NOT USE THIS COMPONENT WITH DYNAMIC ALOCATION
     */
    template<typename T>
    class ExternalTypeComponent : public GameComponent
    {
    private:
        T mValue;
    public:

        ExternalTypeComponent(T value, GameComponent *parentComponent, 
                                                 bool isPrivate = false) : GameComponent(parentComponent,isPrivate), mValue(value)
        {
            static_assert(!std::is_pointer<T>::value);
            if(parentComponent == nullptr)
            {
                throw std::logic_error("ExternalType can't be orphan | external_component_id=" + std::to_string(getId()));
            }
        }

        ~ExternalTypeComponent()
        {
        }
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ GET ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        inline T getValue() const noexcept
        {
            return mValue;
        }

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SET ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        inline void setValue(T value) 
        {
            mValue = value;
        }


        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ATTACHEMENT ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        void attachChildComponent(GameComponent *component)
        {
            throw std::logic_error("ExternalType can't have children | external_component_id=" + std::to_string(getId()));
        }

        void detachChildComponent(GameComponent *component)
        {
            throw std::logic_error("ExternalType can't have children | external_component_id=" + std::to_string(getId()));
        }

        void detachAllChildren()
        {
            throw std::logic_error("ExternalType can't have children | external_component_id=" + std::to_string(getId()));
        }

        void detachFromParent()
        {
            throw std::logic_error("ExternalType can't be orphan | external_component_id=" + std::to_string(getId()));
        }


        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ DATA SERIALISATION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        std::vector<uint8_t> serialiseData() override
        {
            std::vector<uint8_t> serialised = GameComponent::serialiseData();

            addValueToByteVector(mValue, serialised);

            return std::move(serialised);
        }

        /**
         * @brief 
         * @todo completer pour autre type
         * @warning works only with int32_t
         * @param begin 
         * @param end 
         */
        int parseData(std::vector<uint8_t>::const_iterator begin, std::vector<uint8_t>::const_iterator end) override
        {

            int offset = GameComponent::parseData(begin, end-4);

            mValue = *(end-4) | (*(end-3) << 8) | (*(end-2) << 16) | (*(end-1) << 24);

            return offset + 4;
        }
    };



    

} // namespace Iliade


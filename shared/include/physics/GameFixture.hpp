/**
 * @file IameFixture.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-05-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once
#include <memory>
#include <box2d/box2d.h>

#include "physics/IFixtureShape.hpp"

class Iliade::Graphics::IliadeGraphics;

namespace Iliade::Physics
{
    class GameFixture
    {
    private:
        std::unique_ptr<IFixtureShape> mFixtureShape;
    public:

        GameFixture(std::unique_ptr<IFixtureShape> fixtureShape) : mFixtureShape(std::move(fixtureShape))
        {

        }

        inline b2Fixture *getFixture() const noexcept
        {
            return mFixtureShape->getFixture();
        }

        void show(Iliade::Graphics::IliadeGraphics &graphicEngine);
        void display(Iliade::Graphics::IliadeGraphics &graphicEngine) const;

    };

} // namespace Iliade::Physics



/**
 * @file FixtureBox.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-05-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once
#include <box2d/box2d.h>
#include "physics/IFixtureShape.hpp"

namespace Iliade::Physics
{
    class GameElement;

    class FixtureBox : public IFixtureShape
    {
    private:
        GameElement &mParentRef;

        b2Fixture *mFixture;
        b2FixtureDef mBoxFixtureDef;

        float mOffsetX, mOffsetY;
        float mW, mH;

    public:
        FixtureBox(GameElement &parent, float w, float h, float offsetX = 0.0f, float offsetY = 0.0f, 
                   float angle = 0.0f, float density = 1.0f, float friction = 0.5f, float restitution = 0.5f);
        ~FixtureBox();

        inline b2Fixture *getFixture() const noexcept override
        {
            return mFixture;
        }

        void display(Iliade::Graphics::IliadeGraphics &graphicEngine) const override;
    };
} // namespace Iliade::Physics



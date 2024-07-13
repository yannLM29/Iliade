/**
 * @file IFixtureGraphicalBehavior.hpp
 * @author Yann Le Masson
 * @brief 
 * @version 0.1
 * @date 2024-05-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

namespace Iliade::Graphics
{
    class IliadeGraphics;
} // namespace Iliade::Graphics

namespace Iliade::Physics
{
    class IFixtureShape
    {
    public:
        virtual b2Fixture *getFixture() const noexcept = 0;
        virtual void display(Iliade::Graphics::IliadeGraphics &graphicEngine) const = 0;
    };

} // namespace Iliade::Physics



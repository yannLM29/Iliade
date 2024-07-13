#include "physics/GameFixture.hpp"
#include "graphics/IliadeGraphics.hpp"

namespace Iliade::Physics
{
    void GameFixture::show(Iliade::Graphics::IliadeGraphics &graphicEngine)
    {
        graphicEngine.show(*this);
    }
    void GameFixture::display(Iliade::Graphics::IliadeGraphics &graphicEngine) const
    {
        mFixtureShape->display(graphicEngine);
    }
} // namespace Iliade::Physics

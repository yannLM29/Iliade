#include "graphics/IliadeGraphics.hpp"

#include <stdexcept>

#include "core/IliadeEngine.hpp"
#include "graphics/IliadeGraphics.hpp"
#include "graphics/SpriteAsset.hpp"
#include "graphics/SpriteLayer.hpp"


namespace Iliade::Graphics
{

    IliadeGraphics::IliadeGraphics(Iliade::IliadeEngine &engine) : mEngineRef(engine)
    {

    }


    void IliadeGraphics::show(SpriteAsset *sprite, int groundIndex)
    {
        if(groundIndex >= mSpritesToShow.size())
        {
            mEngineRef.errorLog("Wrong ground index");
            throw std::runtime_error("Wrong ground index");
        }

        mSpritesToShow[groundIndex].emplace_back(sprite);
    }

    void IliadeGraphics::show(const Iliade::Physics::GameFixture &fixture)
    {
        mFixturesToShow.emplace_back(&fixture);
    }

    void IliadeGraphics::clearSpritesToShow()
    {
        for(auto &ground : mSpritesToShow)
        {
            ground.clear();
        }

        mFixturesToShow.clear();
    }
    
} // namespace name

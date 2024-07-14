#include "graphics/SpriteAsset.hpp"
#include "core/IliadeEngine.hpp"

namespace Iliade::Graphics
{
    void SpriteAsset::startAnimation(int animationIndex, float speed, bool isOneShot, bool cutLast)
    {
        getEngineRef().sendEvent(std::make_unique<Iliade::Connect::Events::StartAnimEvent>(getId(), animationIndex, speed, isOneShot, cutLast));
    }

    void SpriteAsset::stopAnimation(bool cutLast)
    {
        getEngineRef().sendEvent(std::make_unique<Iliade::Connect::Events::StopAnimEvent>(getId(), cutLast));
    }
} // namespace Iliade::Graphics


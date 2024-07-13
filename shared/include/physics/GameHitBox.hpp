/**
 * 
*/
#pragma once

#include <box2d/b2_fixture.h>

namespace Iliade::Physics
{
    class GameElement;

    class GameHitBox
    {
    private:
        GameElement &mParentRef;

        b2Fixture *mFixture;
        b2FixtureDef mBoxFixtureDef;

        float mW, mH;

    public:
        GameHitBox(GameElement &parent, float w, float h, float offsetX = 0, float offsetY = 0, float angle = 0);

        
        ~GameHitBox();

        inline float getWidth() const noexcept 
        {
            return mW;
        }

        inline float getHeight() const noexcept 
        {
            return mH;
        }
    };
    
} // namespace Iliade::Physics

/**
 * 
*/

#pragma once

#include <box2d/box2d.h>

namespace Iliade::Physics
{
    class IliadePhysics
    {
    private:
        b2World mWorld;
        
    public:
        IliadePhysics(float gravityX,float gravityY) : mWorld(b2Vec2(gravityX, gravityY))
        {

        }


        ~IliadePhysics()
        {

        }

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ GET ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        b2World &getWorldRef() 
        {
            return mWorld;
        }

        void update(int deltaT)
        {
            mWorld.Step(0.020, 8, 3);
        }
    };

    
} // namespace Iliade::Physics

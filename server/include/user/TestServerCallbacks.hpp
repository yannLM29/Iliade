#pragma once

#include "IServerCallbacks.hpp"
#include "user/mainClient.hpp"

class TestServerCallbacks : public Iliade::Connect::IServerCallbacks
{
public:
    bool connectionControl(/**/) 
    {
        return true;
    }

    Iliade::PlayableElement* onConnectPlayerAssignment()
    {
        static int cpt = 0;

        if(cpt == 0)
        {
            cpt++;
            return main_character;
        }
        cpt++;
        return second_character;
    }

};




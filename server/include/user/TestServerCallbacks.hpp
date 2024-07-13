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
        return main_character;
    }

};




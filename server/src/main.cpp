#include "core/IliadeEngine.hpp"
#include "core/GameScene.hpp"
#include "connect/Events/AnimationEvents.hpp"
#include "connect/Events/ChatEvents.hpp"
#include "ClientPlug.hpp"
#include "Server.hpp"
#include "connect/SimpleTCPConnection.hpp"
#include "connect/Events/ChatEvents.hpp"
// #include "connect/Plug.hpp"

#include "core/GameScene.hpp"
#include "core/GameSceneModel.hpp"
#include "user/test.hpp"
#include "user/platformtest.hpp"
#include "graphics/sfml/SfmlIliadeGraphics.hpp"
#include "utils/BitManips.hpp"
#include "inputs/SfmlLocalInputManager.hpp"

#include <chrono>
#include "user/TestServerCallbacks.hpp"
#include "user/mainClient.hpp"

int main()
{
    Iliade::IliadeEngine engine;
    TestServerCallbacks cb;
    Iliade::Connect::Server server(engine, 39255, 5, cb);
    Iliade::GameScene main_scene(engine);
    Iliade::Graphics::Sfml::SfmlIliadeGraphics graphicEngine(engine);
    engine.setGraphicEngine(graphicEngine);
    engine.setEventManager(std::make_unique<Iliade::Connect::ServerEventManager>(server));
    
    engine.logIliadeStartUpInfo();

    graphicEngine.loadTexture("../rsc/mario.png");
    graphicEngine.loadTexture("../rsc/luigi.png");
    graphicEngine.loadTexture("../rsc/star.png");
    graphicEngine.loadTexture("../rsc/platform1.png");
    engine.log(graphicEngine.getLoadedTextureList());

    Character c1(main_scene,graphicEngine);
    main_character = &c1;

    Character c2(main_scene, graphicEngine, "../rsc/luigi.png", 
    {
        {7, 2, 20, 43},
        {43, 2, 17, 43},
        {78, 2, 18, 43},
        {113, 2, 17, 43},
        {147, 2, 20, 43},
        {184, 2, 17, 43},
        {218, 2, 18, 43},
        {254, 2, 17, 43}
    },
    {
        {7, 252, 19, 43},
        {42, 252, 21, 43},
        {77, 252, 22, 43},
        {112, 252, 22, 43},
        {147, 252, 20, 43},
        {182, 252, 22, 43},
        {217, 252, 23, 43},
        {252, 252, 22, 43}
    },
    {
        {6, 452, 21, 43},
        {41, 452, 21, 43},
        {75, 452, 21, 43},
        {111, 452, 21, 43},
        {146, 452, 20, 43},
        {180, 452, 22, 43},
        {214, 452, 23, 43},
        {250, 452, 22, 43}
    });
    second_character = &c2;

    
    platformtest p1(main_scene, graphicEngine);
    platformtest p2(main_scene, graphicEngine);
    c1.setPosition(2,2);
    c2.setPosition(16,2);
    p1.setPosition(5, -15);
    p2.setPosition(18, -18);
    c1.getSpriteRef().chooseAnimation(1);
    // c1.getSpriteRef().localStartAnimation(1, 20, false);

    Iliade::Inputs::Sfml::SfmlLocalInputManager manager(graphicEngine.getWindow());

    std::cout << main_scene.getComponentListDescription() << "\n";
    
    while (manager.getWindowOpenedState())
    {
        manager.schedule();
        server.update(20);
        main_scene.update(20);
        Iliade::GameSceneModel model = main_scene.copyToModel();


        // std::cout << "number of players= " << server.getClientList().size() << "\n";
        // for(auto &client : server.getClientList())
        // {
        //     auto newEvent = client->popEvent();
        //     if(newEvent != nullptr)
        //     {
        //         if(newEvent->getType() == Iliade::Connect::eEventTypes::kChatMessage)
        //         {
        //             std::unique_ptr<Iliade::Connect::Events::ChatEvent> newChatEvent =  std::unique_ptr<Iliade::Connect::Events::ChatEvent>(static_cast<Iliade::Connect::Events::ChatEvent*>(newEvent.release()));
        //             for(auto &clientToSend : server.getClientList())
        //             {
        //                 clientToSend->sendEvent(*newChatEvent);
        //             }
                    
        //             std::cout << newChatEvent->getMessage() << "\n";
        //         }
        //     }
        // }
        // std::string command;
        // std::cin >> command;

        // if(!command.compare("quit")) break;

        for(auto &client : server.getClientList())
        {
            Iliade::Connect::errors error;
            auto serial = model.serialise();
            std::vector<uint8_t> sz;
            Iliade::addValueToByteVector((uint32_t)serial.size(), sz);
            // int n = client->sendUdp(sz, error);
            int n = client->sendUdp(serial, error);
            
        }

        engine.show(main_scene);
        engine.sleep(15);
    }

    std::cout << "end\n";

    return 0;
}
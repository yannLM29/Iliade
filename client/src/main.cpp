
#include "connect/Events/ChatEvents.hpp"
#include "connect/SimpleTCPConnection.hpp"
#include "ServerPlug.hpp"
#include "utils/BitManips.hpp"
#include "user/test.hpp"
#include "user/platformtest.hpp"
#include "graphics/sfml/SfmlIliadeGraphics.hpp"
#include "inputs/SfmlLocalInputManager.hpp"
#include "ClientEventManager.hpp"

#include <iostream>

int main()
{
    int port, portUdp;
    std::cout << "port TCP: ";
    std::cin >> port;

    std::cout << "\nport UPD: ";
    std::cin >> portUdp;
    Iliade::IliadeEngine engine;
    Iliade::Connect::ServerPlug server(engine, "127.0.0.1", port, portUdp, 65450);


    std::string input = "";

    // connexion.asyncRecv(6, [this](std::vector<uint8_t>& dataIn, errors error) { this->parseEventHeader(dataIn, error); });

    Iliade::GameScene main_scene(engine);
    Iliade::Graphics::Sfml::SfmlIliadeGraphics graphicEngine(engine);
    engine.setGraphicEngine(graphicEngine);
    engine.setEventManager(std::make_unique<Iliade::Connect::ClientEventManager>(&main_scene));
    
    engine.logIliadeStartUpInfo();

    graphicEngine.loadTexture("../rsc/mario.png");
    graphicEngine.loadTexture("../rsc/star.png");
    graphicEngine.loadTexture("../rsc/platform1.png");
    engine.log(graphicEngine.getLoadedTextureList());

    Character c1(main_scene,graphicEngine);
    platformtest p1(main_scene, graphicEngine);
    platformtest p2(main_scene, graphicEngine);
    c1.setPosition(2,0);
    p1.setPosition(5, -15);
    p2.setPosition(18, -18);
    c1.getSpriteRef().chooseAnimation(1);
    
    Iliade::Inputs::Sfml::SfmlLocalInputManager manager(graphicEngine.getWindow());

    std::cout << main_scene.getComponentListDescription() << "\n";

    while (manager.getWindowOpenedState())
    {
        manager.schedule();

        while(auto new_event = server.popEvent())
        {
            engine.treatEvent(std::move(new_event));
        }

        Iliade::Connect::errors error;
            
        std::vector<uint8_t> dataModel = server.recvUdp(2500, error);
        if(error)
        {
            engine.errorLog(error, "connect error during recv data");
        }

        auto input_data = manager.getRawInputData();
        server.sendUdp(input_data, error);
        if(error)
        {
            engine.errorLog(error, "connect error during send inputs");
        }
        
        main_scene.updateFromData(dataModel);
        main_scene.update(15);
        engine.show(main_scene);

        std::this_thread::sleep_for(std::chrono::milliseconds(15));
    }
    
}
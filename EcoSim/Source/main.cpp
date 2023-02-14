#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Graphics/Renderwindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/View.hpp>

#include <memory>

#include "Ports/UILayerPort.h"


int main() 
{
    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>( sf::VideoMode(1200, 800), "Ecosystem Simulation" );

    window->setFramerateLimit(60);
    ImGui::SFML::Init(*window);

    LayerPort::UILayerPort port{ window };
    LayerPort::InstallPorts(port);
    port.Setup();

    sf::View view{ sf::FloatRect{0.f,0.f,1200, 800} };
    window->setView(view);

    bool cursorIsInBorders{ false };
    sf::Vector2f viewPortMoveVect{};

    sf::Clock deltaClock;
    while (window->isOpen()) 
    {
        sf::Event event;
        while (window->pollEvent(event)) 
        {
            ImGui::SFML::ProcessEvent(*window, event);

            if (event.type == sf::Event::Closed) 
            {
                window->close();
            }

            if (event.type == sf::Event::MouseMoved)
            {
                float currX = event.mouseMove.x;
                float currY = event.mouseMove.y;
                bool inXBorder{ true };
                bool inYBorder { true };

                if (currX > 0.f && currX < 10.f)
                    viewPortMoveVect = sf::Vector2f{ -5.f, 0.f };
                else if (currX < 1200.f && currX > 1190.f)
                    viewPortMoveVect = sf::Vector2f{ 5.f, 0.f };
                else
                    inXBorder = false;

                if (currY > 0.f && currY < 10.f)
                    viewPortMoveVect = sf::Vector2f{ 0.f, -5.f };
                else if (currY < 800.f && currY > 790.f)
                    viewPortMoveVect = sf::Vector2f{ 0.f, 5.f };
                else
                    inYBorder = false;

                if (!inXBorder && !inYBorder)
                    cursorIsInBorders = false;
                else
                    cursorIsInBorders = true;
            }
        }

        if (cursorIsInBorders)
        {
            sf::View newView{ window->getView() };
            newView.move(viewPortMoveVect);
            window->setView(newView);
        }

        ImGui::SFML::Update(*window, deltaClock.restart());
        
        window->clear();

        /*ImGui::Begin("Hello, world!");
        ImGui::Button("Look at this pretty button");
        ImGui::End();*/

        port.UpdateDraw();

        ImGui::SFML::Render(*window);
        window->display();
    }

    ImGui::SFML::Shutdown();
}
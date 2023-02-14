#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Graphics/Renderwindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/View.hpp>

#include <memory>

#include "Ports/UILayerPort.h"

#define WINDOW_WIDTH 1200.f
#define WINDOW_HEIGHT 800.f

int main() 
{
    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>( sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ecosystem Simulation" );

    window->setFramerateLimit(60);
    ImGui::SFML::Init(*window);

    LayerPort::UILayerPort port{ window };
    LayerPort::InstallPorts(port);
    port.Setup();

    sf::View view{ sf::FloatRect{0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT} };
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
                else if (currX < WINDOW_WIDTH && currX > WINDOW_WIDTH - 10)
                    viewPortMoveVect = sf::Vector2f{ 5.f, 0.f };
                else
                    inXBorder = false;

                if (currY > 0.f && currY < 10.f)
                    viewPortMoveVect = sf::Vector2f{ 0.f, -5.f };
                else if (currY < WINDOW_HEIGHT && currY > WINDOW_HEIGHT - 10)
                    viewPortMoveVect = sf::Vector2f{ 0.f, 5.f };
                else
                    inYBorder = false;

                cursorIsInBorders = !(!inXBorder && !inYBorder);
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
        
        port.UpdateDraw();

        ImGui::SFML::Render(*window);
        window->display();
    }

    ImGui::SFML::Shutdown();
}
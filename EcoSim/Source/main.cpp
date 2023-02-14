#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "Ports/ImGuiLayerPort.h"


int main() 
{
    sf::RenderWindow window{ sf::VideoMode(1200, 800), "Ecosystem Simulation" };
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    LayerPort::ImGuiLayerPort port{ &window };
    LayerPort::InstallPorts(port);
    port.Setup();

    sf::Clock deltaClock;
    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) 
            {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());
        
        window.clear();

        /*ImGui::Begin("Hello, world!");
        ImGui::Button("Look at this pretty button");
        ImGui::End();*/

        port.UpdateDraw();

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}
#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Ports/ImGuiLayerPort.h"


int main() 
{

    LayerPort::ImGuiLayerPort port{ };
    LayerPort::InstallPorts(port);
    port.Setup();


    sf::RenderWindow window(sf::VideoMode(1200, 800), "Ecosystem Simulation");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);


    sf::Texture texture;
    sf::Sprite sprite;
    if (!texture.loadFromFile("Source/rick.jpg"))
    {
    }
    sprite.setTexture(texture);
    sprite.setScale(sf::Vector2f{ 0.2f,0.2f });
    sprite.setPosition(sf::Vector2f{ 300.f, 300.f });

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
        
        
        port.UpdateDraw();

        ImGui::Begin("Hello, world!");
        ImGui::Button("Look at this pretty button");
        ImGui::End();

        window.clear();
        
        window.draw(sprite);
        //window.draw(shape);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}
#include "DefaultPort.h"

void LayerPort::DefaultPort::Setup(std::shared_ptr<sf::RenderWindow> window)
{
    this->window = window;
}

void LayerPort::DefaultPort::Shutdown()
{
}

void LayerPort::DefaultPort::UpdateDraw()
{
    if (showDemoWindow)
        ImGui::ShowDemoWindow(&showDemoWindow);

    {
        ImGui::SetNextWindowSize(ImVec2(350, 400));
        ImGui::SetNextWindowPos(ImVec2(50, 50));
        //ImGuiWindowFlags mainFlags = ImGuiWindowFlags_NoCollapse;
        ImGui::Begin("Ecosystem", 0);

        ImGui::Checkbox("Demo Window", &showDemoWindow);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        ImGui::End();
    }
}

void LayerPort::DefaultPort::OnPrompt(const Prompt& prompt)
{
}

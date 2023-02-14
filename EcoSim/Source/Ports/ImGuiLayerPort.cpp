#include "ImGuiLayerPort.h"

using namespace LayerPort;

ImGuiLayerPort::ImGuiLayerPort(std::shared_ptr<sf::RenderWindow> window)
{
	callback = std::bind(
			&ImGuiLayerPort::RelayPromptToPorts, this, std::placeholders::_1);

	interPortComHandler = new InterPortComHandler{ callback };

	this->window = window;
}

void ImGuiLayerPort::Setup()
{
	for (const auto& p : ports)
		p->Setup(window);
}

void ImGuiLayerPort::Shutdown()
{
	for (const auto& p : ports)
		p->Shutdown();
}

void LayerPort::ImGuiLayerPort::UpdateDraw()
{
	for (const auto& p : ports)
		p->UpdateDraw();
}

void ImGuiLayerPort::AddPort(BasePort* port)
{
	ports.push_back(port);
}

void LayerPort::ImGuiLayerPort::RelayPromptToPorts(const Prompt& prompt)
{
	for (const auto& p : ports)
		p->OnPrompt(prompt);
}

InterPortComHandler* ImGuiLayerPort::GetInterPortComHandler()
{ 
	return interPortComHandler; 
}

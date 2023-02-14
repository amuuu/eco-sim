#include "UILayerPort.h"

using namespace LayerPort;

UILayerPort::UILayerPort(std::shared_ptr<sf::RenderWindow> window)
{
	callback = std::bind(
			&UILayerPort::RelayPromptToPorts, this, std::placeholders::_1);

	interPortComHandler = new InterPortComHandler{ callback };

	this->window = window;
}

void UILayerPort::Setup()
{
	for (const auto& p : ports)
		p->Setup(window);
}

void UILayerPort::Shutdown()
{
	for (const auto& p : ports)
		p->Shutdown();
}

void LayerPort::UILayerPort::UpdateDraw()
{
	for (const auto& p : ports)
		p->UpdateDraw();
}

void UILayerPort::AddPort(BasePort* port)
{
	ports.push_back(port);
}

void LayerPort::UILayerPort::RelayPromptToPorts(const Prompt& prompt)
{
	for (const auto& p : ports)
		p->OnPrompt(prompt);
}

InterPortComHandler* UILayerPort::GetInterPortComHandler()
{ 
	return interPortComHandler; 
}

#include "ImGuiLayerPort.h"

using namespace LayerPort;

void ImGuiLayerPort::Setup()
{
	for (const auto& p : ports)
		p->Setup();
}

void ImGuiLayerPort::Shutdown()
{
	for (const auto& p : ports)
		p->Shutdown();
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

#pragma once

#include "BasePort.h"
#include "EntityManagerPort.h"

#include <vector>

namespace LayerPort
{
	class ImGuiLayerPort
	{
	public:
		
		void Setup();

		void Shutdown();

		void AddPort(BasePort* port);

		void RelayPromptToPorts(const Prompt& prompt);

	private:

		std::vector<BasePort*> ports{};
	};


	static void InstallPorts(ImGuiLayerPort& imguiLayerPort)
	{
		imguiLayerPort.AddPort(new EntityManagerPort{});
	}
}
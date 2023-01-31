#pragma once

#include "BasePort.h"
#include "EntityManagerPort.h"

#include <vector>
#include <queue>
#include <functional>

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
		/*static bool setupDone = false;
		if (setupDone) return;

		std::function<void(const Prompt&)> callback = 
			std::bind(
				&ImGuiLayerPort::AppendPortPromptForImGui, 
				&imguiLayerPort, 
				std::placeholders::_1);*/

		
		imguiLayerPort.AddPort(new EntityManagerPort{ /*callback*/ });



		/*setupDone = true;*/
	}
}
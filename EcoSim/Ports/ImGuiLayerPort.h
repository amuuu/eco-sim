#pragma once

#include "../../GameSystems/GeneralTools/Blackboard.h"
using namespace GeneralBlackBoard;

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
		
		ImGuiLayerPort(BlackBoard* blackboard) : blackboard(blackboard) {}

		void Setup();

		void Shutdown();

		void AddPort(BasePort* port);

		void RelayPromptToPorts(const Prompt& prompt);

		BlackBoard* GetBlackBoard() { return blackboard; }

	private:

		std::vector<BasePort*> ports{};
		BlackBoard* blackboard{};
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

		
		imguiLayerPort.AddPort(new EntityManagerPort{ imguiLayerPort.GetBlackBoard() });



		/*setupDone = true;*/
	}
}
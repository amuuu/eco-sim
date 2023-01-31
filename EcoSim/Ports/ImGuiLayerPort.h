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
		
		ImGuiLayerPort();

		void Setup();

		void Shutdown();

		void UpdateDraw();

		void AddPort(BasePort* port);

		void RelayPromptToPorts(const Prompt& prompt);

		InterPortComHandler* GetInterPortComHandler();

	private:

		std::vector<BasePort*> ports{};
		InterPortComHandler* interPortComHandler;
	};


	static void InstallPorts(ImGuiLayerPort& imguiLayerPort)
	{
		imguiLayerPort.AddPort(new EntityManagerPort{ imguiLayerPort.GetInterPortComHandler() });
	}
}
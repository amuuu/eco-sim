#pragma once

#include "BasePort.h"

#include "BoilerplatePort.h"
#include "EntityManagerPort.h"
#include "ActionsListPort.h"

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

		std::function<void(const Prompt&)> callback;
	};


	static void InstallPorts(ImGuiLayerPort& imguiLayerPort)
	{
		imguiLayerPort.AddPort(new BoilerplatePort{ imguiLayerPort.GetInterPortComHandler() });

		imguiLayerPort.AddPort(new EntityManagerPort{ imguiLayerPort.GetInterPortComHandler() });
		imguiLayerPort.AddPort(new ActionsListPort{ imguiLayerPort.GetInterPortComHandler() });
	}
}
#pragma once

#include "BasePort.h"

#include "DefaultPort.h"

#include "BoilerplatePort.h"
#include "EntityManagerPort.h"
#include "ActionsListPort.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>
#include <queue>
#include <functional>

namespace LayerPort
{
	class ImGuiLayerPort
	{
	public:
		
		ImGuiLayerPort(sf::RenderWindow* window);

		void Setup();

		void Shutdown();

		void UpdateDraw();

		void AddPort(BasePort* port);

		void RelayPromptToPorts(const Prompt& prompt);

		InterPortComHandler* GetInterPortComHandler();

	private:
		
		sf::RenderWindow* window{};

		std::vector<BasePort*> ports{};
		InterPortComHandler* interPortComHandler;

		std::function<void(const Prompt&)> callback;
	};


	static void InstallPorts(ImGuiLayerPort& imguiLayerPort)
	{
		imguiLayerPort.AddPort(new DefaultPort{ imguiLayerPort.GetInterPortComHandler() });
		
		imguiLayerPort.AddPort(new BoilerplatePort{ imguiLayerPort.GetInterPortComHandler() });

		imguiLayerPort.AddPort(new EntityManagerPort{ imguiLayerPort.GetInterPortComHandler() });
		imguiLayerPort.AddPort(new ActionsListPort{ imguiLayerPort.GetInterPortComHandler() });
	}
}
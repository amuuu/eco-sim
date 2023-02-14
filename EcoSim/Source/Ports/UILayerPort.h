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
#include <memory>

namespace LayerPort
{
	class UILayerPort
	{
	public:
		
		UILayerPort(std::shared_ptr<sf::RenderWindow> window);

		void Setup();

		void Shutdown();

		void UpdateDraw();

		void AddPort(BasePort* port);

		void RelayPromptToPorts(const Prompt& prompt);

		InterPortComHandler* GetInterPortComHandler();

	private:
		
		std::shared_ptr<sf::RenderWindow> window{};

		std::vector<BasePort*> ports{};
		InterPortComHandler* interPortComHandler;

		std::function<void(const Prompt&)> callback;
	};


	static void InstallPorts(UILayerPort& UILayerPort)
	{
		UILayerPort.AddPort(new DefaultPort{ UILayerPort.GetInterPortComHandler() });
		
		UILayerPort.AddPort(new BoilerplatePort{ UILayerPort.GetInterPortComHandler() });

		UILayerPort.AddPort(new EntityManagerPort{ UILayerPort.GetInterPortComHandler() });
		UILayerPort.AddPort(new ActionsListPort{ UILayerPort.GetInterPortComHandler() });
	}
}
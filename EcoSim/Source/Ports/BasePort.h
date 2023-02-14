#pragma once

#include "InterPortComHandler.h"
#include "Prompt.h"

#include <GeneralTools/ArgListHelper.h>
#include <GeneralTools/Blackboard.h>
using namespace GeneralBlackBoard;

#include <imgui.h>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../ImGuiGlobals.h"

#include <memory>

namespace LayerPort
{

	class BasePort
	{
		friend class UILayerPort;

	protected:

		virtual void Setup(std::shared_ptr<sf::RenderWindow> window) = 0;
		virtual void Shutdown() = 0;
		
		virtual void UpdateDraw() = 0;
		
		virtual void OnPrompt(const Prompt& prompt) = 0;

		InterPortComHandler* interPortComHandler;

		std::shared_ptr<sf::RenderWindow> window{};

	public:
		
		BasePort(InterPortComHandler* interPortComHandler) : interPortComHandler(interPortComHandler) {}
	};
}
#pragma once

#include "InterPortComHandler.h"
#include "Prompt.h"

#include <GeneralTools/ArgListHelper.h>
#include <GeneralTools/Blackboard.h>
using namespace GeneralBlackBoard;

#include <imgui.h>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../ImGuiGlobals.h"


namespace LayerPort
{

	class BasePort
	{
		friend class ImGuiLayerPort;

	protected:

		virtual void Setup(sf::RenderWindow* window) = 0;
		virtual void Shutdown() = 0;
		
		virtual void UpdateDraw() = 0;
		
		virtual void OnPrompt(const Prompt& prompt) = 0;

		InterPortComHandler* interPortComHandler;

		sf::RenderWindow* window{};

	public:
		
		BasePort(InterPortComHandler* interPortComHandler) : interPortComHandler(interPortComHandler) {}
	};
}
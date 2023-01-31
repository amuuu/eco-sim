#pragma once

#include "InterPortComHandler.h"
#include "Prompt.h"

#include "../../GameSystems/GeneralTools/ArgListHelper.h"
#include "../../GameSystems/GeneralTools/Blackboard.h"
using namespace GeneralBlackBoard;

#include "../imgui.h"
#include "../ImGuiGlobals.h"

//#include <functional>

namespace LayerPort
{

	class BasePort
	{
		friend class ImGuiLayerPort;

	protected:

		virtual void Setup() = 0;
		virtual void Shutdown() = 0;
		
		virtual void UpdateDraw() = 0;
		
		virtual void OnPrompt(const Prompt& prompt) = 0;

		InterPortComHandler* interPortComHandler;

	public:
		
		BasePort(InterPortComHandler* interPortComHandler) : interPortComHandler(interPortComHandler) {}
	};
}
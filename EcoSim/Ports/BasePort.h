#pragma once

#include "Prompt.h"
#include "../../GameSystems/GeneralTools/ArgListHelper.h"

namespace LayerPort
{
	
	class BasePort
	{
		friend class ImGuiLayerPort;

	protected:

		virtual void Setup() = 0;
		virtual void Shutdown() = 0;
		
		virtual void OnPrompt(const Prompt& prompt) = 0;
	};
}
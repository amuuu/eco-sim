#pragma once

#include "Prompt.h"
#include "../../GameSystems/GeneralTools/ArgListHelper.h"

//#include <functional>

namespace LayerPort
{
	
	class BasePort
	{
		friend class ImGuiLayerPort;

	protected:

		virtual void Setup() = 0;
		virtual void Shutdown() = 0;
		
		virtual void OnPrompt(const Prompt& prompt) = 0;

		//std::function<void(const Prompt&)> submitPromptCallback;

	public:

		//BasePort(std::function<void(const Prompt&)> submitPromptCallback) 
		//	: submitPromptCallback(submitPromptCallback)
		//{ }
	};
}
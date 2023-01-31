#pragma once

#include "Prompt.h"

#include <functional>
#include "../../GameSystems/GeneralTools/Blackboard.h"

using namespace GeneralBlackBoard;

namespace LayerPort
{
	struct InterPortComHandler
	{
		using CallbackType = std::function<void(const Prompt&)>;


		InterPortComHandler(CallbackType& callback)
		{
			SubmitPromptCallback = callback;
		}

		BlackBoard& GetBlackBoard() { return blackboard; }

		CallbackType SubmitPromptCallback;

	private:

		BlackBoard blackboard{};
	};
}
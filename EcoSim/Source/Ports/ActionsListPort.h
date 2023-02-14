#pragma once

#include "BasePort.h"

#include <DecisionSystem/MindVarModelsParser.h>
using namespace DecisionSystem;

namespace LayerPort
{
	class ActionsListPort : public BasePort
	{
	private:

		virtual void Setup(sf::RenderWindow* window) override; // BasePort
		virtual void Shutdown() override; // BasePort
		virtual void UpdateDraw() override; // BasePort
		virtual void OnPrompt(const Prompt& prompt) override; // BasePort

		void LoadConfigs();

		void RenderMindVar(const MindVarId& id);

		std::map<MindVarId, bool> mindVarModelsDisplayState{};

	public:

		ActionsListPort(InterPortComHandler* interPortComHandler) : BasePort(interPortComHandler) {}

	};
}
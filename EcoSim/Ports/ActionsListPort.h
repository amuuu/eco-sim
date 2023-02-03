#pragma once

#include "BasePort.h"

#include "../../GameSystems/DecisionSystem/MindVarModelsParser.h"
using namespace DecisionSystem;

namespace LayerPort
{
	class ActionsListPort : public BasePort
	{
	private:

		virtual void Setup() override; // BasePort
		virtual void Shutdown() override; // BasePort
		virtual void UpdateDraw() override; // BasePort
		virtual void OnPrompt(const Prompt& prompt) override; // BasePort

		void LoadConfigs();

		void RenderMindVar(const MindVarId& id);

		std::map<MindVarId, bool> mindVarModelsDisplayState{}; // todo: toggle off


	public:

		ActionsListPort(InterPortComHandler* interPortComHandler) : BasePort(interPortComHandler) {}

	};
}
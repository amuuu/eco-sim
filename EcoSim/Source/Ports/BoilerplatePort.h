#pragma once

#include "BasePort.h"

namespace LayerPort
{
	class BoilerplatePort : public BasePort
	{
	private:

		virtual void Setup() override; // BasePort
		virtual void Shutdown() override; // BasePort
		virtual void UpdateDraw() override; // BasePort
		virtual void OnPrompt(const Prompt& prompt) override; // BasePort

	public:
		
		BoilerplatePort(InterPortComHandler* interPortComHandler) : BasePort(interPortComHandler) {}

	};
}
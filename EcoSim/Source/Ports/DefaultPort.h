#pragma once

#include "BasePort.h"

namespace LayerPort
{
	class DefaultPort : public BasePort
	{
	private:

		virtual void Setup(std::shared_ptr<sf::RenderWindow> window) override; // BasePort
		virtual void Shutdown() override; // BasePort
		virtual void UpdateDraw() override; // BasePort
		virtual void OnPrompt(const Prompt& prompt) override; // BasePort

	public:

		DefaultPort(InterPortComHandler* interPortComHandler) : BasePort(interPortComHandler) {}

	private:

		bool showDemoWindow{ false };
	};
}
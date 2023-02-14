#pragma once

#include "BasePort.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace LayerPort
{
	class BoilerplatePort : public BasePort
	{
	private:

		virtual void Setup(std::shared_ptr<sf::RenderWindow> window) override; // BasePort
		virtual void Shutdown() override; // BasePort
		virtual void UpdateDraw() override; // BasePort
		virtual void OnPrompt(const Prompt& prompt) override; // BasePort

	public:
		
		BoilerplatePort(InterPortComHandler* interPortComHandler) : BasePort(interPortComHandler) {}

	private:
		sf::Texture texture;
		sf::Sprite sprite;
	};
}
#include "BoilerplatePort.h"

#include <GeneralTools/Logger.h>

void LayerPort::BoilerplatePort::Setup(std::shared_ptr<sf::RenderWindow> window)
{
	this->window = window;

	if (!texture.loadFromFile("Source/rick.jpg"))
	{
	}
	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f{ 0.2f,0.2f });
	sprite.setPosition(sf::Vector2f{ 300.f, 300.f });
}

void LayerPort::BoilerplatePort::Shutdown()
{
}

void LayerPort::BoilerplatePort::UpdateDraw()
{
	window->draw(sprite);

	ImGui::SetNextWindowPos(ImVec2(800, 20));
	ImGui::Begin("Boilerplate window ~~", 0);

	if (ImGui::Button("Send prompt to myself"))
	{
		LayerPort::Payload* payload = new LayerPort::Payload{};
		ArgListHelper::PackArgs<int, std::string, float>(payload, 1, "hello", 12.f);
		interPortComHandler->SubmitPromptCallback(Prompt{ "TEST_PROMPT", payload });
	}

	ImGui::End();
}

void LayerPort::BoilerplatePort::OnPrompt(const Prompt& prompt)
{
	Payload* payload = prompt.payload;

	if (prompt.name == "TEST_PROMPT")
	{
		const auto a = ArgListHelper::ExtractFromArgs<int>(payload);
		const auto b = ArgListHelper::ExtractFromArgs<std::string>(payload->next);
		const auto c = ArgListHelper::ExtractFromArgs<float>(payload->next->next);

		LOG_INFO(a << " ~ " << b << " ~ " << c);
	}
}

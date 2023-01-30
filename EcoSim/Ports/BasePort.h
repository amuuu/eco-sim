#pragma once

#include <string>

namespace LayerPort
{

	struct BasePayload
	{
		//virtual ~BasePayload() = 0;
	};

	struct EmptyPayload : public BasePayload
	{
	};

	struct Prompt
	{
		std::string name;
		BasePayload* payload;

		Prompt(std::string name, BasePayload* payload)
			: name(name), payload(payload)
		{
		}

		Prompt(std::string name) : name(name)
		{
			payload = new EmptyPayload{};
		}

		~Prompt()
		{
			delete payload;
		}
	};

	class BasePort
	{
		friend class ImGuiLayerPort;

	protected:

		virtual void Setup() = 0;
		virtual void Shutdown() = 0;
		
		virtual void OnPrompt(const Prompt& prompt) = 0;
	};
}
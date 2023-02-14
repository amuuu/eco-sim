#pragma once

#include <string>
#include <GeneralTools/ArgListHelper.h>


namespace LayerPort
{
	
	using Payload = ArgListHelper::Args;

	struct Prompt
	{
		std::string name{};
		Payload* payload{ nullptr };

		Prompt(const std::string& name, Payload* payload) : name(name), payload(payload)
		{ 
		}

		Prompt(std::string name) : name(name)
		{
			payload = nullptr;
		}

		~Prompt()
		{
			delete payload;
		}
	};

	struct ErrorPrompt : public Prompt
	{
		ErrorPrompt() : Prompt("ERROR")
		{ }
	};
}
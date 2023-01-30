#pragma once

#include <string>

namespace LayerPort
{

	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// 
	// todo: either implement a payload builder or use templates for payloads.
	// 
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	struct BasePayload
	{
		virtual ~BasePayload() {};
	};

	struct EmptyPayload : public BasePayload
	{
		~EmptyPayload() { }
	};

	struct IntArrPayload : public BasePayload
	{
		int* values;

		IntArrPayload(int* values) : values(values) { }

		~IntArrPayload() 
		{ 
			delete[] values; 
		}
	};

	struct Prompt
	{
		std::string name;
		BasePayload* payload;

		Prompt(const std::string& name, BasePayload* payload) : name(name), payload(payload)
		{ }

		Prompt(std::string name) : name(name)
		{
			payload = new EmptyPayload{};
		}

		~Prompt()
		{
			delete payload;
		}
	};

}
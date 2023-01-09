#pragma once
#include <string>
#include <atomic>

namespace ResourceManagement
{

	class Resource
	{
	public:
		const std::string Name;

		Resource(std::string name, const int amount) : Name(std::move(name)), amount(amount) { }

		void SetAmount(const int& newAmount) { amount = newAmount; }
		void ChangeAmount(const int& diff) { amount += diff; }
		int GetAmount() { return amount; }

	private:
		
		std::atomic_int amount;
	};
}
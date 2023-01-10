#pragma once
#include <string>
#include <atomic>

namespace ResourceManagement
{

	class Resource
	{
	public:
		const std::string Name;

		Resource(std::string name, const int amount, const int maxAmount, const int minAmount) : Name(std::move(name)), amount(amount), maxAmount(maxAmount), minAmount(minAmount) { }

		void SetAmount(const int& newAmount) { if (newAmount <= maxAmount && newAmount >= minAmount) amount = newAmount; }
		void ChangeAmount(const int& diff) { if (amount + diff <= maxAmount && amount + diff >= minAmount) amount += diff; }
		int GetAmount() { return amount; }

	private:
		
		std::atomic_int amount;
		const int maxAmount;
		const int minAmount;
	};
}
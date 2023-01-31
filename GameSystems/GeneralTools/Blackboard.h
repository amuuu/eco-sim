#pragma once

#include <map>
#include <vector>

namespace GeneralBlackBoard
{
	class Item
	{
	public:
		virtual ~Item() {};

		Item(Item& i) = delete;
		Item(Item&& i) = delete;
		Item() = default;
	};

	class EmptyItem : public Item { };

	struct Items
	{
	private:

		std::map<unsigned int, Item*> items{};

	public:

		Item*& operator[](unsigned int id)
		{
			return items[id];
		}

		template<typename Type>
		Type* Get(unsigned int id)
		{
			return dynamic_cast<Type*>(items[id]);
		}

		void Set(unsigned int id, Item* val)
		{
			delete items[id];
			items[id] = val;

		}

		~Items()
		{
			// not sure
			/*for (auto& item : items)
			{
				delete item.second;
			}*/
		}
	};

	class Subscriber
	{
	public:
		virtual void OnDataUpdated(Items& items) = 0;
	};


	class Publisher
	{
	public:
		virtual void publish() = 0;
	};


	class BlackBoard
	{
	public:

		BlackBoard() { }

		void UpdateData(unsigned int id, Item* value)
		{
			items.Set(id, value);

			for (const auto& sub : subs)
				sub->OnDataUpdated(items);
		}

		void AddSubcriber(Subscriber* sub)
		{
			subs.push_back(sub);
		}

	private:
		Items items{};
		std::vector<Subscriber*> subs{};
	};

}
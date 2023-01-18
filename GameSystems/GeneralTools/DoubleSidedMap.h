#pragma once


#include <map>
#include <utility>
#include <list>

namespace General
{

	template <typename Id, typename Pointer>
	struct DoubleSidedMap
	{
	
	private:
		using ITERATOR = typename std::map<Id, Pointer>::iterator;

		std::map<Id, Pointer> _map{};
		std::map<Pointer&, ITERATOR&> _mapRev{};
		size_t size{ 0 };

	public:

		 void Add(Id& K1, Pointer& K2)
		 {
			 std::pair<ITERATOR, bool> res = _map.insert_or_assign(K1, K2);
			 
			 if (res.second)
			 {
				 _mapRev[K2] = res.first;
				 
				 size++;
			 }
		 }

		 void Add(Id K1, Pointer K2)
		 {
			 Add(K1, K2);
		 }

		 Pointer& Get(const Id& K)
		 {
			 return _map[K];
		 }

		 Id& Get(const Pointer& K)
		 {
			 return const_cast<Id&>((*(_mapRev[K])).first);
		 }

		 void Remove(Id&& k)
		 {
			 _mapRev.erase(_map[k]); // remove ref iterator
			 _map.erase(k); // remove key
			 
			 size--;
		 }

		 void Remove(Pointer&& k)
		 {
			 _map.erase(_mapRev[k]);
			 _mapRev.erase(k);

			 size--;
		 }

		 const size_t& GetSize() const
		 {
			 return size;
		 }
	};
}
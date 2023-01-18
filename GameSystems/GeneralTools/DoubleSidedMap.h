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
		using ITERATOR = std::map<Id, Pointer>::template iterator;
		
		std::map<Id, Pointer> _map{};
		std::map<Pointer&, ITERATOR> _mapRev{};
		size_t size{ 0 };

	public:
		 void Add(const Id& K1, const Pointer& K2)
		 {
			 std::pair<ITERATOR, bool> res = _map.insert_or_assign(K1);
			 
			 if (res.second)
			 {
				 _mapRev[K2] = res.second;
				 
				 size++;
			 }
		 }

		 const Pointer& Get(const Id& K1)
		 {
			 return _map[K1];
		 }

		 const Id& Get(const Pointer& K2)
		 {
			 return *(_map.find(_mapRev[K2]));
		 }

		 void Remove(Id&& k)
		 {
			 m2.erase(m1[k]); // remove ref iterator
			 m1.erase(k); // remove key
			 
			 size--;
		 }

		 void Remove(Pointer&& k)
		 {
			 m1.erase(m2[k]);
			 m2.erase(k);

			 size--;
		 }

		 const size_t& GetSize() const
		 {
			 return size;
		 }
	};
}
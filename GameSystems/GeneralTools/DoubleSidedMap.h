#pragma once

#include <map>
#include <utility>
#include <list>

namespace General
{

	template <typename _K1, typename _K2>
	class DoubleSidedMap
	{
	
	public:

		 void Add(_K1& K1, _K2& K2)

		 {
			 /*std::pair<IT, bool> res = _map.insert_or_assign(K1, K2);
			 
			 if (res.second)
			 {
				 _mapRev[K2] = res.first;
				 
				 size++;
			 }*/

			 _map[K1] = K2;
			 _mapRev[K2] = _map.find(K1);
			 size++;
		 }

		 void Add(_K1 K1, _K2 K2)
		 {
			 Add(K1, K2);
		 }

		 _K2& Get(const _K1& K)
		 {
			 return _map[K];
		 }

		 _K1& Get(const _K2& K)
		 {
			 return const_cast<_K1&>((*(_mapRev[K])).first);
		 }

		 void Remove(_K1&& k)
		 {
			 _mapRev.erase(_map[k]); // remove ref iterator
			 _map.erase(k); // remove key
			 
			 size--;
		 }

		 void Remove(_K2&& k)
		 {
			 _map.erase(_mapRev[k]);
			 _mapRev.erase(k);

			 size--;
		 }

		 const size_t& GetSize() const
		 {
			 return size;
		 }


	private:
		using IT = typename std::map<_K1, _K2>::iterator;

		typename std::map<_K1, _K2> _map{};
		typename std::map<_K2&, IT&> _mapRev{};
		size_t size{ 0 };

	};
}
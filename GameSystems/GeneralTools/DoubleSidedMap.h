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
		std::map<Id, Pointer> M1{};
		std::map<Pointer, Id> M2{};
		size_t size{ 0 };

	public:
		 void Add(const Id& K1, const Pointer& K2)
		 {
			 M1[K1] = K2;
			 M2[K2] = K1;
			 size++;
		 }

		 const Pointer& Get(const Id& K1)
		 {
			 return M1[K1];
		 }

		 const Id& Get(const Pointer& K2)
		 {
			 return M2[K2];
		 }

		 void Remove(Id&& k)
		 {
			 _Remove(M1, M2, k);
			 
			 size--;
		 }

		 void Remove(Pointer&& k)
		 {
			 _Remove(M2, M1, k);
			 size--;
		 }

		 std::map<Id, Pointer> GetAll_First()
		 {
			 return M1;
		 }

		 std::map<Pointer, Id> GetAll_Second()
		 {
			 return M2;
		 }

		 const size_t& GetSize() const
		 {
			 return size;
		 }


	private:

		template<typename X1, typename X2>
		void _Remove(std::map<X1, X2>& m1, std::map<X2, X1>& m2, X1& x1)
		{
			using IT = std::map<X2, X1>::template iterator;

			m1.erase(x1);

			{
				IT targetIt{};

				auto it = m2.begin();
				while (it != m2.end())
				{
					if ((*it).second == x1)
					{
						m2.erase((*it).first);
						break;
					}

					++it;
				}
			}
		}
	};
}
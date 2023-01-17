#include "../GameSystems/GameSystems/ResourceManagement/ResourcePool.h"
using namespace ResourceManagement;

#include <iostream>
#include <thread>
#include <chrono>

namespace RESOURCE_MANAGEMENT_SAMPLE
{
	static void WorkWithResources(time_t delay, ResourcePool& resourcePool, ResourceId coinId, ResourceId woodId)
	{
		while (true)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(delay));
			std::cout << "\nthread: " << std::this_thread::get_id() << "\n";

			resourcePool.GetResourceBasedOnID(coinId)->ChangeAmount(50);
			resourcePool.GetResourceBasedOnID(woodId)->ChangeAmount(50);
			resourcePool.PrintAllResources();
		}
	}

	static void EXECUTE()
	{
		ResourceManagement::ResourcePool p;

		ResourceId coinId = p.AddNewResource(new Resource{ "Coin", 200, 10000, 0 });
		ResourceId woodId = p.AddNewResource(new Resource{ "Wood", 1000, 10000, 0 });

		p.PrintAllResources();

		std::thread worker1{ WorkWithResources, 500, std::ref(p), coinId, woodId };
		std::thread worker2{ WorkWithResources, 200, std::ref(p), coinId, woodId };

		worker1.join();
		worker2.join();
	}
}
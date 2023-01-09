#pragma once

#include "Resource.h"

#include <memory>
#include <iostream> // todo: remove
#include <map>

typedef int ResourceId;

namespace ResourceManagement
{
	class ResourcePool
	{
	public:

		ResourceId AddNewResource(Resource* r)
		{
			resources[nextResourceID] = r;

			return nextResourceID++;
		}

		Resource* GetResourceBasedOnID(const ResourceId& id)
		{
			return resources[id];
		}

		void PrintAllResources()
		{
			for (const auto& r : resources)
			{
				std::cout << r.second->Name << ": " << r.second->GetAmount() << " (" << r.first << ")\n";
			}
		}

	private:

		std::map<const ResourceId, Resource*> resources{};
		
		ResourceId nextResourceID{ 0 };
	};
}
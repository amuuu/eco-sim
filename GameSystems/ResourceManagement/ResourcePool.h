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

		ResourceId AddNewResource(Resource* r);

		Resource* GetResourceBasedOnID(const ResourceId& id);

		void PrintAllResources();

	private:

		std::map<const ResourceId, Resource*> resources{};
		
		ResourceId nextResourceID{ 0 };
	};
}
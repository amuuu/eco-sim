#pragma once

#include "Resource.h"

#include <memory>
#include <map>

namespace ResourceManagement
{
	using ResourceId = int;

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
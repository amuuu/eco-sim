#include "ResourcePool.h"

using namespace ResourceManagement;

ResourceId ResourcePool::AddNewResource(Resource* r)
{
	resources[nextResourceID] = r;

	return nextResourceID++;
}

Resource* ResourcePool::GetResourceBasedOnID(const ResourceId& id)
{
	return resources[id];
}

void ResourcePool::PrintAllResources()
{
	for (const auto& r : resources)
	{
		std::cout << r.second->Name << ": " << r.second->GetAmount() << " (" << r.first << ")\n";
	}
}

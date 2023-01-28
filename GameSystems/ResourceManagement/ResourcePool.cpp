#include "ResourcePool.h"

#include "../GeneralTools/Logger.h"

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
		LOG_INFO(r.second->Name << ": " << r.second->GetAmount() << " (" << r.first << ")");
	}
}

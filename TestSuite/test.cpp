#include "pch.h"

#include <fstream>

#include "../ExternalTools/nlohmann-json.hpp"
using json = nlohmann::json;

#include "../GameSystems/EntityManagement/EntityManager.h"
#include "../GameSystems/EntityManagement/SimpleDumbEntity.h"


TEST(JSONDecoding, OpenningAFile) {
	
	std::ifstream f{ "TestJson.json" };
	
	json data = json::parse(f);
	
	EXPECT_EQ(data["dooode"], 1);

	f.close();
}

TEST(ENTITY, SimpleInstantiation)
{
	using namespace EntityManagement;

	EntityManager entityManager{ false };

	entityManager.EnqueueNewEntity(new SimpleDumbEntity{});

}
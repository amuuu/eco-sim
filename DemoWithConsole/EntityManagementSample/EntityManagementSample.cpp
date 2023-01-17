#pragma once

#include "../GameSystems/GameSystems/EntityManagement/EntityManager.h"
#include "SimpleDumbEntity.h"
using namespace EntityManagement;

#include <chrono> // for sleep
#include <thread> // for sleep

namespace ENTITY_MANAGEMENT_SAMPLE
{
	static void EXECUTE()
	{
		EntityManager entityManager{ false };
			
		entityManager.EnqueueNewEntity(new SimpleDumbEntity{});
		entityManager.EnqueueNewEntity(new SimpleDumbEntity{});
		entityManager.StartTheLoop();
		entityManager.EnqueueNewEntity(new SimpleDumbEntity{});
		entityManager.EnqueueNewEntity(new SimpleDumbEntity{});

		std::cout << "\n\n[main_thread]: Sleeping for 5 secs\n\n";
		std::this_thread::sleep_for(std::chrono::seconds(5));
		
		entityManager.DestroyEntity(2);
		std::cout << "\n\n\n[main_thread]: Destroyed the entity 2\n\n\n";

		std::cout << "\n\n[main_thread]: Sleeping for 2 secs\n\n";
		std::this_thread::sleep_for(std::chrono::seconds(2));

		entityManager.EnqueueNewEntity(new SimpleDumbEntity{});
		entityManager.EnqueueNewEntity(new SimpleDumbEntity{});


		std::cout << "\n\n[main_thread]: Sleeping for 2 secs\n\n";
		std::this_thread::sleep_for(std::chrono::seconds(2));

		entityManager.DestroyEntity(4);
		std::cout << "\n\n\n[main_thread]: Destroyed the entity 4\n\n\n";
	}
}

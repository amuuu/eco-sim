#include "EntityManagement/EntityManager.h"
using namespace EntityManagement;
#include "DecisionSystem/EntityWithStateOfMind.h"
using namespace DecisionSystem;

int main()
{
	EntityManager entityManager{ false };
	entityManager.EnqueueNewEntity(new EntityWithStateOfMind{});
	entityManager.StartTheLoop();
}

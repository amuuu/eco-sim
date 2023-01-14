#include "EntityManagement/EntityManager.h"
using namespace EntityManagement;
#include "DecisionSystem/EntityWithMindVar.h"
using namespace DecisionSystem;

int main()
{
	MindVarModelsParser::GetInstance()->Init();

	EntityManager entityManager{ false };
	entityManager.EnqueueNewEntity(new EntityWithMindVar{});
	entityManager.StartTheLoop();
}

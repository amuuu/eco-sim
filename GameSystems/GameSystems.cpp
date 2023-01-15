#include "EntityManagement/EntityManager.h"
using namespace EntityManagement;
//#include "DecisionSystem/EntityWithMindVar.h"
//using namespace DecisionSystem;
#include "EntityManagement/SimpleDumbEntity.h"

int main()
{
	//MindVarModelsParser::GetInstance()->Init();

	EntityManager entityManager{ false };
	//entityManager.EnqueueNewEntity(new EntityWithMindVar{});
	//entityManager.EnqueueNewEntity(new SimpleDumbEntity{});
	entityManager.EnqueueNewEntity(new SimpleDumbEntity{});
	entityManager.StartTheLoop();
}

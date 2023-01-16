//#include "EntityManagement/EntityManager.h"
//using namespace EntityManagement;
//#include "DecisionSystem/EntityWithMindVar.h"
//using namespace DecisionSystem;
//#include "EntityManagement/SimpleDumbEntity.h"
#include "EventSystem/SimpleEventListenerClass.h"
#include <vector>
using namespace EventSystem;

int main()
{
	//MindVarModelsParser::GetInstance()->Init();

	/*EntityManager entityManager{ false };
	entityManager.EnqueueNewEntity(new SimpleDumbEntity{});
	entityManager.StartTheLoop();*/

	EventBus::GetInstance()->Init();
	SimpleEventListenerClass selc1{ 1, std::vector<EventId>{1,2} };
	SimpleEventListenerClass selc2{ 2, std::vector<EventId>{2,3} };
	SimpleEventListenerClass selc3{ 3, std::vector<EventId>{1,3} };
	selc1.SendEvent(3);
	selc2.SendEvent(1);
	selc3.SendEvent(2);
	
}

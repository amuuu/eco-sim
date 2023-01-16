//#include "GameSystems/EntityManagement/EntityManager.h"
//using namespace EntityManagement;
//#include "GameSystems/DecisionSystem/EntityWithMindVar.h"
//using namespace DecisionSystem;
//#include "GameSystems/EntityManagement/SimpleDumbEntity.h"
#include "GameSystems/EventSystem/SimpleEventListenerClass.h"
using namespace EventSystem;


#include <iostream>
#include <vector>


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
	selc1.SendEvent(3, "mr. white");
	selc2.SendEvent(1, "wassuuuuuup");
	selc3.SendEvent(2, "greetings");

	EventBus::GetInstance()->UnregisterEventListener(&selc1);
	std::cout << "\nUNREGISTERED 1\n\n";
	selc2.SendEvent(1, "yo yo");
	selc3.SendEvent(2, "wassup");
}

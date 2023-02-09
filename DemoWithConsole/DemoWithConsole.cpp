#define EVENT_SYSTEM_SAMPLE_ACTIVE 0
#define ENTITY_MANAGEMENT_SAMPLE_ACTIVE 0
#define RESOURCE_MANAGEMENT_SAMPLE_ACTIVE 0
#define DECISION_SYSTEM_SAMPLE_ACTIVE 0
#define SCHEDULER_SAMPLE_ACTIVE 1

/////////////////////////////////////////////////////////

#if EVENT_SYSTEM_SAMPLE_ACTIVE 1
#include "EventSystemSample/EventSystemSample.cpp"
#endif

#if ENTITY_MANAGEMENT_SAMPLE_ACTIVE 1
#include "EntityManagementSample/EntityManagementSample.cpp"
#endif

#if RESOURCE_MANAGEMENT_SAMPLE_ACTIVE 1
#include "ResourceManagementSample/ResourceManagementSample.cpp"
#endif

#if DECISION_SYSTEM_SAMPLE_ACTIVE 1
#include "DecisionSystemSample/DecisionSystemSample.cpp"
#endif

#if SCHEDULER_SAMPLE_ACTIVE 1
#include "DecisionSystemSample/SchedulerSample.cpp"
#endif

int main()
{

#if EVENT_SYSTEM_SAMPLE_ACTIVE 1
		EVENT_SYSTEM_SAMPLE::EXECUTE();
#endif

#if ENTITY_MANAGEMENT_SAMPLE_ACTIVE 1
		ENTITY_MANAGEMENT_SAMPLE::EXECUTE();
#endif

#if RESOURCE_MANAGEMENT_SAMPLE_ACTIVE 1
		RESOURCE_MANAGEMENT_SAMPLE::EXECUTE();
#endif

#if DECISION_SYSTEM_SAMPLE_ACTIVE 1
		DECISION_SYSTEM_SAMPLE::EXECUTE();
#endif

#if SCHEDULER_SAMPLE_ACTIVE 1
		SCHEDULER_SAMPLE::EXECUTE();
#endif
}

#include "Component.h"

using namespace EntityManagement;

Component::Component(ID id) 
{ 
	this->id = id; 
}

void Component::Init() { }

void Component::Update() { }

void Component::FixedUpdate() { }

void Component::OnDestroy() { }

HiResTimeStamp Component::GetCurrentTimeStamp() 
{ 
	return HIRES_NOW; 
}

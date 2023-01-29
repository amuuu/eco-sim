#include "Component.h"

using namespace EntityManagement;

Component::Component(ID id) 
{ 
	this->id = id; 
}

Component::~Component()
{
	// not sure about this one yet
	// delete owner;
}

void Component::Init() { }

void Component::Update() { }

void Component::FixedUpdate() { }

void Component::OnDestroy() { }

HiResTimeStamp Component::GetCurrentTimeStamp() 
{ 
	return HIRES_NOW; 
}

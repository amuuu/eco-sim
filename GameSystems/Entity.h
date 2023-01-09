#pragma once

typedef long long Tick;

class Entity
{
public:
	virtual void Init() = 0;
	virtual void Update(Tick tick) = 0;

};
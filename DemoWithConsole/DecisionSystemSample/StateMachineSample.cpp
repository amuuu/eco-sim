#pragma once
#include "GameSystems/DecisionSystem/BehaviorStructures/StateMachine.h"
using namespace StateMachineStructure;

#include <iostream>
#include <thread>

namespace STATE_MACHINE_SAMPLE
{

	class State1 : public State
	{

		virtual void OnEnter(GlobalParams& params) override
		{
			globalParams = &params;

			globalParams->SetParam<std::string>("doode", "yoooo!!!");

			std::cout << "ENTER: State 1" << std::endl;
		}

		virtual void OnExit() override
		{
			std::cout << "EXIT: State 1" << std::endl;
		}

		virtual bool CanTransition(State* target) override
		{
			std::cout << "S1; " << globalParams->GetParam<std::string>("doode") << std::endl;

			return true;
		}

	public:

		State1(std::initializer_list<State*> states) : State(states) {}

	};

	class State2 : public State
	{

		virtual void OnEnter(GlobalParams& params) override
		{
			globalParams = &params;

			std::cout << "S2; " << globalParams->GetParam<std::string>("doode") << std::endl;

			std::cout << "ENTER: State 2" << std::endl;
		}

		virtual void OnExit() override
		{
			std::cout << "EXIT: State 2" << std::endl;
		}

		virtual bool CanTransition(State* target) override
		{
			return true;
		}

	public:

		State2(std::initializer_list<State*> states) : State(states) {}

	};

	static void EXECUTE()
	{
		State2* s2 = new State2{};
		State1* s1 = new State1{};
		State1* s3 = new State1{};
		StateMachine sm{};

		sm.LoadStates(s1, { {s1, s2} });
		sm.ChangeState(s2);
	}
}
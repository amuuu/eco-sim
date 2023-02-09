#include <iostream>

#include <map>
#include <string>
#include <vector>
#include <variant>
#include <type_traits>
#include <utility>
#include <cassert>

namespace StateMachineStructure
{
	static const float ERROR_FLOAT = -1.43499f;
	static const std::string ERROR_STR = "_ERROR_";


	class GlobalParams
	{
	public:

		// std::variant<bool, const T> makes the api too complicated for the user i believe
		template<typename T>
		const T& GetParam(const std::string& key)
		{
			if constexpr (std::is_same_v<T, float>)
			{
				if (numericParams.find(key) != numericParams.end())
					return numericParams[key];
				else
					return ERROR_FLOAT;
			}
			else if constexpr (std::is_same_v<T, std::string>)
			{
				if (stringParams.find(key) != stringParams.end())
					return stringParams[key];
				else
					return ERROR_STR;
			}

		}

		template<typename T>
		void SetParam(const std::string& key, const T& value)
		{
			if constexpr (std::is_same_v<T, float>)
			{
				numericParams[key] = value;
			}
			else if constexpr (std::is_same_v<T, std::string>)
			{
				stringParams[key] = value;
			}
		}

	private:

		std::map<std::string, std::string> stringParams{};
		std::map<std::string, float> numericParams{};
	};

	struct State
	{
		friend class StateMachine;

	private:

		virtual void OnEnter(GlobalParams& params) = 0;
		virtual void OnExit() = 0;
		virtual bool CanTransition(State* target) = 0;

	public:

		bool IsStateConnectedToThisState(State* target)
		{
			for (const auto& state : toStates)
				if (target == state)
					return true;
			return false;
		}

		void ConnectTo(State* state)
		{
			toStates.push_back(state);
		}

		State() = default;

		State(std::initializer_list<State*> states)
		{
			for (auto& s : states)
				toStates.push_back(s);
		}

	protected:

		GlobalParams* globalParams{};

	private:

		std::vector<State*> toStates{};

	};

	class StateMachine
	{
	public:

		StateMachine() = default;

		StateMachine(State* entryState, std::initializer_list<std::pair<State*, State*>> pairs)
		{
			LoadStates(entryState, pairs);
		}

		void ChangeState(State* newState)
		{
			if (!(*currentState)->IsStateConnectedToThisState(newState))
				return;

			if (!(*currentState)->CanTransition(newState))
				return;

			(*currentState)->OnExit();

			currentState = &newState;

			(*currentState)->OnEnter(params);
		}

		void LoadStates(State* entryState, std::initializer_list<std::pair<State*, State*>> pairs)
		{
			bool validEntryState{ false };
			for (const auto& pair : pairs)
			{
				pair.first->ConnectTo(pair.second);

				if (!validEntryState && pair.first == entryState)
					validEntryState = true;
			}

			//assert(validEntryState);
			if (validEntryState)
				LoadEntryState(entryState);
			else
				std::cout << "Entry state isn't included in the initializer list." << std::endl;
		}

	private:

		void LoadEntryState(State* entryState)
		{
			currentState = new State*;
			*currentState = entryState;

			(*currentState)->OnEnter(params);
		}

		GlobalParams params{};
		State** currentState{ nullptr };
	};

	/*
	// EXAMPLE:
	{
		State2* s2 = new State2{}; // child of State
		State1* s1 = new State1{}; // child of State
		State1* s3 = new State1{}; // child of State
		StateMachine sm{};

		sm.LoadStates(s1, { {s1, s2} });
		sm.ChangeState(s2);
	}
	*/
}
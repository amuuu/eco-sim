#pragma once

#include <memory>

#define GENERATE_SINGLETON_GETTER(TargetClassType) \
	static std::shared_ptr<TargetClassType> GetInstance() { \
		static std::shared_ptr<TargetClassType> s{ new TargetClassType }; \
		return s; \
	}

#define GET_SINGLETON(TargetClassType) \
	TargetClassType::GetInstance()
/*
namespace GeneralTools
{
	template<typename SingletonTargetClassType>
	static std::shared_ptr<SingletonTargetClassType> GetInstance()
	{
		static std::shared_ptr<SingletonTargetClassType> s{ new SingletonTargetClassType };
		return s;
	}
}

#define GENERATE_SINGLETON_GETTER(GetInstance, TargetClass)  \
	template<typename T> \
	static std::shared_ptr<T> GetInstance(); \
	template<> \
	static std::shared_ptr<TargetClass> GetInstance();
*/
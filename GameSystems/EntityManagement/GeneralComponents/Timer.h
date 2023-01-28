#pragma once

#include "../Component.h"
#include "../../GeneralTools/Timer.h"

namespace EntityManagement
{
	class Timer : public Component
	{
		virtual void Init() override;

		virtual void Update() override;

		virtual void FixedUpdate() override;

		virtual void OnDestroy() override;

		void Start(int countDownMillis);
		
		void Start();

		void Stop();

		void Restart();

	private:

		General::SimpleTimer timerObject{ false };
	};
}